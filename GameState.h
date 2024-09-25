#include <SFML/Graphics.hpp>
#include <iostream>
#include "BoxObject.h"
#include "BallObject.h"
#include "BoardObject.h"

const sf::Vector2f ball_initial_position(400,501);
const sf::Vector2f board_initial_position(400,500);
sf::Vector2f initial_ball_move_step(-60,-80);
sf::Vector2f intial_board_move_step(-60,0);
class GameState{
    sf::Vector2f window_size;
    sf::Vector2f box_size;
    int no_of_boxes_rows;
    std::vector<BoxObject> vector_of_boxes;
    BallObject m_ball;
    BoardObject m_board;
    sf::RenderWindow& window;
    float m_delta_time;
    sf::Vector2f m_ball_move_step = initial_ball_move_step;
    sf::Vector2f m_board_move_step = intial_board_move_step;
    intersection_points m_ball_intersection_points;


public:
    GameState(sf::RenderWindow& w) : window(w){};
    void create_boxes(int, sf::Vector2f);
    void create_ball(float);
    void create_board(sf::Vector2f);
    std::vector<BoxObject> get_boxes_vector();
    BallObject& get_ball_object();
    float get_delta_time() {return m_delta_time;};

    void set_box_size(sf::Vector2f);
    void set_delta_time(float);
    void draw_boxes();
    void draw_ball();
    void move_ball();
    void move_board(sf::Vector2f);

    void ball_wall_collision();
    void ball_board_collision();
    void handle_event(sf::Event ev);
    void ball_box_collision();

    void draw();
};

























