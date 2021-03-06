#ifndef CGF_SPRITE_H
#define CGF_SPRITE_H

/*
 *  Sprite.h
 *  Animated sprite class
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 *  Base on original code at https://github.com/LaurentGomila/SFML/wiki/Source%3A-AnimatedSprite
 *
 */

#include <vector>
#include <map>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include "TextureManager.h"
#include "Anim.h"
#include "pugixml/pugixml.hpp"

namespace cgf
{

class Sprite : public sf::Drawable, public sf::Transformable
{
public:
    Sprite();
    virtual ~Sprite();

    bool load(char filename[]);
    bool load(char filename[], int w, int h, int hSpace, int vSpace, int xIni, int yIni,
                int column, int row, int total);
    bool loadXML(char filename[]);
    bool loadAnimation(char filename[]);

    void setVisible(bool vis) { visible = vis; }
    bool isVisible() { return visible; }

    // Mirroring (X-axis)
	void setMirror(bool mirror);
    bool getMirror() { return mirror; }

    // Sprite speed
    void setXspeed(double xspeed);
    void setYspeed(double yspeed);
    double getXspeed() { return xspeed; }
    double getYspeed() { return yspeed; }

    // Animation control
    void setAnimation(std::string name);
    std::string getAnimation();
    void setAnimRate(int fdelay);
    void play();
    void pause();
    void stop();
    void setLooped(bool looped) { looping = looped; }
    bool isLooped() { return looping; }
    enum AnimState { STOPPED, PLAYING, PAUSED };

    // Fine tuning animation controls
    bool setFrameRange(int first, int last);
    void setCurrentFrame(int c);
    void frameForward();
    void frameBack();

    int getCurrentFrame() { return curframe; }
    int getTotalFrames() { return totalFrames; }

    void update(double deltaTime);

    // Basic collision checking
    bool bboxCollision(Sprite& other);
    bool circleCollision(Sprite& other);

private:

    static TextureManager* tm;

    // Rendering
    const sf::Texture* tex;
    sf::Vertex vertices[4];
    int spriteW, spriteH;       // width and height of a single sprite frame
    bool visible;
    bool mirror;

    // Motion
    double xspeed,yspeed;       // speed in pixels/s
    int updateCount;            // current count of updates

    // Animation
    std::map<std::string, cgf::Anim> anims;
    std::vector<sf::IntRect> frames;
    cgf::Anim* currentAnim;
    int firstFrame, lastFrame;
    bool looping;
    AnimState animState;
    int totalFrames;
    int curframe;		        // current frame
    double curFrameD;           // the current frame as double
    int framecount,framedelay;  // slow down the frame animation
	std::string animName;

    bool loadMultiImage(char nomeArq[], int w, int h, int hSpace, int vSpace, int xIni, int yIni, int column, int row, int total);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void updateGraphics();
};

} // namespace cgf

#endif // CGF_SPRITE_H
