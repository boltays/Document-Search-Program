#include <gtest/gtest.h>
#include <climits>
#include "../include/inverted_index.hpp"


extern string slashForPath;

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


int compareTwoVector(vector<string> vec1, vector<string> vec2)
{
	return (vec1 == vec2);
}

void determineExactPathLibrary(string & pathOfLibrary)
{
	string a  = std::filesystem::current_path().u8string();
	string stem = fs::current_path().stem().u8string();
	
	string exactPath = a.erase(a.find(stem));
	exactPath = exactPath.erase(exactPath.find(slashForPath + "build"));
	
	pathOfLibrary = exactPath + slashForPath + "library";
}

int compareSizeOfContainers(int size1, int size2)
{
	return (size1 == size2);
}

int compareTwoMap(map<string, wordOccurences> map1, map<string, wordOccurences> map2)
{
    return (map1 == map2);    
}

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