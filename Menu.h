#include <SFML/Graphics.hpp>
#include "GameState.h"



class Menu{
    
    sf::Font m_font;
    sf::Text m_text;
    bool m_game_start = false;

    void draw(sf::RenderWindow&);
    void handle_keyboard();

public:
    void create_menu();
    GameState* game_start(sf::RenderWindow&, sf::Vector2u);
    void game_stop(GameState*);
};