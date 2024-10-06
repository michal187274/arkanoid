#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameState.h"
#include "Menu.h"

int main()
{
    sf::Vector2u window_size(800,600);
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "My window");
    GameState game;
    sf::Clock clock;
    window.setFramerateLimit(60);
    Menu menu;
    menu.create_menu();
    bool game_started;
    bool game_finished;
    sf::Event event;

    while (window.isOpen())
    {
        game_started = menu.game_start(window, game, window_size);
        if(!game_started){
            while(window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                    return 0;
                }
            }
            continue;
        }

        game.set_delta_time(clock.restart().asSeconds());
   
        game.get_ball_object().update_position();
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        };
        game_finished = game.handle_keyboard();
        if(game_finished){
            game.stop_game();
            menu.set_game_stop();
            continue;
        }
        game.move_ball();

        window.clear(sf::Color::Black);        

        game.ball_wall_collision();
        game.ball_board_collision();
        game.ball_box_collision();
        game.draw(window);
        window.display();
    }

    return 0;
}