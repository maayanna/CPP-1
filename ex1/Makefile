CC= g++
FLAGS= -c -Wall -Wextra -Wvla -std=c++14 -g
CODEFILES= ex1.tar big_integer.cpp big_integer.h my_set.cpp my_set.h Makefile


all: testint.o big_integer.o testset.o my_set.o
	$(CC) testint.o big_integer.o -o testint
	$(CC) testset.o my_set.o -o testset


testint: testint.o big_integer.o
	$(CC) testint.o big_integer.o -o testint

testset: testset.o my_set.o big_integer.o
	$(CC) testset.o my_set.o big_integer.o -o testset


big_integer.o: big_integer.cpp big_integer.h
	$(CC) $(FLAGS) big_integer.cpp -o big_integer.o

my_set.o: my_set.cpp my_set.h big_integer.h
	$(CC) $(FLAGS) my_set.cpp -o my_set.o

testint.o: big_int_tester.cpp big_integer.h
	$(CC) $(FLAGS) big_int_tester.cpp  -o testint.o

testset.o: my_set_tester.cpp my_set.h
	$(CC) $(FLAGS) my_set_tester.cpp -o testset.o

# create tar
tar:
	tar -cvf $(CODEFILES)

# clean
clean:
	rm -f *.o testint testset