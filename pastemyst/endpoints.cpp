#include "pch.h"
#include "framework.h"

#include <iostream>
#include "endpoints.h"

std::string EndpointBase  = "https://paste.myst.rs/api/v2/";

// std::string EndpointPaste = EndpointBase + "paste/";
std::string EndpointData  = EndpointBase + "data/";
std::string EndpointTime  = EndpointBase + "time/";
std::string EndpointUser  = EndpointBase + "user/";

std::string EndpointSelfUser = EndpointBase + "user/self/";
std::string EndpointSelfUserPastes = EndpointBase + "user/self/pastes";

std::string EndpointPaste(std::string pasteId) {
	return EndpointBase + "paste/" + pasteId;
}

std::string DataLanguageByName(std::string name) {
	return EndpointData + "language?name=" + name;
}

std::string DataLanguageByExt(std::string extension) {
	return EndpointData + "languageExt?extension=" + extension;
}

std::string TimeExpiresInToUnix(double createdAt, std::string expires) {
	return EndpointTime + "expiresInToUnixTime?createdAt=" + std::to_string(createdAt) + "&expiresIn=" + expires;
}