#include <SFML/Graphics.hpp>

class BoardObject{
    
    sf::RectangleShape m_board_object;
    sf::FloatRect m_global_bounds;

public:
    BoardObject() {};
    void set_position(sf::Vector2f position) {m_board_object.setPosition(position);};
    void set_size(sf::Vector2f size) {m_board_object.setSize(size);};
    
    sf::FloatRect get_global_bounds() {return m_board_object.getGlobalBounds();};
    sf::Vector2f get_position(){return m_board_object.getPosition();};
    sf::RectangleShape get_board(){return m_board_object;};

    void move(sf::Vector2f step){m_board_object.move(step);};


};