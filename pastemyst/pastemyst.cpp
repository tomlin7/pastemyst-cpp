// pastemyst.cpp : Defines the functions for the static library.

#include "pch.h"
#include "framework.h"

#include "pastemyst.h"
#include "endpoints.h"

Client::Client() {
	// ...
}

Client::Client(std::string auth_token) {
	this -> auth_token = auth_token;
}

void Client::Authorize(std::string auth_token) {
    this -> auth_token = auth_token;
}


//void Client::Get() {
//
//}
//
//void Client::Post() {
//
//}
//void Client::Patch() {
//
//}
//void Client::Delete () {
//
//}







//cpr::Response Client::UserExists() {
//
//}
//
//cpr::Response Client::GetUser() {
//
//}
//
//
//cpr::Response Client::GetLanguage() {
//
//}
//
//cpr::Response Client::ExpiresinToUnixTimestamp() {
//
//}