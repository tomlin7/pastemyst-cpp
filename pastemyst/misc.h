#pragma once

enum class ExpiresIn {
	Never,
	OneHour,
	TwoHours,
	TenHours,
	OneDay,
	TwoDays,
	OneWeek,
	OneMonth,
	OneYear
};

enum class HTTP {
	ok = 200,
	badRequest = 400,
	unauthorized = 401,
	notFound = 404
};