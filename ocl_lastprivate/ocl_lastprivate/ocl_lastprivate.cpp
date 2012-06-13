// ocl_lastprivate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "omp_to_ocl.h"

int _tmain(int argc, _TCHAR* argv[])
{
    int i=0;
    cl_mem i_buff = NULL;
	
	o2o_init();
	o2o_create_cmd_queue();
	
	i_buff = o2o_create_buffer(CL_MEM_READ_WRITE, sizeof(int));

	o2o_create_program_from_file("lastprivate.cl");
	o2o_build_program();
	o2o_create_kernel("lastprivate");

	o2o_set_kernel_arg(0, sizeof(cl_mem), &i_buff); 

	o2o_execute_kernel(100);

	o2o_read_buffer(i_buff, sizeof(int), &i);

	o2o_finalize(i_buff);

	printf("  Program Done.   i:%d  \n", i); 
	
	getchar();
	return 0;
}

