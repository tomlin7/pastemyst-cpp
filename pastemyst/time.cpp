#include "pch.h"
#include "framework.h"

#include "client.h"
#include "endpoints.h"
#include "misc.h"


json Client::RawExpiresInToUnixTimestamp(unsigned long createdAt, std::string expiresIn) {
	auto response = cpr::Get(
		cpr::Url{
			TimeExpiresInToUnix
		},
		cpr::Parameters{
			{
				"createdAt", std::to_string(createdAt)
			}, 
			{
				"expiresIn", expiresIn
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

json Client::RawExpiresInToUnixTimestamp(unsigned long createdAt, ExpiresIn expiresIn) {
	return this->RawExpiresInToUnixTimestamp(createdAt, this->GetExpiresInString(expiresIn));
}

unsigned long Client::ExpiresInToUnixTimestamp(unsigned long createdAt, std::string expiresIn) {
	return this->RawExpiresInToUnixTimestamp(createdAt, expiresIn)["result"] .get<unsigned long>();
}

unsigned long Client::ExpiresInToUnixTimestamp(unsigned long createdAt, ExpiresIn expiresIn) {
	return this->ExpiresInToUnixTimestamp(createdAt, this->GetExpiresInString(expiresIn));
}