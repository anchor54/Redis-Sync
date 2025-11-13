#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

std::vector<std::string> split(std::string &input, char delimiter);
std::string toLowerCase(std::string &s);
std::vector<char> serialize(std::string &key, std::string &value, std::vector<char> &buff);

#endif