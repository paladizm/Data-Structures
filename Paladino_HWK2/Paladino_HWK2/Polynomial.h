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
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <list>

class Polynomial{
private:
	int numterms; //Number of terms.
	struct Term{
		double	coeff; //coefficient of the term
		int		expo; //value of the exponent
	};
	list<Term> poly; //list of the terms in decreasing order of exponent.
	void AddPolyToList(double constant, int exponent);
	//Take a constant an an exponent and creates a Polynode and inserts it
	//in decending order of exponents.
	//Pre: The constant must be double and the exponent an int.
	//Post: The polynomial will be added to the list. 	
	Polynomial*& operator+(Polynomial &first);
	//This overloaded operator + deals with the addition of two
	//polynomials.
	//Pre: Must be adding two polynomials. It also simplifies the equation.
	//Post: Returns the added polynomial.
	Polynomial*& operator*(Polynomial &first);
	//This overloaded operator * deals with the product of two
	//polynomials.
	//Pre: Must be multiplying two polynomials. It also simplifies the equation.
	//Post: Returns the product of the polynomials.
	Polynomial*& operator=(const Polynomial *first);
	//This overloaded operator = deals with the copying of lists and uses the
	//default copy of the stl list
	//Pre: Must be equationg two polynomials.
	//Post: Sets the value of the left Polynomial list to the right. 
public:
	Polynomial(); //Constructor
	~Polynomial(); //Destructor
void DefinePoly(istream &ins);
	//Reads a line of data from the stream ins and initializes the polynomial.
	//Pre: Name of the polynomial has already been read. The remaining line
	//     is the number of terms and data for each of the terms.
	//Post: Original value of self is lost.
void AddPoly(const Polynomial& First, const Polynomial& Second);
	//self = First + Second
	//Pre: self is different from First, Second.
	//Post: First, Second remain unchanged. Original value of self is lost.
void MultiplyPoly(const Polynomial& First, const Polynomial& Second);
	//self = First * Second
	//Pre: self is different from First, Second.
	//Post: First, Second remain unchanged. Original value of self is lost.	
void PrintPoly(ostream &outs);
	//Output the polynomial to the stream outs.
double EvalPoly(double x);
	//Return the value of the polynomial at the given value for variable x.
};
#endif