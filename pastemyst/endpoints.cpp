#include "pch.h"
#include "framework.h"

#include <iostream>
#include "endpoints.h"

using namespace std;

string EndpointBase  = "https://paste.myst.rs/api/v2/";

string EndpointPaste = EndpointBase + "paste/";
string EndpointDate  = EndpointBase + "data/";
string EndpointTime  = EndpointBase + "time/";
string EndpointUser  = EndpointBase + "user/";


string EndpointSelfUser = EndpointBase + "user/self/";
string EndpointSelfUserPastes = EndpointBase + "user/self/pastes";