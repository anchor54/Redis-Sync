#include "utils.h"

#include <vector>
#include <string>
#include <sstream>
#include <arpa/inet.h>

std::vector<std::string> split(std::string &input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream isstream(input);
    for (std::string part; std::getline(isstream, part, delimiter);) {
        tokens.push_back(part);
    }
    return tokens;
}

std::string toLowerCase(std::string &s) {
    std::string lowercase = "";
    for (char c: s) {
        lowercase += tolower(c);
    }
    return lowercase;
}

std::vector<char> serialize(std::string &key, std::string &value, std::vector<char> &buff) {
    // [key size][key][value size][value]
    u_int32_t klen_n = htonl(static_cast<u_int32_t>(key.length()));
    u_int32_t vlen_n = htonl(static_cast<u_int32_t>(value.length()));

    buff.insert(
        buff.end(),
        reinterpret_cast<const char*>(&klen_n),
        reinterpret_cast<const char*>(&klen_n) + sizeof(klen_n)
    );
    if (!key.empty()) {
        buff.insert(
            buff.end(),
            reinterpret_cast<const char*>(key.data()),
            reinterpret_cast<const char*>(key.data()) + key.length()
        );
    }

    buff.insert(
        buff.end(),
        reinterpret_cast<const char*>(&vlen_n),
        reinterpret_cast<const char*>(&vlen_n) + sizeof(vlen_n)
    );
    if (!value.empty()) {
        buff.insert(
            buff.end(),
            reinterpret_cast<const char*>(value.data()),
            reinterpret_cast<const char*>(value.data()) + value.length()
        );
    }
    return buff;
}