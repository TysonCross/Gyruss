//--------------------------------------------------------------------------
// Students 1239448 & 1109146
// @date    2017/09/10
// @brief   Unit test for game
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "../game-source-code/common.hpp"
#include "../game-source-code/Bullet.hpp"
#include "../game-source-code/Enemy.hpp"
#include "../game-source-code/Entity.hpp"
#include "../game-source-code/EntityController.hpp"
#include "../game-source-code/Explosion.hpp"
#include "../game-source-code/FPS.hpp"
#include "../game-source-code/Game.hpp"
#include "../game-source-code/InputHandler.hpp"
#include "../game-source-code/PlayerShip.hpp"
#include "../game-source-code/ResourceHolder.hpp"
#include "../game-source-code/Screen.hpp"
#include "../game-source-code/ScreenGameOver.hpp"
#include "../game-source-code/ScreenSplash.hpp"
#include "../game-source-code/SoundController.hpp"
#include "../game-source-code/Starfield.hpp"


#include <iostream>
#include "doctest.h"

TEST_CASE ("Loading a missing file into a resourceHandler<sf::Texture, textures::ID> throws an exception") {
    TextureHolder texture_holder;

            CHECK_THROWS(texture_holder.load(textures::testTexture, "resources/NO_IMAGE"));
}

TEST_CASE ("Loading a texure that exists into a resourceHandler<sf::Texture, textures::ID> succeeds") {
    TextureHolder texture_holder;
            CHECK_NOTHROW(texture_holder.load(textures::testTexture, "resources/test_image.png"));

}

TEST_CASE (
        "Getting a texture previously loaded into a resourceHandler<sf::Texture, textures::ID> succeeds (i.e. does not throw an exception)") {
    TextureHolder texture_holder;
            REQUIRE_NOTHROW(texture_holder.load(textures::testTexture, "resources/test_image.png"));

    sf::Sprite elf;
            CHECK_NOTHROW(elf.setTexture(texture_holder.get(textures::testTexture)));
}

//Check SoundHolder
TEST_CASE ("Loading a missing file into a resourceHandler<sf::SoundBuffer, sounds::ID> throws an exception") {
    SoundHolder sound_holder;

            CHECK_THROWS(sound_holder.load(sounds::testSound, "resources/NO_IMAGE"));
}

TEST_CASE (
        "Loading a sound buffer from a file that exists into a resourceHandler<sf::SoundBuffer, sounds::ID> succeeds (i.e. does not throw an exception)") {
    SoundHolder sound_holder;
            REQUIRE_NOTHROW(sound_holder.load(sounds::testSound, "resources/test.ogg"));

    sf::Sound testSound;
            CHECK_NOTHROW(testSound.setBuffer(sound_holder.get(sounds::testSound)));
}


TEST_CASE (
        "Playing a sound previously loaded into a resourceHandler<sf::SoundBuffer, sounds::ID> succeeds (i.e. does not throw an exception)") {
    SoundHolder sound_holder;
            REQUIRE_NOTHROW(sound_holder.load(sounds::testSound, "resources/test.ogg"));

    sf::Sound testSound;
            REQUIRE_NOTHROW(testSound.setBuffer(sound_holder.get(sounds::testSound)));
            CHECK_NOTHROW(testSound.play());
}

// Check FontHolder
TEST_CASE ("Loading a missing file into a resourceHandler<sf::Font, fonts::ID> throws an exception") {
    FontHolder font_holder;

            CHECK_THROWS(font_holder.load(fonts::testFont, "resources/NO_FONT"));
}

TEST_CASE ("Loading a font that exists into a resourceHandler<sf::Font, fonts::ID> succeeds") {
    FontHolder font_holder;
            CHECK_NOTHROW(font_holder.load(fonts::testFont, "resources/danube.ttf"));

}

TEST_CASE (
        "Getting a font previously loaded into a resourceHandler<sf::Font, fonts::ID> succeeds (i.e. does not throw an exception)") {
    FontHolder font_holder;
            REQUIRE_NOTHROW(font_holder.load(fonts::testFont, "resources/danube.ttf"));
            CHECK_NOTHROW(sf::Text text_test("TEST", font_holder.get(fonts::testFont)));
}

////////////////////////////////////////////////////////////
///  Movement tests
////////////////////////////////////////////////////////////

//PlayerShip movement tests

TEST_CASE ("Creating A PlayerShip object succeeds") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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

//Check rotation works with .setMove & .update
TEST_CASE ("Moving a PlayerShip 10 degrees succeeds") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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

TEST_CASE ("PlayerShip getPosition and underlying transformation both return the same location correctly") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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

//tets holding down move button
TEST_CASE ("Moving a PlayerShip multiple times succeeds") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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

//correct circle imlemented
TEST_CASE ("Moving a PlayerShip 360 degrees brings ship back to where it started") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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


//Check eular function
TEST_CASE ("Moving a PlayerShip -10 degrees correctly casts to 350 and succeeds") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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
    auto moveAngle = -10.0f;
    auto expectedFinalAngle = 350.0f; //using the eular filter to cast negative angle to <360
    playerShip.setMove(moveAngle);
    playerShip.update();
    auto finalAngle = playerShip.getAngle();
            CHECK(finalAngle == expectedFinalAngle);
}

TEST_CASE ("Moving a PlayerShip moves the sprite the correct number of pixels (flip 180)") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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
    auto originalLocation = playerShip.getPosition();
    auto moveAngle = 180;
    playerShip.setMove(moveAngle);
    playerShip.update();
    auto finalLocation = playerShip.getPosition();
    auto expectedLocation = sf::Vector2f{originalLocation.x, resolution.y * shipPathRadiusPadding};
            CHECK(int(finalLocation.y)==int(expectedLocation.y)); //cast to int to get closest pixel accuracy
            CHECK(int(finalLocation.x)==int(expectedLocation.x)); //cast to int to get closest pixel accuracy
}

TEST_CASE ("Reseting ship position brings the ship back to spawning point sucessfully") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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
    auto originalLocation = playerShip.getPosition();
    auto moveAngle = 180;
    playerShip.setMove(moveAngle);
    playerShip.update();
    playerShip.reset();
    playerShip.update();
    auto finalLocation = playerShip.getPosition();
            CHECK(int(finalLocation.x)==int(originalLocation.x)); //cast to int to get closest pixel accuracy
            CHECK(int(finalLocation.y)==int(originalLocation.y)); //cast to int to get closest pixel accuracy
}

TEST_CASE ("Killing the playerShip decrements a life") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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
    auto startingLives = playerShip.getLives();
    auto startingPosition = playerShip.getPosition();

    auto moveShipAmount = 90; //move the ship to simulate player interaction
    playerShip.setMove(moveShipAmount);
    playerShip.update();

    playerShip.die();
    playerShip.update();

            CHECK(playerShip.getLives() == startingLives - 1);
}

TEST_CASE ("Killing the playerShip resets the ship location to centre") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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
    auto startingLives = playerShip.getLives();
    auto startingPosition = playerShip.getPosition();

    auto moveShipAmount = 90; //move the ship to simulate player interaction
    playerShip.setMove(moveShipAmount);
    playerShip.update();

    playerShip.die();
    playerShip.update();

            CHECK(playerShip.getAngle() == 0);
            CHECK(playerShip.getFutureAngle() == 0);
            CHECK(playerShip.isShooting() == false);
            CHECK(playerShip.isMoving() == false);
            CHECK(playerShip.getPosition().x == startingPosition.x);
            CHECK(playerShip.getPosition().y == startingPosition.y);
}

TEST_CASE ("Killing the playerShip makes the ship Invulnerable") {
    TextureHolder textures;
    textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound, "resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove, "resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot, "resources/shoot_laser.ogg");

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
    auto startingLives = playerShip.getLives();
    auto startingPosition = playerShip.getPosition();

    auto moveShipAmount = 90; //move the ship to simulate player interaction
    playerShip.setMove(moveShipAmount);
    playerShip.update();

    playerShip.die();
    playerShip.update();

            CHECK(playerShip.isInvulnerable() == true);
}

// Bullet movement tests

TEST_CASE ("Creating a bullet entity succeeds") {
    TextureHolder textures;
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;

    auto resolution = sf::Vector2i{1920, 1080};
    auto bulletShootAngle = 180;
    auto bulletStartingPoint = resolution.y; //define the starting distance from centre;
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

TEST_CASE ("Shooting a bullet stright up moves corretly") {
    TextureHolder textures;
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;

    auto resolution = sf::Vector2i{1920, 1080};
    auto bulletShootAngle = 180; //bullet moves directly up
    auto bulletStartingPoint = resolution.y; //define the starting distance from centre;
    Bullet bullet(resolution,
                  bulletStartingPoint,
                  bulletShootAngle,
                  0.5,
                  entity::PlayerBullet,
                  textures,
                  textures::BulletPlayer);
    auto startingPosition = bullet.getPosition();
    auto desiredBulletMove = -1; //move the bullet 2 pixels away from starting point, from point of fire
    bullet.setMove(desiredBulletMove);
    bullet.update();
    auto finalPosition = bullet.getPosition();
    auto expectedBulletMove = desiredBulletMove * 2; //double the desired move due to non-linear scaling at edg
    auto expectedPosition = sf::Vector2f(startingPosition.x, startingPosition.y - expectedBulletMove);
            CHECK(int(finalPosition.x)==int(expectedPosition.x));
            CHECK(int(finalPosition.y)==int(expectedPosition.y));
}

TEST_CASE ("Shooting a bullet stright up causes them to scale down as they fly away") {
    TextureHolder textures;
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;

    auto resolution = sf::Vector2i{1920, 1080};
    auto bulletShootAngle = 180;
    auto bulletStartingPoint = resolution.y; //define the starting distance from centre;
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
    //the position below if the original, +2 pixles due to the scaling of effect of the non-linear motion of the bullet
            CHECK(finalScale < startingScale);
}

TEST_CASE ("Shooting a bullet fired from the centre scales up as it moves outwards") {
    TextureHolder textures;
    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    SoundHolder sounds;

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
    //the position below if the original, +2 pixels due to the scaling of effect of the non-linear motion of the bullet
            CHECK(finalScale > startingScale);
}

//Meteoride unit tests

TEST_CASE ("Creating a meteoroid entity succeeds") {
    TextureHolder textures;
    textures.load(textures::Meteoroid, "resources/meteoroid.png");
    SoundHolder sounds;

    auto resolution = sf::Vector2i{1920, 1080};
    auto meteoroidShootAngle = 180;
    auto meteoroidStartingPoint = resolution.y; //define the starting distance from centre;
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

TEST_CASE ("Shooting a meteoroid stright up moves corretly") {
    TextureHolder textures;
    textures.load(textures::Meteoroid, "resources/meteoroid.png");
    SoundHolder sounds;

    auto resolution = sf::Vector2i{1920, 1080};
    auto meteoroidShootAngle = 180; //meteoroid moves directly up
    auto meteoroidStartingPoint = resolution.y; //define the starting distance from centre;
    Bullet meteoroid(resolution,
                  meteoroidStartingPoint,
                  meteoroidShootAngle,
                  0.5,
                  entity::Meteoroid,
                  textures,
                  textures::Meteoroid);
    auto startingPosition = meteoroid.getPosition();
    auto desiredMeteoroidMove = -1; //move the meteoroid 2 pixels away from starting point, from point of fire
    meteoroid.setMove(desiredMeteoroidMove);
    meteoroid.update();
    auto finalPosition = meteoroid.getPosition();
    auto expectedMeteoroidMove = desiredMeteoroidMove * 2; //double the desired move due to non-linear scaling at edg
    auto expectedPosition = sf::Vector2f(startingPosition.x, startingPosition.y - expectedMeteoroidMove);
            CHECK(int(finalPosition.x)==int(expectedPosition.x));
            CHECK(int(finalPosition.y)==int(expectedPosition.y));
}

TEST_CASE ("Shooting a meteoroid stright up causes them to scale down as they fly away") {
    TextureHolder textures;
    textures.load(textures::Meteoroid, "resources/meteoroid.png");
    SoundHolder sounds;

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
    //the position below if the original, +2 pixles due to the scaling of effect of the non-linear motion of the meteoroid
            CHECK(finalScale < startingScale);
}

TEST_CASE ("Shooting a meteoroid fired from the centre scales up as it moves outwards") {
    TextureHolder textures;
    textures.load(textures::Meteoroid, "resources/meteoroid.png");
    SoundHolder sounds;

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
    //the position below if the original, +2 pixels due to the scaling of effect of the non-linear motion of the bullet
            CHECK(finalScale > startingScale);
}

//Enemy Unit tests

TEST_CASE ("Creating an object enemy succeeds") {

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

TEST_CASE ("Basic enemy starts at centre of screen by default") {

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
            CHECK(enemy.getPosition().x == resolution.x / 2);
            CHECK(enemy.getPosition().y == resolution.y / 2);
}

TEST_CASE ("Instructing a basic enemy to move positions the transformation(linear motion)") {

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
// calculate the depth scale of the sprite to take int account non-linear scaling for predicted final position
    auto offset = resolution.x * 0.3; //offset due to ship starting at centre of the screen
    auto depthScale = (enemy.getDistanceFromCentre() + offset) / (resolution.x / 2);
    auto distanceFromCentre = radiusChange * depthScale;

    auto xPosExpected = distanceFromCentre * sin(common::degreeToRad(angleChange)) + (resolution.x / 2);
    auto yPosExpected = distanceFromCentre * cos(common::degreeToRad(angleChange)) + (resolution.y / 2);

            CHECK(int(enemy.getPosition().y)==int(yPosExpected));
            CHECK(int(enemy.getPosition().x)==int(xPosExpected));
}

TEST_CASE ("Instructing an enemy to move positions the transformation(angular motion included)") {

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
// calculate the depth scale of the sprite to take int account non-linear scaling for predicted final position
    auto offset = resolution.x * 0.3; //offset due to ship starting at centre of the screen
    auto depthScale = (enemy.getDistanceFromCentre() + offset) / (resolution.x / 2);
    auto distanceFromCentre = radiusChange * depthScale;

    auto xPosExpected = distanceFromCentre * sin(common::degreeToRad(angleChange)) + (resolution.x / 2);
    auto yPosExpected = distanceFromCentre * cos(common::degreeToRad(angleChange)) + (resolution.y / 2);

            CHECK(int(enemy.getPosition().y)==int(yPosExpected));
            CHECK(int(enemy.getPosition().x)==int(xPosExpected));
}

TEST_CASE ("Enemy scale up as moving outwards") {

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
    //getting the actual size of ths ship sprite to check that it scaled. looking at underlying sprite
    auto originalShipScale = enemy.getRadius();


    auto angleChange = 10;
    auto radiusChange = 100;
    enemy.setMove(angleChange, radiusChange);
    enemy.update();
    auto finalShipScale = enemy.getRadius();
            CHECK(finalShipScale > originalShipScale);

}

TEST_CASE ("Enemy scale down as moving inwards") {

    TextureHolder textures;
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");

    auto resolution = sf::Vector2i{1920, 1080};
    //position the ship some distance away from the centre to start with
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
    auto radiusChange = -50; //negative to move the ship inwards(towards centre) to check it gets smaller
    enemy.setMove(angleChange, radiusChange);
    enemy.update();
    auto finalShipSize = enemy.getRadius();
            CHECK(finalShipSize < originalShipSize);
}

TEST_CASE ("killing the enemy ship resets the object") {

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
    enemy.setMove(angleChange, radiusChange); //simulates the ship having moved away from the start
    enemy.update();

    enemy.die();

            CHECK(enemy.getLives() == 0);
            CHECK(enemy.getPosition() == startingPosition);
            CHECK(enemy.getAngle() == startingAngle);
}

////////////////////////////////////////////////////////////
///  Collision detection tests
////////////////////////////////////////////////////////////

TEST_CASE("two objects on top of each other report a collision"){
    auto resolution = sf::Vector2i{1920, 1080};
    TextureHolder textures;

    sf::Sprite sprite1;
    sprite1.setPosition(10,10);

    sf::Sprite sprite2;
    sprite2.setPosition(10,10);
    //each sprite needs a texture so it can have a size associated with it to simulate the collision detection
    textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");
    sprite1.setTexture(textures.get(textures::EnemyShipGrey));
    sprite2.setTexture(textures.get(textures::EnemyShipGrey));

    //The EntityController requires the playership object as part of its constructor so we have to make one

    textures.load(textures::BulletPlayer, "resources/bullet_player.png");

    auto shipPathRadiusPadding = 0.05f;
    auto shipScale = 1;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          textures);
    //Lastly, the EntityController needs a score and speedModifier
    Score score;
    float speedModifier = 1;
    EntityController entityController(resolution,playerShip,textures,score,speedModifier);
//we can now check that the two sprites, at the same location, return a collision
    CHECK(entityController.collides(sprite1,sprite2));
}

TEST_CASE("two objects on that are not on top of eachother do not report a collission"){
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

    //The EntityController requires the playership object as part of its constructor so we have to make one

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
    //Lastly, the EntityController needs a score and speedModifier
    Score score;
    float speedModifier = 1;
    EntityController entityController(resolution,playerShip,textures,score,speedModifier);
//we can now check that the two sprites, at diffrent locations, do not report true
            CHECK(!entityController.collides(sprite1,sprite2));
}
