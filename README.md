Yahtzee
=======

This is the codebase for the workshop "C++ dal '90 a oggi"

### For Visual Studio users ###

If you use Visual Studio 2013, just download the repo and use the prebuilt solution here: https://github.com/italiancpp/yahtzee/tree/master/VS.

Build the solution and run yahtzee_test.exe. **One test should be red**.

### Prerequisites ###

* [CMake] for every O.S.
* OSX - Linux: at least gcc 4.8
* Win32: [VS 2013]

### How to build it ###

Open a console and go where you downloaded the repo, create a directory called linux-build, win32-build or osx-build

    $ mkdir linux-build

go inside:

    $ cd linux-build

and type 

    $ cmake ..

The cmake create a project compatible for you O.S. 
If you are on linux/osx now you can run

    $ make

If you are on windows with VS 2013 you can run

    $ msbuild Yahtzee.sln

After that you have compiled the program and the test.

On linux you can launch the program with

    $ ./Yahtzee

or run the test with

    $ ./yahtzee_test

If you are on windows you can run the program with:

    $ Debug\Yahtzee.exe

or run the test with

    $ Debug\yahtzee_test.exe

**One test should be red.**

[CMake]:http://www.cmake.org/files/v2.8/cmake-2.8.12.2-win32-x86.exe
[VS 2013]:http://www.visualstudio.com/downloads/download-visual-studio-vs#d-express-windows-desktop
