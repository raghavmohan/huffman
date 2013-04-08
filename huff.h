#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <string>
#include <map> 
#include <fstream>
#include <sstream>


//string clean functions
std::string &clean(std::string &s);
std::string &ltrim(std::string &s);
std::string &rtrim(std::string &s);
std::string &trim(std::string &s);
void replace(std::string& pstring);


void usage(bool exitFlag){
	std::cout << "Usage: ./huff -i <inputfile>" << std::endl;
	if(exitFlag)
		exit(1);

}

void getoptions (int argc, char **argv) {
	int c;
	bool usageFlag = true;
	while ((c = getopt (argc, argv, "v?hRs:i:o:h:")) != -1){
		switch (c) {
			case 'h':
				usage(0);
				break;
			case 'i':
				infile = std::string(optarg);
				usageFlag = false;
				break;
			case 'o':
				outfile = std::string(optarg);
				break;
			default:
				break;
		}
	}
	if(usageFlag)
		usage(true);
} 




