#include <iostream>
#include <string>

#include <QImage>

int main() {
    // Get filename from stdin
    std::cout << "Enter full path to a PNG file:" << std::endl;
    std::string str;
    std::cin >> str;
    QString filename = QString::fromStdString(str);
    // open image
    QImage image(filename, "PNG");
    if (image.isNull()) {
        std::cout << "Can't open this file" << std::endl;
        return 1;
    }
    // get sizes of the image
    const int width = image.width();
    const int height = image.height();
    // transform pixels of the image
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            // get color of pixel
            QRgb pixel = image.pixel(i, j);
            // rise every RGB channel on fixed offset
            const int offset = 20;
            int red = std::min(qRed(pixel) + offset, 255);
            int green = std::min(qGreen(pixel) + offset, 255);
            int blue = std::min(qBlue(pixel) + offset, 255);
            int alpha = qAlpha(pixel);      // cause PNG supports alpha channel
            pixel = qRgba(red, green, blue, alpha);
            // set pixel with new color
            image.setPixel(i, j, pixel);
        }
    }
    // save QImage as PNG
    if (!image.save(filename.insert(filename.lastIndexOf('.'), "_edited"), "PNG")) {
        std::cout << "Can't save the image" << std::endl;
        return 1;
    }
    std::cout << "Resulted image was writed to: " << filename.toStdString() << std::endl;
    return 0;
}
