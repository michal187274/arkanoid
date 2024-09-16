#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameState.h"

GameState game;

sf::RectangleShape board(sf::Vector2f(80,4));
sf::Vector2f move_step_board(0, 0);
float speed(12);

//bool intersects = false;
sf::Vector2f move_step_circle(-0.02, -0.01);
float circle_radius = 10;

sf::CircleShape circle(circle_radius);

void move_object(sf::Transformable &object, sf::Vector2f move_step);
void circle_wall_collision();
bool circle_box_collision(BoxObject);
void set_boxes_positions();
void circle_board_collision();

struct Key_pressed{
    bool right = false;
    bool left = false;
}key_pressed;

//std::vector<std::pair<sf::RectangleShape, bool>> vector_of_boxes;

int main()
{
    game.create_window(sf::Vector2f(800,600)); //jak to dziala
    game.set_box_size(sf::Vector2f(80,40));
    game.create_boxes(3, sf::Vector2f(80,40));
    game.create_ball(10);
    game.get_ball_object().set_move_step(sf::Vector2f(-0.02, -0.01));
    game.get_ball_object().set_position(sf::Vector2f(400,501));
    board.setPosition(400, 500);
    //set_boxes_positions();
    game.get_window().setFramerateLimit(60);
    //bool key_pressed(false);
    sf::Clock clock;
 
    while (game.get_window().isOpen())
    {

        std::cout<<"ball position"<<game.get_ball_object().get_ball_object().getPosition().x<<game.get_ball_object().get_ball_object().getPosition().y<<'\n';
        std::cout<<"BallObject position"<<game.get_ball_object().get_position().x<<game.get_ball_object().get_position().y<<'\n';
        sf::Event event;
        while (game.get_window().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                game.get_window().close();
        }
        if(clock.getElapsedTime().asMilliseconds()>=5){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                move_step_board.x = -0.05;
                key_pressed.left = true;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                move_step_board.x = 0.05;
                key_pressed.right = true;
            }
            circle_board_collision();
            game.get_ball_object().move();
            //move_object(circle, move_step_circle);
            move_object(board, move_step_board);

            move_step_board.x = 0;
        }

        game.get_window().clear(sf::Color::Black);        


        for(auto& v : game.get_boxes_vector()){

            if(circle_box_collision(v)){
                std::cout<<"circleboardcollision"<<'\n';
                v.set_was_hit(true);
                v.set_position(sf::Vector2f(-40,-40));
            }
        };
        //circle_box_collision(std::make_pair(board, false));
        circle_wall_collision();
        //game.get_window().draw(circle);
        game.get_window().draw(board);
        game.draw_boxes();
        game.draw_ball();
        std::cout<<"ball position"<<game.get_ball_object().get_ball_object().getPosition().x<<game.get_ball_object().get_ball_object().getPosition().y<<'\n';
        std::cout<<"BallObject position"<<game.get_ball_object().get_position().x<<game.get_ball_object().get_position().y<<'\n';
        for(auto& v : game.get_boxes_vector()){
            std::cout<<v.get_position().x<<" "<<v.get_position().y<<'\n';
        }
        game.get_window().display();
        return 0;
    }

    return 0;
}

void circle_board_collision(){
    sf::Vector2f board_position = board.getPosition();
   
    sf::FloatRect board_rect = board.getGlobalBounds();
    sf::FloatRect ball_rect = game.get_ball_object().get_gloabal_bounds();
    if(board_rect.intersects(ball_rect)){
        move_step_circle.y = -move_step_circle.y;
        if(key_pressed.left){
            if(move_step_circle.x < 0) move_step_circle.y = move_step_circle.y/2;
        }
    }
}

/*void set_boxes_positions(){
    for(int j = 0; j<120; j+=40){
        for(int i = 0; i<=800; i+=80){
            sf::RectangleShape box(sf::Vector2f(80,40));
            box.setPosition(i,j);
            box.setOutlineColor(sf::Color::Green);
            box.setOutlineThickness(4);
            vector_of_boxes.push_back(std::pair<sf::RectangleShape, bool>(box, false));
        }
    }
}*/

void move_object(sf::Transformable &object, sf::Vector2f move_step){
    sf::Vector2f direction = move_step*speed;
    for(int i(0); i<speed; i++){
        object.move(direction);
    }
}

void circle_wall_collision(){
    sf::Vector2f circle_position = circle.getPosition();
    static bool wall_collision(false);
 
    if(circle_position.x + circle_radius >= 800 ||
        circle_position.x - circle_radius <= 0){
        if(!wall_collision){
            move_step_circle.x = -move_step_circle.x;
            std::cout<<"x collision"<<'\n';
            wall_collision = true;
        }
    }
    else if(circle_position.y - circle_radius <= 0 ||
            circle_position.y + circle_radius >= 600){
            if(!wall_collision){
                move_step_circle.y = -move_step_circle.y;
                std::cout<<"y collision"<<'\n';
                wall_collision = true;
        }
    }
    else wall_collision = false;
};

bool circle_box_collision(BoxObject box){
    float circle_x_intersection_point_right(0);
    float circle_x_intersection_point_left(0);
    float circle_y_intersection_point_up(0);
    float circle_y_intersection_point_down(0);
    sf::Vector2f circle_position = circle.getPosition();

    static bool intersects(false);


    if(box.get_gloabal_bounds().intersects(circle.getGlobalBounds()) && intersects == false){
         
        intersects = true;
        //sf::Vector2f box_position = box.get_position();

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
    else if(!circle.getGlobalBounds().intersects(box.get_gloabal_bounds()))  intersects = false;
    return intersects;
};