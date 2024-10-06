#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BoxObject.h"
#include "BallObject.h"
#include "BoardObject.h"

inline const sf::Vector2f ball_initial_position(350,350);
inline const sf::Vector2f board_initial_position(400,500);
inline const sf::Vector2f initial_ball_move_step(-0.8,-0.8);
inline const sf::Vector2f ball_direction (0,-0.5);
inline const sf::Vector2f intial_board_move_step(-300,0);
inline float ball_speed(180);

inline const int boxes_rows = 3; 
inline const sf::Vector2f box_size(80,40);
inline const sf::Vector2f board_size(80,4);
inline const int ball_radius(10);
class GameState{
    std::vector<BoxObject> vector_of_boxes;
    BallObject m_ball;
    BoardObject m_board;
    float m_delta_time;
    sf::Vector2f m_ball_direction;
    sf::Vector2f m_ball_move_step;
    sf::Vector2f m_board_move_step;
    intersection_points m_ball_intersection_points;

    sf::Vector2f board_position;
    bool m_game_was_started = false;


public:
    void create_boxes(int, sf::Vector2f, sf::Vector2u);
    void create_ball(float);
    void create_board(sf::Vector2f);
    void start_game(sf::Vector2u);
    void stop_game();
    std::vector<BoxObject> get_boxes_vector();
    BallObject& get_ball_object();
    float get_delta_time() {return m_delta_time;};

    void set_delta_time(float);
    void move_ball();
    void move_board(sf::Vector2f);

    void ball_wall_collision();
    void ball_board_collision();
    bool handle_keyboard();
    void ball_box_collision();

    void draw(sf::RenderWindow&);
};

#endif
























