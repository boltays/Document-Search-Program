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