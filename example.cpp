#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <map>
#include <algorithm>
using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;

class GLSystemSDK {
private:
	http_client client;

public:
	GLSystemSDK() : client(U("https://back.glsystem.net/api/v1/auth/login/")) {}
	std::string access_token;
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
class GLSystemSDK_1 {
private:
	http_client client;

public:
	GLSystemSDK_1() : client(U("https://back.glsystem.net/api/v1/calculation")) {}
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
int main() {
	GLSystemSDK sdk;
	GLSystemSDK_1 sdk1;
	std::map<std::string, value> mp;
	mp.insert({ "data",42});
	sdk.login("test", "test") //use your own login and password
		.then([](value json) {
		int j = json.serialize().size();
		std::cout << json.serialize().size() <<std:: endl;
		for(int i=0;i<j;++i)
			std::cout << json.serialize()[i];
	})
		.wait();
	//токен 1233497999910111511595116111107101110345834501005348979954100100100985797541005148102491009910097100499751101569752541005710299514852573444349799991011151159511611110710111095101120112105114101115345848443411410110211410111510495116111107101110345834101555010249101994953549749545050525554515098551025157102511004910154525350991025350100483444341141011021141011151049511611110710111095101120112105114101115345848443411611110710111095116121112101345834661019711410111434125	
	sdk1.create("324324343", 1, {}, "new", "no", true)
			.then([](value json) {
			
		})
			.wait();
	sdk1.get("324324343",false,false,false,"fist",1,1,1,"new")
			.then([](value json) {
			
		})
			.wait();

	return 0;
}
