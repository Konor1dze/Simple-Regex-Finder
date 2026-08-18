//
// Created by konor on 7/31/26.
//

#include "../headers/readFile.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <syncstream>

void readFile(const std::filesystem::path& path, const std::regex& pat, std::streampos startPos, std::streampos endPos, std::size_t startLine) {
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in) return;

    in.seekg(startPos);

    std::string line;
    size_t localLineCounter = startLine;

    if (startPos != std::streampos(0)) {
        std::getline(in, line);
    }

    while (in.tellg() != std::streampos(-1) && in.tellg() <= endPos && std::getline(in, line)) {
        ++localLineCounter;

        std::sregex_iterator p(line.begin(), line.end(), pat);
        std::sregex_iterator end;

        if (p != end) {
            std::osyncstream oss(std::cout);

            for (; p != end; ++p) {
                oss << "Line " << localLineCounter << ": " << (*p)[0] << "\n";
            }
        }
    }
}

size_t countLinesInBlock(const std::filesystem::path& path, std::streampos startPos, std::streampos endPos) {
    std::ifstream fin(path, std::ios::in | std::ios::binary);
    if (!fin) return 0;

    fin.seekg(startPos);
    std::string line;
    std::size_t lineCounter = 0;

    if (startPos != std::streampos{0}) std::getline(fin, line);
    while (fin.tellg() != std::streampos(-1) && fin.tellg() <= endPos && std::getline(fin, line)) {
        ++lineCounter;
    }
    return lineCounter;
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

    size_t firstBlockLines = countLinesInBlock(path, 0, midPos);
    std::regex pat(R"(\+?[ -.]?[(]?\d{1,4}[)]?[ -.]?(?:\(\d{1,4}\)|\d{1,4})[ -.]?\d{2,4}[ -.]?\d{2,4}[ -.]?\d{2,4}\b)");

    std::jthread jt1([&]() {
        readFile(path, pat, 0, midPos, 0);
    });

    std::jthread jt2([&]() {
        readFile(path, pat, midPos, fileSize, firstBlockLines);
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

    std::size_t firstBlockLines = countLinesInBlock(path, 0, midPos);
    std::regex pat(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    std::jthread jt1([&]() {
        readFile(path, pat, 0, midPos, 0);
    });

    std::jthread jt2([&]() {
        readFile(path, pat, midPos, fileSize, firstBlockLines);
    });
}

void readFileUserRegex(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::in | std::ios::binary);

    if (!in) {
        std::cerr << "File is not opened!" << "\n";
        return;
    }

    in.seekg(0, std::ios::end);
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
    std::size_t firstBlockSize = countLinesInBlock(path, 0, midPos);

    std::jthread jt1([&]() {
        readFile(path, user_regex, 0, midPos, 0);
    });

    std::jthread jt2([&]() {
        readFile(path, user_regex, midPos, fileSize, firstBlockSize);
    });
}

void readFileDate(const std::filesystem::path& path) {
    std::ifstream fin(path, std::ios::in | std::ios::binary);

    if (!fin) {
        std::cerr << "File is not opened!" << "\n";
        return;
    }

    fin.seekg(0, std::ios::end);
    std::streampos fileSize = fin.tellg();
    std::streampos midPos = fileSize / 2;
    fin.close();

    std::regex pat(R"(\b\d{1,2}[.\/-]\d{1,2}[.\/-]\d{2,4}\b)");
    std::size_t firstBlockSize = countLinesInBlock(path, 0, midPos);

    std::jthread t1([&]() {
        readFile(path, pat, 0, midPos, 0);
    });

    std::jthread t2([&]() {
        readFile(path, pat, midPos, fileSize, firstBlockSize);
    });
}