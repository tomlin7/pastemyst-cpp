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
	
	Paste paste;
	paste.from_json(rawPaste, paste);

	return paste;
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
	return this->RawCreatePaste((json)pasteContent);
}

Paste Client::CreatePaste(std::string pasteContent) {
	auto rawPaste = this->RawCreatePaste(pasteContent);

	Paste paste;
	paste.from_json(rawPaste, paste);

	return paste;
}

Paste Client::CreatePaste(PasteCreateInfo& pasteContent) {
	return this->CreatePaste((json)pasteContent);
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
	json j;
	editContent.to_json(j, editContent);

	return this->RawEditPaste(pasteID, j);
}

Paste Client::EditPaste(std::string pasteID, std::string editContent) {
	auto rawPaste = this->RawEditPaste(pasteID, editContent);

	Paste paste;
	paste.from_json(rawPaste, paste);

	return paste;
}

Paste Client::EditPaste(std::string pasteID, Paste& editContent) {
	json j;
	editContent.to_json(j, editContent);

	return this->EditPaste(pasteID, j);
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