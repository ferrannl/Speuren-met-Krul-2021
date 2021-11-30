#include "Curl.hpp"

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

const std::string Curl::GetText(const std::string& filename)
{
	std::unique_ptr<CURL, deleter> curl(curl_easy_init(), deleter());
	CURLcode response;
	std::string result;
	const std::string baseUrl = "https://www.swiftcoder.nl/cplus/";
	std::string url = baseUrl + filename;
	if (curl)
	{
		curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, writeFunction);
		curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &result);

		response = curl_easy_perform(curl.get());

		if (response != CURLE_OK)
		{
			std::cerr << "CURL error: " << response << "\n";
		}
	}

	return result;

}