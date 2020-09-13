#include "../include/inverted_index.hpp"

#if defined(_WIN32)
   string slashForPath = "\\";
#elif defined(__linux__)
   string slashForPath = "/";
#endif

/* The name of the txt file for storing indexed txt files*/
string nameOfIndexTxt = "indexedFiles.txt";

/* Default constructor without parameter*/
InvertedIndex::InvertedIndex(){}


/* In this function the path to library is given as input parameter.
   addFile function iterates recursively in each folder. If the current
   path is directory, it keeps iterating and if the current path has .txt
   extension, the path of the txt file is inserted into fileList vector 
   which is private member of the class and it is vector of string type. 
*/
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

/* Getter function is created to get the private member fileList 
   of the class. 
*/
vector<string> & InvertedIndex::getFileList(void)
{
	return this->fileList;
}

/* After inserting all the txt files into vector of class named
   fileList, the below function is used for printing this vector.
   It is not used directly by the user however, it is created for 
   using while testing. The input parameter is of type ostream
   which is assigned to std::cout by default. However, when it is 
   tested, the input parameter is stringstream which gives opportunity
   to test the content of vector easily.
*/
int InvertedIndex::showFiles(std::ostream& cout)
{
    if(getFileList().size() == 0)
	{
		return 1;
	}
	
    for(auto it = getFileList().begin(); it != getFileList().end(); it++)
    {
        cout << *it << "\n";
    }
    return 0;
}


/* The below function is used when the private data member occurencesInFile
   is required to reach. This data member is of type map and utilized for
   storing word, path of the txt file which includes this word, and the frequency
   of this word in this path. This map is then used when all the info is serialized
   into another txt file for further accessing.
*/
map<string, wordOccurences> & InvertedIndex::getOccurenceInFile(void)
{
	return occurencesInFile;
}


/* The below function is utilized to parse the word included in txt files 
   which only contains English letters and Ascii-32 space. After parsing 
   the word in the given txt file, it is inserted into map categories.
   This map uses each word as a key and the frequency of this word in given 
   file as a value. Then, the categories map is used for creating occurencesInFile 
   map of class. This map has word as a key then the path name of the txt file and
   the frequency of the word are paired to be used as a value. It returns 0 if file
   is open properly, otherwise 1.
*/   
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


/* The below function is used for parsing and indexing all the txt files existed in
   fileList vector of the class.
*/
void InvertedIndex::indexAllDir(void)
{
    for(auto it : getFileList())
    {
        parseAndIndex(it);
    }
}


/* After parsing whole txt files and the occurencesInFile map is created, the below
   function is utilized to print occurencesInFile to the console. It has ostream cout 
   as an input parameter which is used for testing by giving stringstream to it. It 
   returns 0 if the file is created properly, otherwise 1.
*/

int InvertedIndex::showAllIndex(std::ostream& cout)
{
    if(getOccurenceInFile().size() == 0)
	{
		return 1;
	}
    for(auto elem : getOccurenceInFile())
    {
        cout << elem.first << "\n";
        for(auto it : elem.second)
        {
            cout <<it.first <<" " <<it.second <<"\n";
        }
    }
    return 0;
}


/* When the occurencesInFile map container is inserted into another txt file
   the frequency of the word in the files are sorted in descending order. The
   below function is used by sort function of <algorithm> library. Return 1 if
   the frequency of term1 is greater than term2.
*/
bool comp(const pair<string, int> &a, const pair<string, int> &b)
{
    int term1 = a.second;
    int term2 = b.second;

    return term1>term2;
}


/* searchWord function is used for printing information of wordToSearch 
   by retrieving from occurencesInFile. It has ostream cout as an input.
   This is then used for testing by giving stringstream as an input to it.
   The wordToSearch is converted to lower case before retrieving.
*/
void InvertedIndex::searchWord(string wordToSearch, std::ostream& cout)
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
			//cout << elem.first << "\n"; 
			sort(elem.second.begin(), elem.second.end(), comp);
			for(auto it : elem.second)
            {                  
                cout <<it.first <<" " <<it.second <<"\n";
            }
		}
	}
}


/* After storing words and their information into occurencesInFile, this map
   is inserted into another txt file properly. The frequency of the word 
   in the txt files are sorted before serializing to txt file. The content 
   for each word is as follows:
   wordToSearch
   path-contains-it frequency-in-the-file
   ..
   ..
   ..
   It returns 0 if the file is opened properly. 
*/
int InvertedIndex::streamAllIndex(std::ostream& cout)
{
    ofstream fileToSerialize(nameOfIndexTxt);
    if(fileToSerialize.is_open())
    {
    	for(auto elem : occurencesInFile)
    	{
        	sort(elem.second.begin(), elem.second.end(), comp);
        	cout << elem.first << "\n";
        
        	fileToSerialize << elem.first <<endl;
        	for(auto it : elem.second)
        	{
            	fileToSerialize <<it.first <<" " <<it.second <<endl;
            	cout <<it.first <<" " <<it.second <<"\n";
        	}
        	fileToSerialize <<endl ;
    	}
    }
    else
    {
    	return 1;
    }
    return 0;
}

/* The below function is used for accessing information from txt file which 
   has information of whole words in terms of path and frequency. The queried 
   word is retreived from the currentPath. Current path is obtained by using 
   current_path member of the filesystem library and then the slashForPath is 
   added which is determined according to underlying operating system. Then
   nameOfIndexTxt is added which is named as indexedFiles.txt. The word is 
   converted to lowercase before accessing. When the word is found all the 
   info about it, then is printed to console. This is again used in testing by
   giving stringstream to it.
*/
void InvertedIndex::retrieveWord(string path, string word, std::ostream& cout)
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

/* The below function is used for command line utility. It accepts 
   argv as an input parameter for getting the parameter entered by 
   the user on command line. The user must enter following commands:
   
   For indexing the library folder:
   ./main.exe -index path-to-library 
   
   For retrieving the word from indexed folder:
   ./main.exe -search wordToSearch
   
   The function uses argv for getting command and then process command
   accordingly.
*/   
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
			stringstream ss;
            obj.streamAllIndex(ss);
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
















