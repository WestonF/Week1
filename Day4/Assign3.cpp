#include <iostream>
#include <cassert>

int main()
{
	unsigned int a = 1;

	//Unary Operators
	a++;		//postfix (suffix) increment
	assert(a == 2);

	a--;		//postfix (suffix) decrement
	assert(a == 1);
	
	++a;		//prefix increment
	assert(a == 2);
	
	--a;		//prefix decrement
	assert(a == 1);
	
	a = 0;
	a = ~a;		//bitwise NOT
	assert(a == 0xFFFFFFFF);
	a = 0;
	a = !(a);	//logical NOT
	assert((bool)a == true);

	a = 2;
	unsigned int* p_a;
	p_a = &a;		//Address-of
	unsigned int b = *p_a;	//Dereference
	assert(b == a);
	

	//Binary operators
	a = 2;			//assignment
	b = 7;
	assert(b * a == 14);	//multiplication

	assert(b / a == 3);	//division (integer) 

	assert(b % a == 1);	//modulo (remainder)

	assert(b + a == 9);	//addition

	assert(b - a == 5);	//subtraction

	assert(b << a == 28);	//bitwise shift left

	assert(b >> a == 1);	//bitwise shift right

	assert(a < b);		//less than

	assert(a <= b);		//less than or equal to

	assert(b > a);		//greater than

	assert(b >= a);		//greater than or equal to

	assert(b != a);		// not equal to

	assert(b == b);		// equality

	a = 11;
	b = 5;
	assert((a & b) == 1);	//bitwise AND
	
	assert((a | b) == 15);	//bitwise OR

	assert((a ^ b) == 14);	//bitwise XOR

	assert(a && b);		//logical AND

	assert(a||b);		//logical OR

	assert(a), assert (b);	//comma operator
	
	a = 2;
	a += 3;		//compound assignment (addition)
	assert(a == 5);
	
	a -= 2;		//compound assignment (subtraction)
	assert(a == 3);
	
	a *= 2;		//compound assignment (multiplication)
	assert(a == 6);

	a /= 2;		//compound assignment (division)
	assert(a == 3);

	a = 5;
	a %= 2;		//compound assignment (modulo)
	assert(a == 1);

	a <<= 2;		//compound assignment (bitwise shift left)
	assert(a == 4);

	a >>= 1;		//compound assignment (bitwise shift right)
	assert(a == 2);
	
	a |= 1;		//compound assignment (bitwise OR)
	assert(a == 3);

	a ^= 2;		//compound assignment (bitwise XOR)
	assert(a == 1);

	a &= 2;		//compound assignment (bitwise AND)
	assert(a == 0);

	//ternary operator

	a = 3;
	b = 5;
	unsigned int c = 2;
	assert(a ? b : c == b);	//conditional

	return 0;
}

