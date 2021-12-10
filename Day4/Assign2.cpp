#include <iostream>
#include <cassert>

int main()
{
	int ia = 2, ib = 3, ic;
	float fa = 4.5, fb = 5.25, fc;
	char ca = '%' , cb = 'B', cc;
	bool ba = true, bb = false, bc;

	std::cout << "int "	<<  ia << " + int "	<< ib << " = " << ia + ib << '\n' 
	<< "looks like an int" << std::endl;
	
	std::cout << "int " 	<<  ia << " + float "	<< fb << " = " << ia + fb << '\n'
	<< "looks like a float" << std::endl;
	
	std::cout << "int " 	<<  ia << " + char "	<< cb << " = " << ia + cb << '\n' 
	<< "looks like an int" << std::endl;
	
	std::cout << "int " 	<<  ia << " + bool "	<< bb << " = " << ia + bb << '\n' 
	<< "looks like an int" << std::endl;
	
	std::cout << "float "	<<  fa << " + float "	<< fb << " = " << fa + fb << '\n' 
	<< "looks like a float" << std::endl;
	
	std::cout << "float "	<<  fa << " + char "	<< cb << " = " << fa + cb << '\n' 
	<< "looks like a float" << std::endl;
	
	std::cout << "float "	<<  fa << " + bool "	<< bb << " = " << fa + bb << '\n' 
	<< "looks like a float" << std::endl;
	
	std::cout << "char "	<<  ca << " + char "	<< cb << " = " << ca + cb << '\n' 
	<< "looks like an int? This is unexpected." << std::endl;
	
	std::cout << "char " 	<<  ca << " + bool "	<< bb << " = " << ca + bb << '\n' 
	<< "looks like an int" << std::endl;
	
	std::cout << "bool "	<<  ba << " + bool "	<< bb << " = " << ba + bb << '\n' 
	<< "looks like an int, but so do the bools pre-addition. Probably an artifact of the casting done by std::cout, although int is the underlying type of bool..." << std::endl;
	
	//There's probably a better way to test the output type of the cast than sending them to the terminal, which layers on a second cast, but I don't have one on hand.

	return 0;
}
