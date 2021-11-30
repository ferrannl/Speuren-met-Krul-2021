#pragma once
#include <string>
#define CURL_STATICLIB
#include <curl\curl.h>
#include <iostream>

class Curl
{
private:
	const std::string& _start_url = "start.txt";

public:
	const std::string GetText(const std::string& filename);
	struct deleter {
		void operator()(CURL* curl) {
			if (curl)
				curl_easy_cleanup(curl);
		}
	};
};
