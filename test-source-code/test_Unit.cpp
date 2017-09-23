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

TEST_CASE ("Loading a missing file into a resourceHandler<sf::Texture, textures::ID> throws an exception")
{
    TextureHolder texture_holder;

    CHECK_THROWS(texture_holder.load(textures::testTexture,"resources/NO_IMAGE"));
}

TEST_CASE ("Loading a texure that exists into a resourceHandler<sf::Texture, textures::ID> succeeds")
{
    TextureHolder texture_holder;
            CHECK_NOTHROW(texture_holder.load(textures::testTexture,"resources/test_image.png"));

}

TEST_CASE ("Getting a texture previously loaded into a resourceHandler<sf::Texture, textures::ID> succeeds (i.e. does not throw an exception)")
{
    TextureHolder texture_holder;
    REQUIRE_NOTHROW(texture_holder.load(textures::testTexture,"resources/test_image.png"));

    sf::Sprite elf;
    CHECK_NOTHROW(elf.setTexture(texture_holder.get(textures::testTexture)));
}

//Check SoundHolder
TEST_CASE ("Loading a missing file into a resourceHandler<sf::SoundBuffer, sounds::ID> throws an exception")
{
    SoundHolder sound_holder;

            CHECK_THROWS(sound_holder.load(sounds::testSound,"resources/NO_IMAGE"));
}

TEST_CASE ("Loading a sound buffer from a file that exists into a resourceHandler<sf::SoundBuffer, sounds::ID> succeeds (i.e. does not throw an exception)")
{
    SoundHolder sound_holder;
            REQUIRE_NOTHROW(sound_holder.load(sounds::testSound,"resources/win_sound.ogg"));

    sf::Sound testSound;
            CHECK_NOTHROW(testSound.setBuffer(sound_holder.get(sounds::testSound)));
}


TEST_CASE ("Playing a sound previously loaded into a resourceHandler<sf::SoundBuffer, sounds::ID> succeeds (i.e. does not throw an exception)")
{
    SoundHolder sound_holder;
            REQUIRE_NOTHROW(sound_holder.load(sounds::testSound,"resources/win_sound.ogg"));

    sf::Sound testSound;
            REQUIRE_NOTHROW(testSound.setBuffer(sound_holder.get(sounds::testSound)));
            CHECK_NOTHROW(testSound.play());
}

// Check FontHolder
TEST_CASE ("Loading a missing file into a resourceHandler<sf::Font, fonts::ID> throws an exception")
{
    FontHolder font_holder;

            CHECK_THROWS(font_holder.load(fonts::testFont,"resources/NO_FONT"));
}

TEST_CASE ("Loading a font that exists into a resourceHandler<sf::Font, fonts::ID> succeeds")
{
    FontHolder font_holder;
            CHECK_NOTHROW(font_holder.load(fonts::testFont,"resources/danube.ttf"));

}

TEST_CASE ("Getting a font previously loaded into a resourceHandler<sf::Font, fonts::ID> succeeds (i.e. does not throw an exception)")
{
    FontHolder font_holder;
            REQUIRE_NOTHROW(font_holder.load(fonts::testFont,"resources/danube.ttf"));
            CHECK_NOTHROW(sf::Text text_test("TEST", font_holder.get(fonts::testFont)));
}

////////////////////////////////////////////////////////////
///  Movement tests
////////////////////////////////////////////////////////////

//PlayerShip movement tests

TEST_CASE ("Creating A PlayerShip object succeeds")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip,"resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound,"resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove,"resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot,"resources/shoot_laser.ogg");

    common::Resolution resolution = {1920,1080};
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    CHECK_NOTHROW(PlayerShip playerShip(textures, sounds, resolution, shipPathRadius, 0, 0.35););
}

//Check rotation works with .setMove & .update
TEST_CASE ("Moving a PlayerShip 10 degrees succeeds")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip,"resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound,"resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove,"resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot,"resources/shoot_laser.ogg");

    common::Resolution resolution = {1920,1080};
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(textures, sounds, resolution, shipPathRadius, 0, 0.35);
    auto originalAngle = playerShip.getAngle();
    auto moveAngle = 10.0f;
    playerShip.setMove(moveAngle);
    playerShip.update();
    auto finalAngle = playerShip.getAngle();
            CHECK(finalAngle == moveAngle);
}

//tets holding down move button
TEST_CASE ("Moving a PlayerShip multiple times succeeds")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip,"resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound,"resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove,"resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot,"resources/shoot_laser.ogg");

    common::Resolution resolution = {1920,1080};
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(textures, sounds, resolution, shipPathRadius, 0, 0.35);
    auto originalAngle = playerShip.getAngle();
    auto moveAngle = 10.0f; //define to move the ship 10 degrees
    for (auto i =0; i<5;i++)
    {
        playerShip.setMove(moveAngle);
        playerShip.update();
    }
    auto expectedAngle = moveAngle*5;
    auto finalAngle = playerShip.getAngle();
            CHECK(finalAngle == expectedAngle);
}

//correct circle imlemented
TEST_CASE ("Moving a PlayerShip 360 degrees brings ship back to where it started")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip,"resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound,"resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove,"resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot,"resources/shoot_laser.ogg");

    common::Resolution resolution = {1920,1080};
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(textures, sounds, resolution, shipPathRadius, 0, 0.35);
    auto originalAngle = playerShip.getAngle();
    auto originalPosition = playerShip.getSprite().getPosition();
    auto moveAngle = 45.0f; //define to move the ship 10 degrees
    for (auto i =0; i<8;i++)
    {
        playerShip.setMove(moveAngle);
        playerShip.update();
    }
    auto finalAngle = playerShip.getAngle();
    auto finalPosition = playerShip.getSprite().getPosition();
            CHECK(finalAngle == originalAngle);
            CHECK(finalPosition == originalPosition);
}


//Check eular function
TEST_CASE ("Moving a PlayerShip -10 degrees correctly casts to 350 and succeeds")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip,"resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound,"resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove,"resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot,"resources/shoot_laser.ogg");

    common::Resolution resolution = {1920,1080};
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(textures, sounds, resolution, shipPathRadius, 0, 0.35);
    auto originalAngle = playerShip.getAngle();
    auto moveAngle = -10.0f;
    auto expectedFinalAngle= 350.0f; //using the eular filter to cast negative angle to <360
    playerShip.setMove(moveAngle);
    playerShip.update();
    auto finalAngle = playerShip.getAngle();
            CHECK(finalAngle == expectedFinalAngle);
}

TEST_CASE ("Moving a PlayerShip moves the sprit the correct number of pixles (flip 180)")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip,"resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound,"resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove,"resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot,"resources/shoot_laser.ogg");

    common::Resolution resolution ={1920,1080};
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(textures, sounds, resolution, shipPathRadius, 0, 0.35);
    auto originalLocation = playerShip.getSprite().getPosition();
    auto moveAngle = 180;
    playerShip.setMove(moveAngle);
    playerShip.update();
    auto finalLocation = playerShip.getSprite().getPosition();
    auto expectedLocation = sf::Vector2f{originalLocation.x, resolution.y*shipPathRadiusPadding};
            CHECK(int(finalLocation.y)==int(expectedLocation.y)); //cast to int to get closest pixel accuracy
            CHECK(int(finalLocation.x)==int(expectedLocation.x)); //cast to int to get closest pixel accuracy
}

TEST_CASE ("Reseting ship position brings the ship back to spawning point sucessfully")
{
    TextureHolder textures;
    textures.load(textures::PlayerShip,"resources/player_ship_animated.png");
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;
    sounds.load(sounds::SpawnSound,"resources/ship_spawn.ogg");
    sounds.load(sounds::PlayerMove,"resources/thrust.ogg");
    sounds.load(sounds::PlayerShoot,"resources/shoot_laser.ogg");

    common::Resolution resolution ={1920,1080};
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(textures, sounds, resolution, shipPathRadius, 0, 0.35);
    auto originalLocation = playerShip.getSprite().getPosition();
    auto moveAngle = 180;
    playerShip.setMove(moveAngle);
    playerShip.update();
    playerShip.reset();
    auto finalLocation = playerShip.getSprite().getPosition();
            CHECK(finalLocation==originalLocation); //cast to int to get closest pixel accuracy
}

// Bullet movement tests

TEST_CASE ("Creating a bullet entity succeeds")
{
    TextureHolder textures;
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;

    common::Resolution resolution ={1920,1080};
    auto BulletShootAngle = 180;
    auto BulletStartingPoint = resolution.y; //define the starting distance from centre;
    CHECK_NOTHROW(Bullet bullet(textures,sounds,resolution,BulletStartingPoint,BulletShootAngle,1,textures::BulletPlayer););
}

TEST_CASE ("Shooting a bullet stright up moves corretly")
{
    TextureHolder textures;
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;

    common::Resolution resolution ={1920,1080};
    auto BulletShootAngle = 180;
    auto BulletStartingPoint = resolution.y; //define the starting distance from centre;
    Bullet bullet(textures,sounds,resolution,BulletStartingPoint,BulletShootAngle,1,textures::BulletPlayer);
    auto startingPosition = bullet.getSprite().getPosition();
    auto desiredBulletMove =-1; //-1 moves bullet up(simulating a player shot)
    bullet.setMove(desiredBulletMove);
    bullet.update();
    auto finalPosition = bullet.getSprite().getPosition();
    //the position below if the original, +2 pixles due to the scaling of effect of the non-linear motion of the bullet
    auto expectedPosition = sf::Vector2f(startingPosition.x,startingPosition.y+desiredBulletMove*-2);
            CHECK(int(finalPosition.x)==int(expectedPosition.x));
            CHECK(int(finalPosition.y)==int(expectedPosition.y));
}

TEST_CASE ("Shooting a bullet stright up causes them to scale down as they fly away")
{
    TextureHolder textures;
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;

    common::Resolution resolution ={1920,1080};
    auto BulletShootAngle = 180;
    auto BulletStartingPoint = resolution.y; //define the starting distance from centre;
    Bullet bullet(textures,sounds,resolution,BulletStartingPoint,BulletShootAngle,1,textures::BulletPlayer);
    auto startingScale = bullet.getRadius();
    auto desiredBulletMove =-10;
    bullet.setMove(desiredBulletMove);
    bullet.update();
    auto finalScale = bullet.getRadius();
    //the position below if the original, +2 pixles due to the scaling of effect of the non-linear motion of the bullet
    CHECK(finalScale<startingScale);
}

TEST_CASE ("Shooting a bullet fired from the centre scales up as it moves outwards")
{
    TextureHolder textures;
    textures.load(textures::BulletPlayer,"resources/bullet_player.png");

    SoundHolder sounds;

    common::Resolution resolution ={1920,1080};
    auto BulletShootAngle = 180;
    auto BulletStartingPoint = resolution.y/2; //define the starting distance from centre;
    Bullet bullet(textures,sounds,resolution,BulletStartingPoint,BulletShootAngle,1,textures::BulletPlayer);
    auto startingScale = bullet.getRadius();
    auto desiredBulletMove =10;
    bullet.setMove(desiredBulletMove);
    bullet.update();
    auto finalScale = bullet.getRadius();
    //the position below if the original, +2 pixles due to the scaling of effect of the non-linear motion of the bullet
            CHECK(finalScale>startingScale);
}