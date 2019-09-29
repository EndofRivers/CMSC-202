CXX = g++
CXXFLAGS = -Wall

proj4: Computer.o User.o main.cpp
	$(CXX) $(CXXFLAGS) Player.o Grid.o User.o Computer.o main.cpp -o proj4

Computer.o: Computer.h Computer.cpp Player.o
	$(CXX) $(CXXFLAGS) -c Computer.cpp

User.o: User.h User.cpp Player.o
	$(CXX) $(CXXFLAGS) -c User.cpp

Player.o: Grid.o Player.cpp Player.h
	$(CXX) $(CXXFLAGS) -c Player.cpp

Grid.o: Grid.cpp Grid.h
	$(CXX) $(CXXFLAGS) -c Grid.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj4

run1:
	./proj4 p4_comp1.txt p4_user1.txt

run2:
	./proj4 p4_comp2.txt p4_user2.txt

run3:
	./proj4 p4_comp3.txt p4_user3.txt

run4:
	./proj4 p4_user1.txt p4_comp1.txt

run5:
	./proj4 p4_user2.txt p4_comp2.txt

run6:
	./proj4 p4_user3.txt p4_comp3.txt