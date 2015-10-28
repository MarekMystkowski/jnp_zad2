#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <assert.h>
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


typedef unordered_map<string, string>  dictionary_t;

static vector< dictionary_t > all_dictionaries;
static vector< bool > there_dictionary;
static unsigned long id_new_dictionary = 0;
static bool is_valid_phone_number(char const * number);


unsigned long maptel_create(){
	if(debug) ios_base::Init();
	if(debug) cerr << "maptel: maptel_create()" << endl;
	ios_base::Init();
	
	dictionary_t dic = dictionary_t();
	all_dictionaries.push_back(dic);
	there_dictionary.push_back(true);
	
	if(debug) cerr << "maptel: maptel_create: new map id = "
	               << id_new_dictionary << endl;
	return id_new_dictionary++;
}

void maptel_delete(unsigned long id){
	if(debug) ios_base::Init();
	if(debug) cerr << "maptel: maptel_delete(" << id << ")" << endl;
	
	assert(id < id_new_dictionary);
	if(there_dictionary[id]){
		there_dictionary[id] = false;
		all_dictionaries[id].clear();
		if(debug) cerr << "maptel: maptel_delete: map " << id
		               << " deleted" << endl;
	}
	else if(debug) cerr << "maptel: maptel_delete: map " << id
		                << " removed earlier" << endl;
}

void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst){
	if(debug) ios_base::Init();
	if(debug) cerr << "maptel: maptel_insert(" << id << ", " << tel_src
	               << ", " << tel_dst << ")" << endl;
	assert(is_valid_phone_number(tel_src));
	assert(is_valid_phone_number(tel_dst));
	string src(tel_src);
	string dst(tel_dst);
	
	all_dictionaries[id][src] = dst;
	if(debug) cerr << "maptel: maptel_insert: inserted" << endl;
}

void maptel_erase(unsigned long id, char const *tel_src){
	if(debug) ios_base::Init();
	if(debug) cerr << "maptel: maptel_erase(" << id << ", " << tel_src
	               <<")" << endl;

	assert(is_valid_phone_number(tel_src));
	string src(tel_src);
	
	assert(id < id_new_dictionary && there_dictionary[id]);
	
	if (all_dictionaries[id].count(src) > 0){
		all_dictionaries[id].erase(src);
		if(debug) cerr << "maptel: maptel_erase: erased" << endl;
	}
	else if(debug) cerr << "maptel: maptel_erase: nothing to erase" << endl;
}

void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len){
	if(debug) ios_base::Init();
	if(debug) cerr << "maptel: maptel_transform(" << id << ", " 
	               << tel_src << ", " << &tel_dst << ", " << len << ")" << endl;
	               
	assert(id < id_new_dictionary && there_dictionary[id]);
	assert(is_valid_phone_number(tel_src));
	
	const string src(tel_src);
	string result = src;
	bool is_cycle = false;
	while(all_dictionaries[id].count(result) > 0  && not is_cycle){
		result= all_dictionaries[id][result];
		if(result.compare(src) == 0){
			// Jest cykl.
			is_cycle = true;
		}
	}
	if(debug && is_cycle) cerr << "maptel: maptel_transform:"
	                              " cycle detected" << endl;
	
	assert(result.size() + 1 <= len); // +1 , ze względu na '\0 'na końcu.
	
	for(size_t i = 0; i < result.size(); i++)
		tel_dst[i] = result[i];
		tel_dst[result.size()] = '\0';
	if(debug) cerr << "maptel: maptel_transform: " << src << " -> "
	               << result << "," << endl;
}

// Tą funkcje też trzeba w pełni debugować ? 
// czy wystarczy dlaczego zwróciła 'false' ?
static bool is_valid_phone_number(char const * number){
	size_t len = 0;
	while(number[len] != '\0' && len <= TEL_NUM_MAX_LEN) len++;
	
	if(len == 0){
		if(debug) cerr << "maptel: is_valid_phone_numbe: empty number" << endl;
		return false;
	}
	
	if(len >  TEL_NUM_MAX_LEN){
		if(debug) cerr << "maptel: is_valid_phone_numbe: number too longr" << endl;
		return false;
	}
	
	for(size_t i = 0; i < len; i++){
		if(number[i] < '0' && number[i] > '9'){
			cerr << "maptel: is_valid_phone_numbe: " << number[i]
			     << "  is not a digit" << endl;
			return false;
		} 	
	}
	return true;
}
