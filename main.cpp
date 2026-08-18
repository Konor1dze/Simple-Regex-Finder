#include <filesystem>
#include <iostream>
#include <fstream>

#include "headers/listWorkingDirectory.h"

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string pathName;
    std::cout << "Enter a directory: ";

    std::cin >> pathName;

    std::filesystem::path path(pathName);

    list_working_directory(path);
}