#include "pch.h"
#include "framework.h"

#include "client.h"
#include "endpoints.h"


cpr::Response Client::GetLanguageByName(std::string name) {
	auto response = cpr::Get(
		cpr::Url{
			EndpointUser + name
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);
	return response;
}

cpr::Response Client::GetLanguageByExtension(std::string extension) {
	auto response = cpr::Get(
		cpr::Url{
			EndpointUser + extension
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);
	return response;
}

