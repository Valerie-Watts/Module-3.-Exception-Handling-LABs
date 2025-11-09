#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <fstream>

class Matrix
{
private:
	int rows = 2, columns = 2;
	std::vector<std::vector<float>> Vmatrix;

public:

	Matrix() : Vmatrix(2, std::vector<float>(2, 0)) {}

	void loadFromFile(std::string filename) 
	{
		std::ifstream file(filename);
		if (!file.is_open()) {
			throw std::runtime_error("File not found at: " + filename);
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (!(file >> Vmatrix[i][j])) {
					throw std::runtime_error("File not found at: " + filename);
				}
			}
		}
		file.close();
	}

	void saveToFile(std::string filename) 
	{
		std::ofstream file(filename);
		if (!file.is_open()) {
			
			throw std::runtime_error("No rights to write to file: " + filename);
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				file << Vmatrix[i][j] << " ";
			}
			file << "\n";
		}
		file.close();
	}

	void print()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				std::cout << Vmatrix[i][j] << " ";
			}

			std::cout << "\n";
		}
	}
};



int main()
{
	Matrix m; 

	try
	{
		m.loadFromFile("nonexistent.txt");
		
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << "\n";
	}

	try
	{
		m.saveToFile("C:\\Windows\\test.txt");

	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << "\n";
	}

	

	return 0; 
}
