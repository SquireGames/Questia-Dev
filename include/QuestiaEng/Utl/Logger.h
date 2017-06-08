#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

#define LOG(msg) \
{ \
	std::string str = msg + std::string(" <") + __FILE__ + "> Line: " + std::to_string(__LINE__) + '\n'; \
	std::ofstream out; \
	out.open("log.txt", std::ios_base::app); \
	out << str; \
	std::cout<<str; \
}

#endif // LOGGER_H
