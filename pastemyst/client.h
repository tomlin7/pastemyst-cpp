#pragma once

#include"cpr/cpr.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;


class Client {
private:
	std::string auth_token;

public:
	Client();
	Client(std::string auth_token);

	void Authorize(std::string auth_token);
	bool IsAuthorized();

	// TODO: avoid duplication of code.
	void Get();
	void Post();
	void Patch();
	void Delete();

	json GetPaste(std::string pasteID);
	json CreatePaste(std::string paste_content);
	json EditPaste(std::string pasteID, std::string editContent);
	bool DeletePaste(std::string pasteID);
	bool BulkDeletePastes(std::vector<std::string>& pasteIDs);
	bool PasteExists(std::string pasteID);

	json GetUser(std::string username);
	json GetSelfUser();
	bool UserExists(std::string username);
	std::vector<std::string> GetSelfPasteIDs();
	std::vector<std::string> GetSelfPasteIDsByAmount(int amount);
	std::vector<json> GetSelfPastes();
	std::vector<json> GetSelfPastesByAmount(int amount);

	json GetLanguageByName(std::string name);
	json GetLanguageByExtension(std::string extension);

	unsigned long ExpiresInToUnixTimestamp(unsigned long createdAt, std::string expiresIn);
};
