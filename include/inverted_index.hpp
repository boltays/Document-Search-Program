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
		InvertedIndex();
        void addFile(const fs::path& pathToScan, int level = 0);
        int showFiles(std::ostream& cout = std::cout);
		int parseAndIndex(string path);
		int showAllIndex(std::ostream& cout = std::cout);
		void indexAllDir(void);
		void searchWord(string wordToSearch, std::ostream& cout = std::cout);
		int streamAllIndex(std::ostream& = std::cout);
		void retrieveWord(string path, string word, std::ostream& cout = std::cout);
        friend void commandLineUtility(InvertedIndex obj, int argc, char* argv[]);
		vector<string> & getFileList(void);
		map<string, wordOccurences> & getOccurenceInFile(void);
		
		
};


#endif