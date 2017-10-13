//--------------------------------------------------------------------------
// Students 1239448 & 1109146
// @date    2017/09/10
// @brief   Unit test for game
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <chrono>
#include <thread>
#include "math.h"
#include "../game-source-code/common.hpp"
#include "../game-source-code/Bullet.hpp"
#include "../game-source-code/Enemy.hpp"
#include "../game-source-code/Entity.hpp"
#include "../game-source-code/EntityController.hpp"
#include "../game-source-code/Explosion.hpp"
#include "../game-source-code/Game.hpp"


#include "doctest.h"

////////////////////////////////////////////////////////////
///  TextureHolder UnitTests
////////////////////////////////////////////////////////////
TEST_CASE ("Loading a missing file into a resourceHandler<sf::Texture, textures::ID> throws an exception")
{
    TextureHolder texture_holder;
            CHECK_THROWS(texture_holder.load(textures::testTexture, "resources/NO_IMAGE"));
}

TEST_CASE ("Loading a texure that exists into a resourceHandler<sf::Texture, textures::ID> succeeds")
{
    TextureHolder texture_holder;
            CHECK_NOTHROW(texture_holder.load(textures::testTexture, "resources/test_image.png"));

}

TEST_CASE ("Getting a texture previously loaded into a resourceHandler<sf::Texture, textures::ID> succeeds (i.e. does not throw an exception)")
{
    TextureHolder texture_holder;
            REQUIRE_NOTHROW(texture_holder.load(textures::testTexture, "resources/test_image.png"));

    sf::Sprite elf;
            CHECK_NOTHROW(elf.setTexture(texture_holder.get(textures::testTexture)));
}

//Check SoundHolder
TEST_CASE ("Loading a missing file into a resourceHandler<sf::SoundBuffer, sounds::ID> throws an exception")
{
    SoundHolder sound_holder;

            CHECK_THROWS(sound_holder.load(sounds::testSound, "resources/NO_IMAGE"));
}

TEST_CASE (
        "Loading a sound buffer from a file that exists into a resourceHandler<sf::SoundBuffer, sounds::ID> succeeds (i.e. does not throw an exception)")
{
    SoundHolder sound_holder;
            REQUIRE_NOTHROW(sound_holder.load(sounds::testSound, "resources/test.ogg"));

    sf::Sound testSound;
            CHECK_NOTHROW(testSound.setBuffer(sound_holder.get(sounds::testSound)));
}


TEST_CASE (
        "Playing a sound previously loaded into a resourceHandler<sf::SoundBuffer, sounds::ID> succeeds (i.e. does not throw an exception)")
{
    SoundHolder sound_holder;
            REQUIRE_NOTHROW(sound_holder.load(sounds::testSound, "resources/test.ogg"));

    sf::Sound testSound;
            REQUIRE_NOTHROW(testSound.setBuffer(sound_holder.get(sounds::testSound)));
            CHECK_NOTHROW(testSound.play());
}

////////////////////////////////////////////////////////////
///  Font Holder Unit tests
////////////////////////////////////////////////////////////
TEST_CASE ("Loading a missing file into a resourceHandler<sf::Font, fonts::ID> throws an exception")
{
    FontHolder font_holder;

            CHECK_THROWS(font_holder.load(fonts::testFont, "resources/NO_FONT"));
}

TEST_CASE ("Loading a font that exists into a resourceHandler<sf::Font, fonts::ID> succeeds")
{
    FontHolder font_holder;
            CHECK_NOTHROW(font_holder.load(fonts::testFont, "resources/danube.ttf"));

}

TEST_CASE (
        "Getting a font previously loaded into a resourceHandler<sf::Font, fonts::ID> succeeds (i.e. does not throw an exception)")
{
    FontHolder font_holder;
            REQUIRE_NOTHROW(font_holder.load(fonts::testFont, "resources/danube.ttf"));
            CHECK_NOTHROW(sf::Text text_test("TEST", font_holder.get(fonts::testFont)));
}

////////////////////////////////////////////////////////////
///  Movement tests for PlayerShip
////////////////////////////////////////////////////////////

// PlayerShip movement tests

TEST_CASE ("Creating A PlayerShip object succeeds")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);

            CHECK_NOTHROW(
            PlayerShip playerShip(resolution,
                                  shipPathRadius,
                                  0,
                                  shipScale,
                                  entity::PlayerShip,
                                  textures);
    );

}

// Check rotation works with .setEnemyMoveState & .setPlayerShipMove
TEST_CASE ("Moving a PlayerShip 10 degrees succeeds")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); //move playerShip to origin
    auto originalAngle = playerShip.getAngle();
    auto moveAngle = 10.0f;
    playerShip.setMove(moveAngle);
    playerShip.update();
    auto finalAngle = playerShip.getAngle();
            CHECK(finalAngle == moveAngle);
}

TEST_CASE ("PlayerShip getPosition and underlying transformation both return the same location correctly")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); //move playerShip to origin
    auto originalAngle = playerShip.getAngle();
    auto moveAngle = 10.0f;
    playerShip.setMove(moveAngle);
    playerShip.update();
    auto spriteLocation = playerShip.getSprite().getPosition();
    auto getPositionLocation = playerShip.getPosition();
            CHECK(spriteLocation == getPositionLocation);
}

// Tests holding down move button
TEST_CASE ("Moving a PlayerShip multiple times succeeds")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); //move playerShip to origin
    auto originalAngle = playerShip.getAngle();
    auto moveAngle = 10.0f; //define to move the ship 10 degrees
    for (auto i = 0; i < 5; i++) {
        playerShip.setMove(moveAngle);
        playerShip.update();
    }
    auto expectedAngle = moveAngle * 5;
    auto finalAngle = playerShip.getAngle();
            CHECK(finalAngle == expectedAngle);
}

// Correct circle implementedd
TEST_CASE ("Moving a PlayerShip 360 degrees brings ship back to where it started")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); //move playerShip to origin
    auto originalAngle = playerShip.getAngle();
    auto originalPosition = playerShip.getPosition();
    auto moveAngle = 45.0f;
    for (auto i = 0; i < 8; i++) {
        playerShip.setMove(moveAngle);
        playerShip.update();
    }
    auto finalAngle = playerShip.getAngle();
    auto finalPosition = playerShip.getPosition();
            CHECK(finalAngle == originalAngle);
            CHECK(finalPosition.x == originalPosition.x);
            CHECK(finalPosition.y == originalPosition.y);
}


// Check "angleFilter" function
TEST_CASE ("Moving a PlayerShip -10 degrees correctly casts to 350 and succeeds")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); // Move playerShip to origin
    auto originalAngle = playerShip.getAngle();
    auto moveAngle = -10.0f;
    auto expectedFinalAngle = 350.0f; // Using the "angleFilter" to move negative angle to between 0 <-> 360
    playerShip.setMove(moveAngle);
    playerShip.update();
    auto finalAngle = playerShip.getAngle();
            CHECK(finalAngle == expectedFinalAngle);
}

TEST_CASE ("Moving a PlayerShip moves the sprite the correct number of pixels (flip 180)")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); // Move playerShip to origin
    auto originalLocation = playerShip.getPosition();
    auto moveAngle = 180;
    playerShip.setMove(moveAngle);
    playerShip.update();
    auto finalLocation = playerShip.getPosition();
    auto expectedLocation = sf::Vector2f{originalLocation.x, resolution.y * shipPathRadiusPadding};
            CHECK(round(finalLocation.y)==round(expectedLocation.y)); // Cast to int to get closest pixel accuracy
            CHECK(round(finalLocation.x)==round(expectedLocation.x)); // Cast to int to get closest pixel accuracy
}

TEST_CASE ("Reseting ship position brings the ship back to spawning point sucessfully")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); // Move playerShip to origin
    auto originalLocation = playerShip.getPosition();
    auto moveAngle = 180;
    playerShip.setMove(moveAngle);
    playerShip.update();
    playerShip.reset();
    playerShip.update();
    auto finalLocation = playerShip.getPosition();
            CHECK(round(finalLocation.x)==round(originalLocation.x)); // Cast to int to get closest pixel
            CHECK(round(finalLocation.y)==round(originalLocation.y)); // Cast to int to get closest pixel
}

TEST_CASE ("Killing the playerShip decrements a life")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); // Move playerShip to origin
    auto startingLives = playerShip.getLives();
    auto startingPosition = playerShip.getPosition();

    auto moveShipAmount = 90; // Move the ship to simulate player interaction
    playerShip.setMove(moveShipAmount);
    playerShip.update();

    playerShip.die();
    playerShip.update();

            CHECK(playerShip.getLives() == startingLives - 1);
}

TEST_CASE ("Killing the playerShip resets the ship location to centre")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); // Move playerShip to origin
    auto startingLives = playerShip.getLives();
    auto startingPosition = playerShip.getPosition();

    auto moveShipAmount = 90; // Move the ship to simulate player interaction
    playerShip.setMove(moveShipAmount);
    playerShip.update();

    playerShip.die();
    playerShip.update();

            CHECK(playerShip.getAngle() == 0);
            CHECK(playerShip.getFutureAngle() == 0);
            CHECK(!playerShip.isShooting());
            CHECK(!playerShip.isMoving());
            CHECK(playerShip.getPosition().x == startingPosition.x);
            CHECK(playerShip.getPosition().y == startingPosition.y);
}

TEST_CASE ("Killing the playerShip makes the ship Invulnerable")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); //Move playerShip to origin
    auto startingLives = playerShip.getLives();
    auto startingPosition = playerShip.getPosition();

    auto moveShipAmount = 90; // Move the ship to simulate player interaction
    playerShip.setMove(moveShipAmount);
    playerShip.update();

    playerShip.die();
    playerShip.update();

            CHECK(playerShip.isInvulnerable() == true);
}

////////////////////////////////////////////////////////////
///  Movement tests for Bullet
////////////////////////////////////////////////////////////

// Bullet movement tests
TEST_CASE ("Creating a bullet entity succeeds")
{
    TextureHolder textures;
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto bulletShootAngle = 180;
    auto bulletStartingPoint = resolution.y; // Define the starting distance from centre
            CHECK_NOTHROW(
            Bullet bullet(resolution,
                          bulletStartingPoint,
                          bulletShootAngle,
                          0.5,
                          entity::PlayerBullet,
                          textures,
                          textures::BulletPlayer);
    );
}

TEST_CASE ("Shooting a bullet stright up moves corretly")
{
    TextureHolder textures;
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto bulletShootAngle = 180; // Bullet moves directly up
    auto bulletStartingPoint = resolution.y; // Define the starting distance from centre;
    Bullet bullet(resolution,
                  bulletStartingPoint,
                  bulletShootAngle,
                  0.5,
                  entity::PlayerBullet,
                  textures,
                  textures::BulletPlayer);
    auto startingPosition = bullet.getPosition();
    auto desiredBulletMove = -1; // Move the bullet 2 pixels away from starting point, from point of fire
    bullet.setMove(desiredBulletMove);
    bullet.update();
    auto finalPosition = bullet.getPosition();
    auto expectedBulletMove = desiredBulletMove * 2; // Double the desired move due to non-linear scaling at edg
    auto expectedPosition = sf::Vector2f(startingPosition.x, startingPosition.y - expectedBulletMove);
            CHECK(round(finalPosition.x)==round(expectedPosition.x));
            CHECK(round(finalPosition.y)==round(expectedPosition.y));
}

TEST_CASE ("Shooting a bullet stright up causes them to scale down as they fly away")
{
    TextureHolder textures;
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto bulletShootAngle = 180;
    auto bulletStartingPoint = resolution.y; // Define the starting distance from centre;
    Bullet bullet(resolution,
                  bulletStartingPoint,
                  bulletShootAngle,
                  0.5,
                  entity::PlayerBullet,
                  textures,
                  textures::BulletPlayer);
    auto startingScale = bullet.getRadius();
    auto desiredBulletMove = -10;
    bullet.setMove(desiredBulletMove);
    bullet.update();
    auto finalScale = bullet.getRadius();
    // The position below if the original, +2 pixels due to the scaling of effect of the non-linear motion of the bullet
            CHECK(finalScale < startingScale);
}

TEST_CASE ("Shooting a bullet fired from the centre scales up as it moves outwards")
{
    TextureHolder textures;
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto bulletShootAngle = 180;
    auto bulletStartingPoint = resolution.y / 2; //define the starting distance from centre;
    Bullet bullet(resolution,
                  bulletStartingPoint,
                  bulletShootAngle,
                  0.5,
                  entity::PlayerBullet,
                  textures,
                  textures::BulletPlayer);
    auto startingScale = bullet.getRadius();
    auto desiredBulletMove = 10;
    bullet.setMove(desiredBulletMove);
    bullet.update();
    auto finalScale = bullet.getRadius();
    // The position below if the original, +2 pixels due to the scaling of effect of the non-linear motion of the bullet
            CHECK(finalScale > startingScale);
}

////////////////////////////////////////////////////////////
///  Movement tests for Meteoroid
////////////////////////////////////////////////////////////

// Meteoroid unit tests
TEST_CASE ("Creating a meteoroid entity succeeds")
{
    TextureHolder textures;
    textures.load(textures::Meteoroid, "resources/meteoroid.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto meteoroidShootAngle = 180;
    auto meteoroidStartingPoint = resolution.y; // Define the starting distance from centre;
            CHECK_NOTHROW(
            Bullet meteoroid(resolution,
                          meteoroidStartingPoint,
                          meteoroidShootAngle,
                          0.5,
                          entity::Meteoroid,
                          textures,
                          textures::Meteoroid);
    );
}

TEST_CASE ("Shooting a meteoroid stright up moves corretly")
{
    TextureHolder textures;
    textures.load(textures::Meteoroid, "resources/meteoroid.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto meteoroidShootAngle = 180; // Meteoroid moves directly up
    auto meteoroidStartingPoint = resolution.y; //Define the starting distance from centre;
    Bullet meteoroid(resolution,
                  meteoroidStartingPoint,
                  meteoroidShootAngle,
                  0.5,
                  entity::Meteoroid,
                  textures,
                  textures::Meteoroid);
    auto startingPosition = meteoroid.getPosition();
    auto desiredMeteoroidMove = -1; // Move the meteoroid 2 pixels away from starting point, from point of fire
    meteoroid.setMove(desiredMeteoroidMove);
    meteoroid.update();
    auto finalPosition = meteoroid.getPosition();
    auto expectedMeteoroidMove = desiredMeteoroidMove * 2; // Double the desired move due to non-linear scaling at edge
    auto expectedPosition = sf::Vector2f(startingPosition.x, startingPosition.y - expectedMeteoroidMove);
            CHECK(round(finalPosition.x)==round(expectedPosition.x));
            CHECK(round(finalPosition.y)==round(expectedPosition.y));
}

TEST_CASE ("Shooting a meteoroid stright up causes them to scale down as they fly away")
{
    TextureHolder textures;
    textures.load(textures::Meteoroid, "resources/meteoroid.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto meteoroidShootAngle = 180;
    auto meteoroidStartingPoint = resolution.y; //define the starting distance from centre;
    Bullet meteoroid(resolution,
                  meteoroidStartingPoint,
                  meteoroidShootAngle,
                  0.5,
                  entity::Meteoroid,
                  textures,
                  textures::Meteoroid);
    auto startingScale = meteoroid.getRadius();
    auto desiredMeteoroidMove = -10;
    meteoroid.setMove(desiredMeteoroidMove);
    meteoroid.update();
    auto finalScale = meteoroid.getRadius();
    // The position below if the original, +2 pixles due to the scaling of effect of the non-linear motion of the meteoroid
            CHECK(finalScale < startingScale);
}

TEST_CASE ("Shooting a meteoroid fired from the centre scales up as it moves outwards")
{
    TextureHolder textures;
    textures.load(textures::Meteoroid, "resources/meteoroid.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto meteoroidShootAngle = 180;
    auto meteoroidStartingPoint = resolution.y / 2; //define the starting distance from centre;
    Bullet meteoroid(resolution,
                  meteoroidStartingPoint,
                  meteoroidShootAngle,
                  0.5,
                  entity::Meteoroid,
                  textures,
                  textures::Meteoroid);
    auto startingScale = meteoroid.getRadius();
    auto desiredMeteoroidMove = 10;
    meteoroid.setMove(desiredMeteoroidMove);
    meteoroid.update();
    auto finalScale = meteoroid.getRadius();
    // The position below if the original, +2 pixels due to the scaling of effect of the non-linear motion of the bullet
            CHECK(finalScale > startingScale);
}

////////////////////////////////////////////////////////////
///  Enemy Object Movement tests
////////////////////////////////////////////////////////////

TEST_CASE ("Creating an object enemy succeeds")
{
    TextureHolder textures;
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto resolution = sf::Vector2i{1920, 1080};
            CHECK_NOTHROW(
            Enemy enemy(resolution,
                        0,
                        0,
                        0.5,
                        entity::Basic,
                        textures,
                        textures::EnemyShipGrey,
                        MovementState::SpiralOut,
                        MovementDirection::Clockwise);
    );
}

TEST_CASE ("Basic enemy starts at centre of screen by default")
{

    TextureHolder textures;
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto resolution = sf::Vector2i{1920, 1080};
    Enemy enemy(resolution,
                0,
                0,
                0.5,
                entity::Basic,
                textures,
                textures::EnemyShipGrey,
                MovementState::SpiralOut,
                MovementDirection::Clockwise);
    enemy.update();
            CHECK(round(enemy.getPosition().x) == round(resolution.x / 2));
            CHECK(round(enemy.getPosition().y) == round(resolution.y / 2));
}

TEST_CASE ("Instructing a basic enemy to move positions the transformation(linear motion)")
{

    TextureHolder textures;
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto resolution = sf::Vector2i{1920, 1080};
    Enemy enemy(resolution,
                0,
                0,
                0.5,
                entity::Basic,
                textures,
                textures::EnemyShipGrey,
                MovementState::SpiralOut,
                MovementDirection::Clockwise);
    enemy.update();

    auto angleChange = 0;
    auto radiusChange = 10;
    enemy.setMove(angleChange, radiusChange);
    enemy.update();
    // Calculate the depth scale of the sprite to take int account non-linear scaling for predicted final position
    auto offset = resolution.x * 0.3; //offset due to ship starting at centre of the screen
    auto depthScale = (enemy.getDistanceFromCentre() + offset) / (resolution.x / 2);
    auto distanceFromCentre = radiusChange * depthScale;

    auto xPosExpected = distanceFromCentre * sin(common::degreeToRad(angleChange)) + (resolution.x / 2);
    auto yPosExpected = distanceFromCentre * cos(common::degreeToRad(angleChange)) + (resolution.y / 2);

            CHECK(round(enemy.getPosition().y)==round(yPosExpected));
            CHECK(round(enemy.getPosition().x)==round(xPosExpected));
}

TEST_CASE ("Instructing an enemy to move positions the transformation (angular motion included)")
{
    TextureHolder textures;
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto resolution = sf::Vector2i{1920, 1080};
    Enemy enemy(resolution,
                0,
                0,
                0.5,
                entity::Basic,
                textures,
                textures::EnemyShipGrey,
                MovementState::SpiralOut,
                MovementDirection::Clockwise);
    enemy.update();

    auto angleChange = 10;
    auto radiusChange = 10;
    enemy.setMove(angleChange, radiusChange);
    enemy.update();
    // Calculate the depth scale of the sprite to take int account non-linear scaling for predicted final position
    auto offset = resolution.x * 0.3; //offset due to ship starting at centre of the screen
    auto depthScale = (enemy.getDistanceFromCentre() + offset) / (resolution.x / 2);
    auto distanceFromCentre = radiusChange * depthScale;

    auto xPosExpected = distanceFromCentre * sin(common::degreeToRad(angleChange)) + (resolution.x / 2);
    auto yPosExpected = distanceFromCentre * cos(common::degreeToRad(angleChange)) + (resolution.y / 2);

            CHECK(round(enemy.getPosition().y)==round(yPosExpected));
            CHECK(round(enemy.getPosition().x)==round(xPosExpected));
}

TEST_CASE ("Enemy scale up as moving outwards away from ")
{

    TextureHolder textures;
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto resolution = sf::Vector2i{1920, 1080};
    Enemy enemy(resolution,
                0,
                0,
                0.5,
                entity::Basic,
                textures,
                textures::EnemyShipGrey,
                MovementState::SpiralOut,
                MovementDirection::Clockwise);
    enemy.update();
    enemy.reset();
    // Getting the actual size of ths ship sprite to check that it scaled.
    auto originalShipScale = enemy.getRadius();


    auto angleChange = 10;
    auto radiusChange = 100;
    enemy.setMove(angleChange, radiusChange);
    enemy.update();
    auto finalShipScale = enemy.getRadius();
            CHECK(finalShipScale > originalShipScale);

}

TEST_CASE ("Enemy scale down as it moves inwards towards centre")
{

    TextureHolder textures;
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto resolution = sf::Vector2i{1920, 1080};
    // Position the ship some distance away from the centre to start with
    auto startingShipRadius = resolution.y / 3;

    Enemy enemy(resolution,
                0,
                startingShipRadius,
                0.5,
                entity::Basic,
                textures,
                textures::EnemyShipGrey,
                MovementState::SpiralOut,
                MovementDirection::Clockwise);
    auto angleChange = 0;
    auto initialMove = -10;
    enemy.setMove(angleChange,-initialMove);
    enemy.update();
    auto originalShipSize = enemy.getRadius();
    auto radiusChange = -50; // Negative to move the ship inwards (towards centre)
    enemy.setMove(angleChange, radiusChange);
    enemy.update();
    auto finalShipSize = enemy.getRadius();
            CHECK(finalShipSize < originalShipSize);
}

TEST_CASE ("Killing the enemy ship resets the object")
{
    TextureHolder textures;
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto resolution = sf::Vector2i{1920, 1080};
    Enemy enemy(resolution,
                0,
                0,
                0.5,
                entity::Basic,
                textures,
                textures::EnemyShipGrey,
                MovementState::SpiralOut,
                MovementDirection::Clockwise);
    auto originalShipSize = enemy.getRadius();
    enemy.update();
    auto startingPosition = enemy.getPosition();
    auto startingAngle = enemy.getAngle();
    auto angleChange = 10;
    auto radiusChange = 10;
    enemy.setMove(angleChange, radiusChange); // Simulates the ship having moved away from the start
    enemy.update();

    enemy.die();

            CHECK(enemy.getLives() == 0);
            CHECK(enemy.getPosition() == startingPosition);
            CHECK(enemy.getAngle() == startingAngle);
}

////////////////////////////////////////////////////////////
///  Shield tests
////////////////////////////////////////////////////////////

TEST_CASE ("Shield Spawns at player ship location"){
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); //move playerShip to origin
    Shield shield(resolution, shipPathRadius, 0, shipScale, textures, playerShip);
    shield.update();
    auto endShipPosition = playerShip.getPosition();
    auto endShieldPosition = shield.getSprite().getPosition();
    CHECK(roundf(endShieldPosition.x)==roundf(endShieldPosition.x));
            CHECK(roundf(endShieldPosition.y)==roundf(endShieldPosition.y));
}


TEST_CASE ("Shield follows the player ship location"){
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    playerShip.update(); //move playerShip to origin
    Shield shield(resolution, shipPathRadius, 0, shipScale, textures, playerShip);
    shield.update();
    auto moveAngle = 90;
    playerShip.setMove(moveAngle);
    playerShip.update();
    shield.update();
    auto endShipPosition = playerShip.getPosition();
    auto endShieldPosition = shield.getSprite().getPosition();
            CHECK(roundf(endShieldPosition.x)==roundf(endShieldPosition.x));
            CHECK(roundf(endShieldPosition.y)==roundf(endShieldPosition.y));}

//This marks the end of the movement tests for all movable objects

////////////////////////////////////////////////////////////
///  Explosion tests
////////////////////////////////////////////////////////////

TEST_CASE("Explosion spawns at desired location")
{
    TextureHolder textures;
    textures.load(textures::Explosion, "resources/explosion.png");
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto resolution = sf::Vector2i{1920, 1080};
    auto spawnRadius = 100;
    auto spawnAngle = 100;
    auto spawnScale = 0.5;

    //will create a enemy ship to simulate the method used in the main game
    Enemy enemy(resolution,
                spawnRadius,
                spawnAngle,
                spawnScale,
                entity::Basic,
                textures,
                textures::EnemyShipGrey,
                MovementState::SpiralOut,
                MovementDirection::Clockwise);
    enemy.update();
//spawn the explosion at the location of the ship. can then check the location without needing to go via polar
    Explosion explosion{resolution,
                        enemy.getRadius(),
                        enemy.getAngle(),
                        enemy.getScale().x*2,
                        entity::Explosion,
                        textures,
                        textures::Explosion};


    CHECK(roundf(explosion.getPosition().x)==roundf(enemy.getPosition().x));
            CHECK(roundf(explosion.getPosition().y)==roundf(enemy.getPosition().y));
}


////////////////////////////////////////////////////////////
///  Collision detection tests
////////////////////////////////////////////////////////////

TEST_CASE("Two objects on top of each other report a collision")
{
    auto resolution = sf::Vector2i{1920, 1080};
    TextureHolder textures;

    sf::Sprite sprite1;
    sprite1.setPosition(10,10);

    sf::Sprite sprite2;
    sprite2.setPosition(10,10);
    // Each sprite needs a texture so it can have a size associated with it to simulate the collision detection

    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");
    sprite1.setTexture(textures.get(textures::EnemyShipGrey));
    sprite2.setTexture(textures.get(textures::EnemyShipGrey));

    // The EntityController requires the playerShip object as part of its constructor

    textures.load(textures::BulletPlayer, "resources/bullet_player.png");
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");

    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    // EntityController needs a score and speedModifier
    Score score;
    float speedModifier = 1;
    EntityController entityController(resolution,playerShip,textures,score,speedModifier);
    // We can now check that the two sprites, at the same location, return a collision
    CHECK(entityController.collides(sprite1,sprite2));
}

TEST_CASE("Two objects on that are not on top of each other do not report a collision"){
    auto resolution = sf::Vector2i{1920, 1080};
    TextureHolder textures;

    sf::Sprite sprite1;
    sprite1.setPosition(10,10);

    sf::Sprite sprite2;
    //set the second sprite far away from the first
    sprite2.setPosition(900,900);
    //each sprite needs a texture so it can have a size associated with it to simulate the collision detection
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");
    sprite1.setTexture(textures.get(textures::EnemyShipGrey));
    sprite2.setTexture(textures.get(textures::EnemyShipGrey));

    // The EntityController requires the playerShip object as part of its constructor so we have to substantiate one

    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");

    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    // Lastly, the EntityController needs a score and speedModifier
    Score score;
    float speedModifier = 1;
    EntityController entityController(resolution,playerShip,textures,score,speedModifier);
    // We can now check that the two sprites, at different locations, do not report true
            CHECK(!entityController.collides(sprite1,sprite2));
}

////////////////////////////////////////////////////////////
///  Score object tests
////////////////////////////////////////////////////////////

TEST_CASE("Score object correctly calculates game score for killing enemy")
{
    Score score;
    score.reset();
    //simulate killing 3 enemies and check reports the correct score
    score.incrementEnemiesKilled(entity::Basic);
    score.incrementEnemiesKilled(entity::Basic);
    score.incrementEnemiesKilled(entity::Satellite);
    auto expectedScore = 500*3; //500 for basic and 150 for satellite
    CHECK(expectedScore==score.getScore());
}

TEST_CASE("Score object correctly calculates records number of enemies killed")
{
    Score score;
    score.reset();
    //simulate killing 3 enemies and check reports the correct score
    score.incrementEnemiesKilled(entity::Basic);
    score.incrementEnemiesKilled(entity::Basic);
    score.incrementEnemiesKilled(entity::Satellite);
    auto expectedNumberOfEnemies =3;
    CHECK(expectedNumberOfEnemies==score.getEnemiesKilled());
}

TEST_CASE("Score object correctly counts the number of bullets fired")
{
    Score score;
    score.reset();
    auto expectedBullets=0;
    for(int i =0; i<10;i++){
        score.incrementBulletsFired();
        expectedBullets++;
    }
    CHECK(expectedBullets==score.getBulletsFired());
}

TEST_CASE("Score object correctly calculates player accuracy")
{
    Score score;
    score.reset();
    auto bulletesFired=0.0f;
    //loop used to simulate shooting 5 bullets
    for(int i =0; i<5;i++){
        score.incrementBulletsFired();
        bulletesFired++;
    }
    auto enemiesHit=0.0f;
    for(int i =0; i<5;i++){
        score.incrementBulletsFired();
        score.incrementEnemiesKilled(entity::Satellite);
        bulletesFired++;
        enemiesHit++;
    }
    //accuracy is defines as hits/shotsfired
    auto expectedAccuracy = enemiesHit/bulletesFired;
            CHECK(expectedAccuracy==score.getPlayerAccuracy());
}

TEST_CASE("Score object correctly recoreds player life length")
{
    sf::Clock testClock;
    Score score;
    score.reset();
    testClock.restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); //put the sleep in a thread to not slow down tests
    auto playerLife = score.getTimeAlive();
    auto expectedLife = testClock.getElapsedTime().asSeconds();
            CHECK((roundf(playerLife * 1000) / 1000)==(roundf(expectedLife * 1000) / 1000));
}

TEST_CASE("Score object correctly recoreds longest player life length")
{
    sf::Clock testClock;
    Score score;
    score.reset();
    testClock.restart();
    auto longestMeasuredLife = 0.0f;
    //create a score object, kill the player 3 times with 3 diffrent delays between them
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    score.resetLifeTimer();
    if(testClock.getElapsedTime().asSeconds()>longestMeasuredLife)
        longestMeasuredLife = testClock.getElapsedTime().asSeconds();
    testClock.restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    score.resetLifeTimer();
    if(testClock.getElapsedTime().asSeconds()>longestMeasuredLife)
        longestMeasuredLife = testClock.getElapsedTime().asSeconds();
    testClock.restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    score.resetLifeTimer();
    if(testClock.getElapsedTime().asSeconds()>longestMeasuredLife)
        longestMeasuredLife = testClock.getElapsedTime().asSeconds();
    testClock.restart();

    auto longestCalculatedPlayerLife = score.getLongestTimeAlive();
    //rounding is done to 3 decimal places
            CHECK((roundf(longestCalculatedPlayerLife * 1000) / 1000)==(roundf(longestMeasuredLife * 1000) / 1000));
}

////////////////////////////////////////////////////////////
///  Common functions tests
////////////////////////////////////////////////////////////

TEST_CASE("Angle filter correctly casts angles to correct quadrent (incrementing over 360 degrees)")
{
    auto inputAngle = 300;
    auto incrementAngle = 100;
    auto expectedCastAngle = inputAngle+incrementAngle-360; //put into correct quad by -360 as positive
    CHECK(common::angleFilter(inputAngle+incrementAngle)==expectedCastAngle);
}

TEST_CASE("Angle filter correctly casts angles to correct quadrent (decrement angle bellow 0)")
{
    auto inputAngle = 100;
    auto incrementAngle = 200;
    auto expectedCastAngle = inputAngle-incrementAngle+360; // put into correct quad by + 360 as negative
            CHECK(common::angleFilter(inputAngle-incrementAngle)==expectedCastAngle);
}

TEST_CASE("Degrees to Radian conversion is correct")
{
    auto inputDegree = 90;
    auto expectedRadian=inputDegree*(M_PI/180);
    CHECK(roundf(common::degreeToRad(inputDegree)*1000)/1000==roundf(expectedRadian*1000)/1000);
}

TEST_CASE("Radian to Degrees conversion is correct")
{
    auto inputRadian = M_PI/2;
    auto expectedDegree=inputRadian*(180/M_PI);
            CHECK(round(common::radToDegree(inputRadian)*1000)/1000==round(expectedDegree*1000)/1000);
}

TEST_CASE("String padding correctly appends chars to an integer")
{
    auto inputInt = 10;
    auto desiredStringLength = 3;
    auto expectedString = " 10"; //space at the start of the string
    auto charPadding = ' ';
    CHECK(common::padIntToString(inputInt,desiredStringLength,charPadding)==expectedString);
}

////////////////////////////////////////////////////////////
///  Entity controller tests
////////////////////////////////////////////////////////////

TEST_CASE("Calling spawn basic enemy generates an enemy ship in the defined spawn type")
{
    TextureHolder textures;
    auto resolution = sf::Vector2i{1920, 1080};
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    // Lastly, the EntityController needs a score and speedModifier
    Score score;
    float speedModifier = 1;
    EntityController entityController(resolution,playerShip,textures,score,speedModifier);
    //create an arbitary kind of enemy ship, using the entity controller

    auto enemySpawnType = entity::Basic;
    entityController.spawnBasicEnemy(enemySpawnType,textures::EnemyShipGrey,MovementDirection::Clockwise,MovementState::SpiralOut);
    //Only one enemy was spawned but the function returns a vector. this Provides a more logical method of itteration
    for(auto &enemy : entityController.getEnemies()){
        CHECK(enemySpawnType==enemy->getType());
    }
}

TEST_CASE("Calling spawn basic enemy generates an enemy ship in the defined movement direction")
{
    TextureHolder textures;
    auto resolution = sf::Vector2i{1920, 1080};
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    // Lastly, the EntityController needs a score and speedModifier
    Score score;
    float speedModifier = 1;
    EntityController entityController(resolution,playerShip,textures,score,speedModifier);
    //create an arbitary kind of enemy ship, using the entity controller

    auto enemyMoveDirection = MovementDirection::Clockwise;
    entityController.spawnBasicEnemy(entity::Basic,textures::EnemyShipGrey,enemyMoveDirection,MovementState::SpiralOut);
    //Only one enemy was spawned but the function returns a vector. this Provides a more logical method of itteration
    for(auto &enemy : entityController.getEnemies()){
        //clockwise rotation is represented by a +1 multiplier on direction sign
                CHECK(enemy->getMovementDirectionSign()==+1);
    }
}

TEST_CASE("Calling spawn basic enemy generates an enemy ship in the defined movement State")
{
    TextureHolder textures;
    auto resolution = sf::Vector2i{1920, 1080};
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    // Lastly, the EntityController needs a score and speedModifier
    Score score;
    float speedModifier = 1;
    EntityController entityController(resolution,playerShip,textures,score,speedModifier);
    //create an arbitary kind of enemy ship, using the entity controller

    auto enemyMoveState = MovementState::SpiralOut;
    entityController.spawnBasicEnemy(entity::Basic,textures::EnemyShipGrey,MovementDirection::Clockwise,enemyMoveState);
    //Only one enemy was spawned but the function returns a vector. this Provides a more logical method of itteration
    for(auto &enemy : entityController.getEnemies()){
                CHECK(enemy->getMovementState()==enemyMoveState);
    }
}

TEST_CASE("Calling spawn spawnSatellites correctly spawns 3 enemies of the right type")
{
    TextureHolder textures;
    auto resolution = sf::Vector2i{1920, 1080};
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::Satellite, "resources/satellite.png");

    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    // Lastly, the EntityController needs a score and speedModifier
    playerShip.update();
    Score score;
    float speedModifier = 1;
    EntityController entityController(resolution,playerShip,textures,score,speedModifier);
    //create an arbitary kind of enemy ship, using the entity controller

    auto enemyType = entity::Satellite;
    auto enemyMoveState = MovementState::SmallCircling;
    auto ExpectedAngle = playerShip.getAngle()+180;

    entityController.spawnSatellites();
    //Only one enemy was spawned but the function returns a vector. this Provides a more logical method of itteration
auto numberOfShipsSpawned = 0;
    for(auto &enemy : entityController.getEnemies()){
        numberOfShipsSpawned++;
        CHECK(enemy->getType()==enemyType);
        CHECK(enemy->getMovementState()==enemyMoveState);
        CHECK(enemy->getAngle()>ExpectedAngle-90); //Satellites spawn in a random range opposite the player
        CHECK(enemy->getAngle()<ExpectedAngle+90);
    }
    CHECK(numberOfShipsSpawned==3); //should spawn 3 satellites
}

TEST_CASE("Calling spawn Meteorid actually spawns a meteorid")
{
    TextureHolder textures;
    auto resolution = sf::Vector2i{1920, 1080};
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    // Lastly, the EntityController needs a score and speedModifier
    Score score;
    float speedModifier = 1;
    EntityController entityController(resolution,playerShip,textures,score,speedModifier);
    //create an arbitary kind of enemy ship, using the entity controller

    entityController.spawnMeteoroid();
    //Only one enemy was spawned but the function returns a vector. this Provides a more logical method of itteration
    auto numberOfMeteoroidsSpawned=0;
    for(auto &meteoroid : entityController.getMeteoroids()){
                numberOfMeteoroidsSpawned++;
    }
    CHECK(numberOfMeteoroidsSpawned==1);
}

TEST_CASE("Calling killAllEnemiesOfType removes all of that type")
{
    TextureHolder textures;
    auto resolution = sf::Vector2i{1920, 1080};
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");
    textures.load(textures::Satellite, "resources/satellite.png");

    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    // Lastly, the EntityController needs a score and speedModifier
    Score score;
    float speedModifier = 1;
    EntityController entityController(resolution,playerShip,textures,score,speedModifier);
    //create an arbitary kind of enemy ship, using the entity controller
    entityController.spawnSatellites();
    entityController.spawnBasicEnemy(entity::Basic,textures::EnemyShipGrey,MovementDirection::Clockwise,MovementState::SpiralOut);
    auto numberOfEnemiesSpawned = 0;
    for(auto &enemy : entityController.getEnemies()){
        numberOfEnemiesSpawned++;
    }
    CHECK(numberOfEnemiesSpawned==4); //should have spawned one basic and one satellite
    //now kill all type satellite
    entityController.killAllEnemiesOfType(entity::Satellite);
    auto numberOfEnemiesLeft = 0;
    for(auto &enemy : entityController.getEnemies()){
        numberOfEnemiesLeft++;
        CHECK(enemy->getType()!=entity::Satellite); //verify no satellits are left
    }
            CHECK(numberOfEnemiesLeft==1); //should have spawned one basic and one satellite
}