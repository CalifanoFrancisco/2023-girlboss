#include <SFML/Graphics.hpp>
#include <iostream>
#include "CubeMap.h"

#define println(x) std::cout << x << std::endl
#define print(x)   std::cout << x
#define FPS 30

const sf::Vector2i resolution = sf::Vector2i(1000, 1000);
sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Screen");

void window_init() {
    window.setFramerateLimit(FPS);
}

class Tile {

    enum m_type {
        EMPTY,
        CUBE,
        STAIR_SOUTHEAST,
        STAIR_SOUTHWEST,
        STAIR_NORTHWEST,
        STAIR_NORTHEAST,
        RAMP_SOUTHEAST,
        RAMP_SOUTHWEST,
        RAMP_NORTHWEST,
        RAMP_NORTHEAST,
        CUBE_HOLE_TOP,
        CUBE_HOLE_SOUTHEAST,
        CUBE_HOLE_SOUTHWEST
    };

};

void moveCamera(sf::View& view) {
    float movement = 20.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) view.move(0.f, -movement);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) view.move(-movement, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) view.move(0.f, movement);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) view.move(movement, 0.f);
}

CubeMap initCubeMap(std::string filename) {
    CubeMap out(filename);
    out.loadTexture("cube-types.png");
    out.scale(sf::Vector2f(4.f, 4.f));
    out.arrange();
    return out;
}

int main() {

    //CubeMap map = initCubeMap("testeo2.txt");
    CubeMap map(5, 4, 3);
    //map.fimport("testeo2.txt");
    map.loadTexture("cube-types.png");
    map.scale(sf::Vector2f(4.f, 4.f));
    map.arrange();

    sf::View view;
    view.zoom(1.5f);

    window_init();

    while (window.isOpen()) {
        window.clear();
        //--------------------------------------------------------------------------------------------------------
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Escape) { window.close(); return 0; }
                break;
            }
            }
        }
        //--------------------------------------------------------------------------------------------------------
        window.setView(view);
        moveCamera(view);
        //--------------------------------------------------------------------------------------------------------
        window.draw(map);
        //--------------------------------------------------------------------------------------------------------
        window.display();
    }
    window.close();
    return 0;
}

