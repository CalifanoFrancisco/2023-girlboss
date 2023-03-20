#include <SFML/Graphics.hpp>
#include <iostream>
#include "WFC.h"

int main() {
    WFC wavefunctioncollapse(10,10);
    wavefunctioncollapse.start();

    return 0;

    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    while (app.isOpen()) {
        sf::Event event;
        while (app.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: app.close(); break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return 0;
        }

        app.clear();
        app.display();
    }

    return EXIT_SUCCESS;
}
