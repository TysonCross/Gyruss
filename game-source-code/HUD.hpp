/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    21/9/17
/// \brief   Head Up Display showing the score, player lives
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_HUD_HPP
#define PROJECT_HUD_HPP

#include "SFML/Graphics.hpp"
#include "ResourceHolder.hpp"
#include "Score.hpp"
#include "PlayerShip.hpp"
#include "common.hpp"

class HUD
{
public:
    HUD(const sf::Vector2i resolution,
        sf::RenderWindow &renderWindow,
        const TextureHolder &textureHolder,
        const FontHolder &fontHolder,
        const Score &score,
        const PlayerShip &playerShip);

    void draw();
    void updatePlayerLives();
    void updateScore();
    void updateEnemiesKilled();
    void updateBulletsFired();
    void updateTime();

private:
    const sf::Vector2i _resolution;
    sf::RenderWindow& _renderWindow;
    const TextureHolder& _textures;
    const FontHolder& _fonts;
    const Score& _score;
    const PlayerShip& _playerShip;

};


#endif //PROJECT_HUD_HPP
