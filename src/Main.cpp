//Libs
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <signal.h>
#include <cstdio>

// Header Files
#include "FileWatcher.h"
#include "Core.h"
#include "Config.h"

using namespace std;

void signalHandler(int signum) {
    if (signum == SIGTERM) {
        // Handle termination signal
        std::cout << "Termination signal received. Exiting..." << std::endl;
        exit(0);
    }
}

int main() {
    // Register signal handler for SIGTERM
    signal(SIGTERM, signalHandler);

    // Fork to create a child process
    pid_t pid = fork();
    if (pid < 0) {
        // Fork failed
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    if (pid > 0) {
        // Parent process
        std::cout << "Daemon started with PID: " << pid << std::endl;
        return 0;
    }

    // Child process (daemon)
    // Detach from terminal
    if (setsid() < 0) {
        std::cerr << "setsid failed!" << std::endl;
        return 1;
    }

    // Redirect standard I/O streams
    freopen("/dev/null", "r", stdin);
    freopen("./output.log", "w", stdout);
    freopen("./erroroutput.log", "w", stderr);

    std::cout << "Daemon started" << std::endl;


    // Daemon logic goes here
    while (true) {
        mainloop();
    }

    return 0;
}