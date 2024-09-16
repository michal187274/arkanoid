#include <SFML/Graphics.hpp>
#include <iostream>
#include "BoxObject.h"
#include "BallObject.h"

class GameState{
    sf::Vector2f window_size;
    sf::RenderWindow window;
    sf::Vector2f box_size;
    int no_of_boxes_rows;
    std::vector<BoxObject> vector_of_boxes;
    BallObject m_ball;

public:
    void create_boxes(int, sf::Vector2f);
    void create_ball(float);
    sf::RenderWindow& get_window();
    std::vector<BoxObject> get_boxes_vector();
    BallObject get_ball_object();

    void set_box_size(sf::Vector2f);
    void create_window(sf::Vector2f);
    void draw_boxes();
    void draw_ball();
};

























