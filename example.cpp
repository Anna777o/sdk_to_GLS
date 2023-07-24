#include "sdk.h"
#include "sdk2.h"
#include <vector>
using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;
//Пример на авторизацию и получение информации о расчете по его id
int main() {
	sdk sdk;
	
	std::wstring token;
	sdk.login("ovdanna@mail.ru", "test")
		.then([&token](value json) {
		std::wstring js= json.serialize();		
		for (int i = 17; i < js.size()-1; ++i)
		{
			if (js[i + 1] != wchar_t(',')) {
				token = token + js[i];
				
			}
			else break;
		}
		//std::wcout << js << std::endl;
		std::wcout << token << std::endl;
		
	}).wait();
	std::string url1 = "https://back.glsystem.net/api/v1/calculation/";
	sdk2 sdk1(url1,"30989",token);
	sdk1.get_by_id(token, 30989)
		.then([](value json) {
		std::wstring js = json.serialize();
		std::wcout << js << std::endl;

	}).wait();
	

	return 0;
}
