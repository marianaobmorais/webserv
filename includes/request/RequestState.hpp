#ifndef REQUEST_STATE_HPP
#define REQUEST_STATE_HPP

struct RequestState
{
	enum state
	{
		RequestLine = 0,
		Headers,
		Body,
		Complete
	};
};

#endif //REQUEST_STATE_HPP