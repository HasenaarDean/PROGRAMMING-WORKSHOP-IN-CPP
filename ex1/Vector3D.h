//================================ Includes =====================================================
#include <iostream>
#include <math.h>
//================================ Constants ====================================================
#ifndef CPP_VECTOR3D_H
#define CPP_VECTOR3D_H
#define SIZE_OF_VECTOR 3
#define X 0
#define Y 1
#define Z 2
#define ZERO_VECTOR 0, 0, 0
#define ONE 1.0
#define MINUS_ONE -1.0
#define ZERO_RADIANS 0
#define SPACE " "
#define DIVISION_BY_ZERO_ERROR "Error: Division by zero!"
#define INDEX_OUT_OF_BOUNDS_ERROR "Error: Index out of bounds!"
//================================ Code Segment =================================================

/**
 * This class represents a three dimensional vector of doubles.
 * We overloaded some mathematical operators for vectors,
 * (such as + - * /), and also implemented some mathematical methods.
 */
class Vector3D
{

public:

///////////////////////////////////////// Constructors: /////////////////////////////////////////

	/**
	 * This is the default constructor for a vector which initializes it to the zero vector.
	 */
	Vector3D();

	/**
	 * This vector constructor gets three doubles: x, y, z coordinates.
	 * @param x - coordinate x.
	 * @param y - coordinate y.
	 * @param z - coordinate z.
	 */
	Vector3D(double x, double y, double z);

	/**
	 * This vector constructor gets an array of three doubles: x, y, z coordinates.
	 * @param vectorCoordinates - the array of three doubles.
	 */
	Vector3D(double vectorCoordinates[SIZE_OF_VECTOR]);

/////////////////////////////////////////// Methods: ////////////////////////////////////////////

	/**
	 * This method changes current vector to be the sum of itself and
	 * an input right hand side vector.
	 * @param rhs - the right hand side vector.
	 * @return reference to the current vector that was calculated.
	 */
	Vector3D& operator+=(const Vector3D& rhs);

	/**
	 * This method changes current vector to be the sum of itself and
	 * an input right hand side number.
	 * @param num - the number we add to the current vector.
	 * @return reference to the current vector that was calculated.
	 */
	Vector3D& operator+=(double num);

	/**
	 * This method changes current vector to be the difference of itself and
	 * an input right hand side vector.
	 * @param rhs - the right hand side vector.
	 * @return reference to the current vector that was calculated.
	 */
	Vector3D& operator-=(const Vector3D& rhs);

	/**
	 * This method changes current vector to be the difference between itself and
	 * an input right hand side number.
	 * @param num - the number we subtract to the current vector.
	 * @return reference to the current vector that was calculated.
	 */
	Vector3D& operator-=(double num);

	/**
	 * This method changes current vector to be the multiplication of itself and
	 * an input right hand side number.
	 * @param num - the number we multiply to the current vector.
	 * @return reference to the current vector that was calculated.
	 */
	Vector3D& operator*=(double num);

	/**
	 * This method changes current vector to be the division of itself and
	 * an input right hand side number.
	 * @param num - the number we divide to the current vector.
	 * @return reference to the current vector that was calculated.
	 */
	Vector3D& operator/=(double num);

	/**
	 * This method calculates the negative vector of a given vector.
	 * @return the negative vector of a given vector.
	 */
	Vector3D operator-() const;

	/**
	 * This method calculates the sum of the current vector and
	 * an input right hand side vector.
	 * @param other - the right hand side vector.
	 * @return new vector which is the sum of the two vectors.
	 */
	const Vector3D operator+(const Vector3D& other) const;

	/**
	 * This method calculates the distance between the current vector and
	 * an input right hand side vector.
	 * @param other - the right hand side vector.
	 * @return the distance between the vectors.
	 */
	const double operator|(const Vector3D& other) const;

	/**
	 * This method calculates the angle between the current vector and
	 * an input right hand side vector.
	 * @param other - the right hand side vector.
	 * @return the angle between the vectors.
	 */
	const double operator^(const Vector3D& other) const;

	/**
	 * This method calculates the multiplication of the current vector and
	 * an input right hand side vector.
	 * @param other - the right hand side vector.
	 * @return new double which is the scalar multiplication of the two vectors.
	 */
	const double operator*(const Vector3D& other) const;

	/**
	 * This method calculates the difference between the current vector and
	 * an input right hand side vector.
	 * @param other - the right hand side vector.
	 * @return new vector which is the difference between the two vectors.
	 */
	const Vector3D operator-(const Vector3D& other) const;

	/**
	 * This method calculates the multiplication of the current vector and
	 * an input double number.
	 * @param num - the number we multiply to the current vector.
	 * @return new vector which is the multiplication of the vector and the number.
	 */
	const Vector3D operator*(double num) const;

	/**
	 * This method calculates the division of the current vector and
	 * an input double number.
	 * @param num - the number we divide to the current vector.
	 * @return new vector which is the division of the vector and the number.
	 */
	const Vector3D operator/(double num) const;

	/**
	 * This method calculates the multiplication of the current vector and
	 * an input double number (in opposite given order).
	 * @param num - the number we multiply to the current vector.
	 * @return new vector which is the multiplication of the vector and the number.
	 */
	friend const Vector3D operator*(const double num, const Vector3D& rhs);

	/**
	 * This method is used to permit assignment to a coordinate of the current vector.
	 * @param index - the coordinate of the current vector we want to change its value.
	 * @return - reference to the coordinate we want to change its value.
	 */
	double& operator[] (const short index);

	/**
	 * This method is used to permit access to a coordinate of the current vector.
	 * @param index - the coordinate of the current vector we want to access its value.
	 * @return - reference to the coordinate we want to access its value.
	 */
	const double& operator[] (const short index) const;

	/**
	 * This method calculates the Euclidean norm of the current vector.
	 * @return the Euclidean norm of the current vector.
	 */
	double norm() const;

	/**
	 * This method calculates the distance between the current vector and another input vector.
	 * @return the distance between the current vector and another input vector.
	 */
	double dist(const Vector3D& other) const;

	/**
	 * This method is used for reading a vector coordinates from stdin.
	 * @param is - the stream we use.
	 * @param vector3D - the vector we give values to.
	 * @return the stream we use.
	 */
	friend std::istream& operator>>(std::istream& is, Vector3D& vector3D);

	/**
	 * This method is used for printing a vector to stdout.
	 * @param os - the stream we use.
	 * @param vector3D - the vector we want to print.
	 * @return the stream we use.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Vector3D vector3D);

	/**
	 * This method checks if we divide a vector by zero or not.
	 * If so: exit program with exit failure.
	 * @param num - the number we divide with.
	 */
	static void checkDivisionByZero(const double num);

	/**
	 * This method checks Index out of bounds error for accessing vector values.
	 * If so: exit program with exit failure.
	 * @param index - the index we access with.
	 */
	static void checkIndexOutOfBounds(const short index, const short begin, const short end);

private:

	/**
	 * This field represents the coordinates (x, y, z) double array to store
	 * vector coordinates values.
	 */
	double _coords[SIZE_OF_VECTOR];
};


#endif //CPP_VECTOR3D_H
