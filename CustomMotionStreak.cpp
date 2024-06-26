/****************************************************************************
 Copyright (c) 2011      ForzeField Studios S.L.
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN false EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CustomMotionStreak.h"
#include "math/CCVertex.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"

NS_CC_BEGIN

CustomMotionStreak::CustomMotionStreak()
: _fastMode(false)
, _startingPositionInitialized(false)
, _texture(nullptr)
, _blendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _positionR(Vec2::ZERO)
, _stroke(0.0f)
, _fadeDelta(0.0f)
, _minSeg(0.0f)
, _maxPoints(0)
, _nuPoints(0)
, _previousNuPoints(0)
, _pointVertexes(nullptr)
, _pointState(nullptr)
, _vertices(nullptr)
, _colorPointer(nullptr)
, _texCoords(nullptr)
{
}

CustomMotionStreak::~CustomMotionStreak()
{
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_FREE(_pointState);
    CC_SAFE_FREE(_pointVertexes);
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_colorPointer);
    CC_SAFE_FREE(_texCoords);
}

CustomMotionStreak* CustomMotionStreak::create(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path)
{
    CustomMotionStreak *ret = new (std::nothrow) CustomMotionStreak();
    if (ret && ret->initWithFade(fade, minSeg, stroke, color, path))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

CustomMotionStreak* CustomMotionStreak::create(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture)
{
    CustomMotionStreak *ret = new (std::nothrow) CustomMotionStreak();
    if (ret && ret->initWithFade(fade, minSeg, stroke, color, texture))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CustomMotionStreak::initWithFade(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path)
{
    CCASSERT(!path.empty(), "Invalid filename");
    
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(path);
    return initWithFade(fade, minSeg, stroke, color, texture);
}

bool CustomMotionStreak::initWithFade(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture)
{
    Node::setPosition(Vec2::ZERO);
    setAnchorPoint(Vec2::ZERO);
    ignoreAnchorPointForPosition(true);
    _startingPositionInitialized = false;
    
    _positionR = Vec2::ZERO;
    _fastMode = true;
    _minSeg = (minSeg == -1.0f) ? stroke/5.0f : minSeg;
    _minSeg *= _minSeg;
    
    _stroke = stroke;
    _fadeDelta = 1.0f/fade;
    
    _maxPoints = (int)(fade*60.0f)+2;
    _nuPoints = 0;
    _pointState = (float *)malloc(sizeof(float) * _maxPoints);
    _pointVertexes = (Vec2*)malloc(sizeof(Vec2) * _maxPoints);
    
    _vertices = (Vec2*)malloc(sizeof(Vec2) * _maxPoints * 2);
    _texCoords = (Tex2F*)malloc(sizeof(Tex2F) * _maxPoints * 2);
    _colorPointer =  (GLubyte*)malloc(sizeof(GLubyte) * _maxPoints * 2 * 4);
    
    // Set blend mode
    _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
    
    // shader state
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    
    setTexture(texture);
    setColor(color);
    scheduleUpdate();
    
    return true;
}

void CustomMotionStreak::setPosition(const Vec2& position)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR = position;
}

void CustomMotionStreak::setPosition(float x, float y)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR.x = x;
    _positionR.y = y;
}

const Vec2& CustomMotionStreak::getPosition() const
{
    return _positionR;
}

void CustomMotionStreak::getPosition(float* x, float* y) const
{
    *x = _positionR.x;
    *y = _positionR.y;
}

float CustomMotionStreak::getPositionX() const
{
    return _positionR.x;
}

void CustomMotionStreak::setPositionX(float x)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR.x = x;
}

float CustomMotionStreak::getPositionY() const
{
    return  _positionR.y;
}

void CustomMotionStreak::setPositionY(float y)
{
    if (!_startingPositionInitialized) {
        _startingPositionInitialized = true;
    }
    _positionR.y = y;
}

void CustomMotionStreak::tintWithColor(const Color3B& colors)
{
    setColor(colors);
    
    // Fast assignation
    for(unsigned int i = 0; i<_nuPoints*2; i++)
    {
        *((Color3B*) (_colorPointer+i*4)) = colors;
    }
}

Texture2D* CustomMotionStreak::getTexture(void) const
{
    return _texture;
}

void CustomMotionStreak::setTexture(Texture2D *texture)
{
    if (_texture != texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
    }
}

void CustomMotionStreak::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}

const BlendFunc& CustomMotionStreak::getBlendFunc(void) const
{
    return _blendFunc;
}

void CustomMotionStreak::setOpacity(GLubyte opacity)
{
    fade = opacity;
    //CCASSERT(false, "Set opacity no supported");
}

GLubyte CustomMotionStreak::getOpacity(void) const
{
    //CCASSERT(false, "Opacity no supported");
    return fade;
}

void CustomMotionStreak::setOpacityModifyRGB(bool bValue)
{
    CC_UNUSED_PARAM(bValue);
}

bool CustomMotionStreak::isOpacityModifyRGB(void) const
{
    return false;
}

void CustomMotionStreak::update(float delta)
{
    if (!_startingPositionInitialized)
    {
        return;
    }
    
    fade -= fadeFactor;
    
    if (fade < 0) {
        if (callbackToDestroy) {
            callbackToDestroy();
            return;
        }
    }
    
    delta *= _fadeDelta;
    
    unsigned int newIdx, newIdx2, i, i2;
    unsigned int mov = 0;
    
    // Update current points
    for(i = 0; i<_nuPoints; i++)
    {
        _pointState[i]-=delta;
        
        if(_pointState[i] <= 0)
            mov++;
        else
        {
            newIdx = i-mov;
            
            if(mov>0)
            {
                // Move data
                _pointState[newIdx] = _pointState[i];
                
                // Move point
                _pointVertexes[newIdx] = _pointVertexes[i];
                
                // Move vertices
                i2 = i*2;
                newIdx2 = newIdx*2;
                _vertices[newIdx2] = _vertices[i2];
                _vertices[newIdx2+1] = _vertices[i2+1];
                
                // Move color
                i2 *= 4;
                newIdx2 *= 4;
                _colorPointer[newIdx2+0] = _colorPointer[i2+0];
                _colorPointer[newIdx2+1] = _colorPointer[i2+1];
                _colorPointer[newIdx2+2] = _colorPointer[i2+2];
                _colorPointer[newIdx2+4] = _colorPointer[i2+4];
                _colorPointer[newIdx2+5] = _colorPointer[i2+5];
                _colorPointer[newIdx2+6] = _colorPointer[i2+6];
            }else
                newIdx2 = newIdx*8;
            
            const GLubyte op = (GLubyte)(_pointState[newIdx] * fade);
            _colorPointer[newIdx2+3] = op;
            _colorPointer[newIdx2+7] = op;
        }
    }
    _nuPoints-=mov;
    
    // Append new point
    bool appendNewPoint = true;
    if(_nuPoints >= _maxPoints)
    {
        appendNewPoint = false;
    }
    
    else if(_nuPoints>0)
    {
        bool a1 = _pointVertexes[_nuPoints-1].getDistanceSq(_positionR) < _minSeg;
        bool a2 = (_nuPoints == 1) ? false : (_pointVertexes[_nuPoints-2].getDistanceSq(_positionR)< (_minSeg * 2.0f));
        if(a1 || a2)
        {
            appendNewPoint = false;
        }
    }
    
    if(appendNewPoint)
    {
        _pointVertexes[_nuPoints] = _positionR;
        _pointState[_nuPoints] = 1.0f;
        
        // Color assignment
        const unsigned int offset = _nuPoints*8;
        *((Color3B*)(_colorPointer + offset)) = _displayedColor;
        *((Color3B*)(_colorPointer + offset+4)) = _displayedColor;
        
        // Opacity
        _colorPointer[offset+3] = fade;
        _colorPointer[offset+7] = fade;
        
        // Generate polygon
        if(_nuPoints > 0 && _fastMode )
        {
            if(_nuPoints > 1)
            {
                ccVertexLineToPolygon(_pointVertexes, _stroke, _vertices, _nuPoints, 1);
            }
            else
            {
                ccVertexLineToPolygon(_pointVertexes, _stroke, _vertices, 0, 2);
            }
        }
        
        _nuPoints ++;
    }
    
    if( ! _fastMode )
    {
        ccVertexLineToPolygon(_pointVertexes, _stroke, _vertices, 0, _nuPoints);
    }
    
    // Updated Tex Coords only if they are different than previous step
    if( _nuPoints  && _previousNuPoints != _nuPoints ) {
        float texDelta = 1.0f / _nuPoints;
        for( i=0; i < _nuPoints; i++ ) {
            _texCoords[i*2] = Tex2F(0, texDelta*i);
            _texCoords[i*2+1] = Tex2F(1, texDelta*i);
        }
        
        _previousNuPoints = _nuPoints;
    }
}

void CustomMotionStreak::reset()
{
    _nuPoints = 0;
}

void CustomMotionStreak::onDraw(const Mat4 &transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);
    
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
    GL::blendFunc( _blendFunc.src, _blendFunc.dst );
    
    GL::bindTexture2D( _texture->getName() );
    
#ifdef EMSCRIPTEN
    // Size calculations from ::initWithFade
    setGLBufferData(_vertices, (sizeof(Vec2) * _maxPoints * 2), 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    setGLBufferData(_texCoords, (sizeof(Tex2F) * _maxPoints * 2), 1);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    setGLBufferData(_colorPointer, (sizeof(GLubyte) * _maxPoints * 2 * 4), 2);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
#else
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, _vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, _texCoords);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, _colorPointer);
#endif // EMSCRIPTEN
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nuPoints*2);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _nuPoints*2);
}

void CustomMotionStreak::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if(_nuPoints <= 1)
        return;
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(CustomMotionStreak::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void CustomMotionStreak::setStroke(const float stroke){
    _stroke = stroke;
}

void CustomMotionStreak::setTimeToDestroy(float time, std::function<void()> destroyCallback) {
    
    callbackToDestroy = destroyCallback;
    fade = 255.0f;
    fadeFactor = 1/(time/6);
    
}


NS_CC_END











