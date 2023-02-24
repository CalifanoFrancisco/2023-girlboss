holiis

este proyecto lo hice creo q en diciembre 2022 por alguna razon
error "Memory access violation 0xFFFFFFF" no importa pq pasa con el destructor del TileMap pero b0e no se puede todo en la vida
tileset personalizado por favorrr (hay una textura rampa q esta mal el ángulo tho)

buen candidato para probar el WFC? nose hay q ver a futuro

Documentacion (a casa maier):

CubeMap(const unsigned int x_, const unsigned int y_, const unsigned int z_)
CubeMap(const unsigned int x_, const unsigned int y_, const unsigned int z_, g_tileType tile)
  Ambos reciben el tamaño de la matriz 3D, segunda versionn les asigna a todas las casillas un tipo (del enum TileTypes.h)
  
CubeMap(std::string filename)
  Carga matriz desde archivo .txt
  
CubeMap::draw(sf::RenderTarget& target, sf::RenderStates states) 
  Permite que el objeto sea dibujable por SFML
  
CubeMap::scale(sf::Vector2f factor)
  Me daba paja hacer el @Override de Entity::scale()  
  
CubeMap::loadTexture(std::string filename)
  carga el tileset de casillas de 49px * 49px 
 
CubeMap::arrange()
  FUNCION ESCENCIAL PARA Q ANDE, acomoda los cubos para que den la ilusion 3D
  
 CubeMap::fexport(std::string filename) && CubeMap::fimport(std::string filename)
  exportan/importan a archivo .txt

TODO:
  Hacer que TileMap extienda sf::Transformable asi aprovecho que ya esta programado

OPTIMiZACIONES:
Transformar matriz 3D en una matriz unidimensional (array):

class IsoMap {
private:
  sf::Vector3i m_size;
public:
  T* matrix = new T[z * y * z];
  T operator[][][](uint x, uint y, uint z) {  //nose si es posible :(  ->   sino usar un macro :)
    return matrix[
      size.x * x +
      size.y * y +
      size.z * z
    ];
  }
};

vamos cali que se puede carajo >:)
