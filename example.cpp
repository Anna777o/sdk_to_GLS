#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <map>
#include <algorithm>
#include <iostream>
#include "sdk.h"
#include "sdk2.h"
#include <vector>
using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;
//проверка работы авторизации
int main() {
	sdk sdk;
	std::wstring token;
	sdk.login("test", "test")
		.then([&token](value json) {
		std::wstring js= json.serialize();		
		for (int i = 17; i < js.size()-1; ++i)
		{
			if (js[i + 1] != wchar_t(',')) {
				token = token + js[i];
				
			}
			else break;
		}
		std::wcout << token << std::endl;
		
	})
		.wait();

	return 0;
}
