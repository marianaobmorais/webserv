#ifndef REQUEST_PARSE_ERROR_HPP
#define REQUEST_PARSE_ERROR_HPP

struct RequestParseError
{
	enum reason
	{
		OK = 0,
		BadRequestLine = 400,
		InvalidMethod = 400,
		UriTooLong = 414,
		InvalidVersion = 400,
		UnsupportedVersion = 505,
		HeaderTooLarge = 431,
		InvalidHeader = 431,
		BodyTooLarge = 413,
		Timeout = 408
	};
};

#endif //REQUEST_PARSE_ERROR_HPP