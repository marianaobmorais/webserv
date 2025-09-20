#ifndef STATIC_PAGE_HANDLER_HPP
# define STATIC_PAGE_HANDLER_HPP

#include <string>

//webserv
#include <request/HttpRequest.hpp>
#include <response/HttpResponse.hpp>

class StaticPageHandler
{
	private:
		StaticPageHandler();
		~StaticPageHandler();

		static const std::string	detectMimeType(const std::string& resolvedPath);

	public:
		static void	handle(HttpRequest& req, HttpResponse& res);
};

#endif //STATIC_PAGE_HANDLER_HPP
