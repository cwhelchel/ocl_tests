// ocl_ordered.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "omp_to_ocl.h"


int main(int argc, char* argv[])
{
    int x = 10;
    int y = 0;
	cl_mem x_buff = NULL;
	cl_mem y_buff = NULL;
	
	o2o_init();
	o2o_create_cmd_queue();
	
	x_buff = o2o_create_buffer(CL_MEM_READ_WRITE, sizeof(int));
	y_buff = o2o_create_buffer(CL_MEM_READ_WRITE, sizeof(int));

	o2o_create_program_from_file("ordered.cl");
	o2o_build_program();
	o2o_create_kernel("ordered");

	o2o_write_buffer(x_buff, sizeof(cl_mem), &x);
	o2o_write_buffer(y_buff, sizeof(cl_mem), &y);

	o2o_set_kernel_arg(0, sizeof(cl_mem), &x_buff); 
	o2o_set_kernel_arg(1, sizeof(cl_mem), &y_buff); 

	o2o_execute_kernel(100);

	o2o_read_buffer(x_buff, sizeof(int), &x);
	o2o_read_buffer(y_buff, sizeof(int), &y);

	o2o_finalize(x_buff);
	o2o_finalize(y_buff);

	printf("  Program Done.   result: %i, %i \n", x, y); 
	
	getchar();
	return 0;
}
