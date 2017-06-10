#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <locale>
#include <codecvt>

#include "QuestiaEng/Utl/Logger.h"

class SaveFile
{
public:
	SaveFile(std::string fileName, bool isUnicode = false);
	SaveFile();
	~SaveFile() = default;

	void setFilePath(const std::string& fileName);
	void setUnicode(bool isUsingUnicode = true) {this->isUnicode = isUsingUnicode;}

	//both unicode and not-unicode
	bool readFile();
	bool readFile(char separator);
	//only not-unicode
	void writeFile();
	void clearSave();

	//only not-unicode
	//lists of things with the same type, T usually being a string for structs, can be int or float
	template <class T> void addItem(const std::string& itemName, T item);
	//single entry per key, T usually being a string for structs, can be int or float
	template <class T> void saveItem(const std::string& itemName, T item);

	//for isUnicode = false, aka std::basic_string<char>
	std::vector<std::string> getItemKeyList();
	std::string getItem(const std::string& itemName);
	const std::vector <std::pair <std::string, std::string> >& getSaveList() {return saveList;}

	//for isUnicode = true, aka std::u32string or std::basic_string<char32_t>
	std::vector<std::u32string> getItemKeyList_uni();
	std::u32string getItem_uni(const std::u32string & itemName);
	const std::vector <std::pair <std::u32string, std::u32string> >& getSaveList_uni() {return saveList_uni;}

private:
	bool readFile_uni();
	bool readFile_uni(char separator);

	std::string fileName;
	bool isUnicode = false;

	std::vector <std::pair <std::string, std::string> > saveList;
	std::vector <std::pair <std::u32string, std::u32string> > saveList_uni;
	//TODO implement
	//std::map <std::string, std::string> commentList;

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
