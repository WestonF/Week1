#include <iostream>

int main()
{
	bool t = true;
	bool f = false;

	std::cout << "NOT " << t << " = " << !t << std::endl;
	
	std::cout << "NOT " << f << " = " << !f << std::endl;

	std::cout << t <<" AND " << t << " = " << (t&&t) << std::endl;

	std::cout << t <<" AND " << f << " = " << (t&&f) << std::endl;

	std::cout << f <<" AND " << f << " = " << (f&&f) << std::endl;

	std::cout << t <<" OR " << t << " = " << (t||t) << std::endl;

	std::cout << t <<" OR " << f << " = " << (t||f) << std::endl;

	std::cout << f <<" OR " << f << " = " << (f||f) << std::endl;

	return 0;
}

