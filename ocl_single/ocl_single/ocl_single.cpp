// ocl_single.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "omp_to_ocl.h"


int _tmain(int argc, _TCHAR* argv[])
{
	o2o_init();
	o2o_create_cmd_queue();

    o2o_open_and_build("single.cl", "single");

    o2o_execute_kernel(100);

    o2o_finalize();

    printf("  Program done.\n");
    getchar();
	return 0;
}

