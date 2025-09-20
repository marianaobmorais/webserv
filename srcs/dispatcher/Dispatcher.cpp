#include <dispatcher/Dispatcher.hpp>
#include <dispatcher/Router.hpp>
#include <response/ResponseBuilder.hpp>

void	Dispatcher::dispatch(ClientConnection& client)
{
	HttpRequest& req = client.getRequest();
	HttpResponse& res = client.getResponse();

	Router::resolve(req, res);

	switch (req.getRouteType())
	{
		case RouteType::StaticPage:
			//StaticPageHandler::handle();
			break ;
		case RouteType::CGI:
			//CgiHandler::handle();
			break ;
		case RouteType::Error:
		default:
			//ErrorHandler::handle():
			break ;
	}

	ResponseBuilder::build(req, res);

	client.setResponseBuffer(ResponseBuilder::responseWriter(res));
}
