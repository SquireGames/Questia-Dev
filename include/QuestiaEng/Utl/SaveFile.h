#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <string>  
#include <algorithm>
#include <vector>  
#include <fstream> 
#include <sstream> 
#include <map>
#include <iostream>

class SaveFile
{
public:
	SaveFile(std::string fileName);
	SaveFile();
	~SaveFile() = default;
	
	void setFilePath(const std::string& fileName) {this->fileName = fileName;}

	bool readFile();
	bool readFile(char separator);
	void writeFile();
	void clearSave();

	//lists of things with the same type, item usually being a string for structs
	template <class T> void addItem(const std::string& itemName, T item);
	//single entry per key, item usually being a string for structs
	template <class T> void saveItem(const std::string& itemName, T item);

	std::vector<std::string> getItemList();
	std::string getItem(const std::string& itemName);

	std::vector <std::pair <std::string, std::string> > getSaveList(){return saveList;}

private:
	std::string fileName;

	std::vector <std::pair <std::string, std::string> > saveList;
	//TODO implement
	std::map <std::string, std::string> commentList;
	std::fstream fileStream;
	std::stringstream sStream;
};

template <class T>
void SaveFile::addItem(const std::string& itemName, T item)
{
	sStream << item;
	saveList.push_back(std::make_pair(itemName, sStream.str()));
	sStream.str(std::string());
}

template <class T>
void SaveFile::saveItem(const std::string& itemName, T item)
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

#endif // SAVEFILE_H
