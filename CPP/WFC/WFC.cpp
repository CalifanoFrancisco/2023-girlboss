#include "WFC.h"

wfc::PixelInfo::PixelInfo(unsigned int x_, unsigned int y_, bmp::rgb_t color_):
    x(x_),y(y_),adjacency(std::vector<bmp::rgb_t>(x_ * y_)), center_color(color_)
{ }

/*
wfc::Data::Data(const bmp::Bitmap& bitmap) {
    m_info.resize(bitmap.width() * bitmap.width());
    init();
}*/

void wfc::Data::init() {

}

void wfc::Data::load() {
    unsigned int area = 2;
    for (int i = 0; m_info.size(); i++) {
        m_info[i].center_color = m_bitmap.getPixel(area, area);
        for (int y = 0; y < m_bitmap.height(); y++) {
        for (int x = 0; x < m_bitmap.width();  x++) {
            if (!(
                x - area < 0         || y - area < 0 ||
                x > m_bitmap.width() || y > m_bitmap.height()
            )) {
                m_info[i].adjacency[y * m_bitmap.width() + x] =
                m_bitmap.getPixel(x - area, y - area);
            }
        }
        }
    }
    bmp::Bitmap out(m_bitmap.width(),m_bitmap.height());
    for (int y = 0; y < m_bitmap.height();y++){
    for (int x = 0; x < m_bitmap.width(); x++) {
        out.setPixel(x,y,m_info[y*m_bitmap.width()+x].center_color);
    }
    }
}
