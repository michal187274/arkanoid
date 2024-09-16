
#include <SFML/Graphics.hpp>
struct intersection_points{
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
    void move();
    void set_position(sf::Vector2f position);
    void calculate_intersection_points();
    void set_outline();
    void set_radius(float);
    void set_move_step(sf::Vector2f);

    sf::Vector2f get_position();
    sf::FloatRect get_gloabal_bounds();
    intersection_points get_intersection_points();
    sf::CircleShape get_ball_object();


};