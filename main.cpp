#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameState.h"
#include "Menu.h"

int main()
{
    bool game_started;
    bool game_finished;
    sf::Event event;
    sf::Vector2u window_size(800,600);

    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "My window");
    GameState* game = nullptr;
    sf::Clock clock;
    Menu menu;

    window.setFramerateLimit(60);
    menu.create_menu();

    while (window.isOpen())
    {
        
        if(!game){
            game = menu.game_start(window, window_size);
            //std::cout<<"game stopped\n";
            while(window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                    return 0;
                }
            }
            continue;
        }
        //std::cout<<"game playing\n";
        game->set_delta_time(clock.restart().asSeconds());
        game->update_ball_position();
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        };

        game_finished = game->handle_keyboard();
        if(game_finished){
            std::cout<<"Game finished\n";
            menu.game_stop(game);
            game = nullptr;
            continue;
        }
        //std::cout<<"game still playing\n";
        game->move_ball();

        window.clear(sf::Color::Black);        

        game->ball_wall_collision();
        game->ball_board_collision();
        game->ball_box_collision();
        game->draw(window);
        window.display();
    }

    return 0;
}