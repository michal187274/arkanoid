#include "BallObject.h"

    void BallObject::move(sf::Vector2f step){
        m_ball_object.move(step);
    }

    void BallObject::set_position(sf::Vector2f position){
        std::cout<<"i'm in BallObject::set_position "<<position.x<<" "<<position.y<<'\n';
        m_position = position;
        m_ball_object.setPosition(position);
    }

    void BallObject::update_position(){
        m_position = m_ball_object.getPosition();
    }

    void BallObject::set_radius(float radius){
        m_radius = radius;
        m_ball_object.setRadius(radius);
    }

    intersection_points BallObject::get_intersection_points(){
        return intersection_points(
        m_points.right = m_position.x + m_radius,
        m_points.left = m_position.x - m_radius,
        m_points.up = m_position.y - m_radius,
        m_points.down = m_position.y + m_radius);
    }

    sf::Vector2f BallObject::get_position(){
        return m_position;
    }

    sf::FloatRect BallObject::get_global_bounds(){
        return m_ball_object.getGlobalBounds();
    }

    sf::CircleShape BallObject::get_ball(){
        return m_ball_object;
    }