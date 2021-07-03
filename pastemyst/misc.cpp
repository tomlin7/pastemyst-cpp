#include "pch.h"
#include "framework.h"

#include "client.h"

std::string Client::GetExpiresInString(ExpiresIn expiresIn) {
	switch (expiresIn)
	{
	case ExpiresIn::Never:
		return "never";
	case ExpiresIn::OneHour:
		return "1h"; 
	case ExpiresIn::TwoHours:
		return "2h";
	case ExpiresIn::OneDay:
		return "1d";
	case ExpiresIn::TwoDays:
		return "2d";
	case ExpiresIn::OneWeek:
		return "1w";
	case ExpiresIn::OneMonth:
		return "1m";
	case ExpiresIn::OneYear:
		return "1y";
	default:
		return "";
	}
}