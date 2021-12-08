#include <iostream>
#include <cmath>

int main()
{
	float num1, num2, num3, num4;
	const float bignumber = 1000000000.f;
	const float smallnumber = 0.005f;
	num3 = 0;
	num4 = 0;
	std::cout 	<< "Floats get less precise when they hold larger values.\n"
			<< "starting with the float resulting from 1 / 7" << std::endl;
	
	num1 = 1.f/7.f;

	std::cout << "If we add a small value such as "
	       	  << smallnumber
		  << " to this number and test if it is equal to the pre-addition value, the result comes out as ";

	num3 = num1 + smallnumber;

	if (num3 == num1)
	{
		std::cout << "true" << std::endl;
	}
	else
	{
		std::cout << "false" << std::endl;
	}

	std::cout << "If we make the number much bigger, say "
	          << bignumber 
		  << " times as big before adding " 
		  << smallnumber
		  << " and testing if it is equal to the pre-addition value, the results come out as ";

	num2 = num1 * bignumber;
	num4 = num2 + smallnumber;
	
	if (num4 == num2)
	{
		std::cout << "true" << std::endl;
	}
	else
	{
		std::cout << "false" << std::endl;
	}


	return 0;
}
