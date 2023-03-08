#include "BMP.h"

//Auxiliar functions
unsigned short bmp::flip(const unsigned short& v)
{
    return ((v >> 8) | (v << 8));
}

unsigned int bmp::flip(const unsigned int& v)
{
    return (
        ((v & 0xFF000000) >> 0x18) |
        ((v & 0x000000FF) << 0x18) |
        ((v & 0x00FF0000) >> 0x08) |
        ((v & 0x0000FF00) << 0x08)
    );
}

bool bmp::big_endian() {
    unsigned int v = 0x01;
    return (1 != reinterpret_cast<char*>(&v)[0]);
}

//Bitmap_file_header
unsigned int bmp::bitmap_file_header::struct_size() const {
    return (
        sizeof(type) +
        sizeof(size) +
        sizeof(reserved1) +
        sizeof(reserved2) +
        sizeof(off_bits)
    );
}

void bmp::bitmap_file_header::clear()
{
    std::memset(this, 0x00, sizeof(bitmap_file_header));
}

void bmp::bitmap_file_header::read(std::ifstream& stream, bitmap_file_header& bfh)
{
    read_from_stream(stream, bfh.type);
    read_from_stream(stream, bfh.size);
    read_from_stream(stream, bfh.reserved1);
    read_from_stream(stream, bfh.reserved2);
    read_from_stream(stream, bfh.off_bits);

    if (big_endian())
    {
        bfh.type      = flip(bfh.type);
        bfh.size      = flip(bfh.size);
        bfh.reserved1 = flip(bfh.reserved1);
        bfh.reserved2 = flip(bfh.reserved2);
        bfh.off_bits  = flip(bfh.off_bits);
    }
}

void bmp::bitmap_file_header::write(std::ofstream& stream, const bitmap_file_header& bfh)
{
    if (big_endian())
    {
        write_to_stream(stream, flip(bfh.type));
        write_to_stream(stream, flip(bfh.size));
        write_to_stream(stream, flip(bfh.reserved1));
        write_to_stream(stream, flip(bfh.reserved2));
        write_to_stream(stream, flip(bfh.off_bits));
    }
    else
    {
        write_to_stream(stream, bfh.type);
        write_to_stream(stream, bfh.size);
        write_to_stream(stream, bfh.reserved1);
        write_to_stream(stream, bfh.reserved2);
        write_to_stream(stream, bfh.off_bits);
    }
}

//Bitmap_information_header
unsigned int bmp::bitmap_information_header::struct_size() const
{
    return (
        sizeof(size) +
        sizeof(width) +
        sizeof(height) +
        sizeof(planes) +
        sizeof(bit_count) +
        sizeof(compression) +
        sizeof(size_image) +
        sizeof(x_pels_per_meter) +
        sizeof(y_pels_per_meter) +
        sizeof(clr_used) +
        sizeof(clr_important)
    );
}

void bmp::bitmap_information_header::clear()
{
    std::memset(this, 0x00, sizeof(bitmap_information_header));
}

void bmp::bitmap_information_header::read(std::ifstream& stream, bitmap_information_header& bih)
{
    read_from_stream(stream, bih.size);
    read_from_stream(stream, bih.width);
    read_from_stream(stream, bih.height);
    read_from_stream(stream, bih.planes);
    read_from_stream(stream, bih.bit_count);
    read_from_stream(stream, bih.compression);
    read_from_stream(stream, bih.size_image);
    read_from_stream(stream, bih.x_pels_per_meter);
    read_from_stream(stream, bih.y_pels_per_meter);
    read_from_stream(stream, bih.clr_used);
    read_from_stream(stream, bih.clr_important);

    if (big_endian())
    {
        bih.size             = flip(bih.size);
        bih.width            = flip(bih.width);
        bih.height           = flip(bih.height);
        bih.planes           = flip(bih.planes);
        bih.bit_count        = flip(bih.bit_count);
        bih.compression      = flip(bih.compression);
        bih.size_image       = flip(bih.size_image);
        bih.x_pels_per_meter = flip(bih.x_pels_per_meter);
        bih.y_pels_per_meter = flip(bih.y_pels_per_meter);
        bih.clr_used         = flip(bih.clr_used);
        bih.clr_important    = flip(bih.clr_important);
    }
}

void bmp::bitmap_information_header::write(std::ofstream& stream, const bitmap_information_header& bih)
{
    if (big_endian())
    {
        write_to_stream(stream, flip(bih.size));
        write_to_stream(stream, flip(bih.width));
        write_to_stream(stream, flip(bih.height));
        write_to_stream(stream, flip(bih.planes));
        write_to_stream(stream, flip(bih.bit_count));
        write_to_stream(stream, flip(bih.compression));
        write_to_stream(stream, flip(bih.size_image));
        write_to_stream(stream, flip(bih.x_pels_per_meter));
        write_to_stream(stream, flip(bih.y_pels_per_meter));
        write_to_stream(stream, flip(bih.clr_used));
        write_to_stream(stream, flip(bih.clr_important));
    }
    else
    {
        write_to_stream(stream, bih.size);
        write_to_stream(stream, bih.width);
        write_to_stream(stream, bih.height);
        write_to_stream(stream, bih.planes);
        write_to_stream(stream, bih.bit_count);
        write_to_stream(stream, bih.compression);
        write_to_stream(stream, bih.size_image);
        write_to_stream(stream, bih.x_pels_per_meter);
        write_to_stream(stream, bih.y_pels_per_meter);
        write_to_stream(stream, bih.clr_used);
        write_to_stream(stream, bih.clr_important);
    }
}

//Bitmap

bmp::Bitmap::Bitmap(unsigned int x, unsigned int y) :
    m_width(x), m_height(y), m_bytes_per_pixel(3), m_row_increment(0)
{ 
    init();
}

void bmp::Bitmap::init()
{
    m_row_increment = m_width * m_bytes_per_pixel;
    m_data.resize(m_height * m_row_increment);
    clear();
}

bmp::Bitmap& bmp::Bitmap::operator=(const Bitmap& image)
{
    if (this != &image)
    {
        m_bytes_per_pixel = image.m_bytes_per_pixel;
        m_width = image.m_width;
        m_height = image.m_height;
        m_row_increment = 0;
        init();
        m_data = image.m_data;
    }

    return *this;
}

bool bmp::Bitmap::operator==(const Bitmap x)
{
    if (m_width  != x.width())  return false;
    if (m_height != x.height()) return false;
    if (m_data   != x.data())   return false;
    return true;
}

inline void bmp::Bitmap::clear(const unsigned char v)
{
    std::fill(m_data.begin(), m_data.end(), v);
}

void bmp::Bitmap::setPixel(const unsigned int x, const unsigned int y, const unsigned char red, const unsigned char green, const unsigned char blue) {
    const unsigned int offset = (x * m_bytes_per_pixel) + (y * m_row_increment);
    m_data[offset + 0] = blue;
    m_data[offset + 1] = green;
    m_data[offset + 2] = red;
}

void bmp::Bitmap::setPixel(const unsigned int x, const unsigned int y, rgb_t color) {
    setPixel(x, y, color.R, color.G, color.B);
}

inline void bmp::Bitmap::get_pixel(const unsigned int x, const unsigned int y, unsigned char& red, unsigned char& green, unsigned char& blue) const
{   
    const unsigned int offset = (y * m_row_increment) + (x * m_bytes_per_pixel);

    blue  = m_data[offset + 0];
    green = m_data[offset + 1];
    red   = m_data[offset + 2];
}

inline bmp::rgb_t bmp::Bitmap::getPixel(const unsigned int x, const unsigned int y) const
{
    rgb_t colour;
    //get_pixel(x, y, colour.R, colour.G, colour.B);
    return colour;
}

int bmp::Bitmap::width() const { return m_width; }

int bmp::Bitmap::height() const { return m_height; }

std::vector<unsigned char> bmp::Bitmap::data() const { return m_data; }

inline std::size_t bmp::Bitmap::file_size(const std::string& filename) const
{
    std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
    if (!file) return 0;
    file.seekg(0, std::ios::end);
    return static_cast<std::size_t>(file.tellg());
}

inline unsigned char* bmp::Bitmap::row(unsigned int row_index) const
{
    return const_cast<unsigned char*>(&m_data[(row_index * m_row_increment)]);
}

void bmp::Bitmap::fimport(const std::string& filename)
{
    std::ifstream stream(filename.c_str(), std::ios::binary);
    if (!stream)
    {
        std::cerr << "bmp::Bitmap::fimport() ERROR: bitmap - "
            << "file " << filename << " not found!" << std::endl;
        return;
    }

    m_width = 0;
    m_height = 0;

    bitmap_file_header bfh;
    bitmap_information_header bih;

    bfh.clear();
    bih.clear();

    bfh.read(stream, bfh);
    bih.read(stream, bih);

    if (bfh.type != 19778)
    {
        std::cerr << "bmp::Bitmap::fimport() ERROR: bitmap - "
            << "Invalid type value " << bfh.type << " expected 19778." << std::endl;

        bfh.clear();
        bih.clear();

        stream.close();

        return;
    }

    if (bih.bit_count != 24)
    {
        std::cerr << "bmp::Bitmap::fimport() ERROR: bitmap - "
            << "Invalid bit depth " << bih.bit_count << " expected 24." << std::endl;

        bfh.clear();
        bih.clear();

        stream.close();

        return;
    }

    if (bih.size != bih.struct_size())
    {
        std::cerr << "bmp::Bitmap::load_bitmap() ERROR: bitmap - "
            << "Invalid BIH size " << bih.size
            << " expected " << bih.struct_size() << std::endl;

        bfh.clear();
        bih.clear();

        stream.close();

        return;
    }

    m_width  = bih.width;
    m_height = bih.height;

    m_bytes_per_pixel = bih.bit_count >> 3;

    unsigned int padding = (4 - ((3 * m_width) % 4)) % 4;
    char padding_data[4] = { 0x00, 0x00, 0x00, 0x00 };

    std::size_t bitmap_file_size = file_size(filename);

    std::size_t bitmap_logical_size = (
        (m_height * m_width * m_bytes_per_pixel) +
        (m_height * padding) +
        bih.struct_size() +
        bfh.struct_size()
    );

    if (bitmap_file_size != bitmap_logical_size)
    {
        std::cerr << "bmp::Bitmap::load_bitmap() ERROR: bitmap - "
            << "Mismatch between logical and physical sizes of bitmap. "
            << "Logical: " << bitmap_logical_size << " "
            << "Physical: " << bitmap_file_size << std::endl;

        bfh.clear();
        bih.clear();

        stream.close();

        return;
    }

    init();

    for ( int i = 0; i < m_height; ++i)
    {
        unsigned char* data_ptr = row(m_height - i - 1); // read in inverted row order

        stream.read(reinterpret_cast<char*>(data_ptr), sizeof(char) * m_bytes_per_pixel * m_width);
        stream.read(padding_data, padding);
    }
}

void bmp::Bitmap::fexport(const std::string& file_name) const
{
    std::ofstream stream(file_name.c_str(), std::ios::binary);

    if (!stream)
    {
        std::cerr << "bmp::Bitmap::fexport(): Error - Could not open file "
            << file_name << " for writing!" << std::endl;
        return;
    }

    bitmap_information_header bih;

    bih.width            = m_width;
    bih.height           = m_height;
    bih.bit_count        = static_cast<unsigned short>(m_bytes_per_pixel << 3);
    bih.clr_important    = 0;
    bih.clr_used         = 0;
    bih.compression      = 0;
    bih.planes           = 1;
    bih.size             = bih.struct_size();
    bih.x_pels_per_meter = 0;
    bih.y_pels_per_meter = 0;
    bih.size_image       = (((bih.width * m_bytes_per_pixel) + 3) & 0x0000FFFC) * bih.height;

    bitmap_file_header bfh;

    bfh.type      = 19778;
    bfh.size      = bfh.struct_size() + bih.struct_size() + bih.size_image;
    bfh.reserved1 = 0;
    bfh.reserved2 = 0;
    bfh.off_bits  = bih.struct_size() + bfh.struct_size();

    bfh.write(stream, bfh);
    bih.write(stream, bih);

    unsigned int padding = (4 - ((3 * m_width) % 4)) % 4;
    char padding_data[4] = { 0x00, 0x00, 0x00, 0x00 };

    for (int i = 0; i < m_height; ++i)
    {
        const unsigned char* data_ptr = &m_data[(m_row_increment * (m_height - i - 1))];
        stream.write(reinterpret_cast<const char*>(data_ptr), sizeof(unsigned char) * m_bytes_per_pixel * m_width);
        stream.write(padding_data, padding);
    }

    stream.close();
}

//rgb
bmp::rgb_t::rgb_t() : R(0), G(0), B(0) { }

bmp::rgb_t::rgb_t(unsigned int r, unsigned int g, unsigned int b) : R(r), G(g), B(b) { }
