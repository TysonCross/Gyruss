//--------------------------------------------------------------------------
// Students 1239448 & 1109146
// @date    2017/09/10
// @brief   Splashscreen interactive display tests
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../game-source-code/ScreenSplash.hpp"


//Splash screen tests
TEST_CASE ("Check splashscreen loads") {
    TextureHolder texture_holder;
    FontHolder font_holder;

    texture_holder.load(textures::SplashScreenExtra, "resources/test_image.png");
    font_holder.load(fonts::Title, "resources/fax_sans_beta.otf");
    font_holder.load(fonts::Default, "resources/fax_sans_beta.otf");

    auto resolution = sf::Vector2i{1024, 768};
    sf::RenderWindow testWindow;
    testWindow.create(sf::VideoMode(resolution.x, resolution.y, 32), "Test");
    ScreenSplash splashScreen;

    int splashResult = splashScreen.draw(testWindow, texture_holder, font_holder, resolution);
            CHECK(splashResult != -1);
}

TEST_CASE ("Quit splashscreen window returns 1(signal: close application)") {
    TextureHolder texture_holder;
    FontHolder font_holder;

    texture_holder.load(textures::SplashScreenExtra, "resources/test_image_close.png");
    font_holder.load(fonts::Title, "resources/fax_sans_beta.otf");
    font_holder.load(fonts::Default, "resources/fax_sans_beta.otf");

    auto resolution = sf::Vector2i{1024, 768};
    sf::RenderWindow testWindow;
    testWindow.create(sf::VideoMode(resolution.x, resolution.y, 32), "Test");
    ScreenSplash splashScreen;

    int splashResult = splashScreen.draw(testWindow, texture_holder, font_holder, resolution);
            CHECK(splashResult == 1);
}

TEST_CASE ("Continue Splashscreen returns 0(signal: continue to game play)") {
    TextureHolder texture_holder;
    FontHolder font_holder;

    texture_holder.load(textures::SplashScreenExtra, "resources/test_image_press.png");
    font_holder.load(fonts::Title, "resources/fax_sans_beta.otf");
    font_holder.load(fonts::Default, "resources/fax_sans_beta.otf");

    auto resolution = sf::Vector2i{1024, 768};

    sf::RenderWindow testWindow;
    testWindow.create(sf::VideoMode(resolution.x, resolution.y, 32), "Test");
    ScreenSplash splashScreen;

    int splashResult = splashScreen.draw(testWindow, texture_holder, font_holder, resolution);
            CHECK(splashResult == 0);
}