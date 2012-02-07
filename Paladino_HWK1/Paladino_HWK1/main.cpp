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
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Polynomial.h"
#include "HelperFunctions.h"
#include "PolyDriver.h"
int main(){
	string in,outp;
	ifstream myfile;
	ofstream out;
	cout << "Please Enter Input File: "; //Asks for the input file.
	cin >> in;
	cout << "Please Enter Output File: "; //Asks for the output file.
	cin >> outp;
	myfile.open(in.c_str());
	out.open(outp.c_str());
	Driver polydriver; //creates the driver.
	if (myfile.is_open()){
		polydriver.OperationHandle(myfile,out);	//Starts the operation handleing. 
	    myfile.close();
	}
	else cout << "Unable to open file"; 
	return 0;
}
