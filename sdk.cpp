#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <map>
#include <algorithm>
using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;
//first class to login into API
class GLSystemSDK {
private:
	http_client client;

public:
	GLSystemSDK() : client(U("https://back.glsystem.net/api/v1/auth/login/")) {}
	std::string access_token;
	//login function that takes username and password as argumanents and returns token
	pplx::task<value> login(const std::string& username, const std::string& password) {
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
	
	

};
//second class to work with calculation
class GLSystemSDK_1 {
private:
	http_client client;

public:
	GLSystemSDK_1() : client(U("https://back.glsystem.net/api/v1/calculation")) {}
	//function that creates new project
	pplx::task<value> create(const std::string token, int project_id = 1, std::map<std::string, value> input_data = {}, std::string status="",
		std::string callback_url="", bool external_api=false) {
		value payload;
		value dictObject;
		for (const auto& pair : input_data) {
			dictObject[utility::conversions::to_string_t(pair.first)] = pair.second;
		}
		payload[U("project_id")] = value::number((project_id));
		payload[U("input_data")] = ((dictObject));
		payload[U("status")] = value::string(utility::conversions::to_string_t(status));
		payload[U("callback_url")] = value::string(utility::conversions::to_string_t(callback_url));
		payload[U("external_api")] = value::boolean((external_api));
		http_request request(methods::POST);
		request.headers().add(U("Authorization: Bearer "),(token));
		
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
	//function that makes calculation
	pplx::task<value> get(const std::string token, bool favorite=false, bool is_history=false, bool is_recalculate=false, std::string ordering="", int page=1,
		int page_size=1, int project_id=0, std::string status="") {
		value payload;
		payload[U("favorite")] = value::boolean((favorite));
		payload[U("is_history")] = value::boolean((is_history));
		payload[U("is_recalculate")] = value::boolean((is_recalculate));
		payload[U("ordering")] = value::string(utility::conversions::to_string_t(ordering));
		payload[U("page")] = value::number((page));
		payload[U("page_size")] = value::number((page_size));
		payload[U("project_id")] = value::number((project_id));
		payload[U("status")] = value::string(utility::conversions::to_string_t(status));
		http_request request(methods::GET);
		request.headers().add(U("Authorization: Bearer "), (token));
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
};
