#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>      //export and import
#include <sstream>      //to stop "0xDDDDDDDD" memory access violation
#include "TileTypes.h"  //enum

class CubeMap : public sf::Drawable {
private:
    sf::Vector3i  m_size;
    sf::Texture   m_texture;
    sf::Sprite*** m_map;
    int***        m_typeMap;

    template <typename F> void tripleIterator(const F& funct) {
        //Iterate through map using a Lambda "[&modifiable_val, reference_val](parameters){ function_content }"
        //tripleIterator([&modifiable, nonModifiable](int x, int y, int z) { code } );
        for (int x = 0; x < m_size.x; x++) {
            for (int y = 0; y < m_size.y; y++) {
                for (int z = 0; z < m_size.z; z++) {
                    funct(x, y, z);
                }
            }
        }
    }    
    template <typename T> T*** tripleAllocator() {
        T*** out = new T * *[m_size.x];
        for (int x = 0; x < m_size.x; x++) {
            out[x] = new T * [m_size.y];
            for (int y = 0; y < m_size.y; y++) {
                out[x][y] = new T[m_size.z];
            }
        }
        return out;
    }
    template <typename T> void tripleDeAllocator(T*** &del) {
        if (del == NULL) return;
        std::stringstream ss;   ss << *del;
        if (ss.str() == "DDDDDDDD") return;

        for (int x = 0; x < m_size.x; x++) {
            for (int y = 0; y < m_size.y; y++) {
                delete[]del[x][y];
            }
            delete[]del[x];
        }
        delete[]del;
        del = nullptr;
    }
    
    //@Override
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
   
    CubeMap(const unsigned int x_, const unsigned int y_, const unsigned int z_);
    CubeMap(const unsigned int x_, const unsigned int y_, const unsigned int z_, g_tileType tile);
    CubeMap(std::string filename);
    ~CubeMap();

    const sf::Vector3i& size();

    void scale(sf::Vector2f factor);
    bool loadTexture(std::string filename);
    void arrange();
    bool fexport(std::string filename);
    bool fimport(std::string filename);
};

/* TODO
* - fexport/fimport add texture filename("cube-types.png") in output file 
* - @Override scale?
* - fix angle of the ramp sprites
*/
