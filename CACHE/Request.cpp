#include "Request.h"
using namespace std;

//For random generator
random_device rd;     /* Only used once to initialise (seed) engine */
mt19937 rng(rd());    /* Random-number engine used (Mersenne-Twister in this case) */


Request::Request()
{
	_asu = 0;
	_lba = 0;
	_size = 0;
	_opcode = ' ';
	_timestamp = 0;
}

Request::Request(ASU asu, LBA lba, BYTE_SIZE size, OP_CODE opcode, TIMESTAMP timestamp)
{
	_asu = asu;
	_lba = lba;
	_size = size;
	_opcode = opcode;
	_timestamp = timestamp;
}

Request::~Request()
{

}

void Request::GenerateRequest(Request& rq)
{
	rq._asu = GetRandomAsu();
	rq._lba = GetRandomLba();
	rq._opcode = GetReadOpCode();
	rq._size = _CELL_SIZE_;
	rq._timestamp = GetCurrentTime();
}

void Request::ParseRequest(string request_string, vector<Request>& req_list)
{
	bool result = false;
	
	istringstream origs(request_string.c_str());
	Request req = Request();

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
		Request rq = Request(req._asu, req._lba + _CELL_SIZE_ * i, _CELL_SIZE_, req._opcode, req._timestamp);
		req_list.push_back(rq);
	}
}

ASU Request::GetRandomAsu()
{
	uniform_int_distribution<int> uni(1, 20); /* Guaranteed unbiased */
	return uni(rng);
}

LBA Request::GetRandomLba()
{
	uniform_int_distribution<int> uni(1000, 10000000); /* Guaranteed unbiased */
	return uni(rng);
}

OP_CODE Request::GetReadOpCode()
{
	return 'r';
}

OP_CODE Request::GetWriteOpCode()
{
	return 'w';
}

TIMESTAMP Request::GetCurrentTime()
{
	return time(NULL);
}

void Request::SetRandomAsu(ASU asu)
{
	_asu = asu;
}

void Request::SetRandomLba(LBA lba)
{
	_lba = lba;
}

void Request::SetReadOpCode(OP_CODE opcode)
{
	_opcode = 'r';
}

void Request::SetWriteOpCode(OP_CODE opcode)
{
	_opcode = 'w';
}

void Request::SetCurrentTime()
{
	_timestamp = time(NULL);
}

