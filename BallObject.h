
#include <SFML/Graphics.hpp>
#include <iostream>

struct intersection_points{
    intersection_points() {};
    intersection_points(float a_left, float a_right, float a_up, float a_down) : 
                        left(a_left),
                        right(a_right),
                        up(a_up),
                        down(a_down) {};
    float left;
    float right;
    float up;
    float down;
};

class BallObject{
    sf::Vector2f m_move_step;
    sf::CircleShape m_ball_object;
    float m_radius;
    intersection_points m_points;
    sf::FloatRect m_global_bounds;
    sf::Vector2f m_position;

public:
    BallObject() {};
    void move(sf::Vector2f);
    void set_position(sf::Vector2f position);
    void calculate_intersection_points();
    void set_outline();
    void set_radius(float);
    void update_position();
    
    sf::Vector2f get_position();
    sf::FloatRect get_global_bounds();
    sf::CircleShape get_ball();
    float get_radius() {return m_radius;};
    intersection_points get_intersection_points();
};