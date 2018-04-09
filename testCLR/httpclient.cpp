#include "curl/curl.h"
//#include <stdio.h>
#include "httpclient.h"
#include <string>

using namespace std;

typedef struct data_buffer {
	char *data;
	int pos;
} write_result;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *data) {
	write_result *res = (write_result *)data;
	printf("size: %d nmemb: %d\n", size, nmemb);
	memcpy(res->data + res->pos, ptr, size * nmemb);
	res->pos += size * nmemb;
	return size * nmemb;
}

size_t write_file(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	return fwrite(ptr, size, nmemb, stream);
}

int get_data(const char* server_ip, int port, const char* filename, int start, int length, char* data) {
	CURL *curl = curl_easy_init();
	CURLcode res;
	if (curl) {
		// initialize write result buffer
		write_result write_res;
		write_res.data = data;
		write_res.pos = 0;
		string url("http://" + string(server_ip) + ":" + to_string(port) + "/get_data?filename=" + string(filename)
		+ "&start=" + to_string(start) + "&length=" + to_string(length));
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_res);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			printf("error %s\n", curl_easy_strerror(res));
			curl_easy_cleanup(curl);
			return 1;
		}
		else {
			printf("data: %s\n", data);
			curl_easy_cleanup(curl);
			return 0;
		}
	}
	return 1;
}

int get_db(const char* server_ip, int port, const char* output_filename) {
	CURL *curl = curl_easy_init();
	CURLcode res;
	FILE *outfile = fopen(output_filename, "wb");
	if (curl) {
		string url("http://" + string(server_ip) + ":" + to_string(port) + "/get_db");
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_file);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			printf("error %s\n", curl_easy_strerror(res));
			curl_easy_cleanup(curl);
			fclose(outfile);
			return 1;
		}
		else {
			curl_easy_cleanup(curl);
			fclose(outfile);
			return 0;
		}
	}
	return 1;
}

int test_connection(const char* server_ip, int port) {
	CURL *curl = curl_easy_init();
	CURLcode res;
	if (curl) {
		string url("http://" + string(server_ip) + ":" + to_string(port) + "/");
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			curl_easy_cleanup(curl);
			return 1;
		}
		else {
			curl_easy_cleanup(curl);
			return 0;
		}
	}
	return 1;
}