#include "Menu.h"

void Menu::create_menu(){
    m_font.loadFromFile("../../arial.ttf");
    m_text.setFont(m_font);
    m_text.setString("Press ""p"" to play");
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Red);
    m_text.setStyle(sf::Text::Bold);
    m_text.setPosition(300,300);
}


void Menu::draw(sf::RenderWindow& window){
    window.draw(m_text); 
    window.display();
    window.clear(sf::Color::Black);
}

void Menu::handle_keyboard(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        m_game_start=true;

}

bool Menu::game_start(sf::RenderWindow& window, GameState& game, sf::Vector2u window_size){
    if(!m_game_start){
        draw(window);
        handle_keyboard();
        return false;
    }
    else{
        game.start_game(window_size);
        return true;
    }
}

void Menu::set_game_stop(){
    m_game_start = false;
}

