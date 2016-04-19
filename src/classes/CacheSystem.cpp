/*
 * CacheSystem.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: bryan
 */

#include "CacheSystem.h"

CacheSystem::CacheSystem(map<string,int> conf) {
	//initialize the cost variables so the compiler will stop bitching at me...
	this->costL1 = 0;
	this->costL2 = 0;
	this->costMem = 0;
	this->costTotal = 0;

	//initialize tracking stuff to zero
	this->track.execTime = 0;
	this->track.numInst = 0;
	this->track.numReads = 0;
	this->track.numWrites = 0;
	this->track.instCycle = 0;
	this->track.readCycle = 0;
	this->track.writeCycle = 0;

	//make memory
//	struct memConfig memConf;
	this->mem = new Memory();//memConf);

	//make L2
	struct L2TransConfig L2tConf;
	L2tConf.L1BlockSize = conf["L1_block_size"];
	L2tConf.transferTime = conf["L2_transfer_time"];
	L2tConf.busWidth = conf["L2_bus_width"];
	struct config L2conf;
	L2conf.name = "L2";
	L2conf.blockSize = conf["L2_block_size"];
	L2conf.cacheSize = conf["L2_cache_size"];
	L2conf.assoc = conf["L2_assoc"];
	L2conf.hitTime = conf["L2_hit_time"];
	L2conf.missTime = conf["L2_miss_time"];
	this->L2_cache = new L2(this->mem, L2conf, L2tConf);


	//make L1 data
	struct config L1conf;
	L1conf.name = "L1 - data";
	L1conf.blockSize = conf["L1_block_size"];
	L1conf.cacheSize = conf["L1_cache_size"];
	L1conf.assoc = conf["L1_assoc"];
	L1conf.hitTime = conf["L1_hit_time"];
	L1conf.missTime = conf["L1_miss_time"];
	this->L1d_cache = new L1(this->L2_cache, L1conf);

	//make L1 inst
	L1conf.name = "L1 - inst";
	this->L1i_cache = new L1(this->L2_cache, L1conf);

	//calculate the cost of system
	this->calcCost(conf);

}


void CacheSystem::newInstruction(char op, unsigned long long int address, unsigned int numBytes){

	//get the list of address request to L1
	vector<unsigned long long int > addressList = this->getAddrList(address,numBytes);


	switch(op){
	//an instruction
	case 'I':
		this->track.numInst++;
		for(int i=0; i<addressList.size(); ++i){
			this->track.instCycle++;
			this->track.execTime += this->L1i_cache->read(addressList[i]);
		}
		break;

	//data read
	case 'R':
		this->track.numReads++;
		for(int i=0; i<addressList.size(); ++i){
			this->track.readCycle++;
			this->track.execTime += this->L1d_cache->read(addressList[i]);
		}
		break;

	//data write
	case 'W':
		this->track.numWrites++;
		for(int i=0; i<addressList.size(); ++i){
			this->track.writeCycle++;
			this->track.execTime += this->L1d_cache->write(addressList[i]);
		}
		break;

	//something's wrong...
	default:
		cout << "got an invalid op character: " << op << endl;
		return;
	}
}


vector<unsigned long long int> CacheSystem::getAddrList(unsigned long long int address, unsigned int numBytes){
	//returns a list of addresses based on the block offset of the base address
	//and the number of bytes requested
	//This is a little gross...I'm sorry. I tried to comment well.


	//use one of the L1 caches to get the block offset of the address
	unsigned int offset = this->L1d_cache->makeTagIndex(address).blockOffset;

	//typecast numBytes as int so it can go negative
	int bytesRemaining = (int) numBytes;

	//init the return vector and add the base address
	vector<unsigned long long int> addresses;
	addresses.push_back(address);

	//get i pointing to the next largest block of 4
	unsigned int i=0;
	while(i<=offset) i+=4;

	//do the first subtraction...
	bytesRemaining -= 4;

	//get the remaining byte-aligned addresses
	int numBlocks =0;
	int misalignment = i-offset;
	while(bytesRemaining >0){
		//push in the aligned address
		addresses.push_back(address+misalignment+(numBlocks*4));
		//increase the number of blocks
		numBlocks++;
		//subtract the number of bytes remaining
		bytesRemaining -= 4;
	}


	//return the list of addresses
	return addresses;

}


void CacheSystem::calcCost(map<string,int> conf){
	//calculate cost of system
	//L1
	this->costL1 = (conf["L1_cache_size"] / 4096) * 100;
	if (conf["L1_assoc"] != 1){
		this->costL1 += (conf["L1_assoc"] / 2) *100;
	}
	//L2
	this->costL2 = (conf["L2_cache_size"] / 16384) * 50;
	if (conf["L2_assoc"] != 1){
		this->costL2 += (conf["L2_assoc"] / 2) * 50;
	}
	//memory
	int memLatencyCost = 50;
	if (conf["mem_ready"] != 50){
		memLatencyCost += 200*(50/conf["mem_ready"]/2);
	}
	int memBandCost = 25;
	if (conf["mem_chunksize"] != 8){
		memBandCost += 100*((conf["mem_chunksize"]/8)-1);
	}
	this->costMem = memLatencyCost + memBandCost;

	//total cost
	this->costTotal = this->costL1 + this->costL2 + this->costMem;
}


void CacheSystem::reportCost(void) {
	//report the cost of the system
	cout << "L1 cache cost (Icache $" << this->costL1 <<
			") + (Dcache $" << this->costL1 << ") = $" << this->costL1*2 << endl;
	cout << "L2 cache cost = $" << this->costL2;
	cout << "; Memory cost = $" << this->costMem;
	cout << "; Total cost = $" << this->costTotal << endl;

}


CacheSystem::~CacheSystem() {

	//delete all the caches
	delete this->L1i_cache;
	delete this->L1d_cache;
	delete this->L2_cache;
	delete this->mem;
}


void CacheSystem::reportData(){
	//calculate some stuff
	unsigned long long int totalRefs = this->track.numInst + this->track.numReads + this->track.numWrites;
	unsigned long long int dataRefs = this->track.numReads + this->track.numWrites;
	unsigned long long int totalCycles = this->track.instCycle + this->track.readCycle + this->track.writeCycle;

	//report the system configuration

	//report refs and exec times
	cout << "Execute time = " << this->track.execTime << "   Total refs = " << totalRefs << endl;
	cout << "Inst refs = " << this->track.numInst << "   Data refs = " << dataRefs << endl;
	cout << endl;

	//report reference types and percentages
	cout << "Number of reference types:   [Percentage]" << endl;
	cout << "Reads  = " << this->track.numReads << "   [";
	cout << (float) ((this->track.numReads / totalRefs) * 100) << ']' << endl;
	cout << "Writes = " << this->track.numWrites << "   [";
	cout << (float) ((this->track.numWrites / totalRefs) * 100) << ']' << endl;
	cout << "Instr  = " << this->track.numInst << "   [";
	cout << (float) ((this->track.numInst / totalRefs) * 100) << ']' << endl;
	cout << "Total  = " << totalRefs << endl;
	cout << endl;

	//report cycles types and percentages
	cout << "Total cycles for activities:   [Percentage]" << endl;
	cout << "Reads  = " << this->track.readCycle << "   [";
	cout << (float) ((this->track.readCycle / totalCycles) * 100) << ']' << endl;
	cout << "Writes = " << this->track.writeCycle << "   [";
	cout << (float) ((this->track.writeCycle / totalCycles) * 100) << ']' << endl;
	cout << "Instr  = " << this->track.instCycle << "   [";
	cout << (float) ((this->track.instCycle / totalCycles) * 100) << ']' << endl;
	cout << "Total  = " << totalRefs << endl;
	cout << endl;

	//do cpi stuff?
	//TODO: the cpi reporting stuff

	//various memory levels reporting
	this->L1i_cache->getTrackingData();
	this->L1d_cache->getTrackingData();
	this->L2_cache->getTrackingData();

	//cost stuff
	this->reportCost();



}
