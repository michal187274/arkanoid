#include "BoxObject.h"

sf::RectangleShape BoxObject::get_box_object(){
    return box_object;
}

void BoxObject::set_position(sf::Vector2f pos){
    position = pos;
    box_object.setPosition(position);
}

void BoxObject::calculate_sides(){
    sides.left = position.x;
    sides.right = sides.left + box_object.getSize().x;
    sides.up = position.y;
    sides.down = sides.up + box_object.getSize().y;
}

void BoxObject::set_outline(){
    box_object.setOutlineColor(sf::Color::Green);
    box_object.setOutlineThickness(4);
}

sf::Vector2f BoxObject::get_position(){
    return position;
}

sf::FloatRect BoxObject::get_global_bounds(){
    return box_object.getGlobalBounds();
}

box_sides BoxObject::get_sides(){
    calculate_sides();
    return sides;
}