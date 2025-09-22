#ifndef REQUEST_META_HPP
#define REQUEST_META_HPP

#include <string>

class RequestMeta
{
	private:
		int			_contentLength; // -1 if there is no
		bool		_chunked; // transfer encoding
		bool		_connectionClose;
		bool		_expectContinue; //expect 100-continue //before send body
		std::string	_host;

		RequestMeta(const RequestMeta& rhs); //blocked
		RequestMeta& operator=(const RequestMeta& rhs); //blocked
	
	public:
		RequestMeta();
		~RequestMeta();

		//setters
		void	setContentLength(int content_length);
		void	setChunked(bool chunked);
		void	setConnectionClose(bool connection_close);
		void	setExpectContinue(bool expect_continue);
		void	setHost(const std::string& host);
		void	resetMeta(void);

		//getters
		int			getContentLength(void) const;
		bool		isChunked(void) const;
		bool		shouldClose(void) const;
		bool		getExpectContinue(void) const;
		std::string	getHost(void) const;
};

#endif //REQUEST_META_HPP