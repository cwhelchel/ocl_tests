// ocl_atomic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "omp_to_ocl.h"

int _tmain(int argc, _TCHAR* argv[])
{
    cl_mem p_buff = NULL;
    int p = 2;

	o2o_init();
	o2o_create_cmd_queue();
	
	p_buff = o2o_create_buffer(CL_MEM_READ_WRITE, sizeof(int));

    o2o_open_and_build("atomic.cl", "atomic_lshift");

	o2o_set_kernel_arg(0, sizeof(cl_mem), &p_buff); 

    printf("%d", p);

    o2o_write_buffer(p_buff, sizeof(int), &p);

	o2o_execute_kernel(1);

	o2o_read_buffer(p_buff, sizeof(int), &p);

	o2o_finalize(p_buff);

	printf("  Program Done.   p:%d  \n", p); 

	getchar();
	return 0;
}


// OpenMP 3.1 atomic write from example A.22.2c
//void atomic_write(int *p, int value)
//{
//    /* Guarantee that value is stored atomically into *p. No part of *p can change
//    * until after the entire write operation is completed.
//    */
//    #pragma omp atomic write
//    *p = value;
//}

//int atomic_read(const int *p)
//{
//    int value;
//    /* Guarantee that the entire value of *p is read atomically. No part of
//    * *p can change during the read operation.
//    */
//    #pragma omp atomic read
//    value = *p;
//    return value;
//}