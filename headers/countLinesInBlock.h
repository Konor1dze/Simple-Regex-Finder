//
// Created by konor on 8/18/26.
//

#ifndef SIMPLEREGEXFINDER_COUNTLINESINBLOCK_H
#define SIMPLEREGEXFINDER_COUNTLINESINBLOCK_H

#include <cstddef>
#include <filesystem>

std::size_t countLinesInBlock(const std::filesystem::path& path, std::streampos startPos, std::streampos endPos);

#endif //SIMPLEREGEXFINDER_COUNTLINESINBLOCK_H
