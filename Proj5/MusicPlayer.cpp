#include "MusicPlayer.h"
//Name: MusicPlayer - Default Constructor
//Precondition: None
//Postcondition: Creates a new MusicPlayer
MusicPlayer::MusicPlayer() {
}
 //Name: MusicPlayer - Overloaded Constructor
//Precondition: None
//Postcondition: Creates a new MusicPlayer and passes the music filename
MusicPlayer::MusicPlayer(string filename) {
  LoadCatalog(filename);
}
//Name: ~MusicPlayer - Destructor
//Precondition: None
//Postcondition: Creates a new MusicPlayer
MusicPlayer::~MusicPlayer() {
  while(!m_songCatalog.empty()){
    delete m_songCatalog.back();
    m_songCatalog.pop_back();
  }
}
//Name: LoadCatalog(string filename)
//Precondition: Requires filename
//Postcondition:
void MusicPlayer::LoadCatalog(string filename) {
  fstream inputStream;
  string title;
  string artist;
  int year;
  int rank;
  string yearTemp;
  string rankTemp;
  Song *song;

  inputStream.open(filename.c_str());

  while(inputStream.good()) {
    getline(inputStream, rankTemp, ',');
    getline(inputStream, title, ',');
    getline(inputStream, artist, ',');
    getline(inputStream, yearTemp, '\n');

    if(inputStream.peek() == '\n')
      inputStream.ignore();

    istringstream(yearTemp) >> year;
    istringstream(rankTemp) >> rank;

    song = new Song(title, artist, year, rank);

    m_songCatalog.push_back(song);
  }
  delete song;
  song = NULL;
}
//Name: MainMenu
//Precondition: None
//Postcondition: Manages the application and the menu
void MusicPlayer::MainMenu() {
  int userInput;
  do { 

    cout << "What would you like to do?" << endl
	 << "1. Display Songs by Year" << endl
	 << "2. Add Song" << endl
	 << "3. Display Playlist" << endl
	 << "4. Quit" << endl;
    cin >> userInput;

    switch(userInput){
    case 1:
      DisplaySongs();
      break;
    case 2:
      AddSong();
      break;
    case 3:
      DisplayPlaylist();
      break;
    case 4:
      break;
    }  
  }while(userInput != 4 || userInput < 1 || userInput > 4);
}
//Name: DisplaySongs
//Precondition: User enters year (1983-2013)
//Postcondition: Lists all songs (numbered) for that year
void MusicPlayer::DisplaySongs() {
  int userInput;
  do{
    cout << "Which year would you like to display? (1983 - 2013)" << endl;
    cin >> userInput;
  }while(userInput < 1983 || userInput > 2013);

  for(int i = 0; i < (int) m_songCatalog.size(); i++){
    if(m_songCatalog.at(i)->getYear() == userInput)
      cout << i + 1 << ". "
	   << m_songCatalog.at(i)->getTitle() << " by "
	   << m_songCatalog.at(i)->getArtist() << endl;
  }
}
//Name: AddSong
//Precondition: m_songCatalog is populated
//Postcondition: Displays the current list and adds a song (by year)
//to the m_playList
void MusicPlayer::AddSong() {
  if(m_playList.isEmpty() == 1)
    cout << "***Current Playlist is Empty***" << endl;
  else
    DisplayPlaylist();

  int yearInput;
  int songInput;

  do{
    cout << "Which year would you like to display? (1983 - 2013)" << endl;
    cin >> yearInput;
  }while(yearInput < 1983 || yearInput > 2013);

  for(int i = 0; i < (int) m_songCatalog.size(); i++){
    if(m_songCatalog.at(i)->getYear() == yearInput)
      cout << i + 1 << ". "
           << m_songCatalog.at(i)->getTitle() << " by "
           << m_songCatalog.at(i)->getArtist() << endl;
  }

  yearInput = (yearInput - 1983) * 100;

   do {
    cout << "Enter the number of the song you would like to add: " << endl;
    cin >> songInput;
   }while(songInput < (yearInput + 1) || songInput > (yearInput + 100));

  m_playList.enqueue(*m_songCatalog.at(songInput - 1));
}
//Name: DisplayPlaylist
//Precondition: None (can be empty)
//Postcondition: Displays the playlist
void MusicPlayer::DisplayPlaylist() {
  for(int i = 0; i < m_playList.size(); i++){
    cout << i + 1 << ". "
	 << m_playList[i].getTitle() << " by "
	 << m_playList[i].getArtist() << " from "
	 << m_playList[i].getYear() << endl;
  }
}
