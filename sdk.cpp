#include "sdk.h"

pplx::task<value> sdk::login(const std::string & username, const std::string & password)
{
	value payload;

	payload[U("username")] = value::string(utility::conversions::to_string_t(username));
	payload[U("password")] = value::string(utility::conversions::to_string_t(password));

	http_request request(methods::POST);
	request.headers().add(U("Content-Type"), U("application/json"));
	request.set_body(payload);

	return client.request(request)
		.then([](http_response response) {
		if (response.status_code() == status_codes::OK) {

			return response.extract_json();
		}
		else {
			throw std::runtime_error("Error: " + std::to_string(response.status_code()));
		}
	});
}
