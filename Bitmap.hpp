#ifndef BITMAP
#define BITMAP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>

struct Color {
    float R, G, B;
    Color():R(0), G(0), B(0) { }
    Color(float r, float g, float b):
        R(r), G(g), B(b) 
    { }
    bool operator==(const Color& color){
        if (R != color.R ||
            G != color.G ||
            B != color.B
        ) return false;
        return true;
    }
};

class Bitmap {
private:
    std::string m_filename;
    int m_height;
    int m_width;
    int m_bytesPerPixel;
    int m_row_increment;
    //unsigned char* data;    //dps optimizar
    std::vector<unsigned char> m_data;

    struct FileHeader {
        unsigned short type;
        unsigned int size;
        unsigned short reserved1;
        unsigned short reserved2;
        unsigned int off_bits;

        unsigned int struct_size() const {
            return 
                sizeof(type) +
                sizeof(size) +
                sizeof(reserved1) +
                sizeof(reserved2) +
                sizeof(off_bits)
            ;
        }

        void clear(){
            std::memset(this, 0x00, sizeof(FileHeader));
        }
    };
    
    struct InfoHeader {
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

        unsigned int struct_size() const {
            return 
                sizeof(size) +
                sizeof(width) +
                sizeof(height) +
                sizeof(planes) +
                sizeof(bit_count) +                   sizeof(compression) +
                sizeof(size_image) +
                sizeof(x_pels_per_meter) +
                sizeof(y_pels_per_meter) +
                sizeof(clr_used) +
                sizeof(clr_important)
            ;
        }

        void clear() {
            std::memset(this, 0x00, sizeof(InfoHeader));
        }
    };

    inline unsigned int   flip(const unsigned int& v) const {
        return (
            ((v & 0xFF000000) >> 0x18) |
            ((v & 0x000000FF) << 0x18) |
            ((v & 0x00FF0000) >> 0x08) |
            ((v & 0x0000FF00) << 0x08)
        );
    }
    inline unsigned short flip(const unsigned short& v) const {
        return ((v >> 8) | (v << 8));
    }

    template <typename T> inline void readFromStream(std::ifstream& stream, T& t) {
        stream.read(reinterpret_cast<char*>(&t), sizeof(T));
    }
    template <typename T> inline void writeToStream(std::ofstream& stream, const T& t) const {
        strean.write(reinterpret_cast<const char*>(&t), sizeof(T));
    }

    inline void readFileHeader (std::ifstream& stream, FileHeader& bmp_fh) {
        readFromStream(stream, bmp_fh.type);
        readFromStream(stream, bmp_fh.size);
        readFromStream(stream, bmp_fh.reserved1);
        readFromStream(stream, bmp_fh.reserved2);
        readFromStream(stream, bmp_fh.off_bits);
        if (big_endian()) {
            bmp_fh.type      = flip(bmp_fh.type);
            bmp_fh.size      = flip(bmp_fh.size);
            bmp_fh.reserved1 = flip(bmp_fh.reserved1);
            bmp_fh.reserved2 = flip(bmp_fh.reserved2);
            bmp_fh.off_bits  = flip(bmp_fh.off_bits);
        }
    }
    inline void readInfoHeader (std::ifstream& stream, InfoHeader& bmp_ih) {
        readFromStream(stream, bmp_ih.size);
        readFromStream(stream, bmp_ih.width);
        readFromStream(stream, bmp_ih.height);
        readFromStream(stream, bmp_ih.planes);
        readFromStream(stream, bmp_ih.bit_count);
        readFromStream(stream, bmp_ih.compression);
        readFromStream(stream, bmp_ih.size_image);
        readFromStream(stream, bmp_ih.x_pels_per_meter);
        readFromStream(stream, bmp_ih.y_pels_per_meter);
        readFromStream(stream, bmp_ih.clr_used);
        readFromStream(stream, bmp_ih.clr_important);
        if (big_endian()) {
            bmp_ih.size             = flip(bmp_ih.size);
            bmp_ih.width            = flip(bmp_ih.width);
            bmp_ih.height           = flip(bmp_ih.height);
            bmp_ih.planes           = flip(bmp_ih.planes);
            bmp_ih.bit_count        = flip(bmp_ih.bit_count);
            bmp_ih.compression      = flip(bmp_ih.compression);
            bmp_ih.size_image       = flip(bmp_ih.size_image);
            bmp_ih.x_pels_per_meter = flip(bmp_ih.x_pels_per_meter);
            bmp_ih.y_pels_per_meter = flip(bmp_ih.y_pels_per_meter);
            bmp_ih.clr_used         = flip(bmp_ih.clr_used);
            bmp_ih.clr_important    = flip(bmp_ih.clr_important);
        }
    }
    inline void writeFileHeader(std::ofstream& stream, FileHeader& bmp_fh) { 
        if (big_endian()) {
            writeToStream(stream, flip(bmp_fh.type));
            writeToStream(stream, flip(bmp_fh.size));
            writeToStream(stream, flip(bmp_fh.reserved1));
            writeToStream(stream, flip(bmp_fh.reserved2));
            writeToStream(stream, flip(bmp_fh.off_bits));
            return;
        }        
        writeToStream(stream, bmp_fh.type);
        writeToStream(stream, bmp_fh.size);
        writeToStream(stream, bmp_fh.reserved1);
        writeToStream(stream, bmp_fh.reserved2);
        writeToStream(stream, bmp_fh.off_bits);
    }
    inline void writeInfoHeader(std::ofstream& stream, InfoHeader& bmp_ih) { 
        if (big_endian()) {
            writeToStream(stream, flip(bmp_ih.size));
            writeToStream(stream, flip(bmp_ih.width));
            writeToStream(stream, flip(bmp_ih.height));
            writeToStream(stream, flip(bmp_ih.planes));
            writeToStream(stream, flip(bmp_ih.bit_count));
            writeToStream(stream, flip(bmp_ih.compression));
            writeToStream(stream, flip(bmp_ih.size_image));
            writeToStream(stream, flip(bmp_ih.x_pels_per_meter));
            writeToStream(stream, flip(bmp_ih.y_pels_per_meter));
            writeToStream(stream, flip(bmp_ih.clr_used));
            writeToStream(stream, flip(bmp_ih.clr_important));
            return;
        }
        writeToStream(stream, bmp_ih.size);
        writeToStream(stream, bmp_ih.width);
        writeToStream(stream, bmp_ih.height);
        writeToStream(stream, bmp_ih.planes);
        writeToStream(stream, bmp_ih.bit_count);
        writeToStream(stream, bmp_ih.compression);
        writeToStream(stream, bmp_ih.size_image);
        writeToStream(stream, bmp_ih.x_pels_per_meter);
        writeToStream(stream, bmp_ih.y_pels_per_meter);
        writeToStream(stream, bmp_ih.clr_used);
        writeToStream(stream, bmp_ih.clr_important);
        
    }

    inline bool big_endian() const {
        unsigned int v = 0x01;
        return 1 != (reinterpret_cast<char*>(&v)[0]);
    }
public:
    Bitmap(const unsigned int width, const unsigned height):
        m_filename(""),
        m_width(width),
        m_height(height),
        m_bytesPerPixel(3),
        m_row_increment(0) 
    { 
        createBitmap();
    }
    Bitmap(const Bitmap& bmp):
        m_filename(bmp.m_filename),
        m_height(bmp.m_height),
        m_width(bmp.m_width),
        m_row_increment(0),
        m_bytesPerPixel(3)
    { 
        createBitmap();
        m_data = bmp.m_data;
    }
    
    Bitmap& operator=(const Bitmap& bmp) {
        if (this != &bmp) {
            m_bytesPerPixel = bmp.m_bytesPerPixel;
            m_filename      = bmp.m_filename;
            m_height        = bmp.m_height;
            m_width         = bmp.m_width;
            createBitmap();
            m_data          = bmp.m_data;
        }
        return *this;
    }
    
    inline void clear(const unsigned char v = 0x00) {
        std::fill(m_data.begin(), m_data.end(), v);
    }

    void createBitmap() {
        m_row_increment = m_width * m_bytesPerPixel;
        m_data.resize(m_height * m_width);
    }

    inline Color getPixel(const unsigned int x, const unsigned int y) const {
        const unsigned int offset = y * m_row_increment + x * m_bytesPerPixel;
        return Color(
            m_data[offset + 0],
            m_data[offset + 1],
            m_data[offset + 2]
        );
    }
    inline void  setPixel(const Color& color, const unsigned int x, const unsigned int y) {
        const unsigned int offset = y * m_row_increment + x * m_bytesPerPixel;
        m_data[offset + 0] = color.B;
        m_data[offset + 1] = color.G;
        m_data[offset + 2] = color.R;
    }

    inline unsigned int width()  const { return m_width;  }
    inline unsigned int height() const { return m_height; }

    void fexport(const std::string& filename) {
        std::ofstream stream(filename.c_str(), std::ios::binary);
        if (!stream) {
            std::cerr << "could not open file" << std::endl;
            return;
        }

        InfoHeader bmp_ih;
        bmp_ih.width            = m_width;
        bmp_ih.height           = m_height;
        bmp_ih.bit_count        = static_cast<unsigned short>(m_bytesPerPixel << 3);
        bmp_ih.clr_important    = 0;
        bmp_ih.clr_used         = 0;
        bmp_ih.compression      = 0;
        bmp_ih.planes           = 1;
        bmp_ih.size             = bmp_ih.struct_size();
        bmp_ih.x_pels_per_meter = 0;
        bmp_ih.y_pels_per_meter = 0;
        bmp_ih.size_image       = (((bmp_ih.width * m_bytesPerPixel) + 3) & 0x0000FFFC) * bmp_ih.height;

        FileHeader bmp_fh;
        bmp_fh.type             = 19778;
        bmp_fh.size             = bmp_fh.struct_size() + bmp_fh.struct_size() + bmp_ih.size_image;
        bmp_fh.reserved1        = 0;
        bmp_fh.reserved2        = 0;
        bmp_fh.off_bits         = bmp_fh.struct_size() + bmp_fh.struct_size();
        
        writeFileHeader(stream, bmp_fh);
        writeInfoHeader(stream, bmp_ih);

        unsigned int padding = (4 - ((3 * m_width) % 4)) % 4;
        char padding_data[4] = {0x00, 0x00, 0x00, 0x00};

        for (unsigned int i = 0; i < m_height; ++i) {
            const unsigned char* data_ptr = &m_data[(m_row_increment * (m_height - i - 1))];
            stream.write(
                reinterpret_cast<const char*>(data_ptr),
                sizeof(unsigned char) * m_bytesPerPixel * m_width
            );
            stream.write(padding_data, padding);
        }
        stream.close();
    }
};

#endif