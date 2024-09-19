#include "BallObject.h"

    void BallObject::move(){
        m_ball_object.move(m_move_step);
    }

    void BallObject::set_position(sf::Vector2f position){
        std::cout<<"i'm in BallObject::set_position "<<position.x<<" "<<position.y<<'\n';
        m_position = position;
        m_ball_object.setPosition(position);
    }

    void BallObject::set_move_step(sf::Vector2f step){
        m_move_step = step;
    }

    void BallObject::set_radius(float radius){
        m_radius = radius;
        m_ball_object.setRadius(radius);
    }

    void BallObject::calculate_intersection_points(){
        m_points.right = m_position.x + m_radius;
        m_points.left = m_position.x - m_radius;
        m_points.up = m_position.y - m_radius;
        m_points.down = m_position.y + m_radius;
    }

    sf::Vector2f BallObject::get_position(){
        return m_position;
    }

    sf::FloatRect BallObject::get_gloabal_bounds(){
        return m_ball_object.getGlobalBounds();
    }

    intersection_points BallObject::get_intersection_points(){
        return m_points;
    }

    sf::CircleShape BallObject::get_ball_object(){
        return m_ball_object;
    }