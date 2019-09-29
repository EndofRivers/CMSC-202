CXX = g++
CXXFLAGS = -Wall

proj5: Tqueue.o MusicPlayer.o Song.o driver.cpp
	$(CXX) $(CXXFLAGS) Tqueue.o Song.o MusicPlayer.o driver.cpp -o proj5

Tqueue.o: Tqueue.cpp
	$(CXX) $(CXXFLAGS) -c Tqueue.cpp

MusicPlayer.o: MusicPlayer.cpp MusicPlayer.h
	$(CXX) $(CXXFLAGS) -c MusicPlayer.cpp

Song.o: Song.cpp Song.h
	$(CXX) $(CXXFLAGS) -c Song.cpp

clean:	
	rm *.o*
	rm *~

run:
	./proj5

run1:
	./proj5 p5_music1.txt

valgrind:
	valgrind ./proj5 p5_music1.txt