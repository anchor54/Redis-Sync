#include <iostream>
#include <string>

/**
 * - [x] Keep accepting requests from terminal
 * - [ ] On BGSAVE:
 *      - [ ] parent forks a child process
 *      - [ ] parent start writting newer data to circular backup buffer
 *      - [ ] the child process writes all the data to RDB file
 *      - [ ] sends the RDB file over network to replica
 *      - 
 */
std::string toLowerCase(std::string &s) {
    std::string lowercase = "";
    for (char c: s) {
        lowercase += tolower(c);
    }
    return lowercase;
}

int main() {
    while (true) {
        std::string data;
        std::getline(std::cin, data);
        if (toLowerCase(data) == "exit") {
            std::cout << "Exiting..." << std::endl;
            return 0;
        }
        std::cout << "[User Input]: " << data << std::endl;
    }
}