/******************************************************************************/
/*!
\file	Vector3.cpp
\author Wen Sheng Tang
\par	email: tang_wen_sheng\@nyp.edu.sg
\brief
Struct to define a 3D vector
*/
/******************************************************************************/
#include <cmath>
#include "Vector3.h"

bool Vector3::IsEqual(float a, float b) const
{
	return a - b <= Math::EPSILON && b - a <= Math::EPSILON;
}

/******************************************************************************/
/*!
\brief	Vector3 default constructor

\param	a
	x value
\param	b
	y value
\param	c
	z value
*/
/******************************************************************************/
Vector3::Vector3(float a, float b, float c) : x(a), y(b), z(c)
{
}

/******************************************************************************/
/*!
\brief	Vector3 copy constructor

\param	rhs
	Vector to copy from
*/
/******************************************************************************/
Vector3::Vector3(const Vector3 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
{
}

/******************************************************************************/
/*!
\brief	Vector3 destructor
*/
/******************************************************************************/
Vector3::~Vector3()
{
}

/******************************************************************************/
/*!
\brief	Set the elements of this vector

\param	a
	x value
\param	b
	y value
\param	c
	z value
*/
/******************************************************************************/
void Vector3::Set( float a, float b, float c )
{
	x = a;
	y = b;
	z = c;
}

/******************************************************************************/
/*!
\brief	Set all elements to zero
*/
/******************************************************************************/
void Vector3::SetZero( void )
{
	x = y = z = 0.0f;
}

/******************************************************************************/
/*!
\brief	Check if vector is zero, using Math::Epsilon

\return TRUE if vector is zero
*/
/******************************************************************************/
bool Vector3::IsZero( void ) const
{
	return IsEqual(x, 0.f) && IsEqual(y, 0.f) && IsEqual(z, 0.f);
}

/******************************************************************************/
/*!
\brief
operator+ overload for vector addition

\param rhs
	Vector3 to add with
\return 
	Resulting vector
*/
/******************************************************************************/
Vector3 Vector3::operator+( const Vector3& rhs ) const
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

/******************************************************************************/
/*!
\brief
operator+= overload for vector addition and assignment

\param rhs
	Vector3 to add with
\return 
	Resulting vector
*/
/******************************************************************************/
Vector3& Vector3::operator+=( const Vector3& rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

/******************************************************************************/
/*!
\brief
operator- overload for vector subtraction

\param rhs
	Vector3 to subtract with
\return Resulting vector
*/
/******************************************************************************/
Vector3 Vector3::operator-( const Vector3& rhs ) const
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

/******************************************************************************/
/*!
\brief
operator-= overload for vector subtraction and assignment

\param rhs
	Vector3 to subtract with
\return 
	Resulting vector
*/
/******************************************************************************/
Vector3& Vector3::operator-=( const Vector3& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

/******************************************************************************/
/*!
\brief
operator- overload for unary negation

\return 
	Resulting vector
*/
/******************************************************************************/
Vector3 Vector3::operator-( void ) const
{
	return Vector3(-x, -y, -z);
}

/******************************************************************************/
/*!
\brief
operator* overload for scalar multiplication

\param scalar - float to multiply with
 
\exception None
\return Resulting vector
*/
Vector3 Vector3::operator*( float scalar ) const
{
	return Vector3(scalar * x, scalar * y, scalar * z);
}

float Vector3::operator* (const Vector3& rhs) const {
	return{ x * rhs.x + y * rhs.y + z * rhs.z };
}

/******************************************************************************/
/*!
\brief
operator*= overload for scalar multiplication and assignment

\param scalar
	float to multiply with
\return 
	Resulting vector
*/
/******************************************************************************/
Vector3& Vector3::operator*=( float scalar )
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

/******************************************************************************/
/*!
\brief
operator== overload for equality check, using Math::EPSILON

\param rhs
	vector to compare with
 
\exception None
\return Resulting vector
*/
/******************************************************************************/
bool Vector3::operator==( const Vector3& rhs ) const
{
	return IsEqual(x, rhs.x) && IsEqual(y, rhs.y) && IsEqual(z, rhs.z);
}

/******************************************************************************/
/*!
\brief
operator!= overload for inequality check, using Math::EPSILON

\param rhs
	vector to compare with
\return 
	Resulting vector
*/
/******************************************************************************/
bool Vector3::operator!= ( const Vector3& rhs ) const
{
	return !IsEqual(x, rhs.x) || !IsEqual(y, rhs.y) || !IsEqual(z, rhs.z);
}

/******************************************************************************/
/*!
\brief	Assignment operation (assign a vector to this vector)

\param	rhs
	Vector to assign
\return 
	A reference to this vector
*/
/******************************************************************************/
Vector3& Vector3::operator=(const Vector3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

/******************************************************************************/
/*!
\brief
Return length of vector

\return 
	Length
*/
/******************************************************************************/
float Vector3::Length( void ) const
{
  return sqrt(x * x + y * y + z * z);
}

/******************************************************************************/
/*!
\brief
Return square of length of vector

\return 
	Length square
*/
/******************************************************************************/
float Vector3::LengthSquared (void ) const
{
	return x * x + y * y + z * z;
}

/******************************************************************************/
/*!
\brief
Dot product of 2 vectors

\param rhs
	Point to calculate dot product with
\return 
	float value of dot product
*/
/******************************************************************************/
float Vector3::Dot( const Vector3& rhs ) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

/******************************************************************************/
/*!
\brief
Cross product of 2 vectors

\param rhs
	Point to calculate cross product with
\return 
	Vector of cross product
*/
/******************************************************************************/
Vector3 Vector3::Cross( const Vector3& rhs ) const
{
	return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

/******************************************************************************/
/*!
\brief
Return a copy of this vector, normalized

\param rhs
	Point to calculate distance from
\exception Divide by zero 
	thrown if normalizing a zero vector
\return 
	Resulting normalized vector
*/
/******************************************************************************/
Vector3 Vector3::Normalized( void ) const throw( DivideByZero )
{
	float d = Length();
	if(d <= Math::EPSILON && -d <= Math::EPSILON)
	  throw DivideByZero();
	return Vector3(x / d, y / d, z / d);
}

Vector3 Vector3::GetMidpoint(const Vector3& lhs, const Vector3& rhs) const
{
	return Vector3((lhs.x + rhs.x) / 2.0f, (lhs.y + rhs.y) / 2.0f, (lhs.z + rhs.z) / 2.0f);
}

// fast square root shit to reduce ram consumption
double inline __declspec (naked) __fastcall sqrt14(double n)
{
	_asm fld qword ptr[esp + 4]
		_asm fsqrt
	_asm ret 8
}

float Vector3::Magnitude() {
	return sqrt14(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

/******************************************************************************/
/*!
\brief
Normalize this vector and return a reference to it

\param rhs
	Point to calculate distance from
\exception Divide by zero 
	thrown if normalizing a zero vector
\return 
	Reference to this vector
*/
/******************************************************************************/
Vector3& Vector3::Normalize( void ) throw( DivideByZero )
{
	float d = Length();
	if(d <= Math::EPSILON && -d <= Math::EPSILON)
	  throw DivideByZero();
	x /= d;
	y /= d;
	z /= d;
	return *this;
}

std::ostream& operator<< (std::ostream& os, Vector3& rhs)
{
	os << "[ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " ]";
	return os;
}

/******************************************************************************/
/*!
\brief
Scalar product of scalar with vector

\param scalar
	scalar value
\param vector
	vector
\return 
	Resulting vector
*/
/******************************************************************************/
Vector3 operator*( float scalar, const Vector3& rhs )
{
	return rhs * scalar;
}
