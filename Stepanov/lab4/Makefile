all: test_1 test_2

firstProg: 
	g++ ./Source/main_1.cpp -o lab4_1
	g++ ./Source/main_1_print.cpp -o lab4_1_print

secondProg: 
	g++ ./Source/main_2.cpp -o lab4_2
	g++ ./Source/main_2_print.cpp -o lab4_2_print

test_1: firstProg
	python testScript.py lab4_1 Tests_1 test answer outProg 5

test_2: secondProg
	python testScript.py lab4_2 Tests_2 test answer outProg 6


