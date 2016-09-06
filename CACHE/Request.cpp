#include "Request.h"

//For random generator
random_device rd;     /* Only used once to initialise (seed) engine */
mt19937 rng(rd());    /* Random-number engine used (Mersenne-Twister in this case) */


REQUEST::REQUEST()
{
	_asu = 0;
	_lba = 0;
	_size = 0;
	_opcode = ' ';
	_timestamp = 0;
}

REQUEST::REQUEST(ASU asu, LBA lba, BYTE_SIZE size, OP_CODE opcode, TIMESTAMP timestamp)
{
	_asu = asu;
	_lba = lba;
	_size = size;
	_opcode = opcode;
	_timestamp = timestamp;
}

REQUEST::~REQUEST()
{

}


void REQUEST::TraceFileRequests(vector<REQUEST>& req_list, int count, string trace_file)
{
	string buffer = "";
	int req_counter = 0;
	ifstream infile(trace_file.c_str());
	while ( (req_counter < count) && (getline(infile, buffer)) )
	{
		// Turn string to REQUEST object's collection
		vector<REQUEST> parsed_buffer;
		REQUEST req = REQUEST();
		req.ParseRequest(buffer, parsed_buffer);

		for each (REQUEST request in parsed_buffer)
		{
			req_list.push_back(request);
			req_counter++;
		}
	}
}

void REQUEST::SameRequests(vector<REQUEST>& reqList, int count)
{
	REQUEST rq = REQUEST();
	rq._asu = GetRandomAsu();
	rq._lba = GetRandomLba();
	rq._opcode = GetReadOpCode();
	rq._size = _CELL_SIZE_;
	rq._timestamp = GetCurrentTime();

	for (int i = 0; i < count; i++)
	{
		reqList.push_back(rq);
	}
}

void REQUEST::DifferentRequests(vector<REQUEST>& reqList, int count)
{
	for (int i = 0; i < count; i++)
	{
		REQUEST rq = REQUEST();
		rq._asu = GetRandomAsu();
		rq._lba = GetRandomLba();
		rq._opcode = GetReadOpCode();
		rq._size = _CELL_SIZE_;
		rq._timestamp = GetCurrentTime();

		reqList.push_back(rq);
	}
}

void REQUEST::HalfPartSameRequests(vector<REQUEST>& reqList, int count)
{
	for (int i = 0; i < count / 2; i++)
	{
		REQUEST rq = REQUEST();
		rq._asu = GetRandomAsu();
		rq._lba = GetRandomLba();
		rq._opcode = GetReadOpCode();
		rq._size = _CELL_SIZE_;
		rq._timestamp = GetCurrentTime();

		reqList.push_back(rq);
	}
	for (int i = 0; i < count / 2; i++)
	{
		reqList.push_back(reqList[i]);
	}
}


void REQUEST::ParseRequest(string request_string, vector<REQUEST>& req_list) const
{
	bool result = false;
	
	istringstream origs(request_string.c_str());
	REQUEST req = REQUEST();

	string part;
	result = getline(origs, part, ',') &&
		(istringstream(part) >> req._asu) &&
		getline(origs, part, ',') &&
		(istringstream(part) >> req._lba) &&
		getline(origs, part, ',') &&
		(istringstream(part) >> req._size) &&
		getline(origs, part, ',') &&
		( (part.size() == 1) ? (req._opcode = part.at(0), true) : false) &&
		getline(origs, part, ',') &&
		(istringstream(part) >> req._timestamp);

	if (!result && origs)
	{
		origs.setstate(ios::failbit);
		return;
	}
	
	unsigned int numberOfRequests = req._size / _CELL_SIZE_;
	for (int i = 0; i < numberOfRequests + 1; i++)
	{
		if (req._opcode != 'r')
		{
			return;
		}
		REQUEST rq = REQUEST(req._asu, req._lba + _CELL_SIZE_ * i, _CELL_SIZE_, req._opcode, req._timestamp);
		req_list.push_back(rq);
	}
}

ASU REQUEST::GetRandomAsu()
{
	uniform_int_distribution<int> uni(1, 20); /* Guaranteed unbiased */
	return uni(rng);
}

LBA REQUEST::GetRandomLba()
{
	uniform_int_distribution<int> uni(1000, 1000000); /* Guaranteed unbiased */
	return uni(rng);
}

OP_CODE REQUEST::GetReadOpCode()
{
	return 'r';
}

OP_CODE REQUEST::GetWriteOpCode()
{
	return 'w';
}

TIMESTAMP REQUEST::GetCurrentTime()
{
	return time(NULL);
}