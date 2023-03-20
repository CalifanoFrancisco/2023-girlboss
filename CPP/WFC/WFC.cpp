#include "WFC.h"

TileInfo::TileInfo(t_tile texture_, bool up, bool down, bool left, bool right) :
    UP(up), DOWN(down), LEFT(left), RIGHT(right), texture(texture_)
{ }

TileInfo::TileInfo() :
    UP(0), DOWN(0), LEFT(0), RIGHT(0), texture(t_tile::NONE)
{
}

Tile::Tile(const std::vector<TileInfo>& info)
{
    tiles.resize(info.size());
    for (int i = 0; i < tiles.size(); i++)
        tiles[i] = info[i].texture;
}

Tile::Tile():
    texture(t_tile::NONE)
{ }

WFC::WFC(int x, int y) :
    m_height(y), m_width(x), m_tiles(std::vector<Tile>(x * y)), m_TotalTextures(12)
{
    init();
}

void WFC::init() {
    atlas.loadFromFile("tileTypes.png");
    //each tile must be 10*10
    println("File \"tileTypes.png\" loaded.");

    m_rules.resize(atlas.getSize().x/10);
    //                     TEXTURE                  U  D  L  R
    m_rules[0]  = TileInfo(t_tile::DOWN_RIGHT     , 0, 1, 0, 1);
    m_rules[1]  = TileInfo(t_tile::DOWN_UP        , 1, 1, 0, 0);
    m_rules[2]  = TileInfo(t_tile::DOWN_LEFT      , 0, 1, 1, 0);
    m_rules[3]  = TileInfo(t_tile::LEFT_RIGHT     , 0, 0, 1, 1);
    m_rules[4]  = TileInfo(t_tile::UP_RIGHT       , 1, 0, 0, 1);
    m_rules[5]  = TileInfo(t_tile::UP_LEFT        , 1, 0, 1, 0);
    m_rules[6]  = TileInfo(t_tile::LEFT_UP_DOWN   , 1, 1, 1, 0);
    m_rules[7]  = TileInfo(t_tile::RIGHT_UP_DOWN  , 1, 1, 0, 1);
    m_rules[8]  = TileInfo(t_tile::UP_LEFT_RIGHT  , 1, 0, 1, 1);
    m_rules[9]  = TileInfo(t_tile::DOWN_LEFT_RIGHT, 0, 1, 1, 1);
    m_rules[10] = TileInfo(t_tile::ALL            , 1, 1, 1, 1);
    m_rules[11] = TileInfo(t_tile::NONE           , 0, 0, 0, 0);

    println(std::string("WFC successfully initiated"));
    //aca bolude
    for (int i = 0; i < m_tiles.size(); i++)
        m_tiles[i] = Tile(m_rules);

    m_output.resize(m_tiles.size());
}

int  WFC::random(int min, int max) const {
    return min + rand() % max;
}

void WFC::collapse(const unsigned int n_tile) {
    int tileType = random(0, m_tiles[n_tile].tiles.size());    //choose random tile texture from avilable textures
    m_tiles[n_tile].texture = static_cast<t_tile>(tileType);
    m_tiles[n_tile].tiles.clear();  //sets entropy == 0
    println(std::string(
      "Tile n°" + std::to_string(n_tile) + " collapsed to state " + std::to_string(tileType)
    ));
}

void WFC::propagate() {
    int n_tile = 83;
    if (
        n_tile + m_width > m_width * m_height ||
        n_tile - m_width < 0                  ||
        n_tile + 1       < m_width * m_height

    ) { }
}

void WFC::start() {
    //Init output
    collapse(random(0, m_tiles.size()));
    propagate();
    while (true) {

    }
}
void WFC::fexport() { }



