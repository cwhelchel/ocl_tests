// ocl_sections.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstring>
#include "omp_to_ocl.h"

const char* kernel1 = "#pragma OPENCL EXTENSION cl_amd_printf : enable \n__kernel void kernel1() { printf(\"k1\\n\"); }\n";
const char* kernel2 = "#pragma OPENCL EXTENSION cl_amd_printf : enable \n__kernel void kernel2() { printf(\"k2\"); }\n";


int _tmain(int argc, _TCHAR* argv[])
{
	o2o_init();
	o2o_create_cmd_queue(CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE);
	
	o2o_create_program_from_source(kernel1);
	o2o_build_program();
	o2o_create_kernel("kernel1");

	//o2o_execute_kernel(1);
    cl_int ret = clEnqueueTask(cmd_q, kernel, 0, NULL, NULL);
    CHECK(ret);


	o2o_finalize();
	
	printf("... Program Done\n");
	getchar();
	return 0;
}

