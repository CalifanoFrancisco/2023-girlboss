#include <iostream>
#include "Bitmap.h"
#include "WFC.h"

void buildTestFile(int x_ = 20, int y_ = 20, std::string filename = "out.bmp") {
    bmp::Bitmap image(x_, y_);
    for (int y = 0; y < image.height(); y++)
        for (int x = 0; x < image.width(); x++)
            image.setPixel(x, y, 
                bmp::rgb_t(
                    255,0,0
                )
            );
    image.fexport(filename);
}

int main() {
    //buildTestFile(10, 10);
    wfc::Data data(bmp::Bitmap("out.bmp"));
    data.load();
    return 0;
}