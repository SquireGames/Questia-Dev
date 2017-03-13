#ifndef FILEDATA_H
#define FILEDATA_H

//#include <boost/filesystem.hpp>
#include <sstream>

#include <iostream>
#include <vector>

namespace utl
{
    bool doesExist(const std::string& fileLocation);
    std::vector<std::string> getFiles(std::string directory, bool isWithDirectory);
    std::vector<std::string> getAllFiles(std::string directory, bool isWithDirectory);
    bool createDirectory(const std::string& filePath);

    std::vector<std::string> filterFiles(const std::vector<std::string>& inputFiles, const std::string& extension);
}

#endif // FILEDATA_H
