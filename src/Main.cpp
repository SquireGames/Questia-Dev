//give warnings about potential incompatible compilers
#ifdef _WIN32
	#if !(__GNUC__ == 6 && \
		  __GNUC_MINOR__ == 1 && \
		  __GNUC_PATCHLEVEL__ == 0)
		  #warning Compiler version may be incompatible with pre-built SFML dlls. Use g++ 6.1.0 (DW2).
	#endif // __GNUC__
#else
	#warning Your operating system was not yet tested with the prebuilt SFML dlls.
#endif

#include <iostream>
#include <stdexcept>

#include "QuestiaDev/Application.h"

int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch (std::exception& exc)
    {
        std::cout << std::endl << "Runtime exception: " << exc.what() <<std::endl;
    }
}
