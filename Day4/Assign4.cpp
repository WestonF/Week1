#include <iostream>
#include <cassert>

int main()
{
	int x = 4;
	int y = x+++2;
	assert(y == 6);
	assert(x == 5);

	//this program does run without issue. 
	//The order of precedence is: suffix increment, addition, assignment. 
	//the program works because the postfix increment returns the value held before the operation. Often thought of as "x doesn't change its value until after the current expression has finished evaluating"
	
	return 0;
}
