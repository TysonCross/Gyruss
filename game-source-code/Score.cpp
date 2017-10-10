/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    23/9/17
/// \brief   Object and methods to keep score of player actions
/////////////////////////////////////////////////////////////////////

#include "Score.hpp"

void Score::update()
{
    auto survivalTimeIncrement = 1.f;
    _survivalTime = _updateTimer.getElapsedTime().asSeconds();

    if (_survivalTime > survivalTimeIncrement)
    {
        _updateTimer.restart();
        addToScore(50);
    }
}
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

        case entity::Satellite :
            addToScore(500);
            break;

        case entity::BasicWanderer :
            addToScore(500);

        default :
            break;
    }
}

void Score::reset()
{
    _score = 0;
    _enemiesKilled = 0;
    _bulletsFired = 0;
    _bulletsHit = 0;
    _longestTimeAlive = 0.f;
    _lifeTimer.restart();
    _updateTimer.restart();
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

const float Score::getTimeAlive() const
{
    return _lifeTimer.getElapsedTime().asSeconds();
}

const float Score::getLongestTimeAlive() const
{
    return _longestTimeAlive;
}

const void Score::resetLifeTimer()
{
    auto currentTimeAlive = _lifeTimer.getElapsedTime().asSeconds();
    if (currentTimeAlive > _longestTimeAlive)
    {
        _longestTimeAlive = currentTimeAlive;
    }
    _lifeTimer.restart();
}




