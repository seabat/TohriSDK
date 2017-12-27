#define BUFFER_SIZE 256

#define HTTP_REQ_SIZE 1014
typedef struct thread_arg{
	int            acceptFD;
	unsigned int   http_req_size;
	unsigned char  http_req_data[HTTP_REQ_SIZE];
	unsigned int   http_res_size;
	unsigned char* http_res_data;
	int            status;
}thread_arg_st;

int sws_dispatch_command(thread_arg_st* arg);

