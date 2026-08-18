//
// Created by konor on 7/31/26.
//

#include "../headers/readFile.h"
#include <iostream>
#include <fstream>
#include <mutex>
#include <regex>
#include <thread>

size_t lineCounter = 0;
void readFile(const std::filesystem::path& path, std::regex pat, std::streampos startPos, std::streampos endPos) {
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in) return;

    in.seekg(startPos);

    std::string line;

    if (startPos != std::streampos(0)) {
        std::getline(in, line);
    }

    while (in.tellg() != std::streampos(-1) && in.tellg() <= endPos && std::getline(in, line)) {
        ++lineCounter;

        for (std::sregex_iterator p(line.begin(), line.end(), pat); p != std::sregex_iterator{}; ++p) {
            std::cout << lineCounter << ": " << (*p)[0] << "\n";
        }
    }
}

void readFilePhoneNumber(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::in | std::ios::binary);

    if (!in) {
        std::cerr << "File is not opened!" << "\n";
        return;
    }

    in.seekg(0, std::ios::end);
    std::streampos fileSize = in.tellg();
    std::streampos midPos = fileSize / 2;
    in.close();

    std::regex pat(R"(\+?[ -.]?[(]?\d{1,4}[)]?[ -.]?(?:\(\d{1,4}\)|\d{1,4})[ -.]?\d{2,4}[ -.]?\d{2,4}[ -.]?\d{2,4}\b)");

    std::jthread jt1([&]() {
        readFile(path, pat, 0, midPos);
    });

    std::jthread jt2([&]() {
        readFile(path, pat, midPos, fileSize);
    });
}

void readFileEmail(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::in | std::ios::binary);

    if (!in) {
        std::cerr << "File is not opened!" << "\n";
        return;
    }

    in.seekg(0, std::ios::end);
    std::streampos fileSize = in.tellg();
    std::streampos midPos = fileSize / 2;
    in.close();

    std::regex pat(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    std::jthread jt1([&]() {
        readFile(path, pat, 0, midPos);
    });

    std::jthread jt2([&]() {
        readFile(path, pat, midPos, fileSize);
    });
}

void readFileUserRegex(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::in | std::ios::binary);

    if (!in) {
        std::cerr << "File is not opened!" << "\n";
        return;
    }

    in.seekg(0, std::ios::beg);
    std::streampos fileSize = in.tellg();
    std::streampos midPos = fileSize / 2;
    in.close();

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

    std::jthread jt1([&]() {
        readFile(path, user_regex, 0, midPos);
    });

    std::jthread jt2([&]() {
        readFile(path, user_regex, midPos, fileSize);
    });
}