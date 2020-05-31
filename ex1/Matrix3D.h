//================================ Includes =====================================================
#include <iostream>
#include "Vector3D.h"
//================================ Constants ====================================================
#ifndef CPP_MATRIX3D_H
#define CPP_MATRIX3D_H
#define SIZE_OF_MATRIX 9
#define FIRST_ROW 0
#define SECOND_ROW 1
#define THIRD_ROW 2
#define A_COORD 0
#define B_COORD 1
#define C_COORD 2
#define D_COORD 3
#define E_COORD 4
#define F_COORD 5
#define G_COORD 6
#define H_COORD 7
#define I_COORD 8
#define FIRST_COLUMN 0
#define SECOND_COLUMN 1
#define THIRD_COLUMN 2
#define ZERO_MATRIX 0, 0, 0, 0, 0, 0, 0, 0, 0
//================================ Code Segment =================================================

/**
 * This class represents a three on three dimensional matrix of doubles.
 * We overloaded some mathematical operators for matrices,
 * (such as + - * /), and also implemented some mathematical methods.
 */
class Matrix3D
{

public:

///////////////////////////////////////// Constructors: /////////////////////////////////////////

	/**
	 * This is the default constructor for a matrix which initializes it to the zero matrix.
	 */
	Matrix3D();

	/**
	 * This matrix constructor gets a number and initializes the matrix to the zero matrix, and
	 * then initializes the main diagonal to contain the input number.
	 * @param num
	 */
	Matrix3D(double num);

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
	Matrix3D(double num1, double num2, double num3, double num4, double num5, double num6,
			 double num7, double num8, double num9);

	/**
	 * This matrix constructor gets an array of 9 coordinates' values of the matrix and
	 * initialize it with them.
	 * @param numsArray - the input array of coordinates values.
	 */
	Matrix3D(double numsArray[SIZE_OF_MATRIX]);

	/**
	 * This matrix constructor gets an array of arrays of 3 coordinates' values (for each row)
	 * of the matrix and initializes it with them.
	 * @param nums2DArray - the two dimensional array of rows of matrix.
	 */
	Matrix3D(double nums2DArray[SIZE_OF_VECTOR][SIZE_OF_VECTOR]);

	/**
	 * This matrix constructor gets 3 row vectors of the matrix and initializes it with them.
	 * @param vector1 - row vector 1.
	 * @param vector2 - row vector 2.
	 * @param vector3 - row vector 3.
	 */
	Matrix3D(Vector3D vector1, Vector3D vector2, Vector3D vector3);

/////////////////////////////////////////// Methods: ////////////////////////////////////////////

	/**
	 * This method changes current matrix to be the sum of itself and
	 * an input right hand side matrix.
	 * @param rhs - the right hand side matrix.
	 * @return reference to the current matrix that was calculated.
	 */
	Matrix3D& operator+=(const Matrix3D& rhs);

	/**
	 * This method changes current matrix to be the difference between itself and
	 * an input right hand side matrix.
	 * @param rhs - the right hand side matrix.
	 * @return reference to the current matrix that was calculated.
	 */
	Matrix3D& operator-=(const Matrix3D& rhs);

	/**
	 * This method changes current matrix to be the multiplication of itself and
	 * an input right hand side matrix.
	 * @param rhs - the right hand side matrix.
	 * @return reference to the current matrix that was calculated.
	 */
	Matrix3D& operator*=(const Matrix3D& rhs);

	/**
	 * This method returns the column vector of the current matrix.
	 * @param column - the column index we want.
	 * @return the column vector of the current matrix.
	 */
	Vector3D column(const short column) const;

	/**
	 * This method returns the row vector of the current matrix.
	 * @param row - the row index we want.
	 * @return the row vector of the current matrix.
	 */
	Vector3D row(const short row) const;

	/**
	 * This method calculates the sum of the current matrix and
	 * an input right hand side matrix.
	 * @param other - the right hand side matrix.
	 * @return new matrix which is the sum of the two matrices.
	 */
	const Matrix3D operator+(const Matrix3D& other) const;

	/**
	 * This method calculates the difference between the current matrix and
	 * an input right hand side matrix.
	 * @param other - the right hand side matrix.
	 * @return new vector which is the difference between the two matrices.
	 */
	const Matrix3D operator-(const Matrix3D& other) const;

	/**
	 * This method returns a new matrix which is the multiplication of the current matrix and
	 * an input right hand side matrix.
	 * @param rhs - the right hand side matrix.
	 * @return a new matrix which is the multiplication of the two matrices.
	 */
	const Matrix3D operator*(const Matrix3D& other) const;

	/**
	 * This method calculates the multiplication of the current matrix and
	 * an input double number, and change the current matrix accordingly.
	 * @param num - the number we multiply to the current matrix.
	 * @return a reference to the current matrix after the multiplication.
	 */
	Matrix3D& operator*=(double num);

	/**
	 * This method calculates the division of the current matrix and
	 * an input double number, and change the current matrix accordingly.
	 * @param num - the number we divide to the current matrix.
	 * @return a reference to the current matrix after the division.
	 */
	Matrix3D& operator/=(double num);

	/**
	 * This methods calculates and returns a new 3D vector, which is the multiplication of the
	 * current matrix and a given input vector.
	 * @param vector3D - the vector we multiply the current matrix with.
	 * @return a new 3D vector, which is the multiplication of the current matrix and
	 * a given input vector.
	 */
	const Vector3D operator*(const Vector3D& vector3D) const;

	/**
	 * This method is used for reading a matrix coordinates from stdin.
	 * @param is - the stream we use.
	 * @param matrix3D - the matrix we give values to.
	 * @return the stream we use.
	 */
	friend std::istream& operator>>(std::istream& is, Matrix3D& matrix3D);

	/**
	 * This method is used for printing a matrix to stdout.
	 * @param os - the stream we use.
	 * @param matrix3D - the matrix we want to print.
	 * @return the stream we use.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Matrix3D matrix3D);

	/**
	 * This method is used to permit assignment to a row vector of the current matrix.
	 * @param index - the row vector index of the current matrix we want to change its values.
	 * @return - reference to the row we want to change its values.
	 */
	Vector3D& operator[] (const short index);

	/**
	 * This method is used to permit access to a row vector of the current matrix.
	 * @param index - the row vector index of the current matrix we want to access its values.
	 * @return - reference to the row we want to access its values.
	 */
	Vector3D operator[] (const short index) const;

	/**
	 * This method calculates the trace of the current matrix.
	 * @return the trace of the current matrix.
	 */
	double trace() const;

	/**
	 * This method calculates the determinant of the current matrix.
	 * @return the determinant of the current matrix.
	 */
	double determinant() const;

private:

	/**
	 * This field represents the array of the row vectors of the matrix.
	 */
	Vector3D _vectorRowsArray[SIZE_OF_VECTOR];
};

#endif //CPP_MATRIX3D_H
