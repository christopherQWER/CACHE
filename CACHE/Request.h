#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

//Size of standard memory cell
#define _CELL_SIZE_ 512

//Types definition
typedef unsigned int LBA;
typedef unsigned int ASU;
typedef unsigned long long BYTE_SIZE;
typedef char OP_CODE;
typedef double TIMESTAMP;


class REQUEST
{
public:
	ASU _asu;					/* Application specific unit */
	LBA _lba;					/* Logical block address */
	BYTE_SIZE _size;			/* Size of data in bytes */
	OP_CODE _opcode;			/* Read or write request */
	TIMESTAMP _timestamp;		/* Time of start */


	REQUEST();
	REQUEST(ASU asu, LBA lba, BYTE_SIZE size, OP_CODE opcode, TIMESTAMP timestamp);
	~REQUEST();

	
	static void TraceFileRequests(vector<REQUEST>& reqList, int count, string traceFile);
	static void SameRequests(vector<REQUEST>& reqList, int count);
	static void DifferentRequests(vector<REQUEST>& reqList, int count);
	static void HalfPartSameRequests(vector<REQUEST>& reqList, int count);

private:
	void ParseRequest(string traceLog, vector<REQUEST>& reqList) const;
	static ASU GetRandomAsu();
	static LBA GetRandomLba();
	static OP_CODE GetReadOpCode();
	static OP_CODE GetWriteOpCode();
	static TIMESTAMP GetCurrentTime();
};