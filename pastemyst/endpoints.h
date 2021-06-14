#pragma once

extern std::string EndpointBase;

// extern std::string EndpointPaste;
extern std::string EndpointData;
extern std::string EndpointTime;
extern std::string EndpointUser;

extern std::string EndpointSelfUser;
extern std::string EndpointSelfUserPastes;

extern std::string DataLanguageByName;
extern std::string DataLanguageByExt;

extern std::string TimeExpiresInToUnix;

std::string EndpointPaste(std::string pasteId);