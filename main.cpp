#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
float circle_radius = 10;
sf::CircleShape circle(circle_radius);
sf::RectangleShape board(sf::Vector2f(80,4));
std::vector<std::pair<float, float>> board_sectors;
sf::Vector2f move_step_circle(-0.02, -0.01);
sf::Vector2f move_step_board(0, 0);
float speed(12);

bool intersects = false;
//helper variables for circle_box_collision function
sf::Vector2f circle_position(0,0);
sf::Vector2f box_position(0,0);
float circle_x_intersection_point_right(0);
float circle_x_intersection_point_left(0);
float circle_y_intersection_point_up(0);
float circle_y_intersection_point_down(0);
float box_x_left_axis(0);
float box_x_right_axis(0);
float box_y_up_axis(0);
float box_y_down_axis(0); 

float board_secotr_length(0);

bool wall_collision(false);

void move_object(sf::Transformable &object, sf::Vector2f move_step);
void circle_wall_collision();
bool circle_box_collision(std::pair<sf::RectangleShape, bool>);
void draw_boxes();
void make_board_sectors();
void circle_board_collision();

std::vector<std::pair<sf::RectangleShape, bool>> vector_of_boxes;

int main()
{
    circle.setPosition(400,501);
    board.setPosition(400, 500);
    draw_boxes();
    window.setFramerateLimit(60);
    board_secotr_length = board.getSize().x/5;
    make_board_sectors();


    while (window.isOpen())
    {
        circle_position = circle.getPosition();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        move_object(circle, move_step_circle);
        move_object(board, move_step_board);
        move_step_board.x = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            move_step_board.x = -0.05; 
            make_board_sectors();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            move_step_board.x = 0.05; 
            make_board_sectors();
        }


        for(auto& v : vector_of_boxes){
            if(!v.second) window.draw(v.first);
            
            if(circle_box_collision(v)){
                v.second = true;
                v.first.setPosition(-40,-40);
            }
        };
        circle_box_collision(std::make_pair(board, false));
        circle_wall_collision();
        //circle_board_collision();
        window.draw(circle);
        window.draw(board);

        window.display();
    }

    return 0;
}


void make_board_sectors(){
    sf::Vector2f board_area(board.getPosition().x - board.getSize().x/2,  board.getPosition().x + board.getSize().x/2);
    float prev_board_sector = board_area.x;
    for(float i=0; i<5 ; i++){
       board_sectors.push_back(std::pair<float, float>(prev_board_sector, prev_board_sector+board_secotr_length));
       prev_board_sector = prev_board_sector+board_secotr_length;
    }
}

void circle_board_collision(){
    float circle_intersection_point_y = circle_position.y-circle_radius;
    float circle_intersection_point_x_left = circle_position.x-circle_radius;
    float circle_intersection_point_x_right = circle_position.x+circle_radius;
    
    if(circle_intersection_point_x_left>=board_sectors[0].first && circle_intersection_point_x_right<=board_sectors[0].second){ 
        std::cout<<"a\n";
        move_step_board.y= -move_step_board.y;
        move_step_board.x= -2*move_step_board.x;
    }
    else if(circle_intersection_point_x_left>=board_sectors[1].first && circle_intersection_point_x_right<=board_sectors[1].second){
        std::cout<<"b\n";
        move_step_board.y= -move_step_board.y;
        move_step_board.x= -1.5*move_step_board.x;
    }
    else if(circle_intersection_point_x_left>=board_sectors[2].first && circle_intersection_point_x_right<=board_sectors[2].second){
        std::cout<<"c\n";
        move_step_board.y= -move_step_board.y;
        move_step_board.x= -move_step_board.x;
    }
    else if(circle_intersection_point_x_left>=board_sectors[3].first && circle_intersection_point_x_right<=board_sectors[3].second){
        std::cout<<"d\n";
        move_step_board.y= -move_step_board.y;
        move_step_board.x= -move_step_board.x-1;
    }
}

void draw_boxes(){
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
    if(box_rect.intersects(circle_rect) && intersects == false){
         
        intersects = true;
        box_position = box.getPosition();

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
                    move_step_circle.y = -move_step_circle.y;
                }
    }
    else if(!circle_rect.intersects(box_rect))  intersects = false;
    return intersects;
};