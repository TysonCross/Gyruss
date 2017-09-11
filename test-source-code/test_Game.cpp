//--------------------------------------------------------------------------
// Student  1239448
// @file    test_SplashScreen.cpp
// @author  Tyson Cross
// @date    2017/09/10
// @brief   Description of file in project Project.
//
// Detailed description of file.
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#include "../game-source-code/SplashScreen.hpp"
#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

//Splash screen tests
TEST_CASE ("Check splashscreen image resource exists")
{
    sf::RenderWindow testWindow;
    const unsigned int gameWidth = 640;
    const unsigned int gameHeight = 480;

    testWindow.create(sf::VideoMode(gameWidth, gameHeight, 32), "Test");
    SplashScreen splashScreen;

    int splashResult= splashScreen.show(testWindow);
    std::cout <<"here";
        CHECK(splashResult!=-1);
}

TEST_CASE ("Quit splashscreen window returns 1(signal: close application)")
{
    sf::RenderWindow testWindow;
    const unsigned int gameWidth = 640;
    const unsigned int gameHeight = 480;

    testWindow.create(sf::VideoMode(gameWidth, gameHeight, 32), "Test");
    SplashScreen splashScreen;

    int splashResult= splashScreen.show(testWindow);
        CHECK(splashResult==1);
}

TEST_CASE ("Continue Splashscreen returns 0(signal: continue to game play)")
{
    sf::RenderWindow testWindow;
    const unsigned int gameWidth = 640;
    const unsigned int gameHeight = 480;

    testWindow.create(sf::VideoMode(gameWidth, gameHeight, 32), "Test");
    SplashScreen splashScreen;

    int splashResult= splashScreen.show(testWindow);
        CHECK(splashResult==0);
}