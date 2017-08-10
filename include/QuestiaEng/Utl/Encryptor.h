#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <memory>

namespace utl
{

struct Salt
{
	std::unique_ptr<unsigned char[]> data;
	int length;
	
	void printValue() const;
};

//generates a random salt
Salt generateSalt(int bytes);

}

#endif // ENCRYPTOR_H
