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
	header = end = NULL;
	return;
}
//###################### Polynomial: ~Polynomial() ####################/
Polynomial::~Polynomial(){	
	return; 
}
//###################### Polynomial: operator+ ####################/
//This overloaded operator + deals with the addition of two
//polynomials.
//Pre: Must be adding two polynomials. It also simplifies the equation.
//Post: Returns the added polynomial.
Polynomial& Polynomial::operator+(const Polynomial &first){
	Polynomial other = *this, sum; 
	Polynode *fheader = first.header;
	Polynode *oheader = other.header;
	for(Polynode *t = oheader; t!=NULL; t=t->next){		
		for(Polynode *k = fheader; k!=NULL; k=k->next){			
			if(t->exp==k->exp){
				double tempconst = ((t->constant)+(k->constant));
				sum.AddPolyToList(tempconst, t->exp);				
			}
		}		
	}
	for(Polynode *x = oheader; x != NULL; x=x->next){
		bool inlist = false;
		for(Polynode *c = sum.header; c!=NULL; c=c->next){
			if(x->exp == c->exp){
				inlist = true;
			}
		}
		if(!inlist){
			sum.AddPolyToList(x->constant, x->exp);
		}
	}
	for(Polynode *x = fheader; x != NULL; x=x->next){
		bool inlist = false;
		for(Polynode *c = sum.header; c!=NULL; c=c->next){
			if(x->exp == c->exp){
				inlist = true;
			}
		}
		if(!inlist){
			sum.AddPolyToList(x->constant, x->exp);
		}
	}
	return(sum);
}
//###################### Polynomial: operator* ####################/
//This overloaded operator * deals with the product of two
//polynomials.
//Pre: Must be multiplying two polynomials. It also simplifies the equation.
//Post: Returns the product of the polynomials.
Polynomial& Polynomial::operator*(const Polynomial &first){
	Polynomial other = *this, prod, final; 
	Polynode *fheader = first.header;
	Polynode *oheader = other.header;
	for(Polynode *t = oheader; t!=NULL; t=t->next){
		for(Polynode *k = fheader; k!=NULL; k=k->next){			
			double tempconst = ((t->constant)*(k->constant));
			int tempexp = ((t->exp)+(k->exp));
			prod.AddPolyToList(tempconst, tempexp);			
		}
	}
	for(Polynode *r = prod.header; r!=NULL; r=r->next){
		Polynomial temp;
		double fcon = 0;
		int fexpo = 0;
		temp.AddPolyToList(r->constant, r->exp);
		bool mfound = false;
		for(Polynode *s = final.header; s!=NULL; s=s->next){
			if(r->exp == s->exp){
				mfound = true;
			}
		}
		if(!mfound){
			for(Polynode *a = r->next; a!=NULL; a=a->next){
				if(r->exp == a->exp){
					temp.AddPolyToList(a->constant, a->exp);
			}
		}
			for(Polynode *z = temp.header; z!=NULL; z=z->next){
				double con = z->constant;
				int expo = z->exp;
				fcon += con;			
		}
		final.AddPolyToList(fcon, r->exp);
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
			frontnum = StringToInt(tokens[i]);
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
     Polynode *temp, *temp2, *temp3, *temp4;
	 bool AddedNode = false;
	 if (header == NULL){
        temp = new Polynode;
		temp->constant = constant;
		temp->exp = exponent;
        header = temp;
		end = temp;
		header->next = NULL;
		end->next = NULL;
		AddedNode = true;
	 }
	 else if(header->exp < exponent){
			 temp2 = header;
			 temp = new Polynode;
             temp->constant = constant;
		     temp->exp = exponent;
		     temp->next = temp2;
			 header = temp;
			 if (header->next == NULL){
			    end = header;
			 }
			 AddedNode = true;
		 }
     else{
		 temp3 = header->next;
		 temp4 = header;
		 for(Polynode *s = temp3; s != NULL && AddedNode == false; s = s->next){
			 if (s->exp < exponent){
				 if (s->next == NULL){
                    temp2 = s;
                    temp = new Polynode;
					temp->constant = constant;
					temp->exp = exponent;
					temp->next = s;
					temp4->next = temp;
					end = s;
					AddedNode = true;
					}
				 else{					
				    temp2 = s;
                    temp = new Polynode;
					temp->constant = constant;
					temp->exp = exponent;
					temp->next = s;
					temp4->next = temp;	
					AddedNode = true;
					}
				 }
			 temp4 = temp4->next;
		 }
	 }
     if (AddedNode == false){
		temp2 = end;
		temp = new Polynode;
		temp->constant = constant;
		temp->exp = exponent;
		temp2->next = temp;
		end = temp;
		end->next = NULL;
	    AddedNode = true;
	 }
}
//###################### Polynomial: EvalPoly ####################/
//Return the value of the polynomial at the given value for variable x.
double Polynomial::EvalPoly(double x){
	double eval = 0;
	for(Polynode *s = header; s!=NULL; s=s->next){
		double con = s->constant;
		int expo = s->exp;
		double temp = pow(x,static_cast<double>(expo));
		eval += con * temp;
	}
	return(eval);
}
//###################### Polynomial: PrintPoly ####################/
//Output the polynomial to the stream outs.
void Polynomial::PrintPoly(ostream &outs){
	outs.setf(ios::fixed);
    outs.setf(ios::showpoint);
    outs.precision(2);
	string output = "";
	double first;
	int exponent;
	for(Polynode *t = header; t != NULL; t=t->next){
		first = t->constant;		
		exponent = t->exp;
		if(t == header){
			if(first == 0){
				if(header->next == NULL){
					outs << "0.00";
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
				if(header->constant != 0){
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
	}
	outs << endl;
}

