#ifndef INVERTED_INDEX_HPP
#define INVERTED_INDEX_HPP

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <filesystem>  
#include <iostream>
#include <iomanip> 
#include <algorithm>

namespace fs = std::filesystem;
using namespace std;

typedef vector<pair<string, int>> wordOccurences;


class InvertedIndex
{
	private:
		map<string, wordOccurences> occurencesInFile;
		vector<string> fileList;
    public:
        void addFile(const fs::path& pathToScan, int level = 0);
        int showFiles(std::ostream& cout = std::cout);
		int parseAndIndex(string path);
		void showAllIndex(void);
		void indexAllDir(void);
		void searchWord(string wordToSearch);
		void streamAllIndex(void);
		void retrieveWord(string path, string word);
        friend void commandLineUtility(InvertedIndex obj, int argc, char* argv[]);
		vector<string> & getFileList(void);
		map<string, wordOccurences> & getOccurenceInFile(void);
		
		
};


#endif