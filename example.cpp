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

int main() {
	sdk sdk;
	sdk2 sdk1;
	std::wstring token;
	sdk.login("ovdanna@mail.ru", "Rjkj,jr02")
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

	sdk1.get_by_id(token, 6514)
		.then([](value json) {

	})
		.wait();

	return 0;
}
