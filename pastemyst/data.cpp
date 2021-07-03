#include "pch.h"
#include "framework.h"

#include "client.h"
#include "endpoints.h"
#include "objects.h"

json Client::RawGetLanguageByName(std::string name) {
	auto response = cpr::Get(
		cpr::Url{
			DataLanguageByName
		},
		cpr::Parameters{
			{
				"name", name
			}
		}
	);

	return json::parse(response.text);
}

Language Client::GetLanguageByName(std::string name) {
	auto rawLanguage = this->RawGetLanguageByName(name);
	return rawLanguage;
}

json Client::RawGetLanguageByExtension(std::string extension) {
	auto response = cpr::Get(
		cpr::Url{
			DataLanguageByExt
		},
		cpr::Parameters{
			{
				"extension", extension
			}
		}
	);
	return json::parse(response.text);
}

Language Client::GetLanguageByExtension(std::string extension) {
	auto rawLanguage = this->RawGetLanguageByExtension(extension);
	return rawLanguage;
}