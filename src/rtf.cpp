// Copyright PS Computer Services Ltd 2003-2010

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>  // needed for strcmp
#include <algorithm> // needed for std::sort
#include <string>
#include <iostream>

#include "rtf.h"
#include "aux.h"
#include "ccontrolword.h"


#include "boost/program_options.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/filesystem/convenience.hpp"


void	convert( std::istream &is, std::ostream &os, const unsigned long maxTextBytes, const bool allowTags, const bool verbose ){
	// maxTextBytes is the max number of output bytes allowed, 0 = infinite
	char	c = 0;
	long	lBraceLevel = 0;
	long	lSkipLevel = 2;  // How deeply nested the document sections are (e.g body. header etc..)
	long	lSkipSections = 1; // How many sections to skip
	bool	bSkipGroup = true;
	unsigned long byteCnt = 0;
	CControlWord cw;
	if( verbose ){
		if( allowTags ){
			std::cout << "Including angle brackets in output.  ";
		}
		else {
			std::cout << "Excluding angle brackets in output.  ";
		}		
    }    	
	// first fetch first byte to check for RTF format
	is.get(c); 
	if( c!='{' ){
		// Not a RTF document!!
                std::cerr << "File is not in RTF format." << std::endl;
                exit( 1 );
	}
	// put the byte back
	is.putback(c);
	// Now start processing the file stream 
	while(	is.eof()==0 && (byteCnt <= maxTextBytes || maxTextBytes==0 )  ){
		is.get(c); // Modded by SMC 20020722
		switch( c ){
		case '\\' :
			{
			is >> cw;
			// output any user text found while parsing control word
			os << cw;
			if( cw == "*" ){
				// must skip rest of group if not already skipping a parent group
				if( bSkipGroup != true){
					bSkipGroup = true;
					lSkipLevel = lBraceLevel;
				}
			}
			//************************************************
			// Workaround for non-compliant RTF documents
			std::string strTmp = cw.getString();
			strTmp = strTmp.substr(0,5);
			if( strTmp == "snext" ){
				// must skip rest of group if not already skipping a parent group
				if( bSkipGroup != true){
					bSkipGroup = true;
					lSkipLevel = lBraceLevel;
				}
			}
			// End of workaround.
			//************************************************
			if( cw == "par" ){
				os << " "; 
				byteCnt++;
			}
			else if( cw == "line" ){
				os << " ";				
				byteCnt++;
			}
			else if( cw == "tab" ){
				os << " ";
				os << " ";
				byteCnt++;
			}
			else if( cw == "page" ){
				os << " ";
				os << " ";
				byteCnt++;
			} 
			else if( cw == "cell" ) {
				// put some spaces between text in cells of table
				os << " ";
				os << " ";
				byteCnt++;
			}
			else if( cw=="pict" || cw=="info"){
				// skip info/bitmap informtion
				if( bSkipGroup == false ){
					bSkipGroup = true;
					lSkipLevel = lBraceLevel;
				}
				// else already skipping group
			}
			else if( cw == "rquote" ){
				os << "'";
			}//else
			cw.putString("");
			break;
			}
		case '{' :
			++lBraceLevel;
			break;
		case '}' :
			--lBraceLevel;
			// Cancel SkipGroup since } signifies end of group
			// out only do this if we are coming out of the group
			// and not coming out of some sub group in the skipped group
			if( lSkipLevel > lBraceLevel) {
				--lSkipSections;
				if( lSkipSections <= 0){
					bSkipGroup = false;
				}
			}
			break;
		case '<' :
			if( allowTags==true ){
				os << "<";
				byteCnt++;
			}
			break;
		case '>' :
			if( allowTags==true ){
				os << ">";
				byteCnt++;
			}
			break;
		default:
			if( bSkipGroup==false ){
				os << c;
				byteCnt++;
			} //if
			break;
		}//switch
	} // while
} //convert









