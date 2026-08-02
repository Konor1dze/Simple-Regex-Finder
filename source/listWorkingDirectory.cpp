//
// Created by konor on 7/31/26.
//

#include "../headers/listWorkingDirectory.h"

#include <format>
#include <vector>
#include <iostream>
#include <map>

#include "../headers/readFile.h"

void list_working_directory(const std::filesystem::path &path) {
    std::error_code ec;

    if (!std::filesystem::is_directory(path, ec)) {
        std::cerr << std::format("The directory does not exist or is not accesible, error: {}\n", ec.message());
        return;
    }

    std::vector<std::filesystem::path> textFiles;
    std::filesystem::directory_iterator it(path, ec);

    if (ec) {
        std::cerr << std::format("Failed to read directory: {}\n", ec.message());
        return;
    }

    std::cout << path.string() << ":\n";

    for (const std::filesystem::directory_entry& x: it) {
        if (x.is_regular_file() && x.path().extension() == ".txt") {
            textFiles.push_back(x.path());
        }
    }

    if (!textFiles.empty()) {
        for (size_t i = 0; i < textFiles.size(); ++i) {
            std::cout << std::format("{}: {}\n", i+1, textFiles[i].filename().string());
        }

        size_t numToFind = 0;
        std::cout << "Enter a number of file you want to read: ";

        if (!(std::cin >> numToFind) || numToFind == 0 || numToFind > textFiles.size()) {
            std::cerr << "Invalid file number selected!\n";
            std::cin.clear();
        }
        std::cout << "\n\n";

        const std::filesystem::path& selectedFile = textFiles[numToFind - 1];

        size_t modeNum = 0;
        std::cout << "[0]: Phone Number Regex\n[1]: Email Regex\n[2]: User Regex\n";
        std::cout << "Enter a mode that you want to use: ";
        if (!(std::cin >> modeNum)) {
            std::cerr << "Invalid mode entered!\n";
            return;
        }

        switch (modeNum) {
            case 0: readFilePhoneNumber(selectedFile); break;
            case 1: readFileEmail(selectedFile); break;
            case 2: readFileUserRegex(selectedFile); break;
            default: std::cerr << "Uknown mode selected!\n"; break;
        }

    } else {
        std::cerr << "The directory does not contains any .txt files!\n";
        return;
    }
}