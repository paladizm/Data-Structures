/**********************************************************
* Author: Zac Paladino
* Date: Oct/08/2008
* Purpose: The Purpose of the program was to make a 
*          functioning Ternary Tree and to do multitude of
*		   operations with these trees.
* Input:  input.txt
* Output: paladino3.txt
* Login-id: cps350-n1.16
**********************************************************/
#include "HelperFunctions.h"
/*********************** Function: MakeTokens ********************/
//This function makes tokens out of the numbers/letters given in the
//input file and places them into a vector for ease of use.
//Pre: The numbers/letters must be the ones that you want to be in
//	   the vector. It takes care of all the whitespace.
//Post: Return the vector with tokens in it.
vector<string> MakeTokens(const string & str, const string & delim){  
  vector<string> tokens;
  size_t p=0, p1 = string::npos;
  while(p != string::npos){
    p1 = str.find_first_of(delim, p);
    if(p1 != p){
      string token = str.substr(p, p1 - p);
      tokens.push_back(token);
    }
    p = str.find_first_not_of(delim, p1);
  }
  return tokens;
}
/*********************** Function: TokenToUpper ********************/
//This function checks to see if the char array has any lowercase
//letters if it does it makes them uppercase.
//Pre: There must be a char array of some kind given to the function.
//Post: Returns the char array as a string and the letters are now uppercase.
string TokenToUpper(char command[]){
   string uppercommand;
   char temp;
   for(int i=0; command[i]; i++){
     if (command[i] >= 'A' && command[i] <= 'Z'){
	    uppercommand += command[i];}
     else{
        temp = toupper(command[i]);
        uppercommand += temp;}
   }
  return uppercommand;
}
/*********************** Function: StringToInt ********************/
//This function makes strings into ints.
//Pre: The string must be an integer before placing in function.
//Post: Returns the int from the conversion of the string.
int StringToInt(string strconvert) {
  int conversion;
  conversion = atoi(strconvert.c_str());
  return(conversion);
}
/*********************** Function: StringToDub ********************/
//This function makes strings into ints.
//Pre: The string must be double before placing in function.
//Post: Returns the double from the conversion of the string.
double StringToDub(string strconvert) {
  double conversion;
  conversion = atoi(strconvert.c_str());
  return(conversion);
}

