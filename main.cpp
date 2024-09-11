#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
sf::RectangleShape board(sf::Vector2f(80,4));
sf::Vector2f move_step_board(0, 0);
float speed(12);

//bool intersects = false;
sf::Vector2f move_step_circle(-0.02, -0.01);
float circle_radius = 10;

sf::CircleShape circle(circle_radius);

void move_object(sf::Transformable &object, sf::Vector2f move_step);
void circle_wall_collision();
bool circle_box_collision(std::pair<sf::RectangleShape, bool>);
void set_boxes_positions();
void circle_board_collision();

struct Key_pressed{
    bool right = false;
    bool left = false;
}key_pressed;

std::vector<std::pair<sf::RectangleShape, bool>> vector_of_boxes;

int main()
{
    circle.setPosition(400,501);
    board.setPosition(400, 500);
    set_boxes_positions();
    window.setFramerateLimit(60);
    //bool key_pressed(false);
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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

            move_object(circle, move_step_circle);
            move_object(board, move_step_board);

            move_step_board.x = 0;
        }

        window.clear(sf::Color::Black);
        for(auto& v : vector_of_boxes){
            if(!v.second) window.draw(v.first);
            
            if(circle_box_collision(v)){
                v.second = true;
                v.first.setPosition(-40,-40);
            }
        };
        //circle_box_collision(std::make_pair(board, false));
        circle_wall_collision();
        window.draw(circle);
        window.draw(board);

        window.display();
    }

    return 0;
}

void circle_board_collision(){
    sf::Vector2f board_position = board.getPosition();
   
    sf::FloatRect board_rect = board.getGlobalBounds();
    sf::FloatRect circle_rect = circle.getGlobalBounds();
    if(board_rect.intersects(circle_rect)){
        move_step_circle.y = -move_step_circle.y;
        if(key_pressed.left){
            if(move_step_circle.x < 0) move_step_circle.y = move_step_circle.y/2;
        }
    }
}

void set_boxes_positions(){
    for(int j = 0; j<120; j+=40){
        for(int i = 0; i<=800; i+=80){
            sf::RectangleShape box(sf::Vector2f(80,40));
            box.setPosition(i,j);
            box.setOutlineColor(sf::Color::Green);
            box.setOutlineThickness(4);
            vector_of_boxes.push_back(std::pair<sf::RectangleShape, bool>(box, false));
        }
    }
}

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

bool circle_box_collision(std::pair<sf::RectangleShape, bool> vec){
    sf::RectangleShape box(vec.first);
    sf::FloatRect box_rect = box.getGlobalBounds();
    sf::FloatRect circle_rect = circle.getGlobalBounds();

    float circle_x_intersection_point_right(0);
    float circle_x_intersection_point_left(0);
    float circle_y_intersection_point_up(0);
    float circle_y_intersection_point_down(0);
    sf::Vector2f circle_position = circle.getPosition();

    static float box_x_left_axis(0);
    static float box_x_right_axis(0);
    static float box_y_up_axis(0);
    static float box_y_down_axis(0); 
    static bool intersects(false);


    if(box_rect.intersects(circle_rect) && intersects == false){
         
        intersects = true;
        sf::Vector2f box_position = box.getPosition();

        circle_x_intersection_point_right = circle_position.x + circle_radius;
        circle_x_intersection_point_left = circle_position.x - circle_radius;
        circle_y_intersection_point_up = circle_position.y - circle_radius;
        circle_y_intersection_point_down = circle_position.y + circle_radius;

        box_x_left_axis = box_position.x;
        box_x_right_axis = box_x_left_axis + box.getSize().x;
        box_y_up_axis = box_position.y;
        box_y_down_axis = box_y_up_axis + box.getSize().y;

        if((circle_x_intersection_point_left <= box_x_right_axis ||
            circle_x_intersection_point_right >= box_x_left_axis) &&
            circle_position.y <= box_y_down_axis &&
            circle_position.y >= box_y_up_axis)
            {
                //std::cout<<"xxxx"<<box_position.x<<" "<<box_position.y<<'\n';
                move_step_circle.x = -move_step_circle.x;
            }

        else if((circle_y_intersection_point_up <= box_y_down_axis ||
                circle_y_intersection_point_down >= box_y_up_axis) &&
                circle_position.x <= box_x_right_axis &&
                circle_position.x >= box_x_left_axis)
                {
                    //std::cout<<"yyyy"<<box_position.x<<" "<<box_position.y<<'\n';
                    std::cout<<"das"<<'\n';
                    move_step_circle.y = -move_step_circle.y;
                }
    }
    else if(!circle_rect.intersects(box_rect))  intersects = false;
    return intersects;
};