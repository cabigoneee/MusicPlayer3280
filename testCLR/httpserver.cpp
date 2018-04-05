#include <sys/types.h>
#include <sys/stat.h>
#include "microhttpd.h"
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <string>

#include "httpserver.h"

using namespace std;

struct MHD_Daemon *daemon;		// global daemon

int answer_to_connection(void *cls, struct MHD_Connection *connection,
	const char *url,
	const char *method, const char *version,
	const char *upload_data,
	size_t *upload_data_size, void **con_cls) {
	struct MHD_Response *response;
	int ret;
	if (strcmp(method, "GET") == 0) {
		if (strcmp(url, "/get_data") == 0) {
			const char *filename = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "filename");
			const char *start = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "start");
			const char *length = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "length");
			if (filename == NULL || start == NULL || length == NULL) {
				return MHD_NO;
			}
			printf("get data: filename: %s start: %s length: %s\n", filename, start, length);
			int i_start = stoi(start);
			int i_length = stoi(length);
			int fd;
			struct stat sbuf;
			if (((fd = _open(filename, O_RDONLY)) == -1) || (fstat(fd, &sbuf) != 0)) {
				//error access file
				if (fd != -1) {
					_close(fd);
				}
				const char* errorstr = "file not exist";
				response = MHD_create_response_from_buffer(strlen(errorstr), (void *)errorstr, MHD_RESPMEM_PERSISTENT);
				if (response != NULL) {
					ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
					MHD_destroy_response(response);
					return ret;
				}
				else {
					return MHD_NO;
				}
			}
			//response = MHD_create_response_from_fd_at_offset64(sbuf.st_size, fd, 0);
			if (i_start + i_length > sbuf.st_size) {
				// error requesting size over total file size
				//printf("alert");
				response = MHD_create_response_from_fd_at_offset64(sbuf.st_size - i_start, fd, i_start);
			}
			else {
				response = MHD_create_response_from_fd_at_offset64(i_length, fd, i_start);
			}
			MHD_add_response_header(response, "Content-Type", "application/octet-stream");
			ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
			MHD_destroy_response(response);
			return ret;
		}
		else if (strcmp(url, "/check_existence") == 0) {
			const char *filename = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "filename");
			if (filename == NULL) {
				return MHD_NO;
			}
			printf("check existence: filename: %s\n", filename);
			const char *result;
			FILE *file = fopen(filename, "r");
			if (file == NULL) {
				//file not exist
				result = "false";
				response = MHD_create_response_from_buffer(strlen(result), (void *)result, MHD_RESPMEM_PERSISTENT);
				ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
			}
			else {
				//file exists
				result = "true";
				fclose(file);
				response = MHD_create_response_from_buffer(strlen(result), (void *)result, MHD_RESPMEM_PERSISTENT);
				ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
			}
			//response = MHD_create_response_from_buffer(strlen(result), (void *)result, MHD_RESPMEM_PERSISTENT);
			//ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
			MHD_destroy_response(response);
			return ret;
		}
		else if (strcmp(url, "/get_db") == 0) {
			int fd;
			struct stat sbuf;
			const char* db_name = "songDB.db";
			if (((fd = _open(db_name, O_RDONLY)) == -1) || (fstat(fd, &sbuf) != 0)) {
				//error access file
				if (fd != -1) {
					_close(fd);
				}
				const char* errorstr = "song db not exist";
				response = MHD_create_response_from_buffer(strlen(errorstr), (void *)errorstr, MHD_RESPMEM_PERSISTENT);
				if (response != NULL) {
					ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
					MHD_destroy_response(response);
					return ret;
				}
				else {
					return MHD_NO;
				}
			}
			response = MHD_create_response_from_fd(sbuf.st_size, fd);
			MHD_add_response_header(response, "Content-Type", "application/octet-stream");
			ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
			MHD_destroy_response(response);
			return ret;
		}
		else {
			const char *result = "unknown path";
			response = MHD_create_response_from_buffer(strlen(result), (void *)result, MHD_RESPMEM_PERSISTENT);
			ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
			MHD_destroy_response(response);
			return ret;
		}
	}
	else {
		return MHD_NO;
	}
}

int startDaemon()
{
	//struct MHD_Daemon *daemon;

	daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
		&answer_to_connection, NULL, MHD_OPTION_END);
	if (NULL == daemon) return 1;
	//getchar();

	//MHD_stop_daemon(daemon);
	return 0;
}

int stopDaemon() {
	if (daemon == NULL) return 1;
	else {
		MHD_stop_daemon(daemon);
		return 0;
	}
}