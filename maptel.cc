#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
extern "C" { 
	#include "maptel.h"
};

#ifndef DNDEBUG
	const bool debug = true;
#else
	const bool debug = false;
#endif
using namespace std;

//a moze tak najbardzij brutalna inicjalizacja strumieni? wpisac ios_base::Init() gdzie tylko sie da?


typedef unordered_map<string, string> dictionary_t;

static vector< dictionary_t > all_dictionaries;
static vector< bool > there_dictionary;
static unsigned long id_new_dictionary = 0;

unsigned long maptel_create(){
	dictionary_t dic;
	all_dictionaries.push_back(dic);
	there_dictionary.push_back(true);
	return id_new_dictionary++;
}

void maptel_delete(unsigned long id){
	there_dictionary[id] = false;
	
	// Nie jest fizycznie usówana :( .
	//~all_dictionaries[id]();
}

void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst){
	string src(tel_src);
	string dst(tel_dst);
	all_dictionaries[id][src] = dst;
}

void maptel_erase(unsigned long id, char const *tel_src){
	string src(tel_src);
	if (all_dictionaries[id].count(src) > 0){
		all_dictionaries[id].erase(src);
	}
}

void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len){
	const string src(tel_src);
	string result = src;
	bool is_cycle = false;
	while(all_dictionaries[id].count(result) > 0  && not is_cycle){
		result= all_dictionaries[id][result];
		if(result.compare(src) == 0){
			// Jest cykl
			is_cycle = true;
		}
	}
	for(size_t i = 0; i < result.size(); i++)
		tel_dst[i] = result[i];
		tel_dst[result.size()] = '\0';
}
