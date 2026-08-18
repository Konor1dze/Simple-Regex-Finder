//
// Created by konor on 8/19/26.
//

#ifndef SIMPLEREGEXFINDER_STARTFUNC_H
#define SIMPLEREGEXFINDER_STARTFUNC_H

#include "listWorkingDirectory.h"

#include <filesystem>
#include <iostream>

inline void startFunc() {
    std::cout << R"(
    ____                               ______ _             __
   / __ \___  ____ ___  _  __         / ____/(_)____  _____/ /___  _____
  / /_/ / _ \/ __ `/ _ \| |/_/______ / /_   / / __  \/ __  / _  / / ___/
 / _, _/  __/ /_/ /  __/>  </_____// __/  / / / / / / /_/ /  __/ / /
/_/ |_|\___/\__, /\___/_/\_\      /_/    /_/_/ /_/\__,_/\___/_/ /_/
           /____/
    )" << std::endl;
    std::cout << "\t\tWelcome to Simple Regex Finder!\n\n";

    std::string pathName;
    std::cout << "Enter a directory: ";

    std::cin >> pathName;

    std::filesystem::path path(pathName);

    list_working_directory(path);
}

inline bool askYesNo(const std::string& question) {
    char choice;
    while (true) {
        std::cout << question << " (y/n): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input error. Try again.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        choice = std::tolower(choice);

        if (choice == 'y') return true;
        if (choice == 'n') return false;

        std::cout << "Incorrect input. Please, enter 'y' or 'n'.\n";
    }
}

inline void continueFunc() {
    if (askYesNo("Do you want to continue?")) {
        std::string pathName;
        std::cout << "Enter a directory: ";

        std::cin >> pathName;

        std::filesystem::path path(pathName);

        list_working_directory(path);
    } else {
        std::cout << "\n";
        std::cout << "Session is over! Thank you for using simple regex finder!\n";
        return;
    }
}

#endif //SIMPLEREGEXFINDER_STARTFUNC_H
