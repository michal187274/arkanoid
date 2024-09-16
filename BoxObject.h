
#include <SFML/Graphics.hpp>
struct box_sides{
    float left;
    float right;
    float up;
    float down;
};

class BoxObject{
    
    sf::RectangleShape box_object;
    sf::Vector2f box_object_size;
    box_sides sides;
    sf::FloatRect global_bounds;
    bool was_hit = false;
    sf::Vector2f position;

public:
    BoxObject(sf::Vector2f size) : box_object_size(size) {
        box_object = sf::RectangleShape(size); //co tu sie dzieje, konstr kopiujacy?
    };
    void set_position(sf::Vector2f position);
    void calculate_sides();
    void set_outline();
    void set_global_bounds();
    void set_was_hit(bool hit);

    bool get_was_hit();
    sf::Vector2f get_position();
    sf::FloatRect get_gloabal_bounds();
    box_sides get_sides();
    sf::RectangleShape get_box_object();


};