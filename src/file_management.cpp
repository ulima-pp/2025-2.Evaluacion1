#include "file_management.h"
#include <spdlog/spdlog.h>

std::tuple<int, std::string> ReadFromConfigFile(const std::string &file)
{
    std::ifstream f(file);
    if (!f.is_open()) 
    {
        spdlog::error("Error opening the file");
        return { 0, "" };
    }
    try {
        nlohmann::json data = nlohmann::json::parse(f);
        const  std::tuple<int, std::string>returnData{ 
            data["cantidad"].get<int>(), 
            data["ubicacion_imagen"].get<std::string>()
        }; 
        return returnData;
    }catch (const nlohmann::json::parse_error& e) {
        spdlog::error("JSON parsing error: {}", e.what());
    }
    return { 0, "" };
}