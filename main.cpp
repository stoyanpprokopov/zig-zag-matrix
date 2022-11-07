#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> VecInt;
typedef std::vector<VecInt> VecVecInt;

// never ever have I seen "enum class" declaration
// compiler is complaining though
enum class EDirection {
	DOWN = 0,
	RIGHT = 1,
};

// Print a single vector of ints
void PrintVector(const VecInt& input) 
{
	for (unsigned int i = 0; i < input.size(); i++) 
	{
		printf("%d ", input[i]);
	}
}

// Print in a zig zag manner, direction dictates whether the 
// next vector after the first will be reversed
// reverses on DOWN, prints same order on RIGHT
void PrintZigZag(VecVecInt& input, EDirection direction) 
{
	int count = input.size();

	if (count == 0) {
		printf("Empty input!\n");
		return;
	}

	// print first element, direction logic is irrelevant
	PrintVector(input[0]);

	for (int i = 1; i < count; i++) {
		if (direction == EDirection::RIGHT) {
			PrintVector(input[i]);
			direction = EDirection::DOWN;
		}
		else {
			std::reverse(input[i].begin(), input[i].end());
			PrintVector(input[i]);
			direction = EDirection::RIGHT;
		}
	}

	printf("\n\n\n\n");
}

VecVecInt GetDiagonals(VecVecInt& input) 
{
	VecVecInt result;
	VecInt diag;

	if (input.size() == 0) {
		return result;
	}

	if (input.size() == 1) {
		result.push_back({ input[0] });
		return result;
	}

	int rows = input.size();
	int columns = input[0].size();

	// grab diagonals starting from top left
	for (int j = 0; j < columns; j++)
	{
		if (j == 0)
		{
			// grab top left element, nothing else to do here
			result.push_back({ input[0][j] });
			continue;
		}

		diag.clear();
		for (int i = 0, k = j; i < rows && k >= 0; i++, k--) 
		{
			diag.push_back(input[i][k]);
		}
		result.push_back(diag);
	}

	// grab remaining diagonals on the bottom right
	for (int i = 1; i < rows; i++)
	{
		if (i == (rows - 1)) {
			// this the bottom right end of the 2d array
			// grab the value and break
			result.push_back({ input[i][columns - 1] });
			break;
		}

		diag.clear();
		for (int j = columns - 1, k = i; j >= 0 && k < rows; j--, k++)
		{
			diag.push_back(input[k][j]);
		}
		result.push_back(diag);
	}

	return result;
}

int main()
{
	VecVecInt input = { { 1, 3, 4},
						{ 2, 5, 8},
						{ 6, 7, 9}, };
						//{ 2, 2, 2},
						//{ 1, 1, 1} };

	/*
	VecVecInt input = { { 1, 3, 4, 4, 4},
						{ 2, 5, 8, 8, 8},
						{ 6, 7, 9, 9, 9}, };

	VecVecInt input = { { 1 } };
	*/

	VecVecInt diagonals = GetDiagonals(input);

	PrintZigZag(diagonals, EDirection::DOWN);
	
	return 0;
}
