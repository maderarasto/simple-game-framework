#include "sgfpch.h"
#include "Vector2.h"

using namespace SGF::Core;

template<typename T>
double Vector2<T>::CalculateValue(const Vector2<T>& vector);


template<typename T>
Vector2<T>::Vector2(T x, T y)
{
	this->x = x;
	this->y = y;
}


template<typename T>
Vector2<T>::Vector2(const Vector2<T>& other)
{
	this->x = other.x;
	this->y = other.y;
}


template<typename T>
Vector2<T>& Vector2<T>::operator=(const Vector2<T>& other)
{
	if (this != &other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	return *this;
}


template<typename T>
bool Vector2<T>::operator==(const Vector2<T>& other) const
{
	return this->x == other.x && this->y == other.y;
}


template<typename T>
bool Vector2<T>::operator!=(const Vector2<T>& other) const
{
	return this->x != other.x || this->y != other.y;
}


template<typename T>
bool Vector2<T>::operator>(const Vector2<T>& other) const
{
	return CalculateValue(*this) > CalculateValue(other);
}


template<typename T>
bool Vector2<T>::operator<(const Vector2<T>& other) const
{
	return CalculateValue(*this) < CalculateValue(other);
}

template<typename T>
bool Vector2<T>::operator>=(const Vector2<T>& other) const
{
	return CalculateValue(*this) >= CalculateValue(other);
}


template<typename T>
bool Vector2<T>::operator<=(const Vector2<T>& other) const
{
	return CalculateValue(*this) <= CalculateValue(other);
}


template<typename T>
Vector2<T> Vector2<T>::operator+(T number)
{
	return Vector2<T>(this->x + number, this->y + number);
}


template<typename T>
Vector2<T> Vector2<T>::operator-(T number)
{
	return Vector2<T>(this->x - number, this->y - number);
}


template<typename T>
Vector2<T> Vector2<T>::operator*(T number)
{
	return Vector2<T>(this->x * number, this->y * number);
}


template<typename T>
Vector2<T> Vector2<T>::operator/(T number)
{
	return Vector2<T>(this->x / number, this->y / number);
}


template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other)
{
	return Vector2<T>(this->x + other.x, this->y + other.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other)
{
	return Vector2<T>(this->x - other.x, this->y - other.y);
}


template<typename T>
Vector2<T>& Vector2<T>::operator+=(T number)
{
	this->x += number;
	this->y += number;

	return *this;
}


template<typename T>
Vector2<T>& Vector2<T>::operator-=(T number)
{
	this->x -= number;
	this->y -= number;

	return *this;
}


template<typename T>
Vector2<T>& Vector2<T>::operator*=(T number)
{
	this->x *= number;
	this->y *= number;

	return *this;
}


template<typename T>
Vector2<T>& Vector2<T>::operator/=(T number)
{
	this->x /= number;
	this->y /= number;

	return *this;
}


template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}


template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}


template<typename T>
double Vector2<T>::CalculateValue(const Vector2<T>& vector)
{
	double powX = vector.x * vector.x;
	double powY = vector.y * vector.y;

	return sqrt(powX + powY);
}

template SGF_API Vector2<int>::Vector2(int x, int y);
template SGF_API Vector2<int>::Vector2(const Vector2<int>& other);
template SGF_API Vector2<int>& Vector2<int>::operator=(const Vector2<int>& other);
template SGF_API bool Vector2<int>::operator==(const Vector2<int>& other) const;
template SGF_API bool Vector2<int>::operator!=(const Vector2<int>& other) const;
template SGF_API bool Vector2<int>::operator>(const Vector2<int>& other) const;
template SGF_API bool Vector2<int>::operator<(const Vector2<int>& other) const;
template SGF_API bool Vector2<int>::operator>=(const Vector2<int>& other) const;
template SGF_API bool Vector2<int>::operator<=(const Vector2<int>& other) const;
template SGF_API Vector2<int> Vector2<int>::operator+(int number);
template SGF_API Vector2<int> Vector2<int>::operator-(int number);
template SGF_API Vector2<int> Vector2<int>::operator*(int number);
template SGF_API Vector2<int> Vector2<int>::operator/(int number);
template SGF_API Vector2<int> Vector2<int>::operator+(const Vector2<int>& other);
template SGF_API Vector2<int> Vector2<int>::operator-(const Vector2<int>& other);
template SGF_API Vector2<int>& Vector2<int>::operator+=(int number);
template SGF_API Vector2<int>& Vector2<int>::operator-=(int number);
template SGF_API Vector2<int>& Vector2<int>::operator*=(int number);
template SGF_API Vector2<int>& Vector2<int>::operator/=(int number);
template SGF_API Vector2<int>& Vector2<int>::operator+=(const Vector2<int>& other);
template SGF_API Vector2<int>& Vector2<int>::operator-=(const Vector2<int>& other);

template SGF_API Vector2<float>::Vector2(float x, float y);
template SGF_API Vector2<float>::Vector2(const Vector2<float>& other);
template SGF_API Vector2<float>& Vector2<float>::operator=(const Vector2<float>& other);
template SGF_API bool Vector2<float>::operator==(const Vector2<float>& other) const;
template SGF_API bool Vector2<float>::operator!=(const Vector2<float>& other) const;
template SGF_API bool Vector2<float>::operator>(const Vector2<float>& other) const;
template SGF_API bool Vector2<float>::operator<(const Vector2<float>& other) const;
template SGF_API bool Vector2<float>::operator>=(const Vector2<float>& other) const;
template SGF_API bool Vector2<float>::operator<=(const Vector2<float>& other) const;
template SGF_API Vector2<float> Vector2<float>::operator+(float number);
template SGF_API Vector2<float> Vector2<float>::operator-(float number);
template SGF_API Vector2<float> Vector2<float>::operator*(float number);
template SGF_API Vector2<float> Vector2<float>::operator/(float number);
template SGF_API Vector2<float> Vector2<float>::operator+(const Vector2<float>& other);
template SGF_API Vector2<float> Vector2<float>::operator-(const Vector2<float>& other);
template SGF_API Vector2<float>& Vector2<float>::operator+=(float number);
template SGF_API Vector2<float>& Vector2<float>::operator-=(float number);
template SGF_API Vector2<float>& Vector2<float>::operator*=(float number);
template SGF_API Vector2<float>& Vector2<float>::operator/=(float number);
template SGF_API Vector2<float>& Vector2<float>::operator+=(const Vector2<float>& other);
template SGF_API Vector2<float>& Vector2<float>::operator-=(const Vector2<float>& other);