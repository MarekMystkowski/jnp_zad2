maptel_test1 : maptel_test1.o maptel.o
	g++ maptel_test1.o maptel.o -o maptel_test1
	
maptel_test2 : maptel_test2.o maptel.o
	g++ maptel_test2.o maptel.o -o maptel_test2
	
maptel_test_my1 : maptel_test_my1.o maptel.o
	g++ maptel_test_my1.o maptel.o -o maptel_test_my1
	
maptel_test2.o: maptel_test2.cc
	g++ -c -Wall -O2 -std=c++11 maptel_test2.cc -o maptel_test2.o
	
maptel_test_my1.o: maptel_test1.c
	gcc -c -Wall -O2 maptel_test_my1.c -o maptel_test_my1.o


maptel_test1.o: maptel_test1.c
	gcc -c -Wall -O2 maptel_test1.c -o maptel_test1.o

maptel.o: maptel.cc
	g++ -c -Wall -O2 -std=c++11 maptel.cc -o maptel.o

maptel_nd.o: maptel.cc
	g++ -DNDEBUG -c -Wall -O2 -std=c++11 maptel.cc -o maptel_nd.o

maptel_test1_nd : maptel_test1.o maptel_nd.o
	g++ maptel_test1.o maptel_nd.o -o maptel_test1_nd
	
maptel_test2_nd : maptel_test2.o maptel_nd.o
	g++ maptel_test2.o maptel_nd.o -o maptel_test2_nd

clean:
	rm -f maptel.o maptel_test1.o maptel_test2.o maptel_test2 maptel_test1 maptel_test2_nd maptel_test1_nd maptel_nd.o maptel_test_my1 maptel_test_my1.o

