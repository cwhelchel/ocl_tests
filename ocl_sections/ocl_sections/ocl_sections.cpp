// ocl_sections.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstring>
#include "omp_to_ocl.h"

const char* kernel1 = "#pragma OPENCL EXTENSION cl_amd_printf : enable \n__kernel void kernel1() { printf(\"k1\\n\"); }\n";
const char* kernel2 = "#pragma OPENCL EXTENSION cl_amd_printf : enable \n__kernel void kernel2() { printf(\"k2\"); }\n";


int _tmain(int argc, _TCHAR* argv[])
{
    cl_int ret;

	o2o_init();
	o2o_create_cmd_queue(CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE);
	
	o2o_create_program_from_source(kernel1);
	o2o_build_program();
	o2o_create_kernel("kernel1");

    size_t k_size = strlen(kernel2);
    cl_program p2 = clCreateProgramWithSource(ocl_ctx, 1, 
                                    &kernel2, 
                                    &k_size,
                                    &ret);
    CHECK(ret);

    ret = clBuildProgram(p2, 1, &d_id, NULL, NULL, NULL);
    CHECK(ret);

    cl_kernel k2 = clCreateKernel(p2, "kernel2", &ret);
    CHECK(ret);

    ret = clEnqueueTask(cmd_q, kernel, 0, NULL, NULL);
    CHECK(ret);

    ret = clEnqueueTask(cmd_q, k2, 0, NULL, NULL);
    CHECK(ret);

	o2o_finalize();
	
	printf("... Program Done\n");
	getchar();
	return 0;
}

