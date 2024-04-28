#pragma once

#include <string>
#include "../other/structs.h"
#include <vector>
#include <iostream>

class Image
{
public:
    Image()
        : bm_data{0}, fileHeader{0}, infoHeader{0}, bm_width{0}, bm_height{0}, padding{0} {}
    
    void readBMP(std::string & path, bool need_info);
    void exportBMP(std::string & path);

    void rectangle(Rectangle & rect);
    void circle(Circle & circ);
    void rotate(Rotate & rot);
    void ornament(Ornament & orn);
private:
    std::vector<std::vector<Color>> bm_data;

    //file header
    unsigned char fileHeader[14];
    // const int fileHeaderSize = 14;
    // unsigned int fileSize;
    
    //info header
    unsigned char infoHeader[40];
    // const int infoHeaderSize = 40;
    unsigned int bm_width;
    unsigned int bm_height;
    // unsigned int bits_per_pixel;
    // unsigned int compression;
    
    //padding
    const int padding;

};
