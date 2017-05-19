#ifndef FILEDATA_H
#define FILEDATA_H

#include <experimental/filesystem>
#include <sstream>

#include <iostream>
#include <vector>
#include <algorithm>

namespace utl
{
    bool doesExist(const std::string& fileLocation);
    std::vector<std::string> getFiles(std::string directory, bool isWithDirectory);
    std::vector<std::string> getAllFiles(std::string directory, bool isWithDirectory);
    bool createDirectory(const std::string& filePath);

    std::vector<std::string> filterFiles(const std::vector<std::string>& inputFiles, const std::string& extension);
    std::vector<std::string> filterDirs(const std::vector<std::string>& inputFiles);
}

#endif // FILEDATA_H
