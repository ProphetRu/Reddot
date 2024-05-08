#include "RequestHandlerFactoryHTTPS.h"
#include "RequestHandlerHTTPS.h"

namespace Server
{
	HTTPRequestHandler* RequestHandlerFactoryHTTPS::createRequestHandler(const HTTPServerRequest&)
	{
		return new RequestHandlerHTTPS;
	}
}
