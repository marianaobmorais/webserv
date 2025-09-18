#ifndef RESPONSE_STATUS_HPP
#define RESPONSE_STATUS_HPP

struct ResponseStatus
{
	enum code
	{
		Continue = 100,
		SwitchingProtocols = 101,

		// 2xx
		OK = 200,
		Created = 201,
		Accepted = 202,
		NoContent = 204,
		PartialContent = 206,

		// 3xx
		MovedPermanently = 301,
		Found = 302,
		SeeOther = 303,
		NotModified = 304,
		TemporaryRedirect = 307,

		// 4xx
		BadRequest = 400,
		Unauthorized = 401,
		Forbidden = 403,
		NotFound = 404,
		MethodNotAllowed = 405,
		RequestTimeout = 408,
		Conflict = 409,
		Gone = 410,
		PayloadTooLarge = 413,
		UriTooLong = 414,
		UnsupportedMediaType = 415,
		ExpectationFailed = 417,

		// 5xx
		InternalServerError = 500,
		NotImplemented = 501,
		BadGateway = 502,
		ServiceUnavailable = 503,
		GatewayTimeout = 504,
		HttpVersionNotSupported = 505
	};
};

#endif //RESPONSE_STATUS_HPP