#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameState.h"

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Vector2f ball_move_step(-60,-80);
    sf::Vector2f board_move_step(-60,0);
    sf::Vector2f ball_initial_position(400,501);
    sf::Vector2f board_initial_position(400,500);
    GameState game(window, ball_initial_position, board_initial_position, ball_move_step, board_move_step);

int main()
{
    sf::Clock clock;
    game.set_box_size(sf::Vector2f(80,40));
    game.create_boxes(3, sf::Vector2f(80,40));
    game.create_ball(10);
    game.create_board(sf::Vector2f(80,4));
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        game.set_delta_time(clock.restart().asSeconds());
   
        game.get_ball_object().update_position();
        sf::Event event;
        game.handle_event(event);
        game.move_ball();

        window.clear(sf::Color::Black);        

        game.ball_wall_collision();
        game.draw();
        window.display();
    }

    return 0;
}
/*to GameState
bool circle_box_collision(BoxObject box){
    float circle_x_intersection_point_right(0);
    float circle_x_intersection_point_left(0);
    float circle_y_intersection_point_up(0);
    float circle_y_intersection_point_down(0);
    //sf::Vector2f circle_position = circle.getPosition();

    sf::Vector2f circle_position = game.get_ball_object().get_position();
    float circle_radius = game.get_ball_object().get_radius();

    static bool intersects(false);


    if(box.get_global_bounds().intersects(game.get_ball_object().get_global_bounds()) && intersects == false){
         
        intersects = true;
        //sf::Vector2f box_position = box.get_position();
        sf::Vector2f move_step_circle = game.get_ball_object().get_move_step();

        circle_x_intersection_point_right = circle_position.x + circle_radius;
        circle_x_intersection_point_left = circle_position.x - circle_radius;
        circle_y_intersection_point_up = circle_position.y - circle_radius;
        circle_y_intersection_point_down = circle_position.y + circle_radius;

        if((circle_x_intersection_point_left <= box.get_sides().right ||
            circle_x_intersection_point_right >= box.get_sides().left) &&
            circle_position.y <= box.get_sides().down &&
            circle_position.y >= box.get_sides().up)
            {
                std::cout<<"xxxx"<<'\n';
                move_step_circle.x = -move_step_circle.x;
            }

        else if((circle_y_intersection_point_up <= box.get_sides().down ||
                circle_y_intersection_point_down >= box.get_sides().up) &&
                circle_position.x <= box.get_sides().right &&
                circle_position.x >= box.get_sides().left)
                {
                    std::cout<<"yyyy"<<'\n';
                    std::cout<<"das"<<'\n';
                    move_step_circle.y = -move_step_circle.y;
                }
    }
    else if(!game.get_ball_object().get_global_bounds().intersects(box.get_global_bounds()))  intersects = false;
    return intersects;
};*/