#include "utils.h"
#include <fstream>
#include <string>
#include <map>

const int KB_SZ = 1024;
const int BUFF_LIMIT = 4 * KB_SZ * KB_SZ;

int rdbExport(std::map<std::string, std::string> &db) {
    std::ofstream rdbFile("../temp/dump.rdb");

    std::vector<char> buff;
    buff.reserve(BUFF_LIMIT + KB_SZ);

    int elements_written = 0;
    for (auto entry: db) {
        elements_written++;
        std::string key = entry.first, value = entry.second;
        serialize(key, value, buff);

        if (buff.size() >= BUFF_LIMIT) {
            buff.insert(
                buff.begin(),
                reinterpret_cast<const char*>(&elements_written),
                reinterpret_cast<const char*>(&elements_written) + sizeof(elements_written)
            );

            rdbFile.write(buff.data(), buff.size());
            buff.clear();
        }
    }

    rdbFile.close();
}