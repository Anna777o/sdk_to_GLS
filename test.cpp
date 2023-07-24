#include "sdk.h"
#include "sdk2.h"
#include <vector>
using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;
//output error 400
void wrong_login_or_password(std::string log, std::string pas)
{
	sdk sdk;
	std::wstring token;
	sdk.login("test", "test")
		.then([&token](value json) {
		std::wstring js = json.serialize();
		for (int i = 17; i < js.size() - 1; ++i)
		{
			if (js[i + 1] != wchar_t(',')) {
				token = token + js[i];

			}
			else break;
		}
		std::wcout << token << std::endl;

	}).wait();
}
//output error 404 
void wrong_id() {
	sdk sdk;
	std::wstring token;
	sdk.login("ovdanna@mail.ru", "test")
		.then([&token](value json) {
		std::wstring js = json.serialize();
		for (int i = 17; i < js.size() - 1; ++i)
		{
			if (js[i + 1] != wchar_t(',')) {
				token = token + js[i];

			}
			else break;
		}
		std::wcout << token << std::endl;

	}).wait();
	std::string url1 = "https://back.glsystem.net/api/v1/calculation/";
	sdk2 sdk1(url1, "3099", token);
	sdk1.get_by_id(token, 3099)
		.then([](value json) {
		std::wstring js = json.serialize();
		std::wcout << js << std::endl;

	}).wait();

}
