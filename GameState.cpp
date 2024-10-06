#include "GameState.h"
#include <cmath>

void GameState::create_boxes(int rows, sf::Vector2f box_size, sf::Vector2u window_size){
    for(int j = 0; j<(rows*box_size.y); j+=box_size.y){
        for(int i = 0; i<=window_size.x; i+=box_size.x){
            std::cout<<"createboxes"<<i<<" "<<j<<'\n';
            BoxObject box(box_size);
            box.set_position(sf::Vector2f(i,j));
            box.set_outline();
            std::cout<<"positions "<<box.get_position().x<<" "<<box.get_position().y<<'\n';
            vector_of_boxes.push_back(box);
        }
    }
    for (auto& box : vector_of_boxes){
        std::cout<<"box bounds "<<box.get_global_bounds().left<<" "<<box.get_global_bounds().top<<'\n';
    }
}

void GameState::create_ball(float radius){
    std::cout<<"createballlllllllll";
    m_ball.set_radius(radius);
    m_ball.set_position(ball_initial_position);
    m_ball_move_step = initial_ball_move_step;
}

void GameState::create_board(sf::Vector2f size){
    std::cout<<"createboarddddddd";
    m_board.set_size(size);
    m_board.set_position(board_initial_position);
    m_board_move_step = intial_board_move_step;
}

void GameState::start_game(sf::Vector2u window_size){
    if (!m_game_was_started){
        create_ball(ball_radius);
        create_board(board_size);
        create_boxes(boxes_rows, box_size, window_size);
        m_game_was_started = true;
    }
}

void GameState::stop_game(){
    create_ball(ball_radius);
    create_board(board_size);
    m_ball_move_step = sf::Vector2f(0,0);
    m_game_was_started = false;
}


BallObject& GameState::get_ball_object(){
    return m_ball;
}

void GameState::draw(sf::RenderWindow& window){
    window.draw(m_ball.get_ball());
    window.draw(m_board.get_board());
    for(auto& v : vector_of_boxes){
        window.draw(v.get_box_object());
    }
}


std::vector<BoxObject> GameState::get_boxes_vector(){
    return vector_of_boxes;
}

void GameState::set_delta_time(float delta){
    m_delta_time = delta;
}

void GameState::move_ball(){
    sf::Vector2f step = m_ball_move_step*m_delta_time*ball_speed;
    m_ball.move(step);
}

void GameState::move_board(sf::Vector2f move_step){
    sf::Vector2f step = move_step*m_delta_time;
    m_board.move(step);
}

void GameState::ball_wall_collision(){

    static bool wall_collision(false);
 
    if(m_ball.get_position().x + m_ball.get_radius() >= 800 ||
        m_ball.get_position().x - m_ball.get_radius() <= 0){
        if(!wall_collision){
            m_ball_move_step = sf::Vector2f(-(m_ball_move_step.x), m_ball_move_step.y);
            std::cout<<"x collision"<<'\n';
            wall_collision = true;
        }
    }
    else if(m_ball.get_position().y - m_ball.get_radius() <= 0 ||
            m_ball.get_position().y + m_ball.get_radius() >= 600){
            if(!wall_collision){
                m_ball_move_step= sf::Vector2f(m_ball_move_step.x, -m_ball_move_step.y);
                std::cout<<"y collision"<<'\n';
                wall_collision = true;
        }
    }
    else wall_collision = false;
}

void GameState::ball_board_collision(){
    if(m_board.get_global_bounds().intersects(m_ball.get_global_bounds())){
        m_ball_move_step.y = -m_ball_move_step.y;
        std::cout<<"cosinus: "<<(cos(((m_board.get_position().x - m_ball.get_position().x))/m_board.get_board().getSize().x/2)*M_PI/6)<<'\n';
        std::cout<<"move_step: "<<m_ball_move_step.x<<'\n';
        if(m_ball.get_position().x > m_board.get_position().x)
            m_ball_move_step.x += m_ball_move_step.x*(cos(((m_board.get_position().x - m_ball.get_position().x))/m_board.get_board().getSize().x/2)*M_PI/6);
        else
            m_ball_move_step.x -= m_ball_move_step.x*(cos(((m_board.get_position().x - m_ball.get_position().x))/m_board.get_board().getSize().x/2)*M_PI/6);
        m_ball_move_step.x = m_ball_move_step.x/sqrt(m_ball_move_step.x*m_ball_move_step.x + m_ball_move_step.y*m_ball_move_step.y);
        m_ball_move_step.y = m_ball_move_step.y/sqrt(m_ball_move_step.x*m_ball_move_step.x + m_ball_move_step.y*m_ball_move_step.y);
        std::cout<<"new move_step: "<<m_ball_move_step.x<<'\n';
    }
}



bool GameState::handle_keyboard(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) move_board(m_board_move_step);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) move_board(-m_board_move_step);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        return true;
    }
    return false;
}

void GameState::ball_box_collision(){
    intersection_points ball_points = m_ball.get_intersection_points();
    static bool intersects(false);

    for(auto &box : vector_of_boxes){
        if(box.get_global_bounds().intersects(m_ball.get_global_bounds()) && intersects == false){
            std::cout<<"boxCollision\n";
            intersects = true;
            //sf::Vector2f box_position = box.get_position();
            
            if((ball_points.left <= box.get_sides().right ||
                ball_points.right >= box.get_sides().left) &&
                m_ball.get_position().y <= box.get_sides().down &&
                m_ball.get_position().y >= box.get_sides().up)
                {
                    box.set_position(sf::Vector2f(-80, -80));
                    std::cout<<"xxxx"<<'\n';
                    m_ball_move_step.x = -m_ball_move_step.x;
                }

            else if((ball_points.up <= box.get_sides().down ||
                    ball_points.down >= box.get_sides().up) &&
                    m_ball.get_position().x <= box.get_sides().right &&
                    m_ball.get_position().x >= box.get_sides().left)
                    {
                        box.set_position(sf::Vector2f(-80, -80));
                        std::cout<<"yyyy"<<'\n';
                        std::cout<<"das"<<'\n';
                        m_ball_move_step.y = -m_ball_move_step.y;
                    }
        }
        else if(!box.get_global_bounds().intersects(m_ball.get_global_bounds()))  intersects = false;
    }
}
