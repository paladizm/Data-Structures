/**********************************************************
* Author: Zac Paladino
* Date: Nov/11/2008
* Purpose: The Purpose of the program was to make a 
*          functioning Huffman Tree and to be able to
*		   encode and decode strings.
*
* Input:  input.txt
* Output: paladino5.txt
* Login-id: cps350-n1.16
**********************************************************/
#include <iostream>
#include <fstream>
using namespace std;
#include "Driver.h"

int main(){
	ifstream myfile;
	ofstream out;
	myfile.open("input.txt");
	out.open("paladino5.txt");
	if (myfile.is_open()){
		Driver(myfile,out);
	    myfile.close();		
	}
	else out << "Unable to open file";
	out.close();
	return 0;
}