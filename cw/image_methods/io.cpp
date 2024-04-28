#include "io.h"


void Image::readBMP(std::string & path, bool need_info)
{
    std::ifstream f;
    f.open(path, std::ios::binary | std::ios::in);

    if (!f.is_open())
    {
        std::cerr << "Failed to open the file" << std::endl;
        std::cout << HELP << std::endl;
        exit(44);
    }

    //file header 
    // unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader), 14);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M') 
    {
        std::cerr << WRONG_FILE << std::endl;
        std::cout << HELP << std::endl;
        exit(44);
    }

    // fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    //

    //info header 
    //unsigned char infoHeader[infoHeaderSize];
    f.read(reinterpret_cast<char*>(infoHeader), 40);


    bm_width = infoHeader[4] + (infoHeader[5] << 8) + (infoHeader[6] << 16) + (infoHeader[7] << 24);
    bm_height = infoHeader[8] + (infoHeader[9] << 8) + (infoHeader[10] << 16) + (infoHeader[11] << 24);

    if (need_info)
    {
        std::cout << "File info:\n\
        1) file header size 14\n\
        2) info header size 40\n\
        3) bits per pixel " << static_cast<unsigned int>(infoHeader[14]) << "\n\
        4) compression " << static_cast<unsigned int>(infoHeader[16]) << "\n\
        5) Width " << bm_width << "\n\
        6) Height " << bm_height << std::endl;
        exit(0);
    }

    // bits_per_pixel = infoHeader[14];
    // compression = infoHeader[16];
    if (static_cast<unsigned int>(infoHeader[14]) != 24 || infoHeader[16])
    {
        std::cout << static_cast<unsigned int>(infoHeader[14]);
        std::cerr << WRONG_FILE << std::endl;
        std::cout << HELP << std::endl;
        exit(44);
    }

    //

    bm_data.resize(bm_height);

    for (int y = 0; y < bm_height; y++)
    {
        bm_data[y].resize(bm_width);
    }

    const int padding = ((4 - (bm_width * 3) % 4) % 4);

    //pixel data processing

    for (int y = 0; y < bm_height; y++)
    {
        for (int x = 0; x < bm_width; x++) 
        {
            unsigned char pixel[3];
            f.read(reinterpret_cast<char*>(pixel), 3);
            bm_data[y][x].b = pixel[2];
            bm_data[y][x].g = pixel[1];
            bm_data[y][x].r = pixel[0];
        }
    }
    f.ignore(padding);
    f.close();

}

void Image::exportBMP(std::string & path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open())
    {
        std::cerr << "Failed to open the file" << std::endl;
        std::cout << HELP << std::endl;
    }

    f.write(reinterpret_cast<char*>(fileHeader), 14);
    f.write(reinterpret_cast<char*>(infoHeader), 40);

    unsigned char bmpPad[3]{0, 0, 0};
    for(int y = 0; y < bm_height; y++)
    {
        for (int x = 0; x < bm_width; x++)
        {
            unsigned char pixel[3];
            pixel[0] = bm_data[y][x].r;
            pixel[1] = bm_data[y][x].g;
            pixel[2] = bm_data[y][x].b;
            f.write(reinterpret_cast<char*>(pixel), 3);
        }
        f.write(reinterpret_cast<char*>(bmpPad), padding);
    }    
    f.close();
}
