/******************************************************************************
 * Name   : Raghav Mohan
 * Email  : rmohan2@wisc.edu
 * UWID   : 9057338981
 * Program: Huffman Codes, P3
 * Date   : 04/08/2013
 *****************************************************************************/
#include "huff.h"
using namespace std;
class INode
{
  public:
    const int f;

    virtual ~INode() {}

  protected:
    INode(int f) : f(f) {}
};

class InternalNode : public INode
{
  public:
    INode *const left;
    INode *const right;

    InternalNode(INode* c0, INode* c1) : INode(c0->f + c1->f), left(c0), right(c1) {}
    ~InternalNode()
    {
      delete left;
      delete right;
    }
};

class LeafNode : public INode
{
  public:
    string c;
    LeafNode(int f, string c) : INode(f), c(c) {}
};

struct NodeCmp
{
  bool operator()(const INode* lhs, const INode* rhs) const { return lhs->f > rhs->f; }
};

INode* BuildTree(map<string, int> (&frequencies))
{
  std::priority_queue<INode*, std::vector<INode*>, NodeCmp> trees;
  std::map<std::string, int>::iterator it1;
  for(it1 = frequencies.begin(); it1 != frequencies.end(); ++it1){
    trees.push(new LeafNode(it1->second, it1->first));
  }
  while (trees.size() > 1)
  {
    INode* childR = trees.top();
    trees.pop();

    INode* childL = trees.top();
    trees.pop();

    INode* parent = new InternalNode(childR, childL);
    trees.push(parent);
  }
  return trees.top();
}

void GenerateCodes(const INode* node, const vector<bool>& prefix, map<string, vector<bool> >& outCodes)
{
  if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
  {
    outCodes[lf->c] = prefix;
  }
  else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
  {
    vector<bool> leftPrefix = prefix;
    leftPrefix.push_back(false);
    GenerateCodes(in->left, leftPrefix, outCodes);

    vector<bool> rightPrefix = prefix;
    rightPrefix.push_back(true);
    GenerateCodes(in->right, rightPrefix, outCodes);
  }
}

int main(int argc, char ** argv)
{
  //get input file, check error etc...
  getoptions(argc, argv);

  //open buildfile
  std::ifstream buildfile;
  buildfile.open(buildfilename.c_str(),std::ios::in);
  if (!buildfile.is_open()){
    std::cout << "Error Opening Build File" << std::endl;
    return 1;
  }

  // Build frequency table from original file
  map<string, int> frequencies;
  map<string, int> frequenciesInput;
  while(!buildfile.eof())
  {
    std::string SampleString;
    getline(buildfile,SampleString); 
    std::stringstream stream(SampleString);
    std::string word;
    while( getline(stream, word, ' ') ){
      if(word.length() > 0){
        clean(word);
        replace(word);
        if(frequencies.find(word) == frequencies.end())
          frequencies.insert(std::pair< std::string, int>(word, 1));
        else{
          frequencies[word]++;	
        }
      }
    }
  }
  vector<string> inputfiles;
  getInputFiles(inlistfilename, inputfiles);

  for(int i = 0; i < (int)inputfiles.size(); ++i){
    addToFrequencies(inputfiles[i], frequencies, frequenciesInput);
  }

   //build huffmann tree from frequency map
  INode* root = BuildTree(frequencies);

  map<string, vector<bool> > codes;
  GenerateCodes(root, vector<bool>(), codes);

  //build huffmann tree from frequency map
  //might need to clear this, first, possible mem leak...
  root = BuildTree(frequencies);

  GenerateCodes(root, vector<bool>(), codes);
  delete root;

  //print huffmann tree stats
  ofstream outfile;
  if(outflag){
    outfile.open(outfilename.c_str());


    for (map<string, int >::const_iterator it = frequenciesInput.begin(); it != frequenciesInput.end(); ++it)
    {
      map<string, vector<bool> >::const_iterator p1 = codes.find(it->first);
      if(p1 != codes.end()){
        std::copy(p1->second.begin(), p1->second.end(),
            std::ostream_iterator<bool>(outfile));
      }
    }
  }

  if(printSummary){
    std::cout << "Word\t\t | Frequency\t | Huffman Code" << std::endl;
    for (int i = 0; i < NUM_COLS ; ++i)
      std::cout << "-";
    std::cout << std::endl;

    for (map<string, int >::const_iterator it = frequenciesInput.begin(); it != frequenciesInput.end(); ++it)
    {
      map<string, vector<bool> >::const_iterator p1 = codes.find(it->first);
      if(p1 != codes.end()){
        if(p1->first.length() >= 8)
          std::cout << p1->first << "\t |";
        else
          std::cout << p1->first << "\t\t |";
        std::cout << frequenciesInput[p1->first] << "\t\t |";
        std::copy(p1->second.begin(), p1->second.end(),std::ostream_iterator<bool>(std::cout));
        std::cout << std::endl;
      }
    }
  }

  return 0;
}


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

std::string &clean(std::string &s) {
  trim(s);
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  return s;
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


void getInputFiles(std::string inlistfilename, vector<string>& inputfiles){
  std::ifstream inlistfile;
  inlistfile.open(inlistfilename.c_str(),std::ios::in);
  if (! inlistfile.is_open()){
    std::cout << "Error Opening Build File" << std::endl;
    return;
  }

  while(!inlistfile.eof())
  {
    std::string SampleString;
    getline(inlistfile,SampleString); 
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

void addToFrequencies(std::string filename, map<string, int> & frequencies, map<string, int> & frequenciesInput){
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
       if(frequenciesInput.find(word) == frequenciesInput.end())
          frequenciesInput.insert(std::pair< std::string, int>(word, 1));
        else{
          frequenciesInput[word]++;	
        }

      }
    }
  }



}

void usage(bool exitFlag){
  std::cout << "Usage: ./huff -b <buildcodefile> -i <List File of Input files> -o <outputfile, optional>" << std::endl;
  std::cout << "Optional:\n\t -o <outputfile>\n\t -s : print summary" << std::endl;
  if(exitFlag)
    exit(1);
}

void getoptions (int argc, char **argv) {
  int c;
  bool usageFlag = true;
  while ((c = getopt (argc, argv, "v?hRs:i:o:h:b:s:")) != -1){
    switch (c) {
      case 'h':
        usage(0);
        break;
      case 'b':
        buildfilename = std::string(optarg);
        usageFlag = false;
        break;
      case 's':
        printSummary = true;
        break;
      case 'i':
        inlistfilename = std::string(optarg);
        usageFlag = false;
        break;
      case 'o':
        outfilename = std::string(optarg);
        outflag = true;
        break;
      default:
        break;
    }
  }
  if(usageFlag)
    usage(true);
} 
