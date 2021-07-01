#include "pch.h"
#include "framework.h"

#include "endpoints.h"

std::string EndpointBase  = "https://paste.myst.rs/api/v2/";

std::string EndpointData  = EndpointBase + "data/";
std::string EndpointTime  = EndpointBase + "time/";
std::string EndpointUser  = EndpointBase + "user/";

std::string EndpointSelfUser = EndpointBase + "user/self/";
std::string EndpointSelfUserPastes = EndpointBase + "user/self/pastes";

std::string DataLanguageByName = EndpointData + "language";
std::string DataLanguageByExt = EndpointData + "languageExt";

std::string TimeExpiresInToUnix = EndpointTime + "expiresInToUnixTime";

std::string EndpointPaste(std::string pasteId) {
	return EndpointBase + "paste/" + pasteId;
}