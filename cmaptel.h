#ifndef CMAPTEL_H
#define CMAPTEL_H

#include "maptel.h"

namespace jnp1 {
	//czytanki odnosnie namespaceow mnie nie lubia, wiec NIE MAM POJECIA czy to tak sie robi

	//MM: Wydaje mi się że lepiej jest zastosować tak jak w: maptel.cc, wtedy nie musimy pisać
	// kodu który automatycznie może się wygenerować. 
	extern "C" unsigned long maptel_create();

	extern "C" void maptel_delete(unsigned long id);

	extern "C" void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst);

	extern "C" void maptel_erase(unsigned long id, char const *tel_src);

	extern "C" void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len);
}

#endif
