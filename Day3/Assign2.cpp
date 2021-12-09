#include <iostream>

int main()
{

	int i_int = 5;
	float i_float = 3.625;
	

	//two solutions for putting an int and a float in the same array, yet both feel like a violation of the intent of the task. Given that arrays are implied to be a series of elements of the same type, I don't know that there is a method for creating a mixed array that doesn't seem like a violation of the intent of this task.

	float arr[2];
      	arr[0] = i_int;
	arr[1] = i_float;
       //this method isn't really a mixed array, it just implicitly casts i_int as a float before storing the value to arr. i_float is a genuine float being treated as a float. Interestingly, float arr[2] = {i_int, i_float} DID create an error.
	
	std::pair<int, float> parr[1] = {{i_int, i_float}};	// this method felt like cheating as it is using a container of sorts to hold the two dissimilar datatypes, even if that container is neither a struct nor a class.


	std::cout << arr[0] << ' ' << arr[1] << std::endl;
	std::cout << parr[0].first << ' ' << parr[0].second << std::endl;

	//Assign 2.2: While the meaning of "automatically" is flexible, it isn't really possible to distinguish what the original datatype was in the elements of arr except by remembering what I put where. Not hard on a two element array. Likely quite difficult in an array of several million elements.
	//On the other hand, the datatypes of parr are explicitly retained. Every element's .first will be an int, and its .second will be a float (although you could still jam an int into the float side as in arr, in which case that int's datatype would be "lost" as we treated it as a float forever after)
	
	return 0;
}
