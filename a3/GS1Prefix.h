// GS1Prefix.h (Assignment 3)
// Alexander Repin
// This is a header file for GS1Prefix.cpp

#include <iostream>

const int MAX = 700;

class Prefix 
{
    int  no;             // number of entries
    int  area[MAX];      // area elements
    char pubLow[MAX][8]; // low end of publisher range
    char pubHgh[MAX][8]; // high end of publisher range
    int  pubLen[MAX];    // no of chars in publisher string
	
	public:
	
	Prefix(const char*);
	bool isRegistered(int a) const;
	int minNoDigits(int a) const;
	bool isRegistered(int a, const char* p) const;

	
};
