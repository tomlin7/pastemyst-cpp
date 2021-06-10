#include "pch.h"
#include "framework.h"

#include "client.h"
#include "endpoints.h"
#include "http.h"

cpr::Response Client::GetUser(std::string username) {
	auto response = cpr::Get(
		cpr::Url{
			EndpointUser + username
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);
	return response;
}

bool Client::UserExists(std::string username) {
	auto response = cpr::Get(
		cpr::Url{
			EndpointUser + username
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);
	return response.status_code == HTTP::ok;
}