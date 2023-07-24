#include "sdk2.h"

pplx::task<value> sdk2::get_by_id(std::wstring &token, int id= 6514)
{
	
	std::string api_url = "https://back.glsystem.net/api/v1/calculation/";
	std::string url = api_url + std::to_string(id) + '/';
	http_client_config config;
	
	http_client client1(utility::conversions::to_string_t(url));
	http_request request(methods::GET);
	
	request.headers().add(U("Authorization"), U("Bearer ")+token);
	//request.headers().add(U("Content-Type"), U("application/json"));
	return client1.request(request)
		.then([](http_response response) {
		if (response.status_code() == 200) {
			std::wcout << "OK" << std::endl;
			return response.extract_json();
		}
		else {
			std::wcout << (response.status_code()) << std::endl;
			throw std::runtime_error("Error: " + std::to_string(response.status_code()));
		}
	});
	
}
