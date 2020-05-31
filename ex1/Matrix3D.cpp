//================================ Includes =====================================================
#include "Matrix3D.h"
#include <iostream>
//================================ Code Segment =================================================

/**
 * This class represents a three on three dimensional matrix of doubles.
 * We overloaded some mathematical operators for matrices,
 * (such as + - * /), and also implemented some mathematical methods.
 */

///////////////////////////////////////// Constructors: /////////////////////////////////////////

/**
 * This is the default constructor for a matrix which initializes it to the zero matrix.
 */
Matrix3D :: Matrix3D() : Matrix3D(ZERO_MATRIX)
{

}

/**
 * This matrix constructor gets a number and initializes the matrix to the zero matrix, and
 * then initializes the main diagonal to contain the input number.
 * @param num
 */
Matrix3D :: Matrix3D(double num)
{
	_vectorRowsArray[FIRST_ROW] = Vector3D();
	_vectorRowsArray[SECOND_ROW] = Vector3D();
	_vectorRowsArray[THIRD_ROW] = Vector3D();

	_vectorRowsArray[FIRST_ROW][X] = num;
	_vectorRowsArray[SECOND_ROW][Y] = num;
	_vectorRowsArray[THIRD_ROW][Z] = num;
}

/**
 * This matrix constructor gets 9 coordinates' values of the matrix and
 * initialize it with them.
 * @param num1 - value of coordinate 1;
 * @param num2 - value of coordinate 2;
 * @param num3 - value of coordinate 3;
 * @param num4 - value of coordinate 4;
 * @param num5 - value of coordinate 5;
 * @param num6 - value of coordinate 6;
 * @param num7 - value of coordinate 7;
 * @param num8 - value of coordinate 8;
 * @param num9 - value of coordinate 9;
 */
Matrix3D :: Matrix3D(double num1, double num2, double num3, double num4, double num5,
		             double num6, double num7, double num8, double num9) :
		             Matrix3D(Vector3D(num1, num2, num3), Vector3D(num4, num5, num6),
							  Vector3D(num7, num8, num9))
{

}

/**
 * This matrix constructor gets an array of 9 coordinates' values of the matrix and
 * initialize it with them.
 * @param numsArray - the input array of coordinates values.
 */
Matrix3D :: Matrix3D(double numsArray[SIZE_OF_MATRIX]) :
Matrix3D(numsArray[A_COORD], numsArray[B_COORD], numsArray[C_COORD],
		 numsArray[D_COORD], numsArray[E_COORD], numsArray[F_COORD],
		 numsArray[G_COORD], numsArray[H_COORD], numsArray[I_COORD])
{

}

/**
 * This matrix constructor gets an array of arrays of 3 coordinates' values (for each row)
 * of the matrix and initializes it with them.
 * @param nums2DArray - the two dimensional array of rows of matrix.
 */
Matrix3D :: Matrix3D(double nums2DArray[SIZE_OF_VECTOR][SIZE_OF_VECTOR]) :
Matrix3D(Vector3D(nums2DArray[FIRST_ROW]), Vector3D(nums2DArray[SECOND_ROW]),
		Vector3D(nums2DArray[THIRD_ROW]))
{

}

/**
 * This matrix constructor gets 3 row vectors of the matrix and initializes it with them.
 * @param vector1 - row vector 1.
 * @param vector2 - row vector 2.
 * @param vector3 - row vector 3.
 */
Matrix3D :: Matrix3D(Vector3D vector1, Vector3D vector2, Vector3D vector3)
{
	_vectorRowsArray[FIRST_ROW] = vector1;
	_vectorRowsArray[SECOND_ROW] = vector2;
	_vectorRowsArray[THIRD_ROW] = vector3;
}

/////////////////////////////////////////// Methods: ////////////////////////////////////////////

/**
 * This method changes current matrix to be the sum of itself and
 * an input right hand side matrix.
 * @param rhs - the right hand side matrix.
 * @return reference to the current matrix that was calculated.
 */
Matrix3D& Matrix3D :: operator+=(const Matrix3D& rhs)
{

	_vectorRowsArray[FIRST_ROW] += rhs[FIRST_ROW];
	_vectorRowsArray[SECOND_ROW] += rhs[SECOND_ROW];
	_vectorRowsArray[THIRD_ROW] += rhs[THIRD_ROW];

	return *this;
}

/**
 * This method changes current matrix to be the difference between itself and
 * an input right hand side matrix.
 * @param rhs - the right hand side matrix.
 * @return reference to the current matrix that was calculated.
 */
Matrix3D& Matrix3D :: operator-=(const Matrix3D& rhs)
{
	return (*this) += (rhs) * MINUS_ONE;
}

/**
 * This method returns the column vector of the current matrix.
 * @param column - the column index we want.
 * @return the column vector of the current matrix.
 */
Vector3D Matrix3D :: column(const short column) const
{

	Vector3D :: checkIndexOutOfBounds(column, 0, SIZE_OF_VECTOR - 1);

	Vector3D vector3D;

	double coord1 = _vectorRowsArray[FIRST_ROW][column];
	double coord2 = _vectorRowsArray[SECOND_ROW][column];
	double coord3 = _vectorRowsArray[THIRD_ROW][column];

	vector3D = Vector3D(coord1, coord2, coord3);

	return vector3D;
}

/**
 * This method returns the row vector of the current matrix.
 * @param row - the row index we want.
 * @return the row vector of the current matrix.
 */
Vector3D Matrix3D :: row(const short row) const
{

	Vector3D :: checkIndexOutOfBounds(row, 0, SIZE_OF_VECTOR - 1);

	return _vectorRowsArray[row];
}

/**
 * This method changes current matrix to be the multiplication of itself and
 * an input right hand side matrix.
 * @param rhs - the right hand side matrix.
 * @return reference to the current matrix that was calculated.
 */
Matrix3D& Matrix3D :: operator*=(const Matrix3D& rhs)
{

	short row;
	short column;

	Matrix3D tempMatrix = Matrix3D(*this);

	for(row = 0 ; row < SIZE_OF_VECTOR ; row++)
	{
		for(column = 0 ; column < SIZE_OF_VECTOR ; column++)
		{
			_vectorRowsArray[row][column] = (tempMatrix.row(row)) * (rhs.column(column));
		}
	}

	return *this;
}

/**
 * This method calculates the sum of the current matrix and
 * an input right hand side matrix.
 * @param other - the right hand side matrix.
 * @return new matrix which is the sum of the two matrices.
 */
const Matrix3D Matrix3D :: operator+(const Matrix3D& other) const
{
	return Matrix3D(*this) += other;
}

/**
 * This method calculates the difference between the current matrix and
 * an input right hand side matrix.
 * @param other - the right hand side matrix.
 * @return new vector which is the difference between the two matrices.
 */
const Matrix3D Matrix3D :: operator-(const Matrix3D& other) const
{
	return Matrix3D(*this) -= other;
}

/**
 * This method returns a new matrix which is the multiplication of the current matrix and
 * an input right hand side matrix.
 * @param rhs - the right hand side matrix.
 * @return a new matrix which is the multiplication of the two matrices.
 */
const Matrix3D Matrix3D :: operator*(const Matrix3D& other) const
{
	return Matrix3D(*this) *= other;
}

/**
 * This method calculates the multiplication of the current matrix and
 * an input double number, and change the current matrix accordingly.
 * @param num - the number we multiply to the current matrix.
 * @return a reference to the current matrix after the multiplication.
 */
Matrix3D& Matrix3D :: operator*=(double num)
{

	_vectorRowsArray[FIRST_ROW] *= num;
	_vectorRowsArray[SECOND_ROW] *= num;
	_vectorRowsArray[THIRD_ROW] *= num;

	return *this;
}

/**
 * This method calculates the division of the current matrix and
 * an input double number, and change the current matrix accordingly.
 * @param num - the number we divide to the current matrix.
 * @return a reference to the current matrix after the division.
 */
Matrix3D& Matrix3D :: operator/=(double num)
{
	Vector3D :: checkDivisionByZero(num);

	double inverse = ONE / num;
	return (*this) *= inverse;
}

/**
 * This methods calculates and returns a new 3D vector, which is the multiplication of the
 * current matrix and a given input vector.
 * @param vector3D - the vector we multiply the current matrix with.
 * @return a new 3D vector, which is the multiplication of the current matrix and
 * a given input vector.
 */
const Vector3D Matrix3D :: operator*(const Vector3D& vector3D) const
{
	Vector3D result;

	short i;

	for(i = 0 ; i < SIZE_OF_VECTOR ; i++)
	{
		result[i] = _vectorRowsArray[i] * vector3D;
	}

	return result;
}

/**
 * This method is used for reading a matrix coordinates from stdin.
 * @param is - the stream we use.
 * @param matrix3D - the matrix we give values to.
 * @return the stream we use.
 */
std::istream& operator>>(std::istream& is, Matrix3D& matrix3D)
{

	short i;

	for(i = 0 ; i < SIZE_OF_VECTOR ; i++)
	{
		is >> matrix3D._vectorRowsArray[i];
	}

	return is;
}

/**
 * This method is used for printing a matrix to stdout.
 * @param os - the stream we use.
 * @param matrix3D - the matrix we want to print.
 * @return the stream we use.
 */
std::ostream& operator<<(std::ostream& os, const Matrix3D matrix3D)
{

	short i;

	for(i = 0 ; i < SIZE_OF_VECTOR ; i++)
	{
		Vector3D tempVector3D = matrix3D.row(i);
		Vector3D& tempVector3DReference = tempVector3D;
		os << tempVector3DReference;

		if(i != SIZE_OF_VECTOR - 1)
		{
			os << std::endl;
		}
	}

	return os;
}

/**
 * This method is used to permit assignment to a row vector of the current matrix.
 * @param index - the row vector index of the current matrix we want to change its values.
 * @return - reference to the row we want to change its values.
 */
Vector3D& Matrix3D :: operator[] (const short index)
{

	Vector3D :: checkIndexOutOfBounds(index, 0, SIZE_OF_VECTOR - 1);

	return _vectorRowsArray[index];
}

/**
 * This method is used to permit access to a row vector of the current matrix.
 * @param index - the row vector index of the current matrix we want to access its values.
 * @return - reference to the row we want to access its values.
 */
Vector3D Matrix3D :: operator[] (const short index) const
{

	Vector3D :: checkIndexOutOfBounds(index, 0, SIZE_OF_VECTOR - 1);

	return _vectorRowsArray[index];
}

/**
 * This method calculates the trace of the current matrix.
 * @return the trace of the current matrix.
 */
double Matrix3D :: trace() const
{
	return _vectorRowsArray[FIRST_ROW][FIRST_COLUMN] + _vectorRowsArray[SECOND_ROW][SECOND_COLUMN]
	+ _vectorRowsArray[THIRD_ROW][THIRD_COLUMN];
}

/**
 * This method calculates the determinant of the current matrix.
 * @return the determinant of the current matrix.
 */
double Matrix3D :: determinant() const
{
	double a = _vectorRowsArray[FIRST_ROW][FIRST_COLUMN];
	double b = _vectorRowsArray[FIRST_ROW][SECOND_COLUMN];
	double c = _vectorRowsArray[FIRST_ROW][THIRD_COLUMN];
	double d = _vectorRowsArray[SECOND_ROW][FIRST_COLUMN];
	double e = _vectorRowsArray[SECOND_ROW][SECOND_COLUMN];
	double f = _vectorRowsArray[SECOND_ROW][THIRD_COLUMN];
	double g = _vectorRowsArray[THIRD_ROW][FIRST_COLUMN];
	double h = _vectorRowsArray[THIRD_ROW][SECOND_COLUMN];
	double i = _vectorRowsArray[THIRD_ROW][THIRD_COLUMN];

	return (a * (e * i - f * h)) - (b * (d * i - f * g)) + (c * (d * h - e * g));
}
