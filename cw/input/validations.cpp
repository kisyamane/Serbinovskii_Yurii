#include "validations.h"


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
