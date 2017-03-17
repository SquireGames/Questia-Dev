#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <string>  //std::string
#include <utility> //std::pair
#include <vector>  //std::vector
#include <fstream> //std::fstream
#include <sstream> //std::stringstream
#include <map>     //std::map
#include <iostream>

// This object assumes the file is good

class SaveFile
{
public:
    SaveFile(std::string _fileName);
    SaveFile();
    ~SaveFile();

    void setFilePath(std::string _fileName)
    {
        fileName = _fileName;
    }

    bool readFile();  // gets updated vector
    bool readFile(char separator);
    void writeFile(); // saves changes
    void clearSave(); // clears map

    template <class T>
    void addItem  (std::string itemName, T item) // saving lists of entities, things with the same type
    {
        sStream << item;
        saveList.push_back(std::make_pair(itemName, sStream.str()));
        sStream.str(std::string());
    }

    template <class T>
    void saveItem (std::string itemName, T item) // overwriting entries
    {
        for(unsigned int it = 0; it != saveList.size(); it++)
        {
            if(saveList[it].first == itemName)
            {
                sStream << item;
                saveList[it].second = sStream.str();
                sStream.str(std::string());
                return;
            }
        }
        addItem(itemName, item);
    }

    std::vector<std::string> getItemList()
    {
        std::vector<std::string> itemList;
        for(unsigned int it = 0; it != saveList.size(); it++)
        {
            itemList.push_back(saveList[it].first);
        }
        return itemList;
    }
    std::string getItem(std::string itemName);

    std::vector <std::pair <std::string, std::string> > getSaveList()
    {
        return saveList;
    }



private:
    std::string fileName;

    std::vector <std::pair <std::string, std::string> > saveList;
    std::map <std::string, std::string> commentList;
    std::fstream fileStream;
    std::stringstream sStream;
};

#endif // SAVEFILE_H
