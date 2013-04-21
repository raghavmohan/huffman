#include <iostream>
#include <queue>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
#include <map> 
#include <fstream>
#include <sstream>
#define NUM_COLS 80


using namespace std;
//string clean functions
void replace(std::string& pstring){
  unsigned int i;
  for(i = 0; i< (pstring).length(); i++){
    (pstring)[i] = tolower((pstring)[i]);

    if(!((pstring).at(i)>= 97 &&  (pstring).at(i) <= 122)){
      (pstring).erase(i, 1);
      i--;
    }
  }
}

std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

std::string &trim(std::string &s) {
  return ltrim(rtrim(s));
}


std::string &clean(std::string &s) {
  trim(s);
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  return s;
}


void getOptions(int argc, char **argv , vector<string>& inputfiles){
  if(argc != 3){
    std::cerr << "Usage: " << argv[0] << " <filename of input files list> <outputfilename>"<< std::endl;
    exit(1);
  }
  std::ifstream buildfile;
  std::string buildfilename(argv[1]);
  buildfile.open(buildfilename.c_str(),std::ios::in);
  if (!buildfile.is_open()){
    std::cout << "Error Opening Build File" << std::endl;
    return;
  }

  while(!buildfile.eof())
  {
    std::string SampleString;
    getline(buildfile,SampleString); 
    std::stringstream stream(SampleString);
    std::string word;
    while( getline(stream, word, ' ') ){
      std::replace( word.begin(), word.end(), '*', '\0');
      if(word.length() > 0){
        inputfiles.push_back(word);
      }
    }
  }
}

void addToFrequencies(std::string filename, map<string, int> & frequencies){
  std::ifstream infile;
  infile.open(filename.c_str(),std::ios::in);
  if (!infile.is_open()){
    std::cout << "Error Opening Build File " << filename << std::endl;
    return;
  }

  // Build frequency table from original file
  while(!infile.eof())
  {
    std::string SampleString;
    getline(infile,SampleString); 
    std::stringstream stream(SampleString);
    std::string word;
    while( getline(stream, word, ' ') ){
      clean(word);
      
      if(word.length() > 0){
        if(frequencies.find(word) == frequencies.end())
          frequencies.insert(std::pair< std::string, int>(word, 1));
        else{
          frequencies[word]++;	
        }
      }
    }
  }



}


int main (int argc, char ** argv){
  vector<string> inputfiles;
  getOptions(argc, argv, inputfiles);

  map<string, int> frequencies;
  for(int i = 0; i < (int)inputfiles.size(); ++i){
    addToFrequencies(inputfiles[i], frequencies);
  }
  ofstream outfile;
  outfile.open(argv[2]);



  for (map<string, int >::const_iterator it = frequencies.begin(); it != frequencies.end(); ++it){
    cout << it->first << endl;
    outfile << it->first << " ";
  }
  return 0;

}
