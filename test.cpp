#include "sdk.h"
#include "sdk2.h"
#include <vector>
using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;

//тестирование calculation если не вводится ничего
int main() {
	GLSystemSDK sdk;
	GLSystemSDK_1 sdk1;

	sdk.login("test", "test")
		.then([](value json) {
		int j = json.serialize().size();
		for (int i = 0; i < j; ++i)
			std::cout << json.serialize()[i];
	})
		.wait();

	sdk1.create("c3a4d4cdf8b8258e7c196fc0019943c7fc63b532")
		.then([](value json) {

	})
		.wait();
	sdk1.get("324324343")
		.then([](value json) {

	})
		.wait();

	return 0;
}
