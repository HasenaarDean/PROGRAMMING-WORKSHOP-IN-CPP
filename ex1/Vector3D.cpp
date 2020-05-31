//================================ Includes =====================================================
#include "Vector3D.h"
//================================ Code Segment =================================================

/**
 * This class represents a three dimensional vector of doubles.
 * We overloaded some mathematical operators for vectors,
 * (such as + - * /), and also implemented some mathematical methods.
 */

///////////////////////////////////////// Constructors: /////////////////////////////////////////

/**
 * This is the default constructor for a vector which initializes it to the zero vector.
 */
Vector3D :: Vector3D() : Vector3D(ZERO_VECTOR)
{

}

/**
 * This vector constructor gets three doubles: x, y, z coordinates.
 * @param x - coordinate x.
 * @param y - coordinate y.
 * @param z - coordinate z.
 */
Vector3D :: Vector3D(double x, double y, double z)
{
	_coords[X] = x;
	_coords[Y] = y;
	_coords[Z] = z;
}

/**
 * This vector constructor gets an array of three doubles: x, y, z coordinates.
 * @param vectorCoordinates - the array of three doubles.
 */
Vector3D :: Vector3D(double vectorCoordinates[SIZE_OF_VECTOR]) :
Vector3D(vectorCoordinates[X], vectorCoordinates[Y], vectorCoordinates[Z])
{

}

/////////////////////////////////////////// Methods: ////////////////////////////////////////////

/**
 * This method changes current vector to be the sum of itself and
 * an input right hand side vector.
 * @param rhs - the right hand side vector.
 * @return reference to the current vector that was calculated.
 */
Vector3D& Vector3D :: operator+=(const Vector3D& rhs)
{

	_coords[X] += rhs._coords[X];
	_coords[Y] += rhs._coords[Y];
	_coords[Z] += rhs._coords[Z];

	return *this;
}


/**
 * This method changes current vector to be the multiplication of itself and
 * an input right hand side number.
 * @param num - the number we multiply to the current vector.
 * @return reference to the current vector that was calculated.
 */
Vector3D& Vector3D :: operator*=(const double num)
{

	_coords[X] *= num;
	_coords[Y] *= num;
	_coords[Z] *= num;

	return *this;
}

/**
 * This method changes current vector to be the division of itself and
 * an input right hand side number.
 * @param num - the number we divide to the current vector.
 * @return reference to the current vector that was calculated.
 */

Vector3D& Vector3D :: operator/=(const double num)
{
	Vector3D :: checkDivisionByZero(num);

	double inverse = ONE / num;
	return (*this) *= inverse;
}

/**
 * This method calculates the sum of the current vector and
 * an input right hand side vector.
 * @param other - the right hand side vector.
 * @return new vector which is the sum of the two vectors.
 */
const Vector3D Vector3D :: operator+(const Vector3D& other) const
{
	return Vector3D(*this) += other;
}

/**
 * This method calculates the multiplication of the current vector and
 * an input double number.
 * @param num - the number we multiply to the current vector.
 * @return new vector which is the multiplication of the vector and the number.
 */
const Vector3D Vector3D :: operator*(const double num) const
{
	return Vector3D(_coords[X] * num, _coords[Y] * num, _coords[Z] * num);
}

/**
 * This method calculates the negative vector of a given vector.
 * @return the negative vector of a given vector.
 */
Vector3D Vector3D :: operator-() const
{
	return (*this) * MINUS_ONE;
}

/**
 * This method changes current vector to be the difference of itself and
 * an input right hand side vector.
 * @param rhs - the right hand side vector.
 * @return reference to the current vector that was calculated.
 */
Vector3D& Vector3D :: operator-=(const Vector3D& rhs)
{
	return (*this) += -(rhs);
}

/**
 * This method calculates the difference between the current vector and
 * an input right hand side vector.
 * @param other - the right hand side vector.
 * @return new vector which is the difference between the two vectors.
 */
const Vector3D Vector3D :: operator-(const Vector3D& other) const
{
	return Vector3D(*this) -= other;
}

/**
 * This method calculates the division of the current vector and
 * an input double number.
 * @param num - the number we divide to the current vector.
 * @return new vector which is the division of the vector and the number.
 */
const Vector3D Vector3D :: operator/(const double num) const
{
	Vector3D :: checkDivisionByZero(num);

	double inverse = ONE / num;

	return Vector3D(*this) * inverse;
}

/**
 * This method changes current vector to be the sum of itself and
 * an input right hand side number.
 * @param num - the number we add to the current vector.
 * @return reference to the current vector that was calculated.
 */
Vector3D& Vector3D :: operator+=(const double num)
{

	Vector3D tempVec(num, num, num);

	return *this += tempVec;
}

/**
 * This method changes current vector to be the difference of itself and
 * an input right hand side vector.
 * @param rhs - the right hand side vector.
 * @return reference to the current vector that was calculated.
 */
Vector3D& Vector3D :: operator-=(const double num)
{

	double tempNum = -num;
	return *this += tempNum;
}

/**
 * This method calculates the multiplication of the current vector and
 * an input double number (in opposite given order).
 * @param num - the number we multiply to the current vector.
 * @return new vector which is the multiplication of the vector and the number.
 */
const Vector3D operator*(const double num, const Vector3D& rhs)
{
	return rhs * num;
}

/**
 * This method calculates the distance between the current vector and
 * an input right hand side vector.
 * @param other - the right hand side vector.
 * @return the distance between the vectors.
 */
const double Vector3D :: operator|(const Vector3D& other) const
{

	double dist;

	dist = (_coords[X] - other[X]) * (_coords[X] - other[X]) +
			(_coords[Y] - other[Y]) * (_coords[Y] - other[Y]) +
			(_coords[Z] - other[Z]) * (_coords[Z] - other[Z]);

	return sqrt(dist);
}

/**
 * This method calculates the multiplication of the current vector and
 * an input right hand side vector.
 * @param other - the right hand side vector.
 * @return new double which is the scalar multiplication of the two vectors.
 */
const double Vector3D :: operator*(const Vector3D& other) const
{

	double answer = _coords[X] * other[X] + _coords[Y] * other[Y] + _coords[Z] * other[Z];

	return answer;
}

/**
 * This method calculates the angle between the current vector and
 * an input right hand side vector.
 * @param other - the right hand side vector.
 * @return the angle between the vectors.
 */
const double Vector3D :: operator^(const Vector3D& other) const
{

	double answer;

	answer = ((*this) * other);
	answer /= (*this).norm() * other.norm();

	bool equalVectors = (*this)[X] == other[X] && (*this)[Y] == other[Y] &&
			            (*this)[Z] == other[Z];
	
	if(answer >= ONE || answer < MINUS_ONE || equalVectors)
	{
		return ZERO_RADIANS;
	}

	answer = acos(answer);

	return answer;
}

/**
 * This method calculates the Euclidean norm of the current vector.
 * @return the Euclidean norm of the current vector.
 */
double Vector3D :: norm() const
{
	Vector3D zeroVector;

	return (*this) | zeroVector;
}

/**
 * This method calculates the distance between the current vector and another input vector.
 * @return the distance between the current vector and another input vector.
 */
double Vector3D :: dist(const Vector3D& other) const
{
	return (*this) | other;
}

/**
 * This method is used for reading a vector coordinates from stdin.
 * @param is - the stream we use.
 * @param vector3D - the vector we give values to.
 * @return the stream we use.
 */
std::istream& operator>>(std::istream& is, Vector3D& vector3D)
{

	is >> vector3D._coords[X];
	is >> vector3D._coords[Y];
	is >> vector3D._coords[Z];

	return is;
}

/**
 * This method is used for printing a vector to stdout.
 * @param os - the stream we use.
 * @param vector3D - the vector we want to print.
 * @return the stream we use.
 */
std::ostream& operator<<(std::ostream& os, const Vector3D vector3D)
{

	os << vector3D._coords[X] << SPACE;
	os << vector3D._coords[Y] << SPACE;
	os << vector3D._coords[Z];

	return os;
}

/**
 * This method is used to permit assignment to a coordinate of the current vector.
 * @param index - the coordinate of the current vector we want to change its value.
 * @return - reference to the coordinate we want to change its value.
 */
double& Vector3D :: operator[] (const short index)
{

	Vector3D :: checkIndexOutOfBounds(index, 0, SIZE_OF_VECTOR - 1);

	return _coords[index];
}

/**
 * This method is used to permit access to a coordinate of the current vector.
 * @param index - the coordinate of the current vector we want to access its value.
 * @return - reference to the coordinate we want to access its value.
 */
const double& Vector3D :: operator[] (const short index) const
{

	Vector3D :: checkIndexOutOfBounds(index, 0, SIZE_OF_VECTOR - 1);

	return _coords[index];
}

/**
 * This method checks if we divide a vector by zero or not.
 * If so: exit program with exit failure.
 * @param num - the number we divide with.
 */
void Vector3D :: checkDivisionByZero(const double num)
{
	if(num == 0)
	{
		std :: cerr << DIVISION_BY_ZERO_ERROR;
		exit(EXIT_FAILURE);
	}
}

/**
 * This method checks Index out of bounds error for accessing vector values.
 * If so: exit program with exit failure.
 * @param index - the index we access with.
 */
void Vector3D :: checkIndexOutOfBounds(const short index, const short begin, const short end)
{
	if(index > end || index < begin)
	{
		std :: cerr << INDEX_OUT_OF_BOUNDS_ERROR;
		exit(EXIT_FAILURE);
	}
}