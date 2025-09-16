#pragma once

#include <tuple>
#include <string>
#include <json.hpp>
#include <fstream>


std::tuple<int, std::string, float, float> ReadFromConfigFile(const std::string& file);