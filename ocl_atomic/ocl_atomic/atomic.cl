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

/*  
  #pragma omp atomic read
  value = *p;
*/
__kernel void atomic_read(__global int* p)
{
	// there is no atomic read function so this 
	// may be moot
}

/*  
  #pragma omp atomic update
  x++;
  x--;
  ++x;
  --x;
  x binop= expr;
  x = x binop expr;
*/
__kernel void atomic_update(__global int* p)
{
	const int expr = 1234;

	// these functions return the old value 
	atomic_inc(p); // x++ or ++x
	atomic_dec(p); // x-- or --x

	// here binop is restricted to + or -
	atomic_add(p, expr);
	atomic_sub(p, expr);
}

/*  
  #pragma omp atomic capture
  v = x++;
  v = x--;
  v = ++x;
  v = --x;
  v = x binop= expr;
*/
__kernel void atomic_capture(__global int* p)
{
	// since there is no atomic read ocl function
	// we just read out the value from global mem
	// - a barrier maybe applicable
	const int expr = 1234;
	int v = 0;

	// these functions return the old value 
	atomic_inc(p); // x++ or ++x
	v = *p;

	atomic_dec(p); // x-- or --x
	v = *p;

	// here binop is restricted to + or -
	atomic_add(p, expr);
	v = *p;

	atomic_sub(p, expr);
	v = *p;
}