#pragma once
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <map>
#include <algorithm>
#include <iostream>
using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;
//класс, отвечающий за авторизацию
class sdk
{
private:
	http_client client;

public:
	sdk() : client(U("https://back.glsystem.net/api/v1/auth/login/")) {}
	pplx::task<value> login(const std::string& username, const std::string& password);
};

