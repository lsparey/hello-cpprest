#include "hello-cpprest.h"

int main()
{
	auto prefix = U("http://0.0.0.0:8888/");
	auto listener = web::http::experimental::listener::http_listener(prefix);

	listener.support(web::http::methods::GET, [](web::http::http_request request)
	{
		auto json = web::json::value();
		json[U("message")] = web::json::value(U("Hello World"));

		auto response = web::http::http_response(web::http::status_codes::OK);
		response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
		response.headers().add(U("Content-Type"), U("application/json; charset=utf-8"));
		response.set_body(json.serialize());

		request.reply(response);
	});

	try
	{
		listener.open().wait();
	}
	catch (std::exception& e)
	{
		std::cout << "Error opening listener: " << e.what() << std::endl;
		return 1;
	}

	std::cout << "Listening on " << utility::conversions::to_utf8string(listener.uri().to_string()) << std::endl;

	std::mutex mutex;
	std::condition_variable condition;

	std::unique_lock<std::mutex> lock{ mutex };
	condition.wait(lock);

	std::cout << "Stopping listener" << std::endl;

	listener.close().wait();

	return 0;
}
