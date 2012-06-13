#pragma OPENCL EXTENSION cl_amd_printf : enable

void get_semaphore(__global int* semaphore)
{
	int occupied = atomic_xchg(semaphore, 1);
	while (occupied > 0)
	{
		occupied = atomic_xchg(semaphore, 1);
	}
	
	printf("semaphore grabbed");
}

void release_semaphore(__global int* semaphore)
{
	int old = atomic_xchg(semaphore, 0);
	printf("semaphore released");
}

void ordered_entry(int id, __global int* ordered_id)
{
	while (id != *ordered_id)
    {
        // wait patiently
    }
    
    printf(" inc\n");
    (*ordered_id)++;   
    printf(" ordered id: %i == %i \n",  *ordered_id, id);
}

__kernel void ordered(__global int* x, __global int* ordered_id)
{
    int id = get_global_id(0);
    
	//ordered_entry(id, ordered_id);
    //printf("ordered exit\n");
    
    get_semaphore(ordered_id);
    
    // do ordered structure block code
    (*x) = (*x) / 2;
    //printf(" x1: %i\n",  *x);
    
    (*x) = (*x) - id;
    //printf(" x2: %i\n",  *x);
    
    release_semaphore(ordered_id);
} 