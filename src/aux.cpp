// Copyright PS Computer Services Ltd 2003-2010

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>  // needed for strcmp
#include <algorithm> // needed for std::sort
#include <string>
#include <iostream>

#include "aux.h"

#include "boost/program_options.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/filesystem/convenience.hpp"

// Auxilliary function
int	CharToHex( unsigned char c ){
	// converts hex digit to an int
        int retval = 0;
        switch( c ){
        	case '0' :
                	retval=0;
                        break;
                case '1' :
                	retval=1;
                        break;
        	case '2' :
                	retval=2;
                        break;
                case '3' :
                	retval=3;
                        break;
        	case '4' :
                	retval=4;
                        break;
                case '5' :
                	retval=5;
                        break;
        	case '6' :
                	retval=6;
                        break;
                case '7' :
                	retval=7;
                        break;
        	case '8' :
                	retval=8;
                        break;
                case '9' :
                	retval=9;
                        break;
        	case 'a' :
                	retval=10;
                        break;
                case 'b' :
                	retval=11;
                        break;
        	case 'c' :
                	retval=12;
                        break;
                case 'd' :
                	retval=13;
                        break;
        	case 'e' :
                	retval=14;
                        break;
                case 'f' :
                	retval=15;
                        break;
		}
	return retval;
} 



void getOptions( int argc, char *argv[], bool &verbose, bool &quiet, bool &toStdOut,
            boost::filesystem::path &sourceFile, boost::filesystem::path &destinationFile, bool &allowTags){
    // for our convenience
    namespace po = boost::program_options;         
    // Assumes options are intialised or set to defaults already
    // Declare the supported options.
    po::options_description desc("Allowed options:");

    desc.add_options()
    ("help", "Produces this help message")
    ("source", po::value<std::string>(), "full filepath of RTF file.")
    ("destination", po::value<std::string>(), "Output file for plain text, ignored if toStdOut flag is specified.")
    ("verbose", "Enable verbose output")
    ("toStdOut", "Outputs the plain text to stdout rather than to a destination file.")
    ("quiet", "Suppresses all output, overrides verbose.")
    ("allowTags", "Does not supress output of angle bracketted tags e.g. <notes>")
    ;
    
    std::string overview = "\nOverview\nThis program reads in the source file, which is assumed to be RTF (Rich text Format) document and converts it to plain text, storing it in destination.  Existing destination files will be overwritten.\n\n";
            
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
    }
    catch(po::invalid_command_line_syntax opt){
        std::cerr << "Invalid command line syntax." << std::endl;
        std::cout << overview << desc << std::endl;
        exit(1);
    }    
    catch(po::unknown_option opt){
        std::cerr << "Unknown command line option." << std::endl;        
        std::cout << overview << desc << std::endl;
        exit(1);
    }
    catch(...){
        std::cerr << "Error parsing command line options." << std::endl;
        std::cout << overview << desc << std::endl;
        exit(1);        
    }
    po::notify(vm);      
    
    if(vm.count("help")){
        std::cout << overview << desc << std::endl;
        exit(0);
    }    

    if(vm.count("verbose")){
        verbose=true;
    }
          
    if( vm.count("quiet")){
        quiet = true;
        verbose = false;
    }
 
    if(vm.count("toStdOut")){
        toStdOut = true;
    }
    if(vm.count("allowTags")){
        allowTags = true;
    }
    else {
       allowTags = false;
    }
    // Get sourceFile
    if(vm.count("source")){
        if(verbose){
            std::cout << "Source file is: " << vm["source"].as< std::string >() << std::endl;
        }
        sourceFile = vm["source"].as< std::string >();
    }
    else {
        if(toStdOut==false) {
          std::cerr << "Missing argument:  --source" << std::endl;
          std::cerr << overview << desc << std::endl;
          exit(1);
        }
    }

    try {
        if(vm.count("destination")){
            if(verbose){
                std::cout << "Destination File is: " << vm["destination"].as< std::string >() << std::endl;
            }
            destinationFile = vm["destination"].as< std::string >();
        }
        else {
          if(!toStdOut){
              std::cout << "Missing argument:  --destination" << std::endl;
              std::cout << overview << desc << std::endl;
              exit(1);
              }
        }
    }
    catch(...){
        std::cerr << "Error while checking for options." << std::endl;
    }

  
}
