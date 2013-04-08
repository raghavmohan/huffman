#include "huff.h"

using namespace std;
const int UniqueSymbols = 1 << CHAR_BIT;
//const char* SampleString = "this is an example for huffman encoding";
 
typedef std::vector<bool> HuffCode;
//typedef std::map<char, HuffCode> HuffCodeMap;
typedef std::map<string, HuffCode> HuffCodeMap;
 
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
    //const char c;
     string c;

    //LeafNode(int f, char c) : INode(f), c(c) {}
    LeafNode(int f, string c) : INode(f), c(c) {}
};
 
struct NodeCmp
{
    bool operator()(const INode* lhs, const INode* rhs) const { return lhs->f > rhs->f; }
};
 
//INode* BuildTree(const int (&frequencies)[UniqueSymbols])
INode* BuildTree(map<string, int> (&frequencies))
{
    std::priority_queue<INode*, std::vector<INode*>, NodeCmp> trees;
   /*  
    for (int i = 0; i < UniqueSymbols; ++i)
    {
        if(frequencies[i] != 0)
            trees.push(new LeafNode(frequencies[i], (char)i));
    }
    */

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
 
void GenerateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes)
{
    if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
    {
        outCodes[lf->c] = prefix;
    }
    else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
    {
        HuffCode leftPrefix = prefix;
        leftPrefix.push_back(false);
        GenerateCodes(in->left, leftPrefix, outCodes);
 
        HuffCode rightPrefix = prefix;
        rightPrefix.push_back(true);
        GenerateCodes(in->right, rightPrefix, outCodes);
    }
}
 
int main()
{
    // Build frequency table
    //int frequencies[UniqueSymbols] = {0};
    

    //std::string SampleString;
    std::cout << "Please enter a sample string" << std::endl;
    char SampleString[256];
    std::cin.getline(SampleString, 256);

    //const char* ptr = SampleString.c_str();
    const char* ptr = SampleString;
    map<string, int> frequencies;
		std::stringstream stream(SampleString);
		std::string word;
		while( getline(stream, word, ' ') ){
			if(word.length() > 0){
        clean(word);
				if(frequencies.find(word) == frequencies.end())
					frequencies.insert(std::pair< std::string, int>(word, 1));
				else
					frequencies[word]++;	
			}
		}

    
    /*
    while (*ptr != '\0')
        ++frequencies[*ptr++];

    */
 
    INode* root = BuildTree(frequencies);
 
    HuffCodeMap codes;
    GenerateCodes(root, HuffCode(), codes);
    delete root;
 
    for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
    {
        std::cout << it->first << " ";
        std::copy(it->second.begin(), it->second.end(),
                  std::ostream_iterator<bool>(std::cout));
        std::cout << std::endl;
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
