#include "utils.h"

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> split(std::string &input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream isstream(input);
    for (std::string part; std::getline(isstream, part, delimiter);) {
        tokens.push_back(part);
    }
    return tokens;
}