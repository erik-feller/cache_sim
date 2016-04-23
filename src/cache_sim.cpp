//============================================================================
// Name        : cache_sim.cpp
// Author      : Bryan DiLaura & Erik Feller
// Version     :
// Copyright   : GNU
// Description : Main file. Responsible for command line input, and handling config files
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdio.h>
#include <unistd.h>
#include "classes/conf_parser.h"
#include "classes/CacheSystem.h"
using namespace std;

int main(int argc, char** argv) {
	//hello!
	cout << "Bryan DiLaura & Erik Feller" << endl << "Cache Project - Apr. 2016" << endl << endl;

	//make sure that there is a config file
	if (argc != 2){
		cout << "Please specify a config file. Exiting." << endl;
		return 1;
	}

	//get the config values
	map<string,int> conf = parseConfig(argv[1]);

	//create the cache system
	CacheSystem cs = CacheSystem(conf);


//	//check that we are getting input from a pipe
//	if(isatty(fileno(stdin))){
//		cout << "Please pipe in the trace file. Exiting." << endl;
//		return 2;
//	}
//	else{
		//grab each line from the pipe
		char op;
        unsigned long long int address;
        unsigned int bytesize;
        while(scanf("%c %Lx %d\n", &op, &address, &bytesize) == 3){
            //Process here
        	cs.newInstruction(op,address,bytesize);

        }

        cs.reportData();

//        cs.reportState();



//	}


	return 0;
}
