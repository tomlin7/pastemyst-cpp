#include "pch.h"
#include "framework.h"

#include "client.h"
#include "endpoints.h"
#include "misc.h"
#include "objects.h"
#include <iostream>

json Client::RawGetUser(std::string username) {
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

User Client::GetUser(std::string username) {
	auto rawUser = this->RawGetUser(username);
	return rawUser;
}

json Client::RawGetSelfUser() {
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

User Client::GetSelfUser() {
	auto rawSelfUser = this->RawGetSelfUser();
	return rawSelfUser;
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

	return response.status_code == (int)HTTP::ok;
}

json Client::RawGetSelfPasteIDs() {
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

std::vector<std::string> Client::GetSelfPasteIDs() {
	return this->RawGetSelfPasteIDs();
}

json Client::RawGetSelfPasteIDsByAmount(int amount) {
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

std::vector<std::string> Client::GetSelfPasteIDsByAmount(int amount) {
	return this->RawGetSelfPasteIDsByAmount(amount);
}

json Client::RawGetSelfPastes() {
	auto pasteIDs = this->GetSelfPasteIDs();
	std::vector<json> pastes;

	for (auto pasteID : pasteIDs) {
		pastes.push_back(this->RawGetPaste(pasteID));
	}

	return pastes;
}

std::vector<Paste> Client::GetSelfPastes() {
	auto pasteIDs = this->GetSelfPasteIDs();
	std::vector<Paste> pastes;

	for (auto pasteID : pasteIDs) {
		pastes.push_back(this->GetPaste(pasteID));
	}

	return pastes;
}

json Client::RawGetSelfPastesByAmount(int amount) {
	auto pasteIDs = this->GetSelfPasteIDsByAmount(amount);
	std::vector<json> pastes;

	for (auto pasteID : pasteIDs) {
		pastes.push_back(this->RawGetPaste(pasteID));
	}
	pastes.resize(amount);

	return pastes;
}

std::vector<Paste> Client::GetSelfPastesByAmount(int amount) {
	auto pasteIDs = this->GetSelfPasteIDsByAmount(amount);
	std::vector<Paste> pastes;

	for (auto pasteID : pasteIDs) {
		pastes.push_back(this->GetPaste(pasteID));
	}
	pastes.resize(amount);

	return pastes;
}