#ifndef REQUEST_METHOD_HPP
#define REQUEST_METHOD_HPP

struct RequestMethod
{
	//RFC 2616 5.1.1
	enum Method
	{
		OPTIONS = 0,
		GET,
		HEAD,
		POST,
		PUT,
		DELETE,
		TRACE,
		CONNECT,
		PATCH,
		INVALID
	};
};

#endif //REQUEST_METHOD_HPP