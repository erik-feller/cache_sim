/*
 * conf_parser.h
 *
 *  Created on: Mar 31, 2016
 *      Author: bryan
 */

#ifndef CONF_PARSER_H_
#define CONF_PARSER_H_

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

/* The following is a list of acceptable config values:
 *
 * L1_block_size
 * L1_cache_size
 * L1_assoc
 * L1_hit_time
 * L1_miss_time
 *
 * L2_block_size
 * L2_cache_size
 * L2_assoc
 * L2_hit_time
 * L2_miss_time
 * L2_transfer_time
 * L2_bus_width
 *
 * mem_sendaddr
 * mem_ready
 * mem_chunktime
 * mem_chunksize
 *
 */

//parses the file to populate the config map
map<string,int> parseConfig(char* file);


#endif /* CONF_PARSER_H_ */
