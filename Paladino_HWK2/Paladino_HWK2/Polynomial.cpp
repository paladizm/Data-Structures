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
#include <cmath>
using namespace std;
#include "Polynomial.h"
#include "HelperFunctions.h"

//###################### Polynomial: Polynomial() ####################/
Polynomial::Polynomial(){	
	numterms = 0;
	//Used the default constructor for the STL list.
	return;
}
//###################### Polynomial: ~Polynomial() ####################/
Polynomial::~Polynomial(){	
	//Used default destruct for the list STL.
	return; 
}
//###################### Polynomial: operator= ####################/
//This overloaded operator = deals with the copying of lists and uses the
//default copy of the stl list
//Pre: Must be equationg two polynomials.
//Post: Sets the value of the left Polynomial list to the right. 
Polynomial*& Polynomial::operator=(const Polynomial *first){
	Polynomial *other = this;
	other->poly = first->poly;
	return(other);
}
//###################### Polynomial: operator+ ####################/
//This overloaded operator + deals with the addition of two
//polynomials.
//Pre: Must be adding two polynomials. It also simplifies the equation.
//Post: Returns the added polynomial.
Polynomial*& Polynomial::operator+(Polynomial &first){
	list<Term>::iterator fcurr;
	list<Term>::iterator ocurr;
	list<Term>::iterator flast;
	list<Term>::iterator olast;	
	list<Term>::iterator scurr;
	list<Term>::iterator slast;	
	Polynomial other = *this, *sum;
	sum = new Polynomial;
	flast = first.poly.end();
	olast = other.poly.end();		
	for(ocurr = other.poly.begin(); ocurr!=olast; ocurr++){
		for(fcurr = first.poly.begin(); fcurr!=flast; fcurr++){
			if(ocurr->expo==fcurr->expo){
				double tempconst = ((ocurr->coeff)+(fcurr->coeff));
				sum->AddPolyToList(tempconst, ocurr->expo);
			}
		}
	}
	slast=sum->poly.end();
	for(ocurr = other.poly.begin(); ocurr!=olast; ocurr++){
		bool inlist = false;
		for(scurr = sum->poly.begin(); scurr!=slast; scurr++){
			if(ocurr->expo == scurr->expo){
				inlist = true;
			}}
			if(!inlist){
				sum->AddPolyToList(ocurr->coeff, ocurr->expo);
				slast = sum->poly.end();
			}		
	}
	slast = sum->poly.end();
	for(fcurr = first.poly.begin(); fcurr!=flast; fcurr++){
		bool inlist = false;
		for(scurr = sum->poly.begin(); scurr!=slast; scurr++){
			if(fcurr->expo == scurr->expo){
				inlist = true;
			}}
			if(!inlist){
				sum->AddPolyToList(fcurr->coeff, fcurr->expo);
				slast = sum->poly.end();
			}		
	}	
	return(sum);
}
//###################### Polynomial: operator* ####################/
//This overloaded operator * deals with the product of two
//polynomials.
//Pre: Must be multiplying two polynomials. It also simplifies the equation.
//Post: Returns the product of the polynomials.
Polynomial*& Polynomial::operator*(Polynomial &first){
	list<Term>::iterator fcurr;
	list<Term>::iterator ocurr;
	list<Term>::iterator flast;
	list<Term>::iterator olast;		
	list<Term>::iterator pcurr;
	list<Term>::iterator plast;
	list<Term>::iterator fincurr;
	list<Term>::iterator finlast;
	Polynomial other = *this, prod, *final;
	final = new Polynomial;
	flast = first.poly.end();
	olast = other.poly.end();
	for(ocurr = other.poly.begin(); ocurr!=olast; ocurr++){
		for(fcurr = first.poly.begin(); fcurr!=flast; fcurr++){
			double tempconst = ((ocurr->coeff)*(fcurr->coeff));
			int tempexp = ((ocurr->expo)+(fcurr->expo));
			prod.AddPolyToList(tempconst, tempexp);
		}
	}
	plast = prod.poly.end();	
	for(pcurr = prod.poly.begin(); pcurr!=plast; pcurr++){		
		Polynomial temp;		
		double fcon = 0;
		int fexpo = 0;
		temp.AddPolyToList(pcurr->coeff, pcurr->expo);
		bool mfound = false;
		finlast = final->poly.end();
		for(fincurr = final->poly.begin(); fincurr!=finlast; fincurr++){
			if(pcurr->expo==fincurr->expo){
				mfound = true;
			}
		}
		if(!mfound){
			list<Term>::iterator it;
			list<Term>::iterator loop;
			it = pcurr;
			it++;
			for(loop = it; loop != plast; loop++){
				if(pcurr->expo == loop->expo){
					temp.AddPolyToList(loop->coeff, loop->expo);
				}
			}
			for(loop = temp.poly.begin(); loop!=temp.poly.end(); loop++){
				double con = loop->coeff;
				int expo = loop->expo;
				fcon += con;
			}
			final->AddPolyToList(fcon, pcurr->expo);			
		}
	}
	return(final);
}
//###################### Polynomial: DefinePoly ####################/
//Reads a line of data from the stream ins and initializes the polynomial.
//Pre: Name of the polynomial has already been read. The remaining line
//     is the number of terms and data for each of the terms.
//Post: Original value of self is lost.
void Polynomial::DefinePoly(istream &ins){
	string line, delim = " ";	
	int exponent, count = 0;
	double frontnum;
	getline(ins,line);
	vector<string> tokens = MakeTokens(line,delim);
	numterms = StringToInt(tokens[0]);
	for (int i=1; i<=(numterms*2); i++){
		int eoro = i%2;
		if (eoro != 0){
			frontnum = StringToDub(tokens[i]);
		}
		else{
			exponent = StringToInt(tokens[i]);
		}
        count++;
		eoro = count%2;
		if(eoro == 0){
			AddPolyToList(frontnum, exponent);
		}
	}	
}
//###################### Polynomial: AddPoly ####################/
//self = First + Second
//Pre: self is different from First, Second.
//Post: First, Second remain unchanged. Original value of self is lost.
void Polynomial::AddPoly(const Polynomial &First, const Polynomial &Second){
	Polynomial temp, temp2;
	temp = First;
	temp2 = Second;
	*this = temp + temp2;
}
//###################### Polynomial: MultiplyPoly ####################/
//self = First * Second
//Pre: self is different from First, Second.
//Post: First, Second remain unchanged. Original value of self is lost.	
void Polynomial::MultiplyPoly(const Polynomial &First, const Polynomial &Second){
	Polynomial temp, temp2;
	temp = First;
	temp2 = Second;
	*this = temp * temp2;
}
//###################### Polynomial: AddPolyToList ####################/
//Take a constant an an exponent and creates a Polynode and inserts it
//in decending order of exponents.
//Pre: The constant must be double and the exponent an int.
//Post: The polynomial will be added to the list. 
void Polynomial::AddPolyToList(double constant, int exponent){
	list<Term>::iterator current;
	list<Term>::iterator last;
	current = poly.begin();
	last = poly.end();
	bool newAddedNode = false;
	if(current == last){
		Term temp;			
		temp.coeff = constant;
		temp.expo = exponent;
		poly.insert(current,temp);
		newAddedNode = true;
	}
	while(current!=last && newAddedNode != true){
		if(exponent > current->expo && newAddedNode != true){
			Term temp;			
			temp.coeff = constant;
			temp.expo = exponent;
			poly.insert(current,temp);
			newAddedNode = true;
		}
		current++;
	}
	if(newAddedNode == false){
		Term temp;			
		temp.coeff = constant;
		temp.expo = exponent;
		poly.push_back(temp);
	}	
}
//###################### Polynomial: EvalPoly ####################/
//Return the value of the polynomial at the given value for variable x.
double Polynomial::EvalPoly(double x){
	double eval = 0;
	list<Term>::iterator current;
	list<Term>::iterator last;
	current = poly.begin();
	last = poly.end();
	while(current!=last){
		double con = current->coeff;
		int expo = current->expo;
		double temp = pow(x,static_cast<double>(expo));
		eval += con * temp;
		current++;
	}
	return(eval);
}
//###################### Polynomial: PrintPoly ####################/
//Output the polynomial to the stream outs.
void Polynomial::PrintPoly(ostream &outs){
	outs.setf(ios::fixed);
    outs.setf(ios::showpoint);
    outs.precision(2);
	list<Term>::iterator current;
	list<Term>::iterator last;
	current = poly.begin();
	last = poly.end();
	string output = "";
	double first;
	int exponent;
	list<Term>::iterator nodepast;
	nodepast = poly.begin();
	if(nodepast != last){
		nodepast++;	
	}
	bool printed = false;
	while(current!=last){	
		printed = true;
		first = current->coeff;
		exponent = current->expo;
		if(current == poly.begin()){
			if(first == 0){
				if(nodepast == poly.end()){
					outs << "0.0";
				}
			}
			else if(first < 0){
				outs << first;
				if(exponent != 0){
					if(exponent == 1){
						outs << "*x";
					}
					else{
				        outs << "*x^";
						outs << exponent;}}}
			else{
			   outs << first;
			   if(exponent != 0){
				   if(exponent == 1){
						outs << "*x";
					}
					else{
				        outs << "*x^";
						outs << exponent;}}}
		}
		else{			
			if(first < 0){
                first = first*-1;
				outs << " - ";
				if (first == 1){					
					if(exponent != 0){
						if(exponent == 1){
						outs << "x";
					}
					else{
				        outs << "x^";
						outs << exponent;};
				}}
				else{
				    outs << first;
                    if(exponent != 0){
						if(exponent == 1){
						outs << "*x";
					}
					else{
				        outs << "*x^";
						outs << exponent;};
			}}}
			else if(first == 0){}
			else{
				if(poly.begin()->coeff != 0){
					outs << " + ";
				}
				outs << first;
                if(exponent != 0){
					if(exponent == 1){
						outs << "*x";
					}
					else{
				        outs << "*x^";
						outs << exponent;}}
			}}
		current++;
		if(nodepast != last){
			nodepast++;
		}
	}
	if(!printed){
		outs << "Polynomial is not defined.";
	}
		outs << endl;
}	
