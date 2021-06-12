#pragma once

#include"cpr/cpr.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;


class Client {
private:
	// ...

public:
	std::string auth_token;

	Client();
	Client(std::string auth_token);

	void Authorize(std::string auth_token);

	void Get();
	void Post();
	void Patch();
	void Delete();


	json GetPaste(std::string pasteID);
	json CreatePaste(std::string paste_content);
	json EditPaste(std::string pasteID, std::string editContent);
	json DeletePaste(std::string pasteID);
	bool PasteExists(std::string pasteID);

	cpr::Response GetUser(std::string username);
	bool UserExists(std::string username);

	cpr::Response GetLanguageByName(std::string name);
	cpr::Response GetLanguageByExtension(std::string extension);

	/*cpr::Response ExpiresinToUnixTimestamp();*/
};
