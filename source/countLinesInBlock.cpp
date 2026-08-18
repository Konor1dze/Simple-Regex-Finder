//
// Created by konor on 8/18/26.
//

#include "../headers/countLinesInBlock.h"

#include <fstream>

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