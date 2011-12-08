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
void	convert( std::istream &is, std::ostream &os, const unsigned long maxTextBytes=0, const bool allowTags=false, const bool verbose=false);



#endif

