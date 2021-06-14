#include "pch.h"
#include "framework.h"

#include "client.h"
#include "endpoints.h"


json Client::GetLanguageByName(std::string name) {
	auto response = cpr::Get(
		cpr::Url{
			DataLanguageByName
		},
		cpr::Parameters{
			{
				"name", name
			}
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);
	return json::parse(response.text);
}

json Client::GetLanguageByExtension(std::string extension) {
	auto response = cpr::Get(
		cpr::Url{
			DataLanguageByExt
		},
		cpr::Parameters{
			{
				"extension", extension
			}
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);
	return json::parse(response.text);
}