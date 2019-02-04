CC=g++
CL=g++

test: test.o ../bin/qpu.o
	$(CL) $^ -o $@

test.o: test.cpp
	$(CC) -c $< -o $@

../bin/qpu.o: ../lib/qpu.cpp ../bin
	$(CC) -c $< -o $@

../bin:
	mkdir ../bin

../lib/qpu.cpp: ../lib/qpu.h

test.cpp: ../lib/qpu.h

clean:
	rm -rf ../bin *.o test
