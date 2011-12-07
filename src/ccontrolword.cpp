// Copyright PS Computer Services Ltd 2003-2010

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>  // needed for strcmp
#include <algorithm> // needed for std::sort
#include <string>
#include <iostream>

#include "ccontrolword.h"
#include "aux.h"


#include "boost/program_options.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/filesystem/convenience.hpp"

// Implementation of the CControlWord class.
////////////////////////////////////////////
CControlWord::CControlWord() {
	theWord = "";
}


CControlWord::~CControlWord() {
}


std::string	CControlWord::getString(){
	return theWord;
}


bool	CControlWord::operator == (const char *cstr){
	if( strcmp( theWord.c_str(), cstr )==0 ){
		return true;
	} //if
	else {
		return false;
	} //else
}


void	CControlWord::putString(std::string &str){
	theWord = str;
}


void	CControlWord::putString(const char *cstr){
	theWord = cstr;
}



std::ostream&	operator << (std::ostream &os, CControlWord &cw){
	// output displayable text (not RTF keywords)
	os << cw.theText;
	return os;
}


std::istream&	operator >> (std::istream &is, CControlWord &cw){
	char c;
	bool inASCIIchar = false;
	bool inFirstChar = true;
	bool finished = false;
	while( finished==false ){
		is.get(c); 
		if( is.eof()!=0 ){
			// end of file reached
			finished=true;
		} //if
		else {
			switch(c) {
			case '\'' :
				// Converts 'xx to ASCII character
				if(inASCIIchar==true){
					// get last 4 bits of character
					int tmp = CharToHex( c );
					tmp = tmp & c;
					cw.theText += (char)tmp;
					inASCIIchar = false;
				}
				else {
					// get first four bits of char
					int tmp = CharToHex( c );
					tmp = c;
					inASCIIchar = true;
				}
				break;
			case '\\' :
				// Start of another control word
				// put character back in stream
				is.putback(c);  
				finished = true;
				break;
			case '{' :
				// end of control word found
				// put character back in stream
				is.putback(c); 
				finished = true;
				break;
			case '}' :
				// end of control word found
				// put character back in stream
				is.putback(c);  
				finished = true;
				break;
			default:
				if( c==' ' ) {
					// space - end of control word (also part of the control word)
					// Ignore character to simplify control word recognition
					finished = true;
				}
				else if (c=='-' || isdigit(c)!=0 ){
					// start of a numeric parameter (part of the control word)
					cw.theWord += c;
				}
				else if( isalnum(c)!=0 ){
					// alphanumeric found, part of control word
					cw.theWord += c;
				}
				else if( c=='*' ){
					// Have found a destination
					cw.theWord +='*';
				}
				else {
					// remaining character must be delimiting control word
					// but is not part of it.
					// Ignore character
					finished = true;
				}	
				break;
			} //switch
		} //else
		inFirstChar = false;
	} //while
	return is;
}

