/*
 * conf_parser.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: bryan
 */

#include "conf_parser.h"


map<string,int> parseConfig(char* file){

	//init map
	map<string,int> confValues;

	//open the file
	string line;
	ifstream confFile(file);
	if(confFile.is_open()){

		//some local variables I need...
		size_t pos;
		string variable;
		int value;

		//go line-by-line through config file
		while(getline(confFile,line)){
			//check to make sure not a blank or a comment
			if(line[0] != '#' && line.length() != 0){
				//read the variable name and value
				pos = line.find('=');
				variable = line.substr(0,pos);
				value = atoi(line.substr(pos+1).c_str());
//				cout << "(" << variable << ", " << value << ")" << endl;

				//put the value into the map
				confValues[variable] = value;
			}
		}
	}
	else{
		cout << "Unable to open config file for some reason..." << endl;
	}

	return confValues;
}

