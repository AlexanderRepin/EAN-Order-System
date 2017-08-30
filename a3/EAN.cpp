#define _CRT_SECURE_NO_WARNINGS
// EAN.cpp (Assignment 3)
// Alexander Repin
// This module checks if the EAN number is validated

#include "GS1Prefix.h"
#include "EAN.h"
#include <stdlib.h>
#include <cstring>

using namespace std; 

EAN::EAN()
{
	eanEan[0] = '\0';
	areaEan[0] = '\0';
	publisherEan[0] = '\0';
	titleEan[0] = '\0';
	style_[0] = '\0';
	input[0] = '\0';
	registered = false;
}

EAN::EAN(const char* str, const Prefix& list)
{
	registered = false;
	if(strcmp(str, "")  && isValid(str))
	{
		strcpy(eanEan, str); 
		if(isRegistered(list))
		{
			style_[0] = '-';
			style_[1] = '\0';	
			registered = true;
		}
		else
		{
			style_[0] = '\0';
			registered = false;
		}
	}
	else
	{
		eanEan[0] = '\0';
		areaEan[0] = '\0';
		publisherEan[0] = '\0';
		titleEan[0] = '\0';
		style_[0] = '\0';
		registered = false;
	}
	
}

bool EAN::empty() const
{
	bool empty = false;
	
	if(eanEan[0] == '\0' || areaEan[0] == '\0' || publisherEan[0] == '\0')
	{
		empty = true;
	}
	return empty;
}
bool EAN::isRegistered() const
{
	return registered;
}
void EAN::style(char inputStyle)
{
	if(inputStyle == ' ' || inputStyle == '-')
	{
		style_[0] = inputStyle;
		style_[1] = '\0';
	}
	else
	{
		style_[0] = '\0';
	}
		
}
void EAN::toStr(char* input) const
{
	if(input != nullptr) //strcpy
	{
		strcpy(input, eanEan);
	}
}
void EAN::toStrWithStyle(char* str) const
{
	char tempPrefix[4];
		
	if(registered)
	{
		for(int i=0; i < 3;i++)
		{
			tempPrefix[i] = str[i];
		}
		tempPrefix[3]='\0'; 
		strcpy(str, tempPrefix);
		strcat(str,style_);
		strcat(str, areaEan);
		strcat(str,style_);
		strcat(str,publisherEan);
		strcat(str,style_);
		strcat(str, titleEan);
		strcat(str,style_);
		strcat(str, eanEan + 12);
	}
	else 
	{
		toStr(str);
	}
}
void EAN::display(std::ostream& os) const
{
	os.width(18);

	//if(registered)
	//{
		os << areaEan << style_ << publisherEan << style_ << titleEan;
	//}
 
}
bool EAN::read(std::istream& is, const Prefix& list)
{

 bool enter = false;
 bool continueLoop = true;

 while(continueLoop)
 {
	 cout << "EAN (0 to quit) : ";
	 is >> eanEan;
	 if(strcmp(eanEan, "0") == 0)
	 {
		
		cout << "Invalid check digit. Try again." << endl;
	 }
	/* else if(strcmp(eanEan, "0") != 0)
	 {
		cout << "Invalid check digit. Try again." << endl;
	 }*/
	 else if(strlen(eanEan) != 13)
	 {
		cout << "Too few Characters. Try Again." << endl;
	 }
	 else
		isRegistered(list);
		continueLoop = false;
		enter = true;
 }

 return enter;
}

bool operator==(const EAN& left, const EAN& right)
{


	/*
bool sameEan = false;

if(strcmp(left.getEAN(),right.getEAN())==0 )
{
	sameEan = true;
}

return sameEan;

*/

	char ileft[18], iright[18];
	left.toStr(ileft);
	right.toStr(iright);
	
	if(strcmp(ileft, iright) == 0)
	{
		return true;
	}
	else
		return false;


}

std::ostream& operator<<(std::ostream& os, const EAN& ean)
{

ean.display(os);
return os;

}


 
//This function checks if the EAN number is valid
bool isValid(const char* eanEan) 
{
	bool lengthValid = false;
	bool numberValid = false;
	int modulo = 0;
	bool exit = false;
	
	if (!eanEan){
		return 0;
	}

	if(strlen(eanEan) == 13)
	{
	lengthValid = true;
	
		for(int i = 0;eanEan[i]!='\0' && !exit;i++)
		{
			if(eanEan[i] -'0' >= 0 && eanEan[i] -'0' <= 9) 
			{
				numberValid = true;
			}
			else
			{
				numberValid = false;
				exit = true;
			}
			
		}
	}
	
	//if the number length is valid and the number is validated, it checks if it is a divisible by 10
	if(numberValid == true && lengthValid == true)
	{
		for(int j = 0;j < 12;j+=2)
		{
			modulo += (eanEan[j + 1] * 3) + eanEan[j];
		}
		modulo+= eanEan[12];
		
		if(modulo % 10 == 0)
		{
			return 1;
		}
		else
			return 0;
	}
	
	return 0;
}
  
//This function checks if this EAN Number is registered 
bool EAN::isRegistered(const Prefix& list)
{
	bool prefixReg = false;
	bool areaTrue = false;
	bool pubTrue = false;
	bool exitP = false;
	bool exitA = false;
	
	int areaValue;
	int pubValue;
	char tStringArea[6] = "";
	if(eanEan[0] -'9' == 0 && eanEan[1] -'7' == 0 && (eanEan[2] -'8' == 0 || eanEan[2] -'9' == 0))
	{
		prefixReg = true;
		
		if(prefixReg == true)
		{
			int tArea = 0;
			
			for (int i = 1; i <= 5 && !exitP; i++)
			{
				strncpy(tStringArea, eanEan + 3, i);
				tStringArea[i] = '\0';
				if (list.isRegistered( atoi(tStringArea)))
				{
					areaTrue = true;
					areaValue = atoi(tStringArea);
					strcpy(areaEan, tStringArea);
					exitP = true;
				}
			}
			if (!areaTrue)
				return false;
		
		}
		
		if(areaTrue == true)
		{
			pubValue = atoi(publisherEan);
			char tStringPub[8] = "";
			for (int i = list.minNoDigits(areaValue); i <= 7 && !exitA; i++){
				strncpy(tStringPub, eanEan + 3 + strlen(tStringArea), i);
				tStringPub[i] = '\0';
				if (list.isRegistered(areaValue, tStringPub)){
					strcpy(publisherEan, tStringPub);
					pubTrue = true;
					exitA = true;
				}
			}
			if (!pubTrue){
				return false;
			}
			else{
				strncpy(titleEan, eanEan + 3 + strlen(areaEan) + strlen(publisherEan), 13 - 4 - strlen(areaEan) - strlen(publisherEan));
				titleEan[13 - 4 - strlen(areaEan) - strlen(publisherEan)] = '\0';
				return true;
			}
	
		}
		
	
	}
		return false;	
}

  
  