//
// Created by konor on 7/31/26.
//

#include "../headers/readFile.h"
#include <iostream>
#include <fstream>
#include <regex>

void readFilePhoneNumber(const std::filesystem::path& path) {
    std::ifstream in(path);

    if (!in) {
        std::cerr << "File is not opened!" << "\n";
        return;
    }

    std::regex pat(R"(\+?[ -.]?[(]?\d{1,4}[)]?[ -.]?(?:\(\d{1,4}\)|\d{1,4})[ -.]?\d{2,4}[ -.]?\d{2,4}[ -.]?\d{2,4}\b)");

    size_t lineCounter = 0;
    for (std::string line; std::getline(in,line); ) {
        ++lineCounter;

        for (std::sregex_iterator p(line.begin(), line.end(), pat); p != std::sregex_iterator{}; ++p) {
            std::cout << lineCounter << ": " << (*p)[0] << "\n";
        }
    }
    std::cout << "\n";
}

void readFileEmail(const std::filesystem::path& path) {
    std::ifstream in(path);

    if (!in) {
        std::cerr << "File is not opened!" << "\n";
        return;
    }

    std::regex pat(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    size_t lineCounter = 0;
    for (std::string line; std::getline(in,line); ) {
        ++lineCounter;

        for (std::sregex_iterator p(line.begin(), line.end(), pat); p != std::sregex_iterator{}; ++p) {
            std::cout << lineCounter << ": " << (*p)[0] << "\n";
        }
    }
    std::cout << "\n";
}

void readFileUserRegex(const std::filesystem::path& path) {
    std::ifstream in(path);

    if (!in) {
        std::cerr << "File is not opened!" << "\n";
        return;
    }

    std::string regex_str;

    std::cout << "Enter your regex (for example, [a-z]+): ";
    std::cin >> regex_str;

    std::regex user_regex;

    try {
        user_regex = std::regex(regex_str);
    } catch (const std::regex_error& err) {
        std::cout << "Regex error: " << err.what() << "\n";
        std::cout << "Error code: " << err.code() << "\n";
        return;
    }

    size_t lineCounter = 0;
    for (std::string line; std::getline(in,line); ) {
        ++lineCounter;

        for (std::sregex_iterator p(line.begin(), line.end(), user_regex); p != std::sregex_iterator{}; ++p) {
            std::cout << lineCounter << ": " << (*p)[0] << "\n";
        }
    }
    std::cout << "\n";
}