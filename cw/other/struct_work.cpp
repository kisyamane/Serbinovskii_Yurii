#include "struct_work.h"


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
