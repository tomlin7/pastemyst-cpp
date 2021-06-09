#include "pch.h"
#include "framework.h"

#include "pastemyst.h"
#include "endpoints.h"

cpr::Response Client::GetPaste(std::string pasteID) {
	auto response = cpr::Get(
		cpr::Url{
			EndpointPaste + pasteID
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);
	return response;
}

cpr::Response Client::CreatePaste(std::string pasteContent) {
	auto response = cpr::Post(
		cpr::Url{
			EndpointPaste
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
	return response;
}

cpr::Response Client::EditPaste(std::string pasteID, std::string editContent) {
	auto response = cpr::Patch(
		cpr::Url{
			EndpointPaste + pasteID
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
	return response;
}

cpr::Response Client::DeletePaste(std::string pasteID) {
	auto response = cpr::Delete(
		cpr::Url{
			EndpointPaste + pasteID
		},
		cpr::Header{
			{
				"Authorization", this->auth_token
			}
		}
	);
	return response;
}