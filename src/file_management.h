#pragma once

#include <tuple>
#include <string>
#include <json.hpp>
#include <fstream>


std::tuple<int, std::string> ReadFromConfigFile(const std::string& file);