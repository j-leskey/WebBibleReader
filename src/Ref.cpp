// Ref class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include <iostream>
#include <string>
using namespace std;

// GetNextToken - general routine for getting next token from a string
// Parameters
//    str - string to search. search is destructive, i.e., token is removed.
//    delimiters - string, a list of characters to use a delimiters between tokens
// Returns: string token (removed from str)

string GetNextToken(string& str, const string& delimiters = " ") {
  // Skip delimiters at beginning                                          
  string::size_type startPos = str.find_first_not_of(delimiters, 0);
  // Find position of delimiter at end of token                                           
  string::size_type endPos = str.find_first_of(delimiters, startPos);

  // Found a token, remove it from string, and return it                       
  string next = str.substr(startPos, endPos - startPos);
  string rest = str.substr(endPos - startPos + 1, string::npos);
  str = rest;
  return(next);
}

// GetBookName - authoritive routine for getting the name of the nth book
// Parameters
//    n - book number
// Returns: string name
string GetBookName(int n) {
  if (n < 1 || n > 66)
    cerr << "Error: no match for Bible book " << n << "." << endl;
  return bookNames[n - 1];
}

// Ref member functions

Ref::Ref() {book = 0; chap = 0; verse = 0;}  	// Default constructor

Ref::Ref(const string s) { // Parse constructor - receives a line "34:5:7 text"
  if (s.length() == 0) {
    book = 0;
    chap = 0;
    verse = 0;
  } else {
    string rtext = s; // make local copy of string to avoid modifying parameter
    // parse the reference - notice, currently there is no error checking!
    // Get book number
    string strbook = GetNextToken(rtext,":");
    book = atoi(strbook.c_str());
    // Get the chapter number
    string strchap = GetNextToken(rtext,":");
    chap = atoi(strchap.c_str());
    // Get the verse number
    string strverse = GetNextToken(rtext," ");
    verse = atoi(strverse.c_str());
  }
}

Ref::Ref(const int b, const int c, const int v) { 	// Construct Ref from three integers
	book = b;
	chap = c;
	verse = v;
}

// Accessors
int Ref::getBook() const {return book;}	 // Access book number
int Ref::getChap() const {return chap;}	 // Access chapter number
int Ref::getVerse() const {return verse;}; // Access verse number

// Comparison functions
bool Ref::operator==(const Ref r) {
  return book == r.getBook() && chap == r.getChap() && verse == r.getVerse();
}
bool Ref::operator<(const Ref r) {
  const bool isBeforeBook = book < r.getBook();
  const bool isBeforeChapter = isBeforeBook ? true : book == r.getBook() && chap < r.getChap();
  const bool isBeforeVerse = isBeforeChapter ? true : book == r.getBook() && chap == r.getChap() && verse < r.getVerse();
  return isBeforeVerse;
}
bool Ref::operator<=(const Ref r) {
  return *this < r || *this == r;
}

void Ref::display() { // Display reference with basic formatting
  cout << GetBookName(book) << " " << chap << ":" << verse;
}

void Ref::displayFlowing() { 	// Display Reference in flowing format
  displayHeader();
  cout << ":";
  displayMarker();
}

void Ref::displayHeader() { // Display book name and chapter name
  cout << "<h2>" << GetBookName(book) << " " << chap << "</h2>";
}

void Ref::displayMarker() { 	// Display verse number
  cout << "<span class=\"verse_number\">" << verse << "</span>";
}
