#include <iostream>
#include <vector>
int main()
{
	constexpr int arrsize = 3;
	float arr[arrsize] = { 2.2, 4.6, 3496.4};
	std::vector<float> vec;
	
	for (int i = 0; i < arrsize; i++)
	{
		vec.push_back(arr[i]);
	}

	std::cout << vec[0] << ' ' << vec[1] << ' ' << vec[2] << std::endl;
	
	std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << std::endl;

	return 0;
}
