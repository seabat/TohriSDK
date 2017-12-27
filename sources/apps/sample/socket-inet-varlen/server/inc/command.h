#define BUFFER_SIZE 256
typedef struct thread_arg{
	int            acceptFD;
	unsigned char  cmd_id;
	unsigned char  cmd_in_size[4];
	unsigned char* p_cmd_in_payload;
	unsigned char  cmd_out_size[4];
	unsigned char* p_cmd_out_payloard;
	int            status;
}thread_arg_st;
int dispatch_command(thread_arg_st* arg);

