/**********************************************************
* Author: Zac Paladino
* Date: Sep/02/2008
* Purpose: The Purpose of the program was to make a 
*          functioning polynomial calculator using
*		   ! for print, * for the product, + for the sum
*		   and @ for a value associated with x.
* Input: The program will ask you for a file to get input
*        from.
* Output: The program will ask you for a file to get output
*        from.
* Login-id: cps350-n1.16
**********************************************************/
#ifndef POLYDRIVER_H
#define POLYDRIVER_H
#include <string>
#include <stdlib.h> 
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
using namespace std;
#include "Polynomial.h"
#include "HelperFunctions.h"
class Driver{
private:
	struct Drivernode{ //This is the node for the Driver List
		char var;      //Takes a variable.
		Polynomial poly; // Takes a Polynomial.
		Drivernode *next; // To get to the next node.
	};
	Drivernode *header, *end; //Head of list and End of list.	
	Polynomial FindPoly(char variable);
		//This function finds a polynomial in the driver list and returns it.
		//Pre: The variable must be in the list otherwise it returns an empty
		//	   polynomial.
		//Post: Returns a Polynomial.
public:
    Driver(); //Constructor
	~Driver(); //Destructor	
	void AddNode(char variable, Polynomial data);
		//This function adds a node onto the driver list.
		//Pre: once a new variable and polynomial data is put in the function
		//     checks to see if the var is already in the list if it is the 
		//     polynomial gets redefined, if not then it gets added to the list.
		//Post: The variable and polynomial are added to the list.
	void OperationHandle(ifstream &myfile,ofstream &out);
		//This function deals with the file input and output.
		//Pre: This function takes care of the input from the file and
		//     seperates (!@*+) into there specific jobs. The output is
		//     also taken care of here.
		//Post: The input file is read and the output file is complete.
};
#endif