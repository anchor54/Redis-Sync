#include <iostream>
#include <string>
#include <map>
#include <functional>   // for function templates
#include <unistd.h>     // for fork
#include <sys/wait.h>   // for wait
#include <signal.h>

#include "utils.h"

/**
 * - [x] Keep accepting requests from terminal
 * - [ ] On BGSAVE:
 *      - [x] parent forks a child process
 *      - [ ] parent start writting newer data to circular backup buffer
 *      - [ ] the child process writes all the data to RDB file
 *      - [ ] sends the RDB file over network to replica
 *      - 
 */

std::map<std::string, std::string> db;

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

void getHandler(std::vector<std::string> args) {
    if (args.empty() || db.find(args.front()) == db.end()) return;
    std::cout << "Found: " << db[args.front()] << std::endl;
}

void setHandler(std::vector<std::string> args) {
    if (args.size() != 2) return;
    db[args.front()] = args.back();
    std::cout << "Done!" << std::endl;
}

void bgsaveHandler(std::vector<std::string> args) {
    pid_t pid = fork();
    if (pid == 0) {      // <-- this is a child process
        std::cout << "Starting background save... \n";
        sleep(5);
        std::cout << "Background save done...\n";
        std::cout << "Child Exiting...\n";
        exit(0);
    }
}

void defaultHandler(std::string &userInput) {
    std::cout << "[User Input]: " << userInput << std::endl;
}

void sigchild_handler(int sig) {
    int status;
    for (int child_pid = waitpid(-1, &status, WNOHANG); child_pid > 0; child_pid = waitpid(-1, &status, WNOHANG)) {
        std::cout << "Reaping child: " << child_pid << std::endl;
    }
}

int main() {
    signal(SIGCHLD, sigchild_handler);  // reaps the child asynchronously

    while (true) {
        std::string input;
        std::cout << "What do you wanna run today?: ";
        std::getline(std::cin, input);
        
        std::map<std::string, handlerFn> handlerMap {
            { "exit", exitHandler },
            { "get", getHandler },
            { "set", setHandler },
            { "bgsave", bgsaveHandler },
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

        std::cout << "--------------------------------------------\n";
    }
}