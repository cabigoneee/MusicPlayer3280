#pragma once
//#include <sys/types.h>
//#include <sys/select.h>
//#include <sys/socket.h>
//#include <sys/stat.h>
//#include "microhttpd.h"
//#include <stdio.h>
//#include <fcntl.h>
//#include <io.h>
//#include <string>

#define PORT 8080

int answer_to_connection(void *cls, struct MHD_Connection *connection,
	const char *url,
	const char *method, const char *version,
	const char *upload_data,
	size_t *upload_data_size, void **con_cls);
int startDaemon(int port = PORT);
int stopDaemon();