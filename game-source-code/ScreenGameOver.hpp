/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Description of file in project Project
///
/// Detailed description of file
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

    int show(sf::RenderWindow &window,
             const TextureHolder &textureHolder,
             const FontHolder &fontHolder,
             const sf::Vector2i) override;
};

#endif //PROJECT_GAMEOVERSCREEN_HPP