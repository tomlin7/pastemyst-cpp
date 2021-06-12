#pragma once

extern std::string EndpointBase;

// extern std::string EndpointPaste;
extern std::string EndpointData;
extern std::string EndpointTime;
extern std::string EndpointUser;

extern std::string EndpointSelfUser;
extern std::string EndpointSelfUserPastes;

//string ato_aastring(double x) {
//	stringstream ss;
//	ss << x;
//	return ss.str();
//}

std::string EndpointPaste(std::string pasteId);
std::string DataLanguageByName(std::string name);
std::string DataLanguageByExt(std::string extension);
std::string TimeExpiresInToUnix(double createdAt, std::string expires);
