#include <iostream>
#include <cassert>
#include <vector>

class matrix
{
	private: 
	std::vector<std::vector<int>> contents;
	public:
	unsigned int rows = 0;
	unsigned int columns = 0;

	//for loading with user-defined values
	void SetContents(unsigned int i_rows, unsigned int i_columns)
	{
		contents.clear();	//purge all numbers and reset size of vectors to 0;
		assert(contents.size() == 0);

		rows = i_rows;
		columns = i_columns;
		for(unsigned int i = 0; i < rows; i++)
		{
			contents.push_back(std::vector<int>());	//must create a vector to start filling with values
			for (unsigned int j = 0; j < columns; j++)
			{
				int value = 0;
				std::cout << "Enter a value for row " << i << ", column " << j << ": " << std::endl;	//this is super-inefficient to the user, but it works.
				std::cin >> value;
				contents.at(i).push_back(value);
			}

		}
	}

	//for loading with pre-defined or otherwise imported values
	void SetContents(std::vector<std::vector<int>> n_contents)	// for "New Contents"
	{
		contents.clear();
		rows = n_contents.size();
		if(rows == 0)
		{
			columns = 0;
		}
		else
		{
			columns = n_contents.at(0).size();
		}

		for (unsigned int i = 0; i < rows; i++)
		{
			contents.push_back(std::vector<int>());	//create a row to fill
			for (unsigned int  j = 0; j < columns; j++)
			{
				contents.at(i).push_back(j < columns ? n_contents.at(i).at(j) : 0); //if the current row is shorter than the defined number of columns, fill all remaining values with zero. If the current row is linger than the defined columns, the remaining elements will be ignored
			}
		}
	}
		//print the contents of the matrix to the console
	void ShowContents()
	{
		for(unsigned int i = 0; i < contents.size(); i++)	//auto makes issues. avoid until I've played wit h it in simpler contexts
		{
			for ( unsigned int j = 0; j < contents.at(i).size(); j++)	//auto had issues with "auto j : contents.at(i)" not sure if it was the auto type or determining the length of the element 
			{
				std::cout << contents.at(i).at(j) << " ";	//print one element and a space
			}
			
			std::cout << std::endl;	//start a new line for the next row
		}
	}
	
	//get a vector that contains the contents of the selected row
	std::vector<int> Row(int index)
	{
	
		return contents.at(index);
	}

	//get a vector that contains teh contents of the selected column
	std::vector<int> Column(int index)
	{
		std::vector<int> outvec;
		for(unsigned int i = 0; i < rows; i++)
		{
			outvec.push_back(contents.at(i).at(index));
		}

		return outvec;
	}

	//for use in operator*
	int DotProd(std::vector<int> row, std::vector<int> column)
	{
		int accumulator = 0;
		
		if (row.size() != column.size())
		{
			std::cout << "invalid dimensions, cannot find dot product" << std::endl;
			return accumulator;
		}
		//implicit else
		for (unsigned int i = 0; i < row.size(); i++)	//auto broke things here too?
		{
			accumulator += row.at(i) * column.at(i);
		}
		return accumulator;
	}	


	matrix operator*(matrix mult)
	{
		matrix return_matrix;
		if (columns != mult.rows)
		{
			std::cout << "invalid dimensions, cannot multiply" << std::endl;
			return_matrix.SetContents(contents);
			return return_matrix;
		}
		//implicit else
		std::vector<std::vector<int>> product;
		
		for (unsigned int i = 0; i < rows; i++)
		{
			std::vector<int> n_row;
			for (unsigned int j = 0; j < mult.columns; j++)
			{
				n_row.push_back(DotProd(Row(i), mult.Column(j)));	//takes the dot product of row[i] of the first matrix and column[j] of the second matrix, and adds it to the end of the "New ROW" array for the product matrix
			}

			product.push_back(n_row);	//load new row vector to end of product, n_row should go out of scope and re-set for the next iteration
		}

		
		return_matrix.SetContents(product);
		return return_matrix;

	}

};

void SetMatrix (matrix &M);



int main()
{

	matrix A, B, C;
	char inchar;
	
	while(1)	//get some values for matricies
	{
		std::cout << "Auto-poupulate matricies? (y/n):" <<std::endl;
		std::cin >> inchar;
		if(inchar == 'y' || inchar == 'Y')
		{
			A.SetContents({{1, 2, 3}, {4, 5, 6}});
			B.SetContents({{7, 8}, {9, 10}, {11, 12}});
			break;
		}
		else if(inchar == 'n' || inchar == 'N')
		{
			std::cout << "Matrix A:" << std::endl;
			SetMatrix(A);
			std::cout << "Matrix B:" << std::endl;
			SetMatrix(B);
			break;
		}
	}

	C = A * B;
	
	std::cout << "Matrix A:" << std::endl;
	A.ShowContents();
	std::cout << "Matrix B:" << std::endl;
	B.ShowContents();
	std::cout << "Output Matrix, Matrix C:" << std::endl;
	C.ShowContents();
	return 0;
}



void SetMatrix (matrix &M)
{

	int rows, cols;
	std::cout << "Matrix rows?" << std::endl;
	std::cin >> rows;
	std::cout << "Matrix columns?" << std::endl;
	std::cin >> cols;
	
	M.SetContents(rows, cols);
}
