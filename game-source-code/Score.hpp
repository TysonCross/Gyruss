/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    23/9/17
/// \brief   Object and methods to keep score of player actions
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_SCORE_HPP
#define PROJECT_SCORE_HPP

#include <SFML/System/Time.hpp>
#include "common.hpp"

class Score
{
public:
    Score();
    void incrementEnemiesKilled(entity::ID type);
    void incrementBulletsFired();
    const unsigned int getScore() const;
    const unsigned int getEnemiesKilled() const;
    const unsigned int getBulletsFired() const;
    const float getPlayerAccuracy() const;

private:
    void addToScore(int points);

    unsigned int _score;
    unsigned int _enemiesKilled;
    unsigned int _bulletsFired;
    unsigned int _bulletsHit;
};


#endif //PROJECT_SCORE_HPP
