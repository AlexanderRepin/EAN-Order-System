// Order.h (Assignment 3)
// Alexander Repin
// This is a header file for Order.cpp

#include "EAN.h"

#include <iostream>
#include <istream>

class Order
{

EAN orderedEAN; //- holds the EAN of the order
int noOrdered; //- number of copies ordered
int noDelivered; //- number of copies delivered

public:

 Order();
 Order(const EAN& ean);
 EAN& getEAN();
 int outstanding() const;
 bool add(std::istream& is);
 bool add(int n);
 bool receive(std::istream& is);
 void display(std::ostream& os) const;

};

std::ostream& operator<<(std::ostream& os, const Order& order);