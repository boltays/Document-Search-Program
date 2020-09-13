#include "../include/inverted_index.hpp"

#if defined(_WIN32)
   string slashForPath = "\\";
#elif defined(__linux__)
   string slashForPath = "/";
#endif


string nameOfIndexTxt = "indexedFiles.txt";

void InvertedIndex::addFile(const fs::path& pathToScan, int level)
{
    for (const auto& entry : fs::directory_iterator(pathToScan)) {
        const auto filenameStr = entry.path().filename().string();
         
        if (entry.is_directory()) {
            addFile(entry, level + 1);
        }
        else if (entry.is_regular_file()) {
            if(entry.path().extension() == ".txt")
            {       
                getFileList().push_back(entry.path().u8string());   
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

vector<string> & InvertedIndex::getFileList(void)
{
	return this->fileList;
}

void InvertedIndex::showFiles()
{
    for (auto it : getFileList())
    {
        cout << it << endl;
    }
}


map<string, wordOccurences> & InvertedIndex::getOccurenceInFile(void)
{
	return occurencesInFile;
}

int InvertedIndex::parseAndIndex(string path)
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
        getOccurenceInFile()[wit->first].push_back(make_pair(path, wit->second));
    }
    return 0;
}


void InvertedIndex::showAllIndex(void)
{
    for(auto elem : getOccurenceInFile())
    {
        std::cout << elem.first << "\n";
        for(auto it : elem.second)
        {
            cout <<it.first <<" " <<it.second <<"\n";
        }
    }
}

void InvertedIndex::indexAllDir(void)
{
    for(auto it : getFileList())
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

void InvertedIndex::searchWord(string wordToSearch)
{
	for(int ind = 0; ind <= wordToSearch.size(); ind++)
    {
        if(wordToSearch[ind] >= 65 && wordToSearch[ind]<= 90)
        {
            wordToSearch[ind] += 32;    
        }                   
    }
	
	for(auto elem : getOccurenceInFile())
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

void InvertedIndex::streamAllIndex(void)
{
    ofstream fileToSerialize(nameOfIndexTxt);
    //
    for(auto elem : getOccurenceInFile())
    {
        sort(elem.second.begin(), elem.second.end(), comp);
        //std::cout << elem.first << "\n";
        
        fileToSerialize << elem.first <<endl;
        for(auto it : elem.second)
        {
            fileToSerialize <<it.first <<" " <<it.second <<endl;
            //cout <<it.first <<" " <<it.second <<"\n";
        }
        fileToSerialize <<endl ;
    }
}

void InvertedIndex::retrieveWord(string path, string word)
{
    string currentPath =  string(fs::current_path().u8string()) + slashForPath + nameOfIndexTxt;
    
	
    ifstream a(currentPath);
    string line;
    string line1;
    
    for(int ind = 0; ind <= word.size(); ind++)
    {
        if(word[ind] >= 65 && word[ind]<= 90)
        {
            word[ind] += 32;    
        }                   
    }
    for(unsigned int curLine = 1; getline(a, line); ++curLine)
     {    
        if (line.find(word) != string::npos) {
            if(!line.compare(word))
            {
                while(getline(a, line1, '\n'))
                {
                    cout <<line1 <<endl;
                    if(line1.size() == 0)
                    {
                        break;
                    }
                }                
            }
        }
    }
}

void commandLineUtility(InvertedIndex obj, int argc, char* argv[])
{
    //cout <<argc <<endl;
    //cout <<argv[1] <<" " <<argv[2] <<endl;
    static string path;
    cout <<path <<endl;
    
    if(argc > 1)
    {
        if(argv[1] == string("-index"))
        {
            //cout <<"index"<<endl;
            path = argv[2];
            cout <<path <<endl;
            obj.addFile(string(argv[2]));
            obj.indexAllDir();           
            //obj.showFiles();
            obj.streamAllIndex();
        }
        else if(argv[1] == string("-search") )
        {
            std::cout << "Current path is " << fs::current_path() << '\n';
            cout <<path <<endl;
            obj.retrieveWord(path, argv[2]);
        }
        else
        {
            
        }
    }
}
















