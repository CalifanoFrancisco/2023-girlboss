holiis

este proyecto lo hice creo q en diciembre 2022 por alguna razon
error "Memory access violation 0xFFFFFFF" no importa pq pasa con el destructor del TileMap pero b0e no se puede todo en la vida
tileset personalizado por favorrr (hay una textura rampa q esta mal el ángulo tho)

buen candidato para probar el WFC? nose hay q ver a futuro

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
