/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    23/9/17
/// \brief   Object and methods to keep score of player actions
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#include "Score.hpp"

void Score::addToScore(int points)
{
    _score += points;
}

void Score::incrementEnemiesKilled(entity::ID type)
{
    _enemiesKilled++;
    _bulletsHit++;

    switch (type)
    {

        case entity::Basic :
            addToScore(500);
            break;

        case entity::BasicAlternate :
            addToScore(500);
            break;

        default :
            break;
    }
}

void Score::incrementBulletsFired()
{
    _bulletsFired++;
}

const float Score::getPlayerAccuracy()
{
    return (_bulletsHit * 1.f)/_bulletsFired;
}

const unsigned int Score::getScore()
{
    return _score;
}

const unsigned int Score::getEnemiesKilled()
{
    return _enemiesKilled;
}

const unsigned int Score::getBulletsFired()
{
    return _bulletsFired;
}