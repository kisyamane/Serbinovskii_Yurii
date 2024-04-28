#include "find_function_to_run.h"
#include "validations.h"


std::string run_this(std::unordered_map<std::string, std::string> & flags_table) {
    if (flags_table.find("help") != flags_table.end()) {
        if (flags_table.size() > 1) {
            std::cout << "Warning: --help was found, so other flags will be ignored" << std::endl;
        }
        return "help";
    }
    else if (flags_table.find("info") != flags_table.end()) {
        if (flags_table.size() > 1) {
            std::cout << "Warning: --info was found, so other flags will be ignored (except of -i)" << std::endl;
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