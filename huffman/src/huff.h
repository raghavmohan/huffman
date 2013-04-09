/******************************************************************************
 * Name   : Raghav Mohan
 * Email  : rmohan2@wisc.edu
 * UWID   : 9057338981
 * Program: Huffman Codes, P3
 * Date   : 04/08/2013
 *****************************************************************************/
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

//globals for input, output
std::string infile;
std::string outfilename;
bool outflag = false;

//string clean functions
std::string &clean(std::string &s);
std::string &ltrim(std::string &s);
std::string &rtrim(std::string &s);
std::string &trim(std::string &s);
void replace(std::string& pstring);


//input/output, check errors, etc...
void usage(bool exitFlag);
void getoptions (int argc, char **argv);
