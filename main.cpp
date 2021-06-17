#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <random>
#include "windows.h"
#include "Snake.h"

void draw(Snake snake, /** The game class object */
          sf::RenderWindow *window, /** Game window pointer */
          std::vector<std::vector<sf::Sprite>>& sprites /** Global sprite matrix */
          ) /** function that apply changes to the global sprite matrix */ {
    sf::Texture snake_texture, wall_texture, empty_texture, apple_texture;
    snake_texture.loadFromFile("snake.jpg");
    wall_texture.loadFromFile("wall.jpg");
    empty_texture.loadFromFile("empty.jpg");
    apple_texture.loadFromFile("apple.jpg");
    for (int i = 0; i < snake.field.size; i++) {
        for (int j = 0; j < snake.field.size; j++) {
            switch (snake.field.body[i][j]) {
                case Wall_id:
                    sprites[i][j].setTexture(wall_texture);
                    break;
                case Snake_id:
                    sprites[i][j].setTexture(snake_texture);
                    break;
                case Empty_id:
                    sprites[i][j].setTexture(empty_texture);
                    break;
                case Apple_id:
                    sprites[i][j].setTexture(apple_texture);
                    break;
            }
        }
    }
    for (int i = 0; i < snake.field.size; i++) {
        for (int j = 0; j < snake.field.size; j++) {
            window->draw(sprites[i][j]);
        }
    }
    window->display();
}

int main() {
    const int n = 6;
    sf::RenderWindow window;
    window.create(sf::VideoMode(640, 640), "My window");
    sf::Texture texture;
    texture.loadFromFile("play_button.jpg");
    sf::Sprite sprite(texture);
    sf::Rect sprite_rect = sprite.getTextureRect();
    unsigned int button_x = (window.getSize().x - sprite_rect.width) / 2;
    unsigned int button_y = (window.getSize().y - sprite_rect.height) / 2;
    sprite_rect.left = button_x;
    sprite_rect.top = button_y;
    sprite.setPosition(button_x, button_y);
    Snake snake(n);
    std::vector<std::vector<sf::Sprite>> sprites;
    for (int i = 0; i < n; i++) {
        std::vector<sf::Sprite> sprite_column;
        for (int j = 0; j < n; j++) {
            sprite_column.emplace_back();
            sprite_column[j].setPosition(10.f / float(n) * 64 * i, 10.f / float(n) * 64 * j);
            sprite_column[j].scale(sf::Vector2f(10.f / float(n), 10.f / float(n)));
        }
        sprites.push_back(sprite_column);
    }

    bool working = snake.move();
    bool game = true;
    sf::Event event;

    int cycle = 0;
    while (working) {
        bool happen = window.pollEvent(event);
        if (game) {
            Sleep(32);
            if (cycle == 100 / snake.field.size - 1)
                game = snake.move();
            draw(snake, &window, sprites);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { snake.up(); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { snake.left(); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { snake.right(); }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { snake.down(); }
            cycle = (cycle + 1) % (100 / snake.field.size);
            if (not game)
                draw(snake, &window, sprites);
        } else {
            window.draw(sprite);
            window.display();
            if (happen and event.type == sf::Event::MouseButtonPressed and
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2 pos = sf::Mouse::getPosition(window);
                if (sprite_rect.contains(pos)) {
                    game = snake.new_game();
                }
            }
        }
        if (happen and event.type == sf::Event::Closed) {
            window.close();
            working = false;
        }
    }
    return 0;
}