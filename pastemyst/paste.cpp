#include "pch.h"
#include "framework.h"

#include "client.h"
#include "endpoints.h"
#include "http.h"

json Client::GetPaste(std::string pasteID) {
	auto response = cpr::Get(
		cpr::Url{
			EndpointPaste(pasteID)
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);

	return json::parse(response.text);
}

json Client::CreatePaste(std::string pasteContent) {
	auto response = cpr::Post(
		cpr::Url{
			EndpointPaste("")
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			},
			{
				"Content-Type", "application/json"
			}
		},
		cpr::Body{
			pasteContent
		}
	);

	return json::parse(response.text);
}

json Client::EditPaste(std::string pasteID, std::string editContent) {
	auto response = cpr::Patch(
		cpr::Url{
			EndpointPaste(pasteID)
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			},
			{
				"Content-Type", "application/json"
			}
		},
		cpr::Body{
			editContent
		}
	);

	return json::parse(response.text);
}

json Client::DeletePaste(std::string pasteID) {
	auto response = cpr::Delete(
		cpr::Url{
			EndpointPaste(pasteID)
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);

	return json::parse(response.text);
}

bool Client::PasteExists(std::string pasteID) {
	auto response = cpr::Get(
		cpr::Url{
			EndpointPaste(pasteID)
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);

	return response.status_code == HTTP::ok;
}