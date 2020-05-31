//================================ Includes =====================================================
#include <string>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <chrono>
#include "Complex.h"
#include "Matrix.hpp"
#include <eigen3/Eigen/Dense>
//================================ Constants ====================================================
#define MAX_SIZE_OF_SQUARED_MATRIX 500
#define MIN_SIZE_OF_SQUARED_MATRIX 1
#define NUM_OF_ARGS 2
#define INDEX_OF_SIZE_OF_MATRIX_ARGUMENT 1
#define TESTED_MATRIX_CELL_VALUE 1
#define OUT_OF_RANGE_SIZE_USAGE_ERROR "Usage: size of matrix should be an int in range 1 to 500"
#define WRONG_NUMBER_OF_ARGS_USAGE_ERROR "Usage: One positive int is required (size of matrix)"
#define PRINT_SIZE_TITLE "size "
#define PRINT_EIGEN_MULT_TITLE "eigen mult "
#define PRINT_EIGEN_ADD_TITLE "eigen add "
#define PRINT_MATLIB_MULT_TITLE "matlib mult "
#define PRINT_MATLIB_ADD_TITLE "matlib add "
//================================ Code Segment =================================================

/**
 * This file measures the running time of our program.
 * It measures the running time of doing arithmetic operations with our matrix library,
 * and with the built-in matrix library.
 */

/**
 * This is the main function of our program. It measures the running time of doing
 * arithmetic operations with our matrix library, and with the built-in matrix library.
 * @param argc - the number of input arguments for our program.
 * @param argv - the values of the input arguments for our program (the matrix size).
 * @return 0 if succeeds, non-zero otherwise.
 * @throw invalid argument error if not positive.
 * @throw out of range exception if the matrices dimensions do not suit each other.
 * @throw logic error of incompatible matrices dimensions.
 * @throw logic error of untransposable matrix exception.
 * @throw out of range exception of index out of bounds.
 */
int main(int argc, char *argv[])
{
	//check validity of number of input arguments and then check validity of range of size
	if (argc != NUM_OF_ARGS)
	{
		std::cerr << WRONG_NUMBER_OF_ARGS_USAGE_ERROR << std::endl;
		exit(EXIT_FAILURE);
	}
	if(argc > MAX_SIZE_OF_SQUARED_MATRIX || argc < MIN_SIZE_OF_SQUARED_MATRIX)
	{
		std::cerr << OUT_OF_RANGE_SIZE_USAGE_ERROR << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string matrixSizeString(argv[INDEX_OF_SIZE_OF_MATRIX_ARGUMENT]);
	unsigned int matrixSize = (unsigned int) std::stoi(argv[1]);
	std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;
	Eigen :: MatrixXd eigenMatrixA = Eigen :: MatrixXd :: Random(matrixSize, matrixSize);
	Eigen :: MatrixXd eigenMatrixB = Eigen :: MatrixXd :: Random(matrixSize, matrixSize);
	Eigen :: MatrixXd eigenMatrixMultiplicationResult;
	Eigen :: MatrixXd eigenMatrixAdditionResult;
	std::cout << PRINT_SIZE_TITLE << matrixSize << std :: endl;
	//measure running time of Eigen matrix multiplication:
	tictoc_stack.push(std::chrono::system_clock::now());
	eigenMatrixMultiplicationResult = eigenMatrixA * eigenMatrixB;
	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() -
													tictoc_stack.top();
	std::cout << PRINT_EIGEN_MULT_TITLE << elapsed_seconds.count() << std :: endl;
	tictoc_stack.pop();
	//measure running time of Eigen matrix addition:
	tictoc_stack.push(std::chrono::system_clock::now());
	eigenMatrixAdditionResult = eigenMatrixA + eigenMatrixB;
	elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
	std::cout << PRINT_EIGEN_ADD_TITLE << elapsed_seconds.count() << std :: endl;
	tictoc_stack.pop();
	//create matlib matrices:
	Matrix<int> myOneMatrix(matrixSize, matrixSize,
			             std::vector<int>(matrixSize * matrixSize, TESTED_MATRIX_CELL_VALUE));
	Matrix<int> multiplyOneMatrix, addOneMatrix;
	//measure running time of Matlib matrix multiplication:
	tictoc_stack.push(std::chrono::system_clock::now());
	multiplyOneMatrix = myOneMatrix * myOneMatrix;
	elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
	std::cout << PRINT_MATLIB_MULT_TITLE << elapsed_seconds.count() << std :: endl;
	tictoc_stack.pop();
	//measure running time of Matlib matrix addition:
	tictoc_stack.push(std::chrono::system_clock::now());
	addOneMatrix = myOneMatrix + myOneMatrix;
	elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
	std::cout << PRINT_MATLIB_ADD_TITLE << elapsed_seconds.count() << std :: endl;
	tictoc_stack.pop();
	return 0;
}