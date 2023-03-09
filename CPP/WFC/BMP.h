#ifndef BMP_IMAGE
#define BMP_IMAGE

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

//funka todo :D

namespace bmp {

struct rgb_t {
	unsigned char R, G, B;
    rgb_t();
    rgb_t(unsigned int r, unsigned int g, unsigned int b);
};

template <typename T> inline void read_from_stream(std::ifstream& stream, T& t) {
    stream.read(reinterpret_cast<char*>(&t), sizeof(T));
}

template <typename T> inline void write_to_stream(std::ofstream& stream, const T& t) {
    stream.write(reinterpret_cast<const char*>(&t), sizeof(T));
}

inline unsigned short flip(const unsigned short& v);
inline unsigned int flip(const unsigned int& v);
inline bool big_endian();

struct bitmap_file_header {
public:
    unsigned short type;
    unsigned int   size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int   off_bits;

    unsigned int struct_size() const;
    void clear();
    void read(std::ifstream& stream, bitmap_file_header& bfh);
    void write(std::ofstream& stream, const bitmap_file_header& bfh);
};

struct bitmap_information_header {
public:
    unsigned int   size;
    unsigned int   width;
    unsigned int   height;
    unsigned short planes;
    unsigned short bit_count;
    unsigned int   compression;
    unsigned int   size_image;
    unsigned int   x_pels_per_meter;
    unsigned int   y_pels_per_meter;
    unsigned int   clr_used;
    unsigned int   clr_important;

    unsigned int struct_size() const;
    void clear();
    void read(std::ifstream& stream, bitmap_information_header& bih);
    void write(std::ofstream& stream, const bitmap_information_header& bih);
};

class Bitmap {
private:
	int m_width;
	int m_height;
	int m_row_increment;
	int m_bytes_per_pixel;
    std::vector<unsigned char> m_data;

    std::vector<unsigned char> data() const;
    inline std::size_t file_size(const std::string& filename) const;
    inline unsigned char* row(unsigned int row_index) const;
public:
    Bitmap(unsigned int x, unsigned int y);
    void init();

	Bitmap& operator=(const Bitmap& x);
    bool operator==(const Bitmap x);

	inline void clear(const unsigned char v = 0x00);
    void setPixel(const unsigned int x, const unsigned int y, const unsigned char red, const unsigned char green, const unsigned char blue);
    void setPixel(const unsigned int x, const unsigned int y, rgb_t color);
    inline void getPixel(const unsigned int x, const unsigned int y, unsigned char& red, unsigned char& green, unsigned char& blue) const;
    inline rgb_t getPixel(const unsigned int x, const unsigned int y) const;

    int width() const;
    int height() const;

    void fimport(const std::string& filename);
	void fexport(const std::string& filename) const;
};

}

#endif // !BMP_IMAGE