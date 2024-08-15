# will have all, since we are going to add stuff to the makefile to make 1 big program
all: p1 p2 p3 p4

p1: p1.o libsparrow.so
	g++ p1.o -L. -lsparrow -o p1

p2: p2.o libsparrow.so
	g++ p2.o -L. -lsparrow -o p2

p3: p3.o libsparrow.so
	g++ p3.o -L. -lsparrow -o p3

p4: p4.o libsparrow.so
	g++ p4.o -L. -lsparrow -o p4

# p5: p5: p5.o libsparrow.so
# 	g++ p5.o -L. -lsparrow -o p5

p1.o: p1.cpp sparrow.h
	g++ -std=c++20 -Wall -fPIC -c p1.cpp -o p1.o

p2.o: p2.cpp sparrow.h
	g++ -std=c++20 -Wall -fPIC -c p2.cpp -o p2.o

p3.o: p3.cpp sparrow.h
	g++ -std=c++20 -Wall -fPIC -c p3.cpp -o p3.o

p4.o: p4.cpp sparrow.h
	g++ -std=c++20 -Wall -fPIC -c p4.cpp -o p4.o

# p5.o: p5.cpp sparrow.h
# 	g++ -std=c++20 -Wall -fPIC -c p5.cpp -o p5.o

libsparrow.so: sparrow.o
	g++ -std=c++20 -Wall -fPIC -shared sparrow.o -o libsparrow.so

sparrow.o: sparrow.cpp sparrow.h
	g++ -std=c++20 -Wall -fPIC -c sparrow.cpp -o sparrow.o

clean:
	rm -f p1 p1.o p2 p2.o p3 p3.o p4 p4.o libsparrow.so sparrow.o test2_bitcounter test3_overload test4_bit_and test6_struct test7_dropzero test8_average test9_divide test11_ref test12_const test13_parse test14_dblptr test16_constructor test17_cout test18_methods test19_indexing test21_destructor test22_cp_constructor test23_cp_assignment test24_mv_constructor test25_mv_assignment test26_add_col test27_get_col test28_output test29_files test30_division
	rm -rf *.dSYM
