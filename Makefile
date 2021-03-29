##########################################################################################
# * JESSE RANKINS
# * UCO COMPUTER SCIENCE 2021
# * CONCEPTS OF AI - TERM PROJECT
# * MINIMAXOPENING MAKEFILE
##########################################################################################

##########################################################################################
# EXECUTABLE
MiniMaxOpening: GUI.o MoveGen.o StaticEstimation.o main.o
	g++ GUI.o MoveGen.o StaticEstimation.o main.o -o MiniMaxOpening
##########################################################################################
# .o FILES
GUI.o: GUI.h GUI.cpp
	g++ -c -g GUI.cpp 

MoveGen.o: MoveGen.h MoveGen.cpp
	g++ -c -g MoveGen.cpp

StaticEstimation.o: StaticEstimation.h StaticEstimation.cpp
	g++ -c -g StaticEstimation.cpp

main.o: GUI.h MoveGen.h StaticEstimation.h main.cpp
	g++ -c -g main.cpp
##########################################################################################
clean:
	rm *.o MiniMaxOpening
##########################################################################################