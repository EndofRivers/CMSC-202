#include "Song.h"

// Song (Constructor)
// Default Constructor
Song::Song() {}
// Song (Overloaded Constructor)
// Initializes member variables
Song::Song(string title, string artist, int year, int rank ) {
  m_title = title;
  m_artist = artist;
  m_year = year;
  m_rank = rank;
}
// getTitle
// given nothing, returns title of song
string Song::getTitle()const {
  return m_title;
}
// getArtist
// given nothing, returns artist of song
string Song::getArtist()const {
  return m_artist;
}
// getYear
// given nothing, returns year of song
int Song::getYear()const {
  return m_year;
}
// getRank
// given nothing, returns rank of song
int Song::getRank()const {
  return m_rank;
}
// setTitle
// given title of a song, returns nothing
void Song::setTitle(string title) {
  m_title = title;
}
// setArtist
// given artist of a song, returns nothing
void Song::setArtist(string artist) {
  m_artist = artist;
}
// setYear
// given year of a song, returns nothing
void Song::setYear(int year) {
  m_year = year;
}
// setRank
// given rank of a song, returns nothing
void Song::setRank(int rank) {
  m_rank = rank;
}
