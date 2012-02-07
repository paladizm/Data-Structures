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
//This function finds a polynomial in the driver list and returns it.
//Pre: The variable must be in the list otherwise it returns an empty
//	   polynomial.
//Post: Returns a Polynomial.
Polynomial Driver::FindPoly(char variable){
	bool polyfound = false;
	Polynomial empty;
	for (Drivernode *t = header; t !=NULL; t=t->next){
		if(t->var == variable){
			polyfound = true;
			return t->poly;			
		}
	}
	return(empty);
}
//###################### Driver: Driver() ####################/
Driver::Driver(){
	header = end = NULL;
	return;
}
//###################### Driver: ~Driver() ####################/
Driver::~Driver(){
	return;
}
//###################### Driver: AddNode ####################/
//This function adds a node onto the driver list.
//Pre: once a new variable and polynomial data is put in the function
//     checks to see if the var is already in the list if it is the 
//     polynomial gets redefined, if not then it gets added to the list.
//Post: The variable and polynomial are added to the list.
void Driver::AddNode(char variable, Polynomial data){
	Drivernode *temp, *temp2;
	bool varfound = false;
	for (Drivernode *t = header; t !=NULL; t=t->next){
		if(t->var == variable){
			varfound = true;
			t->poly = data;
		}
	}
	if(varfound != true){
       if(header == NULL){
		temp = new Drivernode;
		temp->var = variable;
		temp->poly = data;
		temp->next = NULL;
		header = temp;
		end = temp;
	}
	   else{
		temp2 = end;
		temp = new Drivernode;
		temp->var = variable;
		temp->poly = data;
		temp->next = NULL;
		temp2->next = temp;
		end = temp;
	 }
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

