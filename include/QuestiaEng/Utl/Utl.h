#ifndef UTL_H
#define UTL_H

//stl
#include <sstream>  //std::stringstream
#include <vector>   //std::vector
#include <stdlib.h> //std::atoi
#include <string>

#include <string>
#include <locale>
#include <codecvt>

//boost
//#include <boost/algorithm/string.hpp> //boost::split, boost::is_any_of

namespace utl
{
///basic
enum Direction {none = 0, up = 1, upRight = 2, right = 3, downRight = 4, down = 5, downLeft = 6, left = 7, upLeft = 8};

///types
//comparison
bool isNumber(const std::string& string);
bool isWithAnyCharacter(const std::string& string, const std::string& characters);
//conversion
int   toInt(const std::string& string);
float toFloat(const std::string& string);
std::u32string toU32(const std::string& string);
//combination
std::vector <std::string> separateString(const std::string& saveString, const char& delimiter);
std::string conjoinString(const std::vector<std::string>& stringParts, const char& delimiter);
std::string conjoinString(const std::vector<std::string>& stringParts);
}

#endif // UTL_H
