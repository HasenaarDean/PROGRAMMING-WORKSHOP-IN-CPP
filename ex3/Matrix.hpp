//================================ Includes =====================================================
#include "Complex.h"
#include <iostream>
#include <vector>
//================================ Constants ====================================================
#ifndef CPP3_MATRIX_H
#define CPP3_MATRIX_H
#define BASIC_MATRIX_DIMENSION 1
#define BASIC_MATRIX_VALUE 0
#define SEPARATOR_OF_A_TAB '\t'
#define INVALID_MULTIPLICATION_OF_MATRICES_ERROR "Invalid multiplication of matrices!"
#define INCOMPATIBLE_DIMENSIONS_OF_MATRICES_ERROR "The matrices dimensions are not compatible"
#define CAN_NOT_TRANSPOSE_MATRIX_ERROR "This matrix is not squared and thus cannot be transposed"
#define INDEX_OUT_OF_BOUNDS_ERROR "Index out of bounds error!"
#define INVALID_ARGUMENT_ERROR "The number of rows and columns should be both positive"
//================================ Code Segment =================================================

/**
 * This class represents a generic matrix. For example, we implemented
 * arithmetic operations on matrices.
 * @tparam T - the generic type of a coordinate in the generic matrix.
 * We have an assumption of the type T that it is printable and arithmetic operations
 * can be done on it.
 */
template <class T> class Matrix
{
	public:

	/**
	 * This type represents a constant iterator for a generic matrix.
	 */
	typedef typename std::vector<T> :: const_iterator const_iterator;

	/**
	 * This is the default constructor which initializes a one-on-one matrix of zeros.
	 */
	Matrix() : _numOfRows(BASIC_MATRIX_DIMENSION), _numOfCols(BASIC_MATRIX_DIMENSION),
	_vectorMatrix(BASIC_MATRIX_DIMENSION, T(BASIC_MATRIX_VALUE))
	{

	}

	/**
	 * This constructor initializes a generic matrix of zeros in size of rows * cols.
	 * @param rows - number of rows in the matrix.
	 * @param cols - number of columns in the matrix.
	 * @throw: invalid argument error if not positive.
	 */
	Matrix(unsigned int rows, unsigned int cols) : _numOfRows(rows), _numOfCols(cols),
	_vectorMatrix(cols * rows, T(BASIC_MATRIX_VALUE))
	{
		checkPositiveRowAndColNumber();
	}

	/**
	 * This constructor is a copy constructor which copies values from matrix m.
	 * @param m - the input generic matrix that we copy from.
	 */
	Matrix(const Matrix& m) : _numOfRows(m._numOfRows), _numOfCols(m._numOfCols),
	_vectorMatrix(m._vectorMatrix)
	{

	}

	/**
	 * This constructor initializes a generic matrix with values in the generic vector.
	 * @param rows - number of rows in the matrix.
	 * @param cols - number of columns in the matrix.
	 * @param cells - the generic vector that we copy from.
	 * @throw: invalid argument error if not positive.
	 */
	Matrix(unsigned int rows, unsigned int cols, const std :: vector<T>& cells) :
	_numOfRows(rows), _numOfCols(cols), _vectorMatrix(cells)
	{
		checkPositiveRowAndColNumber();
	}

	/**
	 * This destructor is a default destructor for the generic matrix.
	 */
	~Matrix() = default;

	/**
	 * This method checks if the mtrix dimensions are positive.
	 * @throw: invalid argument error if not positive.
	 */
	void checkPositiveRowAndColNumber()
	{
		if(!((int)_numOfCols > 0 && (int)_numOfRows > 0))
		{
			throw std :: invalid_argument(INVALID_ARGUMENT_ERROR);
		}
	}

	/**
	 * This method returns number of rows in the matrix.
	 * @return number of rows in the matrix.
	 */
	unsigned int rows() const
	{
		return _numOfRows;
	}

	/**
	 * This method returns number of columns in the matrix.
	 * @return number of columns in the matrix.
	 */
	unsigned int cols() const
	{
		return _numOfCols;
	}

	/**
	 * This method is the assign operator for a generic matrix.
	 * @param m - the generic matrix we copy from.
	 * @return - a reference to the new matrix.
	 */
	Matrix& operator=(const Matrix& m)
	{
		if(&m == this)
		{
			return *(this);
		}
		else
		{
			_numOfRows = m._numOfRows;
			_numOfCols = m._numOfCols;
			_vectorMatrix = m._vectorMatrix;
			return *(this);
		}
	}

	/**
	 * This method checks if the matrices dimensions suit each other.
	 * @param m - the right other matrix.
	 * @throw logic error exception if the matrices dimensions do not suit each other.
	 */
	void checkMatrixDimensions(const Matrix& m) const
	{
		if(_numOfCols != m._numOfCols || _numOfRows != m._numOfRows)
		{
			throw std :: logic_error(INCOMPATIBLE_DIMENSIONS_OF_MATRICES_ERROR);
		}
	}

	/**
	 * This method adds two generic matrices.
	 * @param m - the right hand side matrix.
	 * @return addition of two generic matrices.
	 * @throw logic error exception if the matrices dimensions do not suit each other.
	 */
	Matrix operator+(const Matrix& m) const
	{

		checkMatrixDimensions(m);

		Matrix result(*this);
		for(unsigned int matrixIndex = 0 ; matrixIndex < _vectorMatrix.size() ; ++matrixIndex)
		{
			result._vectorMatrix[matrixIndex] += m._vectorMatrix[matrixIndex];
		}
		return result;
	}

	/**
	 * This method subtract two generic matrices.
	 * @param m - the right hand side matrix.
	 * @return subtraction of two generic matrices.
	 * @throw logic error exception if the matrices dimensions do not suit each other.
	 */
	Matrix operator-(const Matrix& m) const
	{

		checkMatrixDimensions(m);

		Matrix result(*this);
		for(int matrixIndex = 0 ; matrixIndex < _vectorMatrix.size() ; ++matrixIndex)
		{
			result._vectorMatrix[matrixIndex] -= m._vectorMatrix[matrixIndex];
		}
		return result;
	}

	/**
	 * This method checks validity of matrices multiplication.
	 * @param m - the right hand side matrix.
	 * @throw logic error of incompatible matrices dimensions.
	 */
	void checkValidityOfMatricesMultiplication(const  Matrix& m) const
	{
		if(m._numOfRows != _numOfCols)
		{
			throw std :: logic_error(INVALID_MULTIPLICATION_OF_MATRICES_ERROR);
		}
	}

	/**
	 * This method multiply two generic matrices.
	 * @param m - the right hand side matrix.
	 * @return multiplication of two generic matrices.
	 * @throw logic error of incompatible matrices dimensions.
	 */
	Matrix operator*(const  Matrix& m) const
	{
		checkValidityOfMatricesMultiplication(m);

		T calculateCoord = T(0);

		Matrix result(_numOfRows, m._numOfCols);

		for(unsigned int col = 0 ; col < m._numOfCols ; ++col)
		{
			for(unsigned int row = 0 ; row < _numOfRows ; ++row)
			{
				for(unsigned int i = 0 ; i < _numOfCols ; ++i)
				{

					calculateCoord += m(i, col) * (*this)(row, i);
				}
				result(row, col) = calculateCoord;
				calculateCoord = T(0);
			}
		}
		return result;
	}

	/**
	 * This method compares between two matrices.
	 * @param m - the right hand side matrix.
	 * @return true if the two matrices are equal, false otherwise.
	 */
	bool operator==(const Matrix& m) const
	{
		if(_numOfCols != m._numOfCols || _numOfRows != m._numOfRows)
		{
			return false;
		}

		return _vectorMatrix == m._vectorMatrix;

	}

	/**
	 * This method compares between two matrices.
	 * @param m - the right hand side matrix.
	 * @return true if the two matrices are not equal, false otherwise.
	 */
	bool operator!=(const Matrix& m) const
	{
		return !(m == (*this));
	}

	/**
	 * This method checks if a given matrix is a square matrix.
	 * @return true if a given matrix is a square matrix, false otherwise.
	 */
	bool isSquareMatrix() const
	{
		return (_numOfCols == _numOfRows);
	}

	/**
	 * This method checks if a given matrix can be transposed.
	 * @throw logic error of untransposable matrix exception.
	 */
	void checkTranspose() const
	{
		if(!((*this).isSquareMatrix()))
		{
			throw std :: logic_error(CAN_NOT_TRANSPOSE_MATRIX_ERROR);
		}
	}

	/**
	 * This method transposes a generic matrix.
	 * @return the transposed matrix.
	 * @throw logic error of untransposable matrix exception.
	 */
	Matrix trans() const
	{
		checkTranspose();

		unsigned int transSize = _numOfCols;

		Matrix result(transSize, transSize);

		for(int col = 0 ; col < transSize ; ++col)
		{
			for(int row = 0 ; row < transSize ; ++row)
			{
				result(col, row) = (*this)(row, col);
			}
		}

		return result;

	}

	/**
	 * This method checks index out of bounds exception for accessing a matrix coordinate.
	 * @param row - the coordinate row
	 * @param column - the coordinate column
	 * @throw out of range exception of index out of bounds.
	 */
	void checkIndexOutOfBounds(const unsigned int row, const unsigned int column) const
	{
		if(!(column < _numOfCols && row < _numOfRows))
		{
			throw std :: out_of_range(INDEX_OUT_OF_BOUNDS_ERROR);
		}
	}

	/**
	 * This method accesses a matrix coordinate.
	 * @param row - the coordinate row
	 * @param column - the coordinate column
	 * @return matrix coordinate (row, column).
	 * @throw out of range exception of index out of bounds.
	 */
	T const operator()(const unsigned int row, const unsigned int column) const
	{
		checkIndexOutOfBounds(row, column);

		return _vectorMatrix[column + _numOfCols * row];
	}

	/**
	 * This method accesses a matrix coordinate.
	 * @param row - the coordinate row
	 * @param column - the coordinate column
	 * @return matrix coordinate (row, column).
	 * @throw out of range exception of index out of bounds.
	 */
	T& operator()(const unsigned int row, const unsigned int column)
	{
		checkIndexOutOfBounds(row, column);

		return _vectorMatrix[column + _numOfCols * row];
	}

	/**
	 * This method prints a generic matrix.
	 * @param os - the output stream reference.
	 * @param m - the matrix we want to print.
	 * @return the output stream reference.
	 */
	friend std :: ostream& operator<<(std :: ostream& os, const Matrix& m)
	{
		for(unsigned int row = 0 ; row < m._numOfRows ; ++row)
		{
			for(unsigned int col = 0 ; col < m._numOfCols ; ++col)
			{
				os << m(row, col);
				os << SEPARATOR_OF_A_TAB;
			}

			os << std :: endl;

		}

		return os;

	}

	/**
	 * This method iterates over a generic matrix.
	 * @return generic matrix iterator.
	 */
	const_iterator begin() const
	{

		return _vectorMatrix.cbegin();

	}

	/**
	 * This method returns the address after the last cell of a given generic matrix.
	 * @return the address after the last cell of a given generic matrix.
	 */
	const_iterator end() const
	{

		return _vectorMatrix.cend();

	}

	private:

	/**
	 * Number of rows in the generic matrix.
	 */
	unsigned int _numOfRows;

	/**
	 * Number of columns in the generic matrix.
	 */
	unsigned int _numOfCols;

	/**
	 * The generic matrix values are stored in a generic vector.
	 */
	std :: vector<T> _vectorMatrix;

};

/**
 * This method is a specialization of the trans method for a complex numbers matrix.
 * It calculates the Hermitian matrix of a complex numbers matrix.
 * @return the Hermitian matrix of a complex numbers matrix.
 * @throw logic error of untransposable matrix exception.
 */
template <> Matrix<Complex> Matrix<Complex> :: trans() const
{
	checkTranspose();

	unsigned int transSize = this->_numOfRows;

	Matrix<Complex> result(transSize, transSize);

	for(unsigned int col = 0 ; col < transSize ; ++col)
	{
		for(unsigned int row = 0 ; row < transSize ; ++row)
		{
			Complex tempComplex = (*this)(row, col).conj();
			result(col, row) = tempComplex;
		}
	}

	return result;

}

#endif
