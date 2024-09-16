#include "GameState.h"

sf::RenderWindow& GameState::get_window(){
    return window;
}
void GameState::create_boxes(int rows, sf::Vector2f size){
    for(int j = 0; j<(rows*size.x); j+=size.x){
        for(int i = 0; i<=window_size.x; i+=size.x){
            std::cout<<"createboxes"<<i<<" "<<j<<'\n';
            BoxObject box(box_size);
            box.set_position(sf::Vector2f(i,j));
            box.set_outline();
            std::cout<<"positions "<<box.get_position().x<<" "<<box.get_position().y<<'\n';
            vector_of_boxes.push_back(box);
        }
    }
}

void GameState::create_ball(float radius){
    m_ball.set_radius(radius);
}

BallObject GameState::get_ball_object(){
    return m_ball;
}
void GameState::draw_ball(){
    window.draw(m_ball.get_ball_object());
}

void GameState::create_window(sf::Vector2f size){
    window_size = size;
    window.create(sf::VideoMode(window_size.x, window_size.y), "My window");
}

void GameState::set_box_size(sf::Vector2f size){
    box_size = size;
}

/*jak to dziala/////////////////
sf::VideoMode GameState::get_window_size{
    return sf::VideoMode(window_size);
}
*/

std::vector<BoxObject> GameState::get_boxes_vector(){
    return vector_of_boxes;
}

void GameState::draw_boxes(){
    std::cout<<vector_of_boxes.size()<<'\n';
    for(auto& v : vector_of_boxes){
        std::cout<<"was hit "<<std::boolalpha<<v.get_was_hit()<<'\n';
        std::cout<<"box position w klasie "<<v.get_position().x<<" "<<v.get_position().y<<'\n';
        std::cout<<"box position "<<v.get_box_object().getPosition().x<<" "<<v.get_box_object().getPosition().y<<'\n';
        if(!(v.get_was_hit())){
            std::cout<<"drawdarawasarawdasd"<<'\n';
            window.draw(v.get_box_object());
        }
    }
}

