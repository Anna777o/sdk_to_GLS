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
//класс, отвечающий за получение информации о расчете
class sdk2
{
private:
	
	std::string m_apiUrl;
	std::string m_id;
	std::wstring m_token;

public:
	
	sdk2(const std::string& apiUrl, const std::string& id, const std::wstring& token)
		: m_apiUrl(apiUrl), m_id(id), m_token(token)
	{
	}
	pplx::task<value> get_by_id(std::wstring & token, int id);
};

