#pragma OPENCL EXTENSION cl_amd_printf : enable

__kernel void single()
{
    int id = get_global_id(0);
    
    if (id == 0)
        printf("single execution\n");
    barrier(CLK_GLOBAL_MEM_FENCE);
    
    printf("multiple\n");
} 