#include <iostream>

int getsize(std::string i_type);

int main()
{
	std::string i_type = ""; 
	int typesize;
	//cin some stuff
	while(true)
	{
		std::cout << "Enter a variable type name (ex. \"int\") to get its size, or \"exit\" to exit" << std::endl;
		std::getline(std::cin, i_type);

		typesize = getsize (i_type);
	
		if (typesize > 0)
		{
			std::cout << "One " << i_type << " is " << typesize << " bytes." << std::endl;
		}
		else if (i_type == "exit")
		{
			break;
		}
		else
		{
			std::cout << "This program does not recognize " << i_type << " as a variable type" << std::endl;
		}

	}
	return 0;
}

int getsize(std::string i_type)
{
	int returnval = 0;

	if ((i_type == "char")||(i_type == "signed char"))
	{
		returnval = sizeof(char);
	}
	else if (i_type == "unsigned char")
	{
		returnval = sizeof(unsigned char);
	}
	else if ((i_type == "int")||(i_type == "signed int"))
	{
		returnval = sizeof(signed int);
	}
	else if (i_type == "unsigned int")
	{
		returnval = sizeof(unsigned int);
	}
	else if ((i_type == "short")||(i_type == "signed short")||(i_type == "short int")||(i_type == "signed short int"))
	{
		returnval = sizeof(signed short);
	}
	else if ((i_type == "unsigned short")||(i_type == "unsigned short int"))
	{
		returnval = sizeof(unsigned short);
	}
	else if ((i_type == "long")||(i_type == "signed long")||(i_type == "long int")||(i_type == "signed long int"))
	{
		returnval = sizeof(signed long);
	}
	else if ((i_type == "unsigned long")||(i_type == "unsigned long int"))
	{
		returnval = sizeof(unsigned long);
	}
	else if ((i_type == "long long")||(i_type == "signed long long")||(i_type == "long long int")||(i_type == "signed long long int"))
	{
		returnval = sizeof(signed long long);
	}
	else if ((i_type == "unsigned long long")||(i_type == "unsigned long long int"))
	{
		returnval = sizeof(unsigned long long);
	}
	else if (i_type == "float")
	{
		returnval = sizeof(float);
	}
	else if (i_type == "double")
	{
		returnval = sizeof(double);
	}
	else if (i_type == "long double")
	{
		returnval = sizeof(long double);
	}
	else if (i_type == "wchar_t")
	{
		returnval = sizeof(wchar_t);
	}
	else
	{
		returnval = -1;
	}


	std::cout << i_type << std::endl;
	return returnval;
}
