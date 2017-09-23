/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    21/9/17
/// \brief   Description of file in project Project
///
/// Detailed description of file
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_HUD_HPP
#define PROJECT_HUD_HPP

#include <sstream>
#include "SFML/Graphics.hpp"
#include "ResourceHolder.hpp"
#include "Score.hpp"
#include "common.hpp"

class HUD
{
public:
    HUD(sf::RenderWindow &renderWindow,
        TextureHolder &textureHolder,
        FontHolder &fontHolder,
            Score &score);

    void draw();
    void updatePlayerLives();
    void updateScore();
    void updateEnemiesKilled();
    void updateBulletsFired();
    void updateTime();

private:
    Score _score;
    sf::RenderWindow _window;
    TextureHolder _textures;
    FontHolder _fonts;

};


#endif //PROJECT_HUD_HPP
