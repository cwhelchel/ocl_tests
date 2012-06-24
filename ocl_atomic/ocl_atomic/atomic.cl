/*  
  #pragma omp atomic write
  *p = value;
*/
__kernel void atomic_write(__global int* p)
{
	// passing in value as kernel arg would be
	// silly. we just use something arbitrary
	// and pretend that our kernel calculated it.
	atomic_xchg(p, 123);
}