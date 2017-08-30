// GS1Prefix.cpp (Assignment 3)
// Alexander Repin
// This module gets the prefix from the list of possible EAN values

#include "GS1Prefix.h"
#include <fstream>
#include <cstring>

using namespace std;

 // load copies the prefix table from filename into *filename 
 Prefix::Prefix(const char* filename)
 {
     //bool rc = false;
     if (filename != nullptr) 
	 { 
         std::ifstream file(filename);
		 
         if (file.is_open()) 
		 {
             int no = 0;
             while (file.good()) 
			 {  // version 1.2
                 file >> area[no] >> pubLow[no] >> pubHgh[no]; 
                 if (file.good()) 
				 {
                     pubLen[no] = strlen(pubLow[no]);
                     no++;
                 }
             }
             if (no > 0) 
			 {
                 //rc = true;
                 this->no = no;
             }
         }
     }
     //return rc;
 }
 
 bool Prefix::isRegistered(int a) const
 {
	
	for(int i=0;i<=no;i++)
	{
		if(a == area[i])
		{
			return true;
		}
	}
	return false;
 }

int Prefix::minNoDigits(int a) const
 {
 
	int minDigits = 0;
	bool exit = false;
	for(int i=0;i<=no && !exit;i++)
	{
	
		if(a == area[i])
		{
		
			minDigits = strlen(pubLow[i]);
			exit = true;
		}
		
	}
	return minDigits;
 
 }

 bool Prefix::isRegistered(int a, const char* p) const
 {
	for(int i=0;i<=no;i++)
	{
		//"Returns a negative number if string1 is less than string2, returns zero if the two strings are equal, and returns a positive number is string1 is greater than string2"
		if(a == area[i] && pubLen[i] == strlen(p))
		{
			if(!(strcmp(pubHgh[i],p) < 0 || strcmp(pubLow[i],p) > 0))
			{
				return true;
			}		
			
		}
	}
	return false;
 }
 
 