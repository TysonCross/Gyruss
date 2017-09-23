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
#include "common.hpp"

class HUD
{
public:
    HUD();
    draw();

private:
    updatePlayerLives();
    updateScore();
    updateEnemiesKilled();
    updateBulletsFired();

    sf::RenderWindow _window;
    TextureHolder _textures;
    FontHolder _fonts;
    int _playerLives;
    int _score;
    int _enemiesKilled;
    int bulletsFired;
    int _totalTime;

};


#endif //PROJECT_HUD_HPP
