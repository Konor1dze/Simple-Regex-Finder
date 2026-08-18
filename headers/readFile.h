//
// Created by konor on 7/31/26.
//

#ifndef LEARNINGCPP_READFILE_H
#define LEARNINGCPP_READFILE_H
#include <filesystem>
#include <regex>

bool readFile(const std::filesystem::path& path, const std::regex& pat, std::streampos startPos, std::streampos endPos, std::size_t startLine);
void readFilePhoneNumber(const std::filesystem::path& path);
void readFileEmail(const std::filesystem::path& path);
void readFileUserRegex(const std::filesystem::path& path);
void readFileDate(const std::filesystem::path& path);
bool readFileForRegex(const std::filesystem::path& path, const std::regex& userPat);

#endif //LEARNINGCPP_READFILE_H
