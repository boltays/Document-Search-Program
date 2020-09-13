#include <gtest/gtest.h>
#include <climits>
#include "../include/inverted_index.hpp"

/* The variables and function from source file is externed
   for using in test functions.
*/
extern string slashForPath;
extern bool comp(const pair<string, int> &a, const pair<string, int> &b);
extern string nameOfIndexTxt;

class InIndex : public testing::Test
{
public:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

/* Function tompare two vectors */
int compareTwoVector(vector<string> vec1, vector<string> vec2)
{
	return (vec1 == vec2);
}

/* The following function is used the get the path of library folder
   for using sample folder in the program. Filesystem library of 
   C++17 is utilized.
*/
void determineExactPathLibrary(string & pathOfLibrary)
{
	string a  = std::filesystem::current_path().u8string();
	string stem = fs::current_path().stem().u8string();
	
	string exactPath = a.erase(a.find(stem));
	exactPath = exactPath.erase(exactPath.find(slashForPath + "build"));
	
	pathOfLibrary = exactPath + slashForPath + "library";
}

/*  The below function is used for comparing the size of two containers.*/
int compareSizeOfContainers(int size1, int size2)
{
	return (size1 == size2);
}

/*  The below function is used for comparing two maps.*/
int compareTwoMap(map<string, wordOccurences> map1, map<string, wordOccurences> map2)
{
    return (map1 == map2);    
}

/* The following function is used to test addFile function by comparing two 
   objects' fileList vectors.
*/
TEST_F(InIndex, iterate_through_given_library)
{
	InvertedIndex obj1;
	InvertedIndex obj2;
	
	string pathOfLibrary;
	determineExactPathLibrary(pathOfLibrary);
	
	obj1.addFile(pathOfLibrary);
	obj2.addFile(pathOfLibrary);
	
	ASSERT_EQ(compareTwoVector(obj1.getFileList(), obj2.getFileList()), 1);	
}

/* showFiles function is tested according to its return type. Two objects 
   are created one parse and index given directory, other one not.  Therefore
   one has vector with info other one not and returns 1
*/
TEST_F(InIndex, test_show_files)
{
	InvertedIndex obj1;
	InvertedIndex obj2;
	
	string pathOfLibrary;
    determineExactPathLibrary(pathOfLibrary);
    
    obj1.addFile(pathOfLibrary);
    
    stringstream ss;
    ASSERT_EQ(obj1.showFiles(ss), 0);
    ASSERT_EQ(obj2.showFiles(ss), 1);	
}


/* The following function is used for testing indexAllDir function. This function 
   stores all the info into map and three objects are used two of them do the process
   properly and one not. Comparing their maps give if the function works well.
*/
TEST_F(InIndex, test_parser_indexer)
{
	InvertedIndex obj1;
	InvertedIndex obj2;
	InvertedIndex obj3;
	
	string pathOfLibrary;
	determineExactPathLibrary(pathOfLibrary);
    obj1.addFile(pathOfLibrary);
    obj2.addFile(pathOfLibrary);
    
	obj1.indexAllDir();
	obj2.indexAllDir();
	
	ASSERT_EQ(compareTwoMap(obj1.getOccurenceInFile(), obj3.getOccurenceInFile()), 0);
	ASSERT_EQ(compareTwoMap(obj1.getOccurenceInFile(), obj2.getOccurenceInFile()), 1);
	ASSERT_EQ(compareSizeOfContainers(obj1.getOccurenceInFile().size(), obj2.getOccurenceInFile().size()), 1);
	ASSERT_EQ(compareSizeOfContainers(obj1.getOccurenceInFile().size(), obj3.getOccurenceInFile().size()), 0);
}


/* The following test showAllIndex function which prints map if it exist. If
   it exists it is opened well and return 0 otherwise 1 and this is used for
   testing.
*/
TEST_F(InIndex, test_showing_all_index)
{
	InvertedIndex obj;
	InvertedIndex obj1;
	
	string pathOfLibrary;
	determineExactPathLibrary(pathOfLibrary);
    obj.addFile(pathOfLibrary);
    
    obj.indexAllDir();
    obj1.indexAllDir();
    
    stringstream ss;
    ASSERT_EQ(obj.showAllIndex(ss), 0);   
    ASSERT_EQ(obj1.showAllIndex(ss), 1);       
}

/* The comp function is used for sorting and it returns 1 if first parameter
   is greater than second one. Otherwise it returns 0. Two pair is created
   for mocking path and frequency value of given word.
*/
TEST_F(InIndex, test_comparison_function)
{
	pair<string, int> a;
	pair<string, int> b;
	
	a.first  = "test1";
	a.second =  45;
	
	b.first  = "test2";
	b.second =  64;
	
	ASSERT_EQ(comp(b,a), 1);
	ASSERT_EQ(comp(a,b), 0);
}


/* The below function is used for testing streamAllIndex function. It inserts 
   occurenceInFile map into txt file. It uses ostream as an input param. By 
   default it is cout and stringstream is given for testing purpose here since 
   it is needed to obtain the content of it. 
*/
TEST_F(InIndex, test_streaming_index_to_file)
{
	InvertedIndex obj;
	InvertedIndex obj1;
	
	string pathOfLibrary;
	determineExactPathLibrary(pathOfLibrary);
	
	
    obj.addFile(pathOfLibrary);
    obj.indexAllDir();
    
    obj1.addFile(pathOfLibrary);
    obj1.indexAllDir();
    
    string pathToText = fs::current_path().u8string();
    pathToText += slashForPath + nameOfIndexTxt;
    
    stringstream stream;
    
    ASSERT_EQ(obj.streamAllIndex(stream), 0);
    ASSERT_NE(fs::file_size(pathToText), 0);	
	
	ASSERT_EQ(compareTwoMap(obj1.getOccurenceInFile(), obj.getOccurenceInFile()), 1);	
	
    stringstream show;
	obj1.streamAllIndex(show);
    
    
    string streamString;
    string showString;
    
    while(stream >> streamString && show >> showString)
    {
    	//cout << streamString <<" " <<showString <<endl;
    	ASSERT_EQ(streamString.compare(showString), 0);
    }
}

/* The searchWord function is tested which accepts ostream as an input and 
   it is by default std::cout. Here stringstream is given as an input for 
   getting the content instead of printing to console. streamAllIndex is 
   used for comparing with searchWord.
*/
TEST_F(InIndex, test_retrieve_word_from_file)
{
	InvertedIndex obj;
	InvertedIndex obj1;
	
	string pathOfLibrary;
	determineExactPathLibrary(pathOfLibrary);
	
    obj.addFile(pathOfLibrary);
    obj.indexAllDir();
       
    stringstream ss;
    obj.streamAllIndex(ss);
       
    stringstream retrieveFunction;
    stringstream searchWordFunction;
    
    
    string path = fs::current_path().u8string();
    path += slashForPath + nameOfIndexTxt;
    obj.retrieveWord(path, "the", retrieveFunction);
    obj.searchWord("the", searchWordFunction);
    
    
    string line;
    string line1;
    

	int countForNewLine = 0;
	
    while(retrieveFunction >> line && searchWordFunction >> line1)
    {
		//cout <<line <<" " <<line1 <<endl;
    	ASSERT_EQ(line.compare(line1), 0);
    }    
}


/* The retrieveFunction converts word to lowercase for this reason,
   given same word in two version has no effect. Here the and The words
   are queried and the results are compared by using stringstream again 
   with the help of retrieveFunction and searchWord.
*/
TEST_F(InIndex, upper_lower_case_sensitivity)
{
	InvertedIndex obj;
	InvertedIndex obj1;
	
	string pathOfLibrary;
	determineExactPathLibrary(pathOfLibrary);
	
    obj.addFile(pathOfLibrary);
    obj.indexAllDir();
       
    stringstream ss;
    obj.streamAllIndex(ss);
       
    stringstream retrieveFunction;
    stringstream searchWordFunction;
    
    
    string path = fs::current_path().u8string();
    path += slashForPath + nameOfIndexTxt;
    obj.retrieveWord(path, "the", retrieveFunction);
    obj.searchWord("The", searchWordFunction);
    
    //cout <<path <<endl;
    string line;
    string line1;
    

	int countForNewLine = 0;
	
    while(retrieveFunction >> line && searchWordFunction >> line1)
    {
    	ASSERT_EQ(line.compare(line1), 0);
    }    
}