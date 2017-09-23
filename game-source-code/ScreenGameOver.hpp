/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Simple Game Over / Death Screen definition
///
/// Class interface for showing a screen with information on how to the score
/// and asking for input from player as an option to restart the game
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_GAMEOVERSCREEN_HPP
#define PROJECT_GAMEOVERSCREEN_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Screen.hpp"

class ScreenGameOver : public Screen

{
public:

    int draw(sf::RenderWindow &window,
             const TextureHolder &textureHolder,
             const FontHolder &fontHolder,
             const sf::Vector2i) override;
};

#endif //PROJECT_GAMEOVERSCREEN_HPP
