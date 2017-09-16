//--------------------------------------------------------------------------
// Students 1239448 & 1109146
// @date    2017/09/10
// @brief   Splashscreen interactive display tests
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../game-source-code/SplashScreen.hpp"
#include <iostream>
#include "doctest.h"


//Splash screen tests
TEST_CASE ("Check splashscreen loads")
{
    TextureHolder texture_holder;
    FontHolder font_holder;
    SoundHolder sound_holder;

    texture_holder.load(textures::SplashScreen,"resources/test_image.png");
    sound_holder.load(sounds::StartSound,"resources/win_sound.ogg");
    font_holder.load(fonts::Title,"resources/fax_sans_beta.otf");
    font_holder.load(fonts::Info,"resources/fax_sans_beta.otf");

    common::Resolution res= {1024,768};

    sf::RenderWindow testWindow;
    testWindow.create(sf::VideoMode(res.x, res.y, 32), "Test");
    SplashScreen splashScreen;

    int splashResult= splashScreen.show(testWindow, texture_holder, sound_holder, font_holder, res);
        CHECK(splashResult!=-1);
}

TEST_CASE ("Quit splashscreen window returns 1(signal: close application)")
{
    TextureHolder texture_holder;
    FontHolder font_holder;
    SoundHolder sound_holder;

    texture_holder.load(textures::SplashScreen,"resources/test_image_close.png");
    sound_holder.load(sounds::StartSound,"resources/win_sound.ogg");
    font_holder.load(fonts::Title,"resources/fax_sans_beta.otf");
    font_holder.load(fonts::Info,"resources/fax_sans_beta.otf");

    common::Resolution res= {1024,768};

    sf::RenderWindow testWindow;
    testWindow.create(sf::VideoMode(res.x, res.y, 32), "Test");
    SplashScreen splashScreen;

    int splashResult= splashScreen.show(testWindow, texture_holder, sound_holder, font_holder, res);
        CHECK(splashResult==1);
}

TEST_CASE ("Continue Splashscreen returns 0(signal: continue to game play)")
{
    TextureHolder texture_holder;
    FontHolder font_holder;
    SoundHolder sound_holder;

    texture_holder.load(textures::SplashScreen,"resources/test_image_press.png");
    sound_holder.load(sounds::StartSound,"resources/win_sound.ogg");
    font_holder.load(fonts::Title,"resources/fax_sans_beta.otf");
    font_holder.load(fonts::Info,"resources/fax_sans_beta.otf");

    common::Resolution res= {1024,768};

    sf::RenderWindow testWindow;
    testWindow.create(sf::VideoMode(res.x, res.y, 32), "Test");
    SplashScreen splashScreen;

    int splashResult= splashScreen.show(testWindow, texture_holder, sound_holder, font_holder, res);
        CHECK(splashResult==0);
}