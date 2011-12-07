// Copyright PS Computer Services Ltd 2003-2010
// Simon Capstick
// Original code 2003/03/17
// Adapted 2010/11/30

#ifndef RTF_H
#define RTF_H

#include <string>
#include <iostream>
#include "boost/program_options.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/filesystem/convenience.hpp"

// These convert a file stream of a Rich Text Format document to plain text or HTML
void	convert( std::istream &is, std::ostream &os, unsigned long maxTextBytes=0, bool allowTags=false);

//void    getOptions( int argc, char *argv[], bool &verbose, bool &quiet, bool &toStdOut,
 //                   boost::filesystem::path &sourceFile, boost::filesystem::path &destinationFile, bool &allowTags);

//int	CharToHex( unsigned char c );


#endif

