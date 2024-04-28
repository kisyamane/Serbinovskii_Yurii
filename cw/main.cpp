

#include "input/checking_flags.h"
#include "input/find_function_to_run.h"
#include "image_methods/io.h"
#include "image_methods/one_class.h"
#include "image_methods/image_work.h"
#include "other/struct_work.h"
#include "other/structs.h"
#include "other/messages.h"

int main(int argc, char** argv) 
{
    std::cout << "Course work for option 1, created by Yurii Serbinovskii." << std::endl;
    if (argc < 2) 
    {
        std::cout << "It seems, you forgot to pick the option" << std::endl;
        std::cout << HELP << std::endl;
        exit(40);
    }
    

    std::unordered_map<std::string, std::string> flags_table = getFlags(argc, argv);
    std::string function_to_run = run_this(flags_table);

    if (function_to_run == "help") 
    {
        std::cout << PRINT_HELP << std::endl;
        exit(0);
    }

    Image img;
    bool need_info = flags_table.find("info") != flags_table.end() ? true : false;
    img.readBMP(flags_table["input"], need_info);

    if (flags_table.find("output") == flags_table.end() || flags_table["output"] == flags_table["input"])
    {
        std::cerr << OUTPUT << std::endl;
        exit(43);
    }

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
        img.ornament(orn);
    }
    else if (function_to_run == "rotate")
    {
        Rotate rot = rot_struct(flags_table);
        img.rotate(rot);
    }
    img.exportBMP(flags_table["output"]);
}

