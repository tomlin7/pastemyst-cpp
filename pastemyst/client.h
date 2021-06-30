#pragma once

#include"cpr/cpr.h"
#include "nlohmann/json.hpp"
#include "objects.h"

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

	json RawGetPaste(std::string pasteID);
	json RawCreatePaste(std::string pasteContent);
	json RawCreatePaste(PasteCreateInfo& pasteContent);
	json RawEditPaste(std::string pasteID, std::string editContent);
	json RawEditPaste(std::string pasteID, Paste& editContent);
	json RawDeletePaste(std::string pasteID);
	json RawBulkDeletePastes(std::vector<std::string>& pasteIDs);

	Paste GetPaste(std::string pasteID);
	Paste CreatePaste(std::string pasteContent);
	Paste CreatePaste(PasteCreateInfo& pasteContent);
	Paste EditPaste(std::string pasteID, std::string editContent);
	Paste EditPaste(std::string pasteID, Paste& editContent);
	bool DeletePaste(std::string pasteID);
	bool BulkDeletePastes(std::vector<std::string>& pasteIDs);
	bool PasteExists(std::string pasteID);

	json RawGetUser(std::string username);
	json RawGetSelfUser();
	json RawGetSelfPasteIDs();
	json RawGetSelfPasteIDsByAmount(int amount);
	json RawGetSelfPastes();
	json RawGetSelfPastesByAmount(int amount);

	User GetUser(std::string username);
	User GetSelfUser();
	bool UserExists(std::string username);
	std::vector<std::string> GetSelfPasteIDs();
	std::vector<std::string> GetSelfPasteIDsByAmount(int amount);
	std::vector<Paste> GetSelfPastes();
	std::vector<Paste> GetSelfPastesByAmount(int amount);

	json RawGetLanguageByName(std::string name);
	json RawGetLanguageByExtension(std::string extension);

	Language GetLanguageByName(std::string name);
	Language GetLanguageByExtension(std::string extension);

	json RawExpiresInToUnixTimestamp(unsigned long createdAt, std::string expiresIn);

	unsigned long ExpiresInToUnixTimestamp(unsigned long createdAt, std::string expiresIn);
};
