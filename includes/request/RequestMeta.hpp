#ifndef REQUEST_META_HPP
#define REQUEST_META_HPP

#include <string>

class RequestMeta
{
	private:
		int			_contentLength;
		bool		_chunked;
		bool		_connectionClose;
		bool		_expectContinue;
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

		//getters
		int			getContentLength(void);
		bool		getChunked(void);
		bool		getConnectionClose(void);
		bool		getExpectContinue(void);
		std::string	getHost(void);
};

#endif //REQUEST_META_HPP