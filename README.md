# Document Search Program

## Requirements
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
* mingw32-make

8. After succesfull building get git link of project by using git clone link.
		
9. Enter to the downloaded directory and run following commands:
* mkdir build
* cd build
* cmake ../ -G "MinGW Makefiles"
* mingw32-make	

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

					
		
	 
	 
	  
	    
		 
		 
