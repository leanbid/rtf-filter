// Copyright PS Computer Services Ltd 2003-2010
// Simon Capstick
// Original code 2003/03/17
// Adapted 2010/11/30

#ifndef CCONTROLWORD_H
#define CCONTROLWORD_H

// Used for parsing RTF documents
// Gets text and extracts displayable text
//////////////////////////////////////////////////////////////////////
class CControlWord {
public:
	CControlWord();
	~CControlWord();
std::string		getString();
void			putString(std::string&);
void			putString(const char *);
bool			operator == (const char *);
friend std::ostream &	operator << (std::ostream &, CControlWord &);
friend std::istream &	operator >> (std::istream &, CControlWord &);
private:
std::string	theWord; // RTF Control Word + Parameter data
std::string	theText; // Displayeable Text found
}; 

#endif
