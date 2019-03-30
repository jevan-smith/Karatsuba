.SUFFIXES: .o .cpp .x

CFLAGS = -ggdb -std=c++17
objects =  bigInt.o main.o

main.out: $(objects)
	g++ $(CFLAGS) -o main.out $(objects)

.cpp.o:
	g++ $(CFLAGS) -c $< -o $@

bigInt.o: bigInt.cpp bigInt.hpp
main.o: main.cpp bigInt.hpp

clean:
	rm -fr *.o *~ *.x
