#pragma OPENCL EXTENSION cl_amd_printf : enable

__kernel void lastprivate(__global int* i)
{
    int id = get_global_id(0);
    int arr[100];
    
    arr[id] = id*5;
    
    if (id == get_global_size(0)-1)
		*i = id;
	
	barrier(CLK_GLOBAL_MEM_FENCE);
	
	if (id == get_global_size(0)-1)
	{
		printf("%d\n", arr[id]);
		printf("%d\n", *i);
	}
} 