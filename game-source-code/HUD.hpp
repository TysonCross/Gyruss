/////////////////////////////////////////////////////////////////////
/// \brief   Head Up Display showing the score, player lives
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_HUD_HPP
#define PROJECT_HUD_HPP

#include "SFML/Graphics.hpp"
#include "ResourceHolder.hpp"
#include "Score.hpp"
#include "PlayerShip.hpp"
#include "common.hpp"

using sf::RenderWindow;
using sf::Vector2i;

////////////////////////////////////////////////////////////
/// \brief HUD class, to inform the user of remaining lives and other game information
///
/// Sources information from the score object from game
///
/// \see Score
////////////////////////////////////////////////////////////
class HUD
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief HUD class constructor. Initiated on game start.
    ///
    /// \param resolution stores the size of the screen so the HUD knows where to position itself
    /// \param renderWindow enables the HUD to draw directly onto the game screen
    /// \param fontHolder is used to pass the required fonts to the HUD
    /// \param score object enables the HUD to display the current game score, calculated and stored in score object
    /// \param playerShip provides the playerShip state to the HUD, so the player can see if his is alive/dead/invulnerable
    ///
    /// \see [SFML/RenderWindow](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1RenderWindow.php)
    /// \see [SFML/Vector2](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php)
    /// \see PlayerShip
    ////////////////////////////////////////////////////////////
    HUD(const Vector2i resolution,
        RenderWindow &renderWindow,
        const FontHolder &fontHolder,
        const Score &score,
        const PlayerShip &playerShip);
    ////////////////////////////////////////////////////////////
    /// \brief Appends the HUD to the current game renderWindow for the current lives and game score
    ////////////////////////////////////////////////////////////
    void draw();

private:
    ////////////////////////////////////////////////////////////
    /// \brief Vector to store the game resolution, to enable the HUD to know its internal deterministically generated dimensions
    ////////////////////////////////////////////////////////////
    const Vector2i _resolution;

    ////////////////////////////////////////////////////////////
    /// \brief Reference to the main game renderWindow, to enable the HUD to draw itself over the main game window
    /// \see [SFML/RenderWindow](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1RenderWindow.php)
    ////////////////////////////////////////////////////////////
    RenderWindow& _renderWindow;
    ////////////////////////////////////////////////////////////
    /// \brief Reference to the main font holder, to give the HUD access to its required fonts
    /// \see ResourceHolder
    ////////////////////////////////////////////////////////////
    const FontHolder& _fonts;

    ////////////////////////////////////////////////////////////
    /// \brief Reference to the main score object, so the HUD to draw the latest player score
    /// \see Score
    ////////////////////////////////////////////////////////////
    const Score& _score;

    ////////////////////////////////////////////////////////////
    /// \brief Reference to the main playerShip, the so HUD can know the ship current state.
    ////////////////////////////////////////////////////////////
    const PlayerShip& _playerShip;
};

#endif //PROJECT_HUD_HPP
