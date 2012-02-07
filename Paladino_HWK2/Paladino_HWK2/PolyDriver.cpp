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
#include "PolyDriver.h"
//###################### Driver: FindPoly ####################/
//This function finds a polynomial in the driver vector and returns it.
//Pre: The variable must be in the vector otherwise it returns an empty
//	   polynomial.
//Post: Returns a Polynomial.
Polynomial Driver::FindPoly(char variable){
	Polynomial temp;
	bool letterfound = false;
	int placement = 0;
	for(int i=0; i<static_cast<int>(Letters.size()) && letterfound != true; i++){
		if(Letters[i] == variable){
			letterfound = true;
		}
		else{
			placement++;
		}
	}
	if (letterfound){
		temp = PolyList[placement];
		return(temp);
	}
	Polynomial empty;	
	return(empty);
}
//###################### Driver: Driver() ####################/
Driver::Driver(){
	PolyList.reserve(26); //Sets the total number of allowed polynomials to 26
	Letters.reserve(26); //Sets the total number of allowed letters to 26	
	return;
}
//###################### Driver: ~Driver() ####################/
Driver::~Driver(){
	return;
}
//###################### Driver: AddNode ####################/
//This function adds a node onto the driver list.
//Pre: once a new variable and polynomial data is put in the function
//     checks to see if the var is already in the vector if it is the 
//     polynomial gets redefined, if not then it gets added to the vector.
//Post: The variable and polynomial are added to the vector.
void Driver::AddNode(char variable, Polynomial data){
	bool letterfound = false;
	int placement = 0;
	for(int i=0; i<static_cast<int>(Letters.size()) && letterfound != true; i++){
		if(Letters[i] == variable){
			letterfound = true;
		}
		else{
			placement++;
		}
	}
	if(letterfound){
		PolyList[placement] = data;
	}
	else{
		Letters.push_back(variable);
		PolyList.push_back(data);
	}
}
//###################### Driver: OperationHandle ####################/
//This function deals with the file input and output.
//Pre: This function takes care of the input from the file and
//     seperates (!@*+) into there specific jobs. The output is
//     also taken care of here.
//Post: The input file is read and the output file is complete.
void Driver::OperationHandle(ifstream &myfile, ofstream &out){
	string line, parsedcommand;	
	while (!myfile.eof()){
	  char cmd[30];
	  myfile >> cmd;       
      parsedcommand = TokenToUpper(cmd);
      if(isalpha(parsedcommand[0])){
		  Polynomial define;
	      define.DefinePoly(myfile);
		  out << "Polynomial " << parsedcommand[0] << " Defined" << endl;		  
		  AddNode(parsedcommand[0], define);
		  out << endl;
	  }
	  if(parsedcommand[0] == '!'){
		  Polynomial print;
		  print = FindPoly(parsedcommand[1]);
		  out << "Printing " << parsedcommand[1] << ":" << endl;
		  out << parsedcommand[1] << " = ";
		  print.PrintPoly(out);
		  out << endl;
	  }
	  if(parsedcommand[0] == '+'){
		  string parsedcommand1, parsedcommand2;
		  Polynomial newvar, oldvar1, oldvar2;
		  myfile >> cmd;
		  parsedcommand1 = TokenToUpper(cmd);
		  oldvar1 = FindPoly(parsedcommand1[0]);
		  myfile >> cmd;
		  parsedcommand2 = TokenToUpper(cmd);
		  oldvar2 = FindPoly(parsedcommand2[0]);
		  newvar.AddPoly(oldvar1,oldvar2);
		  AddNode(parsedcommand[1], newvar);
		  out << "Evaluation of " << parsedcommand1[0] << "+" << parsedcommand2[0] 
		  << " To Make Polynomial " << parsedcommand[1] << endl;
		  out << endl;
	  }
	  if(parsedcommand[0] == '*'){
		  string parsedcommand1, parsedcommand2;
		  Polynomial newvar, oldvar1, oldvar2;
		  myfile >> cmd;
		  parsedcommand1 = TokenToUpper(cmd);
		  oldvar1 = FindPoly(parsedcommand1[0]);
		  myfile >> cmd;
		  parsedcommand2 = TokenToUpper(cmd);
		  oldvar2 = FindPoly(parsedcommand2[0]);
		  newvar.MultiplyPoly(oldvar1,oldvar2);
		  AddNode(parsedcommand[1], newvar);
		  out << "Evaluation of "<< parsedcommand1[0] << "*" << parsedcommand2[0] 
		  << " To Make Polynomial "<< parsedcommand[1] << endl;		  
		  out << endl;
	  }
	  if(parsedcommand[0] == '@'){
		  Polynomial eval;
		  eval = FindPoly(parsedcommand[1]);
		  string num;
		  getline(myfile, num);
		  double mul = atof(num.c_str()), final;
		  final = eval.EvalPoly(mul);
		  out << parsedcommand[1] << "(" << mul << ") = ";
		  out << final << endl;
		  out << endl;
	  }
	}

}

