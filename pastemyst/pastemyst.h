#pragma once

#include "cpr/cpr.h"

class Client {
private:
	// ...
	
public:
	std::string auth_token;

	Client();
	Client(std::string auth_token);

    void Authorize(std::string auth_token);

	cpr::Response GetPaste(std::string pasteID);
	cpr::Response CreatePaste(std::string paste_content);
	cpr::Response EditPaste(std::string pasteID, std::string editContent);
	cpr::Response DeletePaste(std::string pasteID);

	/*cpr::Response UserExists();
	cpr::Response GetUser();

	cpr::Response GetLanguage();
	
	cpr::Response ExpiresinToUnixTimestamp();*/
};



//struct Pasty {
//	char* id;
//	char* language;
//	char* title;
//	char* code;
//};
//
//struct Paste {
//	char* id;
//	char* owner_id;
//	char* title;
//	long double created_at;
//	char* expires_in;
//	long double deletes_at;
//	long double stars;
//	bool is_private;
//	bool is_public;
//	char* tags;
//	char* pasties;
//	char* edits;
//};