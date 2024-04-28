#pragma once

#include "structs.h"
#include <iostream>
#include <unordered_map>


Rectangle rect_struct(std::unordered_map<std::string, std::string> & flags_table);
Circle circ_struct(std::unordered_map<std::string, std::string> & flags_table);
Ornament orn_struct(std::unordered_map<std::string, std::string> & flags_table);
Rotate rot_struct(std::unordered_map<std::string, std::string> & flags_table);