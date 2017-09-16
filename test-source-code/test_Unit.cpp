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
#include "../game-source-code/ResourceHolder.hpp"
#include "../game-source-code/common.hpp"

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