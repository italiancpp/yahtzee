Yahtzee
=======

This is the codebase for the workshop "C++ from '90 to '14"

### Prerequisites ###

* [CMake] for every O.S.
* OSX - Linux: at least gcc 4.8
* Win32: [VS 2013]

### How to build it ###

Open a console and go where you downloaded the repo, create a directory called linux-build, win32-build or osx-build, go inside and type 

    $ cmake ..

The cmake create a project compatible for you O.S. If you are on linux/osx now you can run

    $ make

And you compile the program and the test. You can launch the program with

    $ ./yahtzee

or run the test with

    $ ./yahtzee_test


One test should be red.

[CMake]:http://www.cmake.org/files/v2.8/cmake-2.8.12.2-win32-x86.exe
[VS 2013]:http://www.visualstudio.com/downloads/download-visual-studio-vs#d-express-windows-desktop
