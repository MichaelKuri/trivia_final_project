#pragma once
#include <string>
#include "RequestResult.h"
#include "RequestInfo.h"

class RequestResult;

class IRequestHandler

{
public:
	virtual bool isRequestRelevant(RequestInfo)=0;
	virtual RequestResult handleRequest(RequestInfo) =0;

private:

};
