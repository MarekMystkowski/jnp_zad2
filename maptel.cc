#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
extern "C" { 
	#include "maptel.h"
};
using namespace std;

typedef unordered_map<string, string> dictionary_t;

static vector< dictionary_t > AllDictionaries;
static int idNewDictionary = 0;



