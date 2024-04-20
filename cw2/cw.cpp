#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <regex>

#include "messages.h"
#include "checking_flags.h"


//start of structs.h
#include <array>



//end of structs.h

//start of checking_flags.h

struct option long_opt[]={
    {"input", 1, 0, 'i'},
    {"output", 1, 0, 'o'},
    {"info", 0, 0, 0},
    {"help", 0, 0, 'h'},
    {"rect", 0, 0, 0},
    {"left_up", 1, 0, 0},
    {"right_down", 1, 0, 0},
    {"thickness", 1, 0, 0},
    {"color", 1, 0, 0},
    {"fill_color", 1, 0, 0},
    {"ornament", 0, 0, 0},
    {"pattern", 1, 0, 0},
    {"color", 1, 0, 0},
    {"count", 1, 0, 0},
    {"rotate", 0, 0, 0},
    {"angle", 1, 0, 0},
    {"circle", 0, 0, 0},
    {"center", 1, 0, 0},
    {"radius", 1, 0, 0},
    {"fill", 1, 0, 0},
    {0, 0, 0, 0}
};


std::unordered_map<std::string, std::string> getFlags(int argc, char** argv) 
{
    int optindx;
    int opt;
    opterr = 0;
    std::string flag;
    std::unordered_map<std::string, std::string> flags_table;

    while((opt = getopt_long(argc, argv, "i:o:h", long_opt, &optindx)) != -1) {
        switch (opt)
        {
        case '?':
            std::cerr << UNKNOWN_ARG << argv[optind - 1] << std::endl;
            std::cout << HELP << std::endl;
            exit(44);
            break;
        case 'i':
            flags_table["input"] = optarg;
            break;
        case 'o':
            flags_table["output"] = optarg;
            break;
        case 'h':
            flags_table["help"] = "";
            break;
        default:
            if (optarg) {
                flags_table[long_opt[optindx].name] = optarg;
            }
            else {
                flags_table[long_opt[optindx].name] = "";
            }
            break;
        }
    }
    return flags_table;
}


//end of checking_flags.h

//start of validations.h


int value_check(std::string function, std::unordered_map<std::string, std::string> & flags_table)
{
    std::regex cords_reg ("^[0-9]+\\.[0-9]+$");
    std::regex color_reg ("^[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}$");
    std::regex positive_reg ("^[0-9]+$");
    if (function == "rect")
    {
        std::smatch cords_match_lu;
        if (!std::regex_search(flags_table["left_up"], cords_match_lu, cords_reg))
        {
            std::cerr << WRONG_VALUE << "left_up" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        std::smatch cords_match_rd;
        if (!std::regex_search(flags_table["right_down"], cords_match_rd, cords_reg))
        {
            std::cerr << WRONG_VALUE << "right_down" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        std::smatch thickness_match;
        if (!std::regex_search(flags_table["thickness"], thickness_match, positive_reg))
        {
            std::cerr << WRONG_VALUE << "thickness" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        std::smatch color_match_c;
        if (!std::regex_search(flags_table["color"], color_match_c, color_reg))
        {
            std::cerr << WRONG_VALUE << "color" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        if (flags_table["fill"] != "true" && flags_table["fill"] != "false") 
        {
            std::cerr << WRONG_VALUE << "fill" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        if (flags_table["fill"] == "true") {
            std::smatch color_match_fc;
            if (!std::regex_search(flags_table["fill_color"], color_match_fc, color_reg))
            {
                std::cerr << WRONG_VALUE << "fill_color" << std::endl;
                std::cout << HELP << std::endl;
                exit(43);
            }
        }
        return 1;
    }
    if (function == "circle")
    {
        std::smatch radius_match;
        if (!std::regex_search(flags_table["radius"], radius_match, positive_reg))
        {
            std::cerr << WRONG_VALUE << "radius" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        std::smatch center_match;
        if (!std::regex_search(flags_table["center"], center_match, cords_reg))
        {
            std::cerr << WRONG_VALUE << "center" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        std::smatch thickness_match;
        if (!std::regex_search(flags_table["thickness"], thickness_match, positive_reg))
        {
            std::cerr << WRONG_VALUE << "thickness" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        std::smatch color_match_c;
        if (!std::regex_search(flags_table["color"], color_match_c, color_reg))
        {
            std::cerr << WRONG_VALUE << "color" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        if (flags_table["fill"] != "true" && flags_table["fill"] != "false") 
        {
            std::cerr << WRONG_VALUE << "fill" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        if (flags_table["fill"] == "true") {
            std::smatch color_match_fc;
            if (!std::regex_search(flags_table["fill_color"], color_match_fc, color_reg))
            {
                std::cerr << WRONG_VALUE << "fill_color" << std::endl;
                std::cout << HELP << std::endl;
                exit(43);
            }
        }
        return 1;
    }
    if (function == "rotate")
    {
        std::smatch cords_match_lu;
        if (!std::regex_search(flags_table["left_up"], cords_match_lu, cords_reg))
        {
            std::cerr << WRONG_VALUE << "left_up" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        std::smatch cords_match_rd;
        if (!std::regex_search(flags_table["right_down"], cords_match_rd, cords_reg))
        {
            std::cerr << WRONG_VALUE << "right_down" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        if (flags_table["angle"] != "90" && flags_table["angle"] != "180" && flags_table["angle"] != "270") 
        {
            std::cerr << WRONG_VALUE << "angle" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        return 1;
    }
    if (function == "ornament")
    {
        std::smatch thickness_match;
        if (!std::regex_search(flags_table["thickness"], thickness_match, positive_reg))
        {
            std::cerr << WRONG_VALUE << "thickness" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        std::smatch color_match_c;
        if (!std::regex_search(flags_table["color"], color_match_c, color_reg))
        {
            std::cerr << WRONG_VALUE << "color" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        std::smatch count_match;
        if (!std::regex_search(flags_table["count"], count_match, positive_reg))
        {
            std::cerr << WRONG_VALUE << "count" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        if (flags_table["pattern"] != "rectangle" && flags_table["pattern"] != "circle" && flags_table["pattern"] != "semicircles") {
            std::cerr << WRONG_VALUE << "pattern" << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
        return 1;
    }
    std::cerr << WHAT << std::endl;
    std::cout << "value_check" << std::endl;
    exit(40);
}


int validate_dependecies(std::string function, std::unordered_map<std::string, std::string> & flags_table) {
    // for (auto& [name, argument] : flags_table) {
    //     std::cout << name << " : " << argument << std::endl;
    // }
    if (function == "rect") {
        if (flags_table.find("left_up") == flags_table.end() || flags_table.find("right_down") == flags_table.end() 
        || flags_table.find("thickness") == flags_table.end() || flags_table.find("color") == flags_table.end() 
        || flags_table.find("fill") == flags_table.end()) 
        {
            return 0;
        }
        else
        {
            if (flags_table["fill"] == "true" && flags_table.find("fill_color") == flags_table.end())
            {
                return 0;
            }
            return 1;
        }
    }
    if (function == "ornament") {
        if (flags_table.find("pattern") == flags_table.end() || flags_table.find("color") == flags_table.end() 
        || flags_table.find("thickness") == flags_table.end() || flags_table.find("count") == flags_table.end()) 
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if (function == "rotate") {
        if (flags_table.find("left_up") == flags_table.end() || flags_table.find("right_down") == flags_table.end() 
        || flags_table.find("angle") == flags_table.end()) 
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if (function == "circle") {
        if (flags_table.find("center") == flags_table.end() || flags_table.find("radius") == flags_table.end() 
        || flags_table.find("thickness") == flags_table.end() || flags_table.find("color") == flags_table.end() 
        || flags_table.find("fill") == flags_table.end()) 
        {
            return 0;
        }
        else
        {
            if (flags_table["fill"] == "true" && flags_table.find("fill_color") == flags_table.end())
            {
                return 0;
            }
            return 1;
        }
    }
    std::cerr << WHAT << std::endl;
    std::cout << "validate_dependecies" <<std::endl;
    exit(40);
}

//end of validations.h

//start of find_function_to_run.h

std::string run_this(std::unordered_map<std::string, std::string> & flags_table) {
    if (flags_table.find("help") != flags_table.end()) {
        if (flags_table.size() > 1) {
            std::cout << "Warning: --help was found, so other flags will be ignored" << std::endl;
        }
        return "help";
    }
    else if (flags_table.find("info") != flags_table.end()) {
        if (flags_table.size() > 1) {
            std::cout << "Warning: --info was found, so other flags will be ignored" << std::endl;
        }
        return "info";
    }
    else if (flags_table.find("rect") != flags_table.end()) {
        if (flags_table.find("circle") != flags_table.end() || flags_table.find("rotate") != flags_table.end() || flags_table.find("ornament") != flags_table.end()) {
            std::cerr << ONLY_ONE << std::endl;
            std::cout << HELP << std::endl;
            exit(42);
        }
        if (validate_dependecies("rect", flags_table) && value_check("rect", flags_table)) {
            return "rect";
        }
        else {
            std::cerr << DEPENDECIES << "rect" << std::endl;
            std::cout << HELP << std::endl;
            exit(41);
        }
    }
    else if (flags_table.find("ornament") != flags_table.end()) {
        if (flags_table.find("circle") != flags_table.end() || flags_table.find("rotate") != flags_table.end() || flags_table.find("rect") != flags_table.end()) {
            std::cerr << ONLY_ONE << std::endl;
            std::cout << HELP << std::endl;
            exit(42);
        }
        if (validate_dependecies("ornament", flags_table) && value_check("ornament", flags_table)) {
            return "ornament";
        }
        else {
            std::cerr << DEPENDECIES << "ornament" << std::endl;
            std::cout << HELP << std::endl;
            exit(41);
        }
    }
    else if (flags_table.find("rotate") != flags_table.end()) {
        if (flags_table.find("circle") != flags_table.end() || flags_table.find("rect") != flags_table.end() || flags_table.find("ornament") != flags_table.end()) {
            std::cerr << ONLY_ONE << std::endl;
            std::cout << HELP << std::endl;
            exit(42);
        }
        if (validate_dependecies("rotate", flags_table) && value_check("rotate", flags_table)) {
            return "rotate";
        }
        else {
            std::cerr << DEPENDECIES << "rotate" << std::endl;
            std::cout << HELP << std::endl;
            exit(41);
        }
    }
    else if (flags_table.find("circle") != flags_table.end()) {
        if (flags_table.find("rect") != flags_table.end() || flags_table.find("rotate") != flags_table.end() || flags_table.find("ornament") != flags_table.end()) {
            std::cerr << ONLY_ONE << std::endl;
            std::cout << HELP << std::endl;
            exit(42);
        }
        if (validate_dependecies("circle", flags_table) && value_check("circle", flags_table)) {
            return "circle";
        }
        else {
            std::cerr << DEPENDECIES << "circle" << std::endl;
            std::cout << HELP << std::endl;
            exit(41);
        }
    }
    else {
        std::cerr << "It seems, you forgot to enter the functions" << std::endl;
        std::cout << HELP << std::endl;
        exit(40);
    }
}



#include <fstream>

struct Rectangle
{
    std::array<int, 2> left_up;
    std::array<int, 2> right_down;
    int thickness;
    std::array<int, 3> color;
    bool fill;
    std::array<int, 3> fill_color;
};

struct Ornament
{
    std::string pattern; //изменить в дальнейшем
    std::array<int, 3> color;
    int thickness;
    int count;
};

struct Rotate
{
    std::array<int, 2> left_up;
    std::array<int, 2> right_down;
    int angle;
};

struct Circle
{
    std::array<int, 2> center;
    int radius;
    int thickness;
    std::array<int, 3> color;
    bool fill;
    std::array<int, 3> fill_color;
};


struct Color
{
    unsigned char r, g, b;

    Color()
        : r(0), g(0), b(0) {}
    Color(unsigned char r, unsigned char g, unsigned char b)
        : r(r), g(g), b(b) {}
};

//fill_the_structs

Rectangle rect_struct(std::unordered_map<std::string, std::string> & flags_table) 
{
    Rectangle rect;
    rect.left_up[0] = std::stoi(flags_table["left_up"].substr(0, flags_table["left_up"].find('.')));
    rect.left_up[1] = std::stoi(flags_table["left_up"].substr(flags_table["left_up"].find('.') + 1, std::string::npos - flags_table["left_up"].find('.')));
    std::cout << rect.left_up[0] << ' ' << rect.left_up[1] << std::endl;

    rect.right_down[0] = std::stoi(flags_table["right_down"].substr(0, flags_table["right_down"].find('.')));
    rect.right_down[1] = std::stoi(flags_table["right_down"].substr(flags_table["right_down"].find('.') + 1, std::string::npos - flags_table["right_down"].find('.')));
    std::cout << rect.right_down[0] << ' ' << rect.right_down[1] << std::endl;

    rect.thickness = std::stoi(flags_table["thickness"]);
    rect.color[0] = std::stoi(flags_table["color"].substr(0, flags_table["color"].find('.')));
    rect.color[1] = std::stoi(flags_table["color"].substr(flags_table["color"].find('.') + 1, flags_table["color"].rfind('.') - flags_table["color"].find('.')));
    rect.color[2] = std::stoi(flags_table["color"].substr(flags_table["color"].rfind('.') + 1, std::string::npos - flags_table["color"].rfind('.')));

    std::cout << rect.color[0] << ' ' << rect.color[1] << ' ' << rect.color[2] << std::endl;

    rect.fill = (flags_table["fill"] == "true");
    std::cout << rect.fill << std::endl;
    
    if (rect.fill == true)
    {
        rect.fill_color[0] = std::stoi(flags_table["fill_color"].substr(0, flags_table["fill_color"].find('.')));
        rect.fill_color[1] = std::stoi(flags_table["fill_color"].substr(flags_table["fill_color"].find('.') + 1, flags_table["fill_color"].rfind('.') - flags_table["fill_color"].find('.')));
        rect.fill_color[2] = std::stoi(flags_table["fill_color"].substr(flags_table["fill_color"].rfind('.') + 1, std::string::npos - flags_table["fill_color"].rfind('.')));
    }

    std::cout << rect.fill_color[0] << ' ' << rect.fill_color[1] << ' ' << rect.fill_color[2] << std::endl;

    return rect;
}

Circle circ_struct(std::unordered_map<std::string, std::string> & flags_table) 
{
    Circle circ;
    circ.center[0] = std::stoi(flags_table["center"].substr(0, flags_table["center"].find('.')));
    circ.center[1] = std::stoi(flags_table["center"].substr(flags_table["center"].find('.') + 1, std::string::npos - flags_table["center"].find('.')));

    std::cout<< circ.center[0] << ' ' << circ.center[1] << std::endl;

    circ.radius = std::stoi(flags_table["radius"]);

    circ.thickness = std::stoi(flags_table["thickness"]);
    circ.color[0] = std::stoi(flags_table["color"].substr(0, flags_table["color"].find('.')));
    circ.color[1] = std::stoi(flags_table["color"].substr(flags_table["color"].find('.') + 1, flags_table["color"].rfind('.') - flags_table["color"].find('.')));
    circ.color[2] = std::stoi(flags_table["color"].substr(flags_table["color"].rfind('.') + 1, std::string::npos - flags_table["color"].rfind('.')));

    std::cout << circ.color[0] << ' ' << circ.color[1] << ' ' << circ.color[2] << std::endl;


    circ.fill = (flags_table["fill"] == "true");
    
    if (circ.fill == true)
    {
        circ.fill_color[0] = std::stoi(flags_table["fill_color"].substr(0, flags_table["fill_color"].find('.')));
        circ.fill_color[1] = std::stoi(flags_table["fill_color"].substr(flags_table["fill_color"].find('.') + 1, flags_table["fill_color"].rfind('.') - flags_table["fill_color"].find('.')));
        circ.fill_color[2] = std::stoi(flags_table["fill_color"].substr(flags_table["fill_color"].rfind('.') + 1, std::string::npos - flags_table["fill_color"].rfind('.')));
    }

    return circ;
}

Ornament orn_struct(std::unordered_map<std::string, std::string> & flags_table) 
{
    Ornament orn;

    orn.pattern = flags_table["pattern"];

    orn.count = std::stoi(flags_table["count"]);

    orn.thickness = std::stoi(flags_table["thickness"]);

    orn.color[0] = std::stoi(flags_table["color"].substr(0, flags_table["color"].find('.')));
    orn.color[1] = std::stoi(flags_table["color"].substr(flags_table["color"].find('.') + 1, flags_table["color"].rfind('.') - flags_table["color"].find('.')));
    orn.color[2] = std::stoi(flags_table["color"].substr(flags_table["color"].rfind('.') + 1, std::string::npos - flags_table["color"].rfind('.')));

    return orn;
}

Rotate rot_struct(std::unordered_map<std::string, std::string> & flags_table) 
{
    Rotate rot;
    rot.left_up[0] = std::stoi(flags_table["left_up"].substr(0, flags_table["left_up"].find('.')));
    rot.left_up[1] = std::stoi(flags_table["left_up"].substr(flags_table["left_up"].find('.') + 1, std::string::npos - flags_table["left_up"].find('.')));

    rot.right_down[0] = std::stoi(flags_table["right_down"].substr(0, flags_table["right_down"].find('.')));
    rot.right_down[1] = std::stoi(flags_table["right_down"].substr(flags_table["right_down"].find('.') + 1, std::string::npos - flags_table["right_down"].find('.')));

    rot.angle = std::stoi(flags_table["angle"]);

    return rot;
}


class Image
{
public:
    Image()
        : bm_data{0}, fileHeader{0}, infoHeader{0}, bm_width{0}, bm_height{0}, padding{0} {}
    
    void readBMP(std::string path);
    void exportBMP(std::string path);

    void rectangle(Rectangle rect);
    void circle(Circle circ);
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


void Image::readBMP(std::string path)
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
            bm_data[y][x].r = pixel[0];
            bm_data[y][x].g = pixel[1];
            bm_data[y][x].b = pixel[2];
        }
    }
    f.ignore(padding);
    f.close();

}

void Image::exportBMP(std::string path) {
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

void Image::rectangle(Rectangle rect)
{
    if (rect.left_up[0] >= bm_width)
    {
        rect.left_up[0] = bm_width - 1;
    }
    if (rect.left_up[1] >= bm_height)
    {
        rect.left_up[1] = bm_height - 1;
    }
    if (rect.right_down[0] <= bm_width)
    {
        rect.right_down[0] = bm_width - 1;
    }
    if (rect.right_down[1] <= bm_height)
    {
        rect.right_down[1] = bm_height - 1;
    }

    if (rect.left_up[0] > rect.right_down[0])
    {
        int tmp = rect.left_up[0];
        rect.left_up[0] = rect.right_down[0];
        rect.right_down[0] = rect.left_up[0];
    }
    if (rect.left_up[1] < rect.right_down[1])
    {
        int tmp = rect.left_up[1];
        rect.left_up[1] = rect.right_down[1];
        rect.right_down[1] = rect.left_up[1];
    }
    int x1, y1, x2, y2;
    for (int k = 0; k < rect.thickness; k++)
    {
        x1 = rect.left_up[0] + k;
        y1 = rect.left_up[1] - k;
        x2 = rect.right_down[0] - k;
        y2 = rect.right_down[1] + k;

        for (int x = x1; x <= x2; x++) 
        {

            bm_data[y1][x].r = rect.color[0];
            bm_data[y1][x].g = rect.color[1];
            bm_data[y1][x].b = rect.color[2];
        }
        for (int y = y1; y >= y2; y--) 
        {

            bm_data[y][x1].r = rect.color[0];
            bm_data[y][x1].g = rect.color[1];
            bm_data[y][x1].b = rect.color[2];
        }
        for (int x = x1; x <= x2; x++) 
        {

            bm_data[y2][x].r = rect.color[0];
            bm_data[y2][x].g = rect.color[1];
            bm_data[y2][x].b = rect.color[2];
        }
        for (int y = y1; y >= y2; y--) 
        {

            bm_data[y][x2].r = rect.color[0];
            bm_data[y][x2].g = rect.color[1];
            bm_data[y][x2].b = rect.color[2];
        }
    }
    if (rect.fill == true)
    {
        x1++;
        y1--;
        x2--;
        y2++;
        for (int y = y1; y >= y2; y--)
        {
            for (int x = x1; x <= x2; x++)
            {
                bm_data[y][x].r = rect.fill_color[0];
                bm_data[y][x].g = rect.fill_color[1];
                bm_data[y][x].b = rect.fill_color[2];
            }
        }
    }
}

#include <cmath>

void Image::circle(Circle circ) 
{
    double x1 = circ.center[0] - circ.radius;
    double y1 = circ.center[1] + circ.radius;
    double x2 = circ.center[0] + circ.radius;
    double y2 = circ.center[1] - circ.radius;
    std::cout << x1 << ' ' << x2 << ' ' << y1 <<' ' <<y2 << std::endl;

    int r1 = circ.radius;
    int r2 = circ.radius - circ.thickness;

    for (int y = y1; y >= y2; y--)
    {
        for (int x = x1; x <= x2; x++) 
        {
            double hyp = pow(pow(circ.center[0] - x, 2.0) + pow(circ.center[1] - y, 2), 0.5);
            if (hyp <= r1 && hyp > r2 && y < bm_height && y >= 0 && x < bm_width && bm_width >= 0)
            {
                bm_data[y][x].r = circ.color[0];
                bm_data[y][x].g = circ.color[1];
                bm_data[y][x].b = circ.color[2];
            }
            else if (circ.fill == true && hyp <= r2 && y < bm_height && y >= 0 && x < bm_width && x >= 0) 
            {
                bm_data[y][x].r = circ.fill_color[0];
                bm_data[y][x].g = circ.fill_color[1];
                bm_data[y][x].b = circ.fill_color[2];
            }
        }
    }
}

int main(int argc, char** argv) 
{
    if (argc < 2) 
    {
        std::cout << "It seems, you forgot to enter the functions" << std::endl;
        std::cout << HELP << std::endl;
        exit(40);
    }
    
    std::string last_arg = argv[argc-1];
    std::string prelast_arg = argv[argc-2];

    std::unordered_map<std::string, std::string> flags_table = getFlags(argc, argv);
    std::string function_to_run = run_this(flags_table);

    if (function_to_run == "help") 
    {
        std::cout << PRINT_HELP << std::endl;
        exit(0);
    }
    if (function_to_run == "info")
    {
        std::cout << PRINT_INFO << std::endl;
        exit(0);
    }
    if (flags_table.find("input") == flags_table.end() || flags_table["input"] == "")
    {
        if (last_arg[0] != '-' && prelast_arg[0] != '-') 
        {
            flags_table["input"] = last_arg;
        }
        else
        {
            std::cerr << INPUT << std::endl;
            std::cout << HELP << std::endl;
            exit(43);
        }
    }
    if (flags_table.find("output") == flags_table.end() || flags_table["output"] == flags_table["input"])
    {
        std::cerr << OUTPUT << std::endl;
        exit(43);
    }

    Image img;
    img.readBMP(flags_table["input"]);
    if (function_to_run == "rect")
    {
        Rectangle rect = rect_struct(flags_table);
        img.rectangle(rect);
    }
    else if (function_to_run == "circle")
    {
        Circle circ = circ_struct(flags_table);
        img.circle(circ);
    }
    else if (function_to_run == "ornament")
    {
        Ornament orn = orn_struct(flags_table);
        // img.ornament(flags_table);
    }
    else if (function_to_run == "rotate")
    {
        Rotate rot = rot_struct(flags_table);
        // img.rotate(flags_table);
    }
    img.exportBMP(flags_table["output"]);
}

