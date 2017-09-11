/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    Game.cpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/09
/// \brief   Main Game controller implementation
///
/// Implements the Game loop, and game states
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Game.hpp"


//Static Member redeclaration
Game::GameState Game::_gameState = Splash;
ResourceMapper Game::_resourceMapper;
common::Resolution Game::_resolution;
sf::RenderWindow Game::_mainWindow;
std::map<int, bool> Game::_keysPressed;


void Game::Start()
{
    _resolution.x = std::stoi(_resourceMapper.getResourceValues("Resolution").at(0));
    _resolution.y = std::stoi(_resourceMapper.getResourceValues("Resolution").at(1));

    sf::Image icon;
    icon.loadFromFile(_resourceMapper.getResource("WindowIcon"));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    _mainWindow.create(sf::VideoMode(_resolution.x, _resolution.y, 32), "Gyruss",
                       sf::Style::Close, settings );
    //_mainWindow.setKeyRepeatEnabled(true);
    _mainWindow.setMouseCursorVisible(false);
    _mainWindow.setVerticalSyncEnabled(true);
    _mainWindow.setFramerateLimit(60);
    _mainWindow.setIcon(32, 32, icon.getPixelsPtr());

    while (_gameState != Game::Exiting)
    {
        InitializeGameLoop();
    }
    _mainWindow.close();
}

void Game::InitializeGameLoop()
{
    sf::Event event;
    sf::Clock clock;
    sf::Color color(sf::Color::Black);

    //First Game State
    if (_gameState == Game::Splash)
    {
        showSplashScreen();
    }

    //Spawn Player ship
    const auto shipPathRadius = (_resolution.y / 2) - (_resolution.y * 0.08f);
    PlayerShip playerShip(_resourceMapper, shipPathRadius, 0, 0.4);

    //Game Handler
    InputHandler inputHandler;

    //Starfield starfield;
    //------Star Field------------

    const auto number_of_stars = 60;
    const auto maximum_depth = 6;
    const auto star_size = 8.0f;
    const auto star_speed = 0.081;
    auto star_scale = 0.0f;

    std::vector<common::Star> starField;
    sf::RectangleShape star(sf::Vector2f(star_size,star_size));

    //Initialize star random placement
    for( auto i = 0; i < number_of_stars; i++)
    {
        common::Star temp;
        temp.x = rand() % _resolution.x - (_resolution.x / 2.0f);
        temp.y = rand() % _resolution.y - (_resolution.y / 2.0f);
        //z-Depth
        temp.z = -1 * 1.0f * (rand() % maximum_depth) - maximum_depth;
        starField.push_back(temp);
    }
    //-----------------------------


    //Game Loop
    while (_gameState == Game::Playing)
    {
        //Check for events since last frame
        while (_mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _gameState = Game::Exiting;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
                && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
            {
                _gameState = Game::Exiting;
            }

            if (event.type == sf::Event::EventType::KeyReleased)
                if (event.key.code == sf::Keyboard::Space)
            {
                playerShip.shoot();
            }


            // During the current polling period, key-presses are detected
            // if pressed added to the map, and removed if the key is released
            if (event.type == sf::Event::EventType::KeyPressed)
            {
                if (_keysPressed.count(event.key.code) == 0)
                {
                    _keysPressed[event.key.code] = true;
                }
            }

            if (event.type == sf::Event::EventType::KeyReleased)
            {
                if (_keysPressed.count(event.key.code) > 0)
                {
                    _keysPressed.erase(event.key.code);
                }
            }
        } // End of input polling

        inputHandler.resolveKeyMapping(_keysPressed, playerShip);

        //ToDo: Get all the objects to be drawn

        clock.restart();
    sf::Sprite sprite;
        _mainWindow.clear(color);

        //----Star Loop-------
        auto i = 0;
        for ( auto& sun : starField )
        {

            //Move
            sun.z += star_speed;

            //Rainbow candy
            auto r = rand()%128 * 2;
            auto g = rand()%128 * 2;
            auto b = rand()%128 * 2;

            //If star is visible
            if (sun.z >= 0.0f)
            {
                //recycle stars
               sun.z = -maximum_depth;
            }
            if (sun.z <= -maximum_depth)
            {
                //tiny
                star_scale = 0;
            }
            else
            {
                star_scale = (sun.z + (maximum_depth)) / (maximum_depth);
            }
            //Dimming
            i++;
            if (i%4)
            {
                star.setFillColor(sf::Color(255 * star_scale, 255 * star_scale, 255 * star_scale));
            }
            else
            {
                star.setFillColor(sf::Color(r * star_scale, g * star_scale, b * star_scale));
            }
            //Scaling
            star.setSize(sf::Vector2f(star_size * star_scale, star_size * star_scale));
//            star.setScale(star_size * star_scale, star_size * star_scale);
            // /Moving
            star.setPosition(sf::Vector2f(-sun.x / sun.z + (_resolution.x/2),
                                          sun.y / sun.z + (_resolution.y/2)));

            _mainWindow.draw(star);
        }

        _mainWindow.draw(playerShip.getSprite());
        //-----------------
        _mainWindow.display();
    }
}

void Game::showSplashScreen()
{
    SplashScreen splashScreen;
    if (splashScreen.show(_mainWindow,_resourceMapper) == 0)
    {
        _gameState = Game::Playing;
        return;
    }
    _gameState = Game::Exiting;
}