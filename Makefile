all:
	g++ -o main code/main.cpp
	./main < tests/test1.txt && echo "\n\n\n\n\n\n--------------------Test Done----------------------\n\n\n\n"
	./main < tests/test1.txt && echo "\n\n\n\n\n\n--------------------Test Done----------------------\n\n\n\n"
	./main < tests/test1.txt && echo "\n\n\n\n\n\n--------------------Test Done----------------------\n\n\n\n"
	./main < tests/test1.txt && echo "\n\n\n\n\n\n--------------------Test Done----------------------\n\n\n\n"
