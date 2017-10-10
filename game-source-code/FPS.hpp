/////////////////////////////////////////////////////////////////////
/// \brief   Check the FPS
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_FPS_HPP
#define PROJECT_FPS_HPP

#include "SFML/System/Clock.hpp"

class FPS
{
public:
    /// \brief Default constructor
    FPS();

    /// \brief Return the Frame per second count
    /// \return The FPS count
    const unsigned int getFPS() const;

    /// \brief Restarts the clock, and increments the frame count
    void update();

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    unsigned int _frame;
    unsigned int _fps;
    sf::Clock _clock;
};

#endif //PROJECT_FPS_HPP
