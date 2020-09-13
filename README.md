# Document Search Program
---
  In this project, the given library folder which has txt files are scanned for searching word and its number of occurences
  in multiple txt files. 
	
  Inverted Index structure is used for storing data. In this structure, each word is parsed and then stored with the path 
  of txt files which have this word and the number of occurences of this word in each txt file.
  The following is a sample tabular form of this structure:
	
	Name 
	animals/cats/doc1.txt (2), 
	ceng/linux/centos.txt (1),	
	history/asia/china.txt(5)
	
	Genius 
	Science/chemistry/marie_curie.txt (6), 
	Science/physics/heisenberg.txt (5)

   After this user enters word query and the word is retrived and printed to user. In this output, paths are 
   ordered according to number of occurrences. This project consists of following modules:

   * Filesystem analyzer for discovering documents in the library
   * Library indexer
   * Library searcher 
   * A command line utility
   * Unit tests for each of your modules

## Requirements 
---
Requirements are as follows:

## For Linux:
---
1. First C++17 compliant g++ toolchain must be installed. In this project g++-8 is installed. You can install by typing following commands:

   * sudo add-apt-repository ppa:ubuntu-toolchain-r/test
   * sudo apt-get update
   * sudo apt-get install gcc-8 g++-8
   * gcc-8 --version

   If the last command gives correct output it is done.

2. Then the make must be installed. In this project GNU Make 4.1 is used and installed by above commands.

3. Finally you must install cmake by going the following link and follow README file for installing it:
   https://cmake.org/download/

4. After completing all the steps gdownload the googletest in the following link:
   https://github.com/google/googletest/releases/tag/release-1.10.0

5. Extract googletest and go into directory and type the following commands:
   
   * mkdir build
   * cd build
   * cmake ..
   * make

   If doing so yields proper outputs, it is installed properly.

6. Then clone the repository of Document Search project, go into the folder and create build dir by typing

   * mkdir build

   and go into the folder by typing

   * cd build

7. Then run the following command for compile CMakeLists.txt:

   * cmake -DCMAKE_CXX_COMPILER=g++-8 ..

   If it completes properly run the following command to build project:
	
   * make

8. In the current directory, build, you can type the following command line utility for indexing library folder:

   * ./main -index ../library

   You can change your library path by your custom library path. Be careful with slash character between directory name.
   In linux it is / and in Windows it is \ which is escape sequence so you must double each slash like home\\directory\\
   After indexing this sample library you can query any word by replacing wordToSearch with yours:

   * ./main -search wordToSearch

9. For running all the test go into test dir in build by typing

   * cd test

   and then type

   * ./test_main for running all the tests.


## For Windows:
---
For running project in Windows, the user should follow the following instructions which is tested:
	
1. The Msys 2.0 must be installed by following the below link:
			
	https://www.msys2.org/
		
2. After the first step is done, user must install MinGW, make and MinGW by going the setup
   directory of msys2 which is named msys64 for 64 bit pc.
		
3. Upon reaching the folder, msys2.exe must be clicked and the command line of it will be 
   opened. Here you must enter bunch of commands to make your environment prepared. The 
   commands are as following:
			
   * On 64 bits computer the following:
	pacman -S mingw-w64-x86_64-gcc
			 
   * Then for installing make:
	pacman -S mingw64/mingw-w64-x86_64-make
			 
   * Then for installing cmake:
	pacman -S mingw-w64-x86_64-cmake
		
4. After all the tools are installed, download googletest below, which is the latest version 
   at current time:
		
	https://github.com/google/googletest/releases/tag/release-1.10.0
			
   After downloading the googletest, extract it into the directory of msys64->home->username.
			
5. Then close msys command line and go back to the directory mysy64 and click mingw64 or 32 for opening
   their command line.
		
6. Go into googletest dir by typing -> cd googletest..... directory. Then create build dir by typing 
   mkdir build and go into build by typing cd build. 
		
7. After that run following commands for building googletest:
   * cmake ../ -G "MinGW Makefiles"
   * mingw32-make.exe

8. After succesfull building get git link of Document Search Project by using git clone link.
		
9. Enter to the downloaded directory and run following commands:
   * mkdir build
   * cd build
   * cmake ../ -G "MinGW Makefiles"
   * mingw32-make.exe	

10. Following commands must be entered in build directory:
    * For indexing library type:
	./main.exe -index ../library
		
    * For printing the information of any word in files type:
	./main.exe -search word

11. For testing, enter to the test folder in build by;

	cd test/

    and then run the exe file by;

	./text_main.exe 

    and all the tests will be runned.

					
		
	 
	 
	  
	    
		 
		 
