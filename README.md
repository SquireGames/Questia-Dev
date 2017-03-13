# Questia

Questia is an in development top down action roleplaying game that takes place in the Medieval ages. It is written in c++, along with the SFML API for rendering and audio. This project features many modular components that could be added into anybodies engine, including resource management, gui systems, tile map editing, and file parsing. All future updates to the game will be pushed to this repository. All of the source code is open source, so use the code in your own projects.

Compiling guide
----------------
This game was tested to compile on:
* Windows

This game uses the following:
* Libraries
  * SFML 2.4.2 (GCC 6.1.0 MinGW (DW2) - 32-bit)
    * [Download here](http://www.sfml-dev.org/download/sfml/2.4.2/)
    * All required .dll's, .a's and include files are already included in this repository
    * The following files will need to be copied to the executable's directory: 
      * sfml-audio-2.dll
      * sfml-graphics-2.dll
      * sfml-system-2.dll
      * sfml-window-2.dll
      * openal32.dll
* Compiler 
  * GCC 6.1.0 MinGW (DW2) - 32-bit
    * You must use exactly this version, or the pre-compiled SFML will not work properly. You can also recompile SFML yourself to use any other compiler.
    * The following files will need to be copied to the executable's directory: 
      * libgcc_s_dw2-1.dll
      * libstdc++\-6.dll
      * libwinpthread-1.dll
     
* Other dependencies
  * Folders that must be in the executables directory to launch the game: Data, Maps, Media

The game's media, maps, and data files not open source. You must attain a copy of the game to have access to those files.

LICENSE:
----------------
This project is licensed under the terms of the GNU GPLv3 license, see LICENSE.txt.
