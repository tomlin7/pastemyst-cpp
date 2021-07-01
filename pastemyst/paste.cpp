#include "pch.h"
#include "framework.h"

#include "client.h"
#include "endpoints.h"
#include "http.h"
#include "objects.h"

json Client::RawGetPaste(std::string pasteID) {
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

Paste Client::GetPaste(std::string pasteID) {
	auto rawPaste = this->RawGetPaste(pasteID);
	return rawPaste;
}

json Client::RawCreatePaste(std::string pasteContent) {
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

json Client::RawCreatePaste(PasteCreateInfo& pasteContent) {
	json jsonPasteContent = pasteContent;
	return this->RawCreatePaste(jsonPasteContent.dump());
}

Paste Client::CreatePaste(std::string pasteContent) {
	return this->RawCreatePaste(pasteContent);
}

Paste Client::CreatePaste(PasteCreateInfo& pasteContent) {
	return this->RawCreatePaste(pasteContent);
}

json Client::RawEditPaste(std::string pasteID, std::string editContent) {
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

json Client::RawEditPaste(std::string pasteID, Paste& editContent) {
	json jsonEditContent = editContent;
	return this->RawEditPaste(pasteID, jsonEditContent.dump());
}

Paste Client::EditPaste(std::string pasteID, std::string editContent) {
	auto rawPaste = this->RawEditPaste(pasteID, editContent);
	return rawPaste;
}

Paste Client::EditPaste(std::string pasteID, Paste& editContent) {
	return this->RawEditPaste(pasteID, editContent);
}

json Client::RawDeletePaste(std::string pasteID) {
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

bool Client::DeletePaste(std::string pasteID) {
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

	return response.status_code == HTTP::ok;
}

json Client::RawBulkDeletePastes(std::vector<std::string>& pasteIDs) {
	json finalResult;
	for (auto pasteID : pasteIDs) {
		auto result = this->DeletePaste(pasteID);
		finalResult[pasteID] = result;
	}

	return finalResult;
}

bool Client::BulkDeletePastes(std::vector<std::string>& pasteIDs) {
	auto finalResult = true;
	for (auto pasteID : pasteIDs) {
		auto result = this->DeletePaste(pasteID);
		if (!result)
			finalResult = false;
	}

	return finalResult;
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