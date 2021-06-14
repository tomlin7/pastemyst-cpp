#include "pch.h"
#include "framework.h"

#include <iostream>
#include "client.h"
#include "endpoints.h"
#include "http.h"

json Client::GetUser(std::string username) {
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

	return json::parse(response.text);
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

json Client::GetSelfUser() {
	if (!this->IsAuthorized())
		std::cout << "Not Authorized" << std::endl;

	auto response = cpr::Get(
		cpr::Url{
			EndpointSelfUser
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);

	return json::parse(response.text);
}

std::vector<std::string> Client::GetSelfPasteIDs() {
	if (!this->IsAuthorized())
		std::cout << "Not Authorized" << std::endl;

	auto response = cpr::Get(
		cpr::Url{
			EndpointSelfUserPastes
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);

	return json::parse(response.text);
}

std::vector<std::string> Client::GetSelfPasteIDsByAmount(int amount) {
	if (!this->IsAuthorized())
		std::cout << "Not Authorized" << std::endl;

	auto response = cpr::Get(
		cpr::Url{
			EndpointSelfUserPastes
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);
	std::vector<std::string> result = json::parse(response.text);
	result.resize(amount);
	
	return result;
}

std::vector<json> Client::GetSelfPastes() {
	auto pasteIDs = this->GetSelfPasteIDs();
	std::vector<json> pastes;

	for (auto pasteID : pasteIDs) {
		pastes.push_back(this->GetPaste(pasteID));
	}

	return pastes;
}

std::vector<json> Client::GetSelfPastesByAmount(int amount) {
	auto pasteIDs = this->GetSelfPasteIDsByAmount(amount);
	std::vector<json> pastes;

	for (auto pasteID : pasteIDs) {
		pastes.push_back(this->GetPaste(pasteID));
	}
	pastes.resize(amount);

	return pastes;
}
