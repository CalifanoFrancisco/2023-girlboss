#ifndef WFC_IMAGE
#define WFC_IMAGE

#include <iostream>
#include <vector>

#include "BMP.h"

#define DEBUG true
#if DEBUG
    #define println(x) std::cout << x << std::endl
    #define print(x)   std::cout << x
#else
    #define println(x)
    #define print(x)
#endif // DEBUG


namespace wfc {

struct PixelInfo {
    bmp::rgb_t center_color;
    unsigned int x, y;
    std::vector<bmp::rgb_t> adjacency;
    PixelInfo(unsigned int x_, unsigned int y_, bmp::rgb_t color_);
    PixelInfo();
};

class Data {
private:
    bmp::Bitmap m_bitmap;
    std::vector<PixelInfo> m_info;
public:
    Data (const bmp::Bitmap& bitmap);
    void init();
    void load();
};



}


#endif

