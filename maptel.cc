#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <assert.h>
#include "maptel.h"


#ifndef NDEBUG
	static const bool debug = true;
#else
	static const bool debug = false;
#endif

using namespace std;

typedef unordered_map< string, string >  dictionary_t;

static bool is_valid_phone_number(char const *number);

static vector< dictionary_t >& all_dictionaries() {
	static vector< dictionary_t > all_dict;
	return all_dict;
}

// Czy slownik o zadanym numerze istnieje.
static vector< bool >& there_dictionary() {
	static vector< bool > there_dict;
	return there_dict;
}

static unsigned long& id_new_dictionary() {
	static unsigned long id_new_dict = 0;
	return id_new_dict;
}



unsigned long maptel_create(){
	if(debug) cerr << "maptel: maptel_create()" << endl;
	
	dictionary_t dic = dictionary_t();
	(all_dictionaries()).push_back(dic);
	(there_dictionary()).push_back(true);
	
	if(debug) cerr << "maptel: maptel_create: new map id = "
	               << id_new_dictionary() << endl;
	return (id_new_dictionary())++;
}

void maptel_delete(unsigned long id){
	if(debug) cerr << "maptel: maptel_delete(" << id << ")" << endl;	
	assert(id < id_new_dictionary());
	
	if((there_dictionary())[id]){
		(there_dictionary())[id] = false;
		(all_dictionaries())[id].clear();
		if(debug) cerr << "maptel: maptel_delete: map " << id
		               << " deleted" << endl;
	}
	else if(debug) cerr << "maptel: maptel_delete: map " << id
		                << " removed earlier" << endl;
}

void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst){
	if(debug) cerr << "maptel: maptel_insert(" << id << ", " << tel_src
	               << ", " << tel_dst << ")" << endl;
	assert(is_valid_phone_number(tel_src));
	assert(is_valid_phone_number(tel_dst));
	
	string src(tel_src);
	string dst(tel_dst);
	
	(all_dictionaries())[id][src] = dst;
	
	if(debug) cerr << "maptel: maptel_insert: inserted" << endl;
}

void maptel_erase(unsigned long id, char const *tel_src){
	if(debug) cerr << "maptel: maptel_erase(" << id << ", " << tel_src
	               <<")" << endl;

	assert(is_valid_phone_number(tel_src));
	assert(id < id_new_dictionary() && (there_dictionary())[id]);
	
	string src(tel_src);
	if((all_dictionaries())[id].count(src) > 0){
		(all_dictionaries())[id].erase(src);
		if(debug) cerr << "maptel: maptel_erase: erased" << endl;
	}
	else if(debug) cerr << "maptel: maptel_erase: nothing to erase" << endl;
}

void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len){
	if(debug) cerr << "maptel: maptel_transform(" << id << ", " 
	               << tel_src << ", " << &tel_dst << ", " << len << ")" << endl;
	               
	assert(id < id_new_dictionary() && (there_dictionary())[id]);
	assert(is_valid_phone_number(tel_src));
	
	string result(tel_src);
	
	// Mapa do sprawdzania czy wierzchołek jest w cyklu.
	unordered_map< string, bool > number_on_path;
	bool is_cycle = false;
	number_on_path[result] = true;
	
	while((all_dictionaries())[id].count(result) > 0  && not is_cycle){
		result= (all_dictionaries())[id][result];
		if(number_on_path.count(result) > 0){
			// Jest cykl.
			is_cycle = true;
			result = string(tel_src);
		}
		number_on_path[result] = true;
	}
	
	if(debug && is_cycle) cerr << "maptel: maptel_transform:"
	                              " cycle detected" << endl;
	assert(result.size() + 1 <= len); // +1, ze wzgledu na '\0' na koncu.
	
	for(size_t i = 0; i < result.size(); i++) tel_dst[i] = result[i];
	tel_dst[result.size()] = '\0';
	
	if(debug) cerr << "maptel: maptel_transform: " << tel_src << " -> "
	               << result << "," << endl;
}

static bool is_valid_phone_number(char const * number){
	size_t len = 0;
	while(number[len] != '\0' && len <= TEL_NUM_MAX_LEN) len++;
	
	if(len == 0 || len > TEL_NUM_MAX_LEN){
		return false;
	}
	
	for(size_t i = 0; i < len; i++){
		if(number[i] < '0' && number[i] > '9'){
			return false;
		}
	}
	return true;
}
