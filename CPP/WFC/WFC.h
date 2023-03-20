#ifndef WFC_H
#define WFC_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>     //rand();
#include <string>       //std::to_string(int n);
#include <vector>

#define DEBUG 1
#if DEBUG
    #define println(x) std::cout << x << std::endl
    #define print(x)   std::cout << x
#else
    #define println(x)
    #define print(x)
#endif // DEBUG

enum t_tile {
    DOWN_RIGHT      = 0,
    DOWN_UP         = 1,
    DOWN_LEFT       = 2,
    LEFT_RIGHT      = 3,
    UP_RIGHT        = 4,
    UP_LEFT         = 5,
    LEFT_UP_DOWN    = 6,
    RIGHT_UP_DOWN   = 7,
    UP_LEFT_RIGHT   = 8,
    DOWN_LEFT_RIGHT = 9,
    ALL             = 10,
    NONE            = 11
};

 struct TileInfo {
    bool UP, DOWN, LEFT, RIGHT;
    t_tile texture;
    TileInfo();
    TileInfo(bool up, bool down, bool left, bool right);
    TileInfo(t_tile texture, bool up, bool down, bool left, bool right);
};

struct Tile {
    //Non collapsed
    std::vector<t_tile> tiles;  //size() == entropy
    //Collapsed
    t_tile texture;
    Tile(const std::vector<TileInfo>& info);
    Tile();
};

class WFC : public sf::Drawable {
private:


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        std::cout << "falta esto" << std::endl;
    }
    int random(int min, int max) const;

    std::vector<TileInfo> m_rules;
    std::vector<Tile> m_tiles;
    int m_height, m_width;
    int m_TotalTextures;
    sf::Texture atlas;

    std::vector<int> m_output;
public:
    WFC(int x, int y);  //init
    void init();
    void propagate();   //Modify entropy of tiles
    void collapse(const unsigned int n_tile);    //Collapse single tile to state
    void start();
    void fexport();     //Export image
};

#endif // WFC_H
