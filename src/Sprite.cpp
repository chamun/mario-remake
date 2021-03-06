/*
 *  Sprite.cpp
 *  Sprite class
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include "include/Sprite.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

namespace cgf
{


TextureManager* Sprite::tm = TextureManager::getInstance();

// Construtor
Sprite::Sprite()
{
    mirror = false;
    visible = true;
    // Init animation vars
    xspeed = 0;
    yspeed = 0;
    curframe = 0;
    curFrameD = 0;
    framedelay = 10;
    firstFrame = 0;
    lastFrame = 0;
    animState = STOPPED;
    looping = false;
    currentAnim = NULL;
	tm = TextureManager::getInstance();
}

bool Sprite::load(char filename[])
{
    tex = tm->findTexture(filename);
    if(tex == NULL)
        return false;

    spriteW = tex->getSize().x;
    spriteH = tex->getSize().y;

    // Add a single frame as the whole image
    sf::IntRect rect;
    rect.left = 0;
    rect.width = spriteW;
    rect.top = 0;
    rect.height = spriteH;
    cout << "image: " << rect.left << "," << rect.top
         << " - " << rect.width << "x" << rect.height << endl;
    frames.push_back(rect);
    totalFrames = frames.size();
    setCurrentFrame(0);
    return true;
}

bool Sprite::load(char filename[], int w, int h, int hSpace, int vSpace, int xIni, int yIni,
                 int column, int row, int total)
{
    if(!loadMultiImage(filename,w,h,hSpace,vSpace,xIni,yIni,column,row,total))
        return false;

    setCurrentFrame(0);
    //setOrigin(w/2, h/2);
	return true;
}

bool Sprite::loadXML(char xmlFile[])
{
    cout << "Sprite::loadXML " << xmlFile << endl;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xmlFile);

    if ( !result )
		return false;

    // Read texture atlas file name

    pugi::xml_node atlas = doc.child("TextureAtlas");
    pugi::xml_attribute imagepath = atlas.attribute("imagePath");

    string attrib = imagepath.as_string();

    cout << "Sprite::loadSpriteSparrowXML: " << attrib << endl;
    cout << "TextureAtlas: " << attrib << endl;

    tex = tm->findTexture((char *)attrib.c_str());
    if(tex == NULL)
        return false;

    // Read all subtextures (frames)
    for (pugi::xml_node subtex: atlas.children("sprite"))
    {
        int x1, y1, h, w;

        x1 = subtex.attribute("x").as_int();
        y1 = subtex.attribute("y").as_int();
        w = subtex.attribute("w").as_int();
        h = subtex.attribute("h").as_int();

        spriteW = w;
        spriteH = h;

        //cout << "Texture: " << x1 << " " << y1 << " " << w-1 << " " << h-1 << endl;
        sf::IntRect rect;
        rect.left = x1;
        rect.width = w;
        rect.top = y1;
        rect.height = h;
        cout << "frame " << setw(3) << frames.size() << ": " << rect.left << "," << rect.top
            << " - " << rect.width << "x" << rect.height << endl;
        frames.push_back(rect);

    }

    totalFrames = frames.size();

    cout << "Sprite::loadSpriteSparrowXML total frames = " << totalFrames << endl;

    setCurrentFrame(0);
    return true;
}

bool Sprite::loadAnimation(char filename[])
{
    cout << "Sprite::loadAnimation " << filename << endl;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename);

    if ( !result )
        return false;

    // Read texture atlas file name
    pugi::xml_node root = doc.child("animation");

    // Read all animation sequences
//    for(pugi::xml_node seq = root.child("sequence"); seq; seq = seq.next_sibling("sequence"))
    for(pugi::xml_node seq : root.children("sequence"))
    {
        cgf::Anim anim;
        string name = seq.attribute("name").as_string();
        cout << "Animation: " << name << endl;
        anim.frameStart = seq.attribute("start").as_int();
        anim.frameEnd   = seq.attribute("end").as_int();
        anim.loop       = seq.attribute("loop").as_bool();
        anims[name] = anim;
    }

    cout << "Sprite::loadAnimation total sequences = " << anims.size() << endl;
    return true;
}

bool Sprite::loadMultiImage(char filename[], int w, int h, int hSpace, int vSpace, int xIni, int yIni, int columns, int rows, int total)
{
    tex = tm->findTexture(filename);

    int width  = tex->getSize().x;
    int height = tex->getSize().y;

    // Check if the input parameters are valid
    if ( (hSpace<0 || vSpace<0) || (hSpace>width || vSpace>height) )
        return false;

    if ( xIni<0 || yIni<0 )
        return false;

    if ( columns<1 || rows<1 )
        return false;

    totalFrames = total;

    if (totalFrames < 1)
        return false;

    int x, y, tot;

    tot = 0;
    y = yIni;

    for(int r=0; r<rows && tot<total; rows++)
    {
        x = xIni;
        for(int c=0; c<columns && tot<total; c++)
        {
            sf::IntRect rect;
            rect.left = x;
            rect.width = w;
            rect.top = y;
            rect.height = h;
            cout << "frame " << setw(3) << tot << ": " << x << " " << y << " " << w << " " << h << endl;
            frames.push_back(rect);

            x += w + hSpace;
            tot++;
        }
        y += h + vSpace;
    }

//    xOffset = w/2;
//    yOffset = h/2;

    //setOrigin(w/2, h/2);

    cout << "Sprite::loadMultimage total frames = " << total << endl;

    return true;
}

void Sprite::setAnimation(string name)
{
    auto seq = anims.find(name);
    if(seq == anims.end())
        return;
	if (name == animName)
		return;

    currentAnim = &seq->second;
    setFrameRange(currentAnim->frameStart, currentAnim->frameEnd);
    setLooped(currentAnim->loop);

    animState = AnimState::STOPPED;
	animName = name;
}

std::string Sprite::getAnimation()
{
	return animName;
}

void Sprite::play()
{
    if(animState == AnimState::STOPPED)
        setCurrentFrame(firstFrame);
    animState = AnimState::PLAYING;
}

void Sprite::pause()
{
    animState = AnimState::PAUSED;
}

void Sprite::stop()
{
    animState = AnimState::STOPPED;
}


Sprite::~Sprite()
{
    //dtor
}

// Especifica quantos pixels o sprite ira se mover em x.
void Sprite::setXspeed(double xspeed)
{
	this->xspeed = xspeed;
}

// Especifica quantos pixels a sprite ira se mover em y.
void Sprite::setYspeed(double yspeed)
{
	this->yspeed = yspeed;
}

// Sets the current frame
void Sprite::setCurrentFrame(int c)
{
	if ( c>=0 && c<totalFrames )
		curframe = c;
	else
		curframe = 0;
    curFrameD = curframe;

	updateGraphics();
}

void Sprite::updateGraphics()
{
    //sf::IntRect rect = m_animation->getFrame(m_currentFrame);
    sf::IntRect rect = frames[curframe];

    vertices[0].position = sf::Vector2f(0, 0);
    vertices[1].position = sf::Vector2f(0, rect.height);
    vertices[2].position = sf::Vector2f(rect.width, rect.height);
    vertices[3].position = sf::Vector2f(rect.width, 0);

    float left = static_cast<float>(rect.left) + 0.0001;
    float right = left + rect.width;
    float top = static_cast<float>(rect.top);
    float bottom = top + rect.height;

    if(mirror) {
        float tmp = left;
        left = right;
        right = tmp;
    }

    vertices[0].texCoords = sf::Vector2f(left, top);
    vertices[1].texCoords = sf::Vector2f(left, bottom);
    vertices[2].texCoords = sf::Vector2f(right, bottom);
    vertices[3].texCoords = sf::Vector2f(right, top);

    spriteW = rect.width;
    spriteH = rect.height;
}

/** @brief setFrameRange
  *
  * @todo: document this function
  */
bool Sprite::setFrameRange(int first, int last)
{
    if(first > last || first < 0 || last >= totalFrames)
        return false;
    firstFrame = first;
    lastFrame = last;
    setCurrentFrame(firstFrame);
    return true;
}

// Advance to next frame
void Sprite::frameForward()
{
	curframe++;
	if (curframe > lastFrame)
		curframe = firstFrame;
}

// Go back to previous frame
void Sprite::frameBack()
{
	curframe--;
	if (curframe < firstFrame)
		curframe = lastFrame;
}

// Recebe por parametro o valor que sera usado para especificar o atributo
// framedelay, responsavel por diminuir ou aumentar a taxa de animacao.
void Sprite::setAnimRate(int fdelay)
{
    if (fdelay >= 0)
		framedelay = fdelay;
	else
		framedelay = 0;

    // Reset framecount so next draw will work as it should be
    framecount = 0;
}

// Metodo responsavel por fazer as atualizacoes necessarias para a correta
// animacao do sprite.
void Sprite::update(double deltaTime)
{
	updateGraphics(); 
    // Move sprite according to its speed and the amount of time that has passed
    sf::Vector2f offset(xspeed/1000 * deltaTime, yspeed/1000 * deltaTime);
    move(offset);

    if(animState == AnimState::PLAYING) {
        int lastf = curframe;
        curFrameD += (double)framedelay/1000*deltaTime;
        curframe = (int) curFrameD;
        if(curframe > lastFrame && looping || firstFrame == lastFrame) {
            curFrameD = firstFrame;
            curframe = firstFrame;
        }
        if(curframe != lastf)
            setCurrentFrame(curframe);
    }
}

void Sprite::setMirror(bool mirror) 
{ 
	this->mirror = mirror; 
}

// Check bounding box collision between this and other sprite
bool Sprite::bboxCollision(Sprite& other)
{
    sf::Vector2f pos = this->getPosition();
    sf::Vector2f scale = this->getScale();

    float scalex2 = other.getScale().x;
    float scaley2 = other.getScale().y;

    float px2 = other.getPosition().x;
    float py2 = other.getPosition().y;

    float width1 = this->spriteW/2 * scale.x;
    float width2 = other.spriteW/2 * scalex2;

    float height1 = this->spriteH/2 * scale.y;
    float height2 = other.spriteH/2 * scaley2;

    float x0 = pos.x - width1;
    float y0 = pos.y - height1;
    float x1 = pos.x + width1;
    float y1 = pos.y + height1;

    float x2 = px2 - width2;
    float y2 = py2 - height2;
    float x3 = px2 + width2;
    float y3 = py2 + height2;

    return !(x1<x2 || x3<x0 || y1<y2 || y3<y0);
}

// Check circle collision between this and other sprite
bool Sprite::circleCollision(Sprite& other)
{
   int radius1 = max(this->spriteW, this->spriteH)/2;
   int radius2 = max(other.spriteW, other.spriteW)/2;
   radius1 *= this->getScale().x;
   radius2 *= other.getScale().y;
   float px1 = this->getPosition().x;
   float px2 = other.getPosition().x;
   float py1 = this->getPosition().y;
   float py2 = other.getPosition().y;
   float dist = sqrt(pow(px1 - px2, 2) + pow(py1 - py2, 2));
   //cout << "Radius: " << radius1 << " and " << radius2 << endl;
   //cout << "distance: " << dist << endl;
   return (dist < radius1 + radius2);
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (tex)
    {
        states.transform *= getTransform();
        states.texture = tex;
        target.draw(vertices, 4, sf::Quads, states);
    }
}

} // namespace cgf
