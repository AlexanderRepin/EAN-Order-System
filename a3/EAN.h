// EAN.h (Assignment 3)
// Alexander Repin
// This is a header file for EAN.cpp

#include <cstdlib>
#include <string>
#include <istream>
#include<cstring>
#include<cstdio>
#include<iostream>
class Prefix;

class EAN 
{
char eanEan[14];  //holds the ISBN digits
char areaEan[6];  //holds the area digits
char publisherEan[8];  //holds the publisher digits
char titleEan[8];  //holds the title digits
char input[2];
char style_[2];
bool registered;

bool isRegistered(const Prefix& list);

public:

EAN();
EAN(const char* str, const Prefix& list);
bool empty() const;
bool isRegistered() const;
void style(char);
void toStr(char* str) const;
void toStrWithStyle(char* str) const;
void display(std::ostream& os) const;
bool read(std::istream& is, const Prefix& list);
/*
const char* getEAN() const{
	char* r=new char[strlen(eanEan)+1];
	strcpy(r,eanEan);
	return r;

}

*/
};

bool operator==(const EAN& left, const EAN& right);
std::ostream& operator<<(std::ostream& os, const EAN& ean);

bool isValid(const char* str);