// Copyright PS Computer Services Ltd 2003-2010

#include <iostream>
#include <string>
#include <fstream>

#include "rtf.h"
#include "aux.h"
#include "ccontrolword.h"


#include "boost/program_options.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/filesystem/convenience.hpp"

namespace fs = boost::filesystem;


int main(int argc, char *argv[]){
    bool verbose = false;
    bool quiet = true;
    bool toStdOut = false;
    bool allowTags = false;
    boost::filesystem::path sourceFile("");
    boost::filesystem::path destinationFile("");
    // Configure valid options and get user's options
    try {
        getOptions( argc, argv, verbose, quiet, toStdOut, sourceFile, destinationFile, allowTags);    	
    }
    catch(...){
        std::cerr << "Error while getting options." << std::endl;
        return 1 ;
    }
    // Open RTF input file
    if( verbose && !toStdOut){
      std::cout << "Opening RTF file: " << sourceFile << std::endl;
    } 
    fs::ifstream is( sourceFile );
    // Output plain text...
    if( toStdOut ){
      convert( is, std::cout, 0, allowTags );
    }
    else {
      if( verbose ){
        std::cout << "Outputting plaintext to file: " << destinationFile.file_string() << std::endl;
      }
      fs::ofstream os(destinationFile);
      convert( is, os, 0, allowTags );
    }

    return 0;                                                                                             
}                                  
