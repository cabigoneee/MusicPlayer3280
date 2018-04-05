#pragma once
#include <stdio.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, char *data);
size_t write_file(void *ptr, size_t size, size_t nmemb, FILE *stream);
int get_data(const char* server_ip, int port, const char* filename, int start, int length, char* data);
int get_db(const char* server_ip, int port, const char* filename);
int test_connection(const char* server_ip, int port);