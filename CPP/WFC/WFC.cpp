#include "WFC.h"

wfc::PixelInfo::PixelInfo(unsigned int x_, unsigned int y_, bmp::rgb_t color_):
    x(x_),y(y_),adjacency(std::vector<bmp::rgb_t>(x_ * y_)), center_color(color_)
{ }

wfc::PixelInfo::PixelInfo():
    x(0), y(0),center_color(bmp::rgb_t(0,0,0))
{ }

wfc::Data::Data(const bmp::Bitmap& bitmap) :
    m_bitmap(bitmap)
{
    init();
}

void wfc::Data::init() {
    m_info.resize(m_bitmap.width() * m_bitmap.height());
}

void wfc::Data::load() {
    unsigned int area = 2;
    int percentage = 0;

    println("Analyzing image");

    for (int i = 0; i < m_info.size(); i++) {
        m_info[i].center_color = m_bitmap.getPixel(area, area);
        m_info[i].adjacency.resize((area * 2 + 1) * (area * 2 + 1));

        //Console logs of percent of image read
        if (percentage != (i * 100) / m_info.size() * DEBUG) {
            percentage = (i * 100) / m_info.size();
            std::cout << percentage << "%   " << i << "/" << m_info.size() <<std::endl;
        }

        for (int y = 0; y < m_bitmap.height(); y++) {
        for (int x = 0; x < m_bitmap.width();  x++) {

            if (
                (int(x - area) >= 0 && x < m_bitmap.width() ) &&
                (int(y - area) >= 0 && y < m_bitmap.height())
            ) {
                //NO ANDA >:((
                m_info[i].adjacency[y * m_bitmap.width() + x]; //=
                m_bitmap.getPixel(x - area, y - area);
            }
        }
        }
    }
    if (DEBUG) std::cout << "100%  " << m_info.size() << "/" << m_info.size() <<std::endl;


}

