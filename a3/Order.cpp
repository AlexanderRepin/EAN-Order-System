// Order.cpp (Assignment 3)
// Alexander Repin
// This module places an order for a book

#include "Order.h"

#include <cstring>
#include <string>
#include <istream>
#include <iomanip>

 ////////////////////// ORDER ///////////////////////////
 
 //Sets variables to save empty state
Order::Order()
{
 
	noOrdered = 0; 
	noDelivered = 0;
	orderedEAN=EAN();
 
}
 //This recieves reference to current EAN object
 Order::Order(const EAN& ean)
{
/*
	orderedEAN=EAN();
	noOrdered = 0;
	noDelivered = 0;
	*/
	if(ean.empty() == false)
	{
	orderedEAN=ean; 
	noOrdered = 0;
	noDelivered = 0;
	}
	else
	{
		*this = Order();
	}

}
 
 //Returning the ean
 EAN& Order::getEAN()
{
 
 return orderedEAN;
 
}
 //This returns the num of copies remaining
 int Order::outstanding() const
{
 //int remaining=0;
 
 //remaining = noOrdered - noDelivered;
 //std::cout<<"Outstanding is: "<<remaining<<std::endl;
 return noOrdered - noDelivered;
}
 //Increases the amount of orders by the input
 bool Order::add(std::istream& is)
{
 bool add = false;
 int order;

 //While condition checks if the number is less than 0, == 0 or a valid number
 while(!add)
 {
  std::cout << "Quantity(0 - Quit): " << std::endl;

  is >> order;

  if(order < 0)
  {
	std::cout << "Positive Number only, Try Again! " << std::endl;
	add = false;
  }
  else if(order == 0)
  {
	 std::cout << "No order found! " << std::endl;
	 add = false;
  }
  else
  {
	 
	 add = true;
  }
	
 }
 
 return add;
}
 //This function adds the input into the order
 bool Order::add(int n)
{

	if(orderedEAN.empty() == false && n >= 0)
	{
		noOrdered += n;
		return true;
	}
	
	else
		return false;

}
 //This function recieves refernence to to the is and updates current object
 bool Order::receive(std::istream& is)
{
 bool recieved = false;
 int input;

 std::cout << "Quantity (0 - Quit): " << std::endl;
 is >> input;

//While condition checks if the recieved value is 0, == 0 or a valid number
while(!recieved)
{

 
 if(input < 0)
 { 
	std::cout << "Enter a positive number! " << std::endl;
	recieved = false;
 }
 else if(input == 0)
 {
	std::cout << "**No delivery recorded! " << std::endl;
	recieved = false;
 }
 else if(outstanding() < input)
 {
	 //std::cout << input << " is not an order " << outstanding() << " is on the order! " << std::endl;

	 noDelivered+= input;
	recieved = true;
 }
 else
 {
	noDelivered+= input;
	recieved = true;
 }

}

 return recieved;
}
 
 //Displaying the noOrdered and noDelivered
 void Order::display(std::ostream& os) const
{

 orderedEAN.display(os);
 os << std::setw(9) << noOrdered << std::setw(11) << noDelivered << std::endl;
 
}

//This function displays the order object
std::ostream& operator<<(std::ostream& os, const Order& order)
{
 
 order.display(os);
 return os;
 
}
 