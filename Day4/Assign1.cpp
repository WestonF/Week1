#include <iostream> 
#include <cassert>


int main()
{
	//I'll leave these here just to show my thought process
	//assert(true);	//What's a succeessful assert look like during runtime?	Answer: Nothing. Life carries on quietly.
	//assert(false);	//what's a failed assert look like? Answer: "Assertion <expression> has failed\nAborted"
	//assert(x);	//what's a compiler error around an assert look like? (x is not in scope, should error out)


	assert(3 == 3.0);
	float x = 3.1;
	//assert(x == 3.1);	//FAILED
	assert (3.1 == 3.1);
	assert (true == 1.0);	//Prompted a compiler "note" but no error or failed assert
	assert ('a' == 97);
	int* p = 0;
	assert ( NULL == p);
	assert (NULL == 0);	//Prompted a compiler warning, but no error or failed assert
	//All others passed!
	
	return 0;
}
