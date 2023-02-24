#include "CubeMap.h"
#include "TileTypes.h"

//-- ctor & dtor --------------------------------------------------------------------------------------------
CubeMap::CubeMap(const unsigned int x_, const unsigned int y_, const unsigned int z_) {    
    m_size = sf::Vector3i(x_, y_, z_);
    m_map = tripleAllocator<sf::Sprite>();
    int*** auxTypeMap = tripleAllocator<int>();
    tripleIterator([&auxTypeMap](int x, int y, int z) { auxTypeMap[x][y][z] = g_tileType::CUBE; });
    m_typeMap = auxTypeMap;
}

CubeMap::CubeMap(const unsigned int x_, const unsigned int y_, const unsigned int z_, g_tileType tile) {
    m_size = sf::Vector3i(x_, y_, z_);
    m_map = tripleAllocator<sf::Sprite>();
    int*** auxTypeMap = tripleAllocator<int>();
    tripleIterator([&auxTypeMap, tile](int x, int y, int z) { auxTypeMap[x][y][z] = tile; });
    m_typeMap = auxTypeMap;
}

CubeMap::CubeMap(std::string filename) {
    fimport(filename);
}

CubeMap::~CubeMap() {
    tripleDeAllocator<sf::Sprite>(m_map);
    tripleDeAllocator<int>(m_typeMap);
}

//-- @Override ----------------------------------------------------------------------------------------------
void CubeMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int x = 0; x < m_size.x; x++) {
        for (int y = 0; y < m_size.y; y++) {
            for (int z = 0; z < m_size.z; z++) {
                target.draw(m_map[x][y][z], states);
            }
        }
    }
  
}

//-- Func ---------------------------------------------------------------------------------------------------
const sf::Vector3i& CubeMap::size() { 
    return m_size; 
}

void CubeMap::scale(sf::Vector2f factor) {
    sf::Sprite*** aux = m_map;
    tripleIterator([&aux, factor](int x, int y, int z) { aux[x][y][z].scale(factor); });
    m_map = aux;
}

bool CubeMap::loadTexture(std::string filename) {
    //cannot use tripleIterator function due to texture references needing to be a const reference
    m_texture.loadFromFile(filename);
    sf::IntRect smallTexture;
    for (int x = 0; x < m_size.x; x++) {
    for (int y = 0; y < m_size.y; y++) {
    for (int z = 0; z < m_size.z; z++) {       
        m_map[x][y][z].setTextureRect(sf::IntRect(49 * m_typeMap[x][y][z], 0, 49, 49));
        m_map[x][y][z].setTexture(m_texture);
    }
    }
    }
    return true;
}

void CubeMap::arrange() {
    const sf::Vector2f spriteSize(
        49 * m_map[0][0][0].getScale().x,
        49 * m_map[0][0][0].getScale().y
    );
    sf::Sprite*** aux = m_map;
    sf::Vector3i  size = m_size;
    tripleIterator(
        [&aux, spriteSize, size](int x, int y, int z) {
            aux[x][y][z].setPosition(
                x * (spriteSize.x / 2) + ((size.x - y) * (spriteSize.x / 2)),
                y * (spriteSize.y / 2) + ((size.x - y) * (spriteSize.y / 4)) + x * (spriteSize.y / 4) -
                z * (spriteSize.y / 2)
            );
        }
    );
    m_map = aux;
}

bool CubeMap::fexport(std::string filename) {
    std::ofstream file(filename);
    file << m_size.x << " " << m_size.y << " " << m_size.z << std::endl;
    int*** auxTypeMap = m_typeMap;
    tripleIterator([&file, auxTypeMap](int x, int y, int z) { file << auxTypeMap[x][y][z] << " "; });
    file.close();
    return true;
}

bool CubeMap::fimport(std::string filename) {
    std::ifstream file(filename);
    if (!file) return false;                //Check if file exists
    std::string word = "";

    //deallocate old memory                 // @Optimization:
    tripleDeAllocator<int>(m_typeMap);        //   Reduce iterations by not 
    tripleDeAllocator<sf::Sprite>(m_map);     //   using lambda tripleDeAllocator<>()

    file >> word; m_size.x = stoi(word);
    file >> word; m_size.y = stoi(word);
    file >> word; m_size.z = stoi(word);

    //reallocate with updated m_size
    m_typeMap = tripleAllocator<int>();
    m_map = tripleAllocator<sf::Sprite>();

    //iterate through file and copy 
    for (sf::Vector3i coors(0, 0, 0); file >> word; coors.z++) {
        if (coors.z == m_size.z) { coors.z = 0; coors.y++; }
        if (coors.y == m_size.y) { coors.y = 0; coors.x++; }
        m_typeMap[coors.x][coors.y][coors.z] = stoi(word);
    }
    file.close();
    return true;
}