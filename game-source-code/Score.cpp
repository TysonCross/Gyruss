/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    23/9/17
/// \brief   Object and methods to keep score of player actions
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#include "Score.hpp"
Score::Score() : _score{0},
                 _enemiesKilled{0},
                 _bulletsFired{0},
                 _bulletsHit{0}{}

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

const float Score::getPlayerAccuracy() const
{
    if (_bulletsFired!=0)
    {
        return (_bulletsHit * 1.f) / _bulletsFired;
    }
    else
    {
        return 0.f;
    }
}

const unsigned int Score::getScore() const
{
    return _score;
}

const unsigned int Score::getEnemiesKilled() const
{
    return _enemiesKilled;
}

const unsigned int Score::getBulletsFired() const
{
    return _bulletsFired;
}