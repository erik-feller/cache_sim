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
#include "conf_parser.h"
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
	map<string,int> test = parseConfig(argv[1]);


	//check that we are getting input from a pipe
	if(isatty(fileno(stdin))){
		cout << "Please pipe in the trace file. Exiting." << endl;
		return 2;
	}
	else{
		//grab each line from the pipe
		string lineInput;
		while(getline(cin,lineInput)){

			cout << "test" << lineInput << endl;
		}
	}


	return 0;
}
