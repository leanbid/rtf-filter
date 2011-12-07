// Copyright PS Computer Services Ltd 2003-2010
// Simon Capstick
// Original code 2003/03/17
// Adapted 2010/11/30

#ifndef AUX_H
#define AUX_H


#include "boost/program_options.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/filesystem/convenience.hpp"

int	CharToHex( unsigned char c );
void    getOptions( int argc, char *argv[], bool &verbose, bool &quiet, bool &toStdOut,
            boost::filesystem::path &sourceFile, boost::filesystem::path &destinationFile, bool &allowTags);


#endif

