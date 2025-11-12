#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "utils.h"

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

using handlerFn = std::function<void(std::vector<std::string>)>;

void exitHandler(std::vector<std::string> _) {
    std::cout << "Good bye..." << std::endl;
    exit(0);
}

void defaultHandler(std::string &userInput) {
    std::cout << "[User Input]: " << userInput << std::endl;
}

int main() {
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        
        std::map<std::string, handlerFn> handlerMap {
            { "exit", exitHandler },
        };
        
        std::vector<std::string> tokens = split(input, ' ');
        std::string command = toLowerCase(tokens.front());
        std::vector<std::string> args(tokens.begin() + 1, tokens.end());
    
        if (handlerMap.find(command) != handlerMap.end()) {
            handlerFn handler = handlerMap[command];
            handler(args);
        } else {
            defaultHandler(input);
        }
    }
}