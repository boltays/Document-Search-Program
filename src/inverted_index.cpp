#include "../include/inverted_index.hpp"

string nameOfIndexTxt = "indexedFiles.txt";

void InvertIndex::addFile(const fs::path& pathToScan, int level)
{
    for (const auto& entry : fs::directory_iterator(pathToScan)) {
        const auto filenameStr = entry.path().filename().string();
         
        if (entry.is_directory()) {
            addFile(entry, level + 1);
        }
        else if (entry.is_regular_file()) {
            if(entry.path().extension() == ".txt")
            {       
                fileList.push_back(entry.path().u8string());   
            }
            else
            {
                //Raise a warning.              
            }       
        }
        else
            std::cout << std::setw(level * 3) << "" << " [?]" << filenameStr << '\n';

        
    }
}

void InvertIndex::showFiles()
{
    for (auto it : fileList)
    {
        cout << it << endl;
    }
}


int InvertIndex::parseAndIndex(string path)
{
    ifstream file;
    file.open(path);
    if(!file.is_open()) return 1;
    map<string, int> categories;
    while(file.good())
    {
        string s;
        getline(file, s);
        int pos = s.find_first_of(' ');
        if(pos < 0) continue;
        while(s.size() > 0)
        {
            pos = s.find_first_of(' ');
            if(pos < 0)
                pos = s.size();
            string word = s.substr(0, pos);  
			if(word != "")
            {
                for(int ind = 0; ind <= word.size(); ind++)
                {
                    if(word[ind] >= 65 && word[ind]<= 90)
                    {
                        word[ind] += 32;    
                    }                   
                }
            } 
			
            categories[word]++;
            s = s.erase(0, pos+1);
        } 
    }
    for(auto wit = categories.begin(); wit != categories.end(); ++wit)
    {
        occurencesInFile[wit->first].push_back(make_pair(path, wit->second));
    }
    return 0;
}


void InvertIndex::showAllIndex(void)
{
    for(auto elem : occurencesInFile)
    {
        std::cout << elem.first << "\n";
        for(auto it : elem.second)
        {
            cout <<it.first <<" " <<it.second <<"\n";
        }
    }
}

void InvertIndex::indexAllDir(void)
{
    for(auto it : fileList)
    {
        parseAndIndex(it);
    }
}

bool comp(const pair<string, int> &a, const pair<string, int> &b)
{
    int term1 = a.second;
    int term2 = b.second;

    return term1>term2;
}

void InvertIndex::searchWord(string wordToSearch)
{
	for(auto elem : occurencesInFile)
	{
		if(wordToSearch == elem.first)
		{
			std::cout << elem.first << "\n"; 
			sort(elem.second.begin(), elem.second.end(), comp);
			for(auto it : elem.second)
            {                  
                cout <<it.first <<" " <<it.second <<"\n";
            }
		}
	}
}















