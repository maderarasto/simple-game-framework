#pragma once

#include "SGF/api.h"

namespace SGF::Core
{
	template<typename T>
	struct SGF_API Vector2
	{
	public:
		Vector2(T x, T y);
		
		Vector2(const Vector2<T>& other);
		Vector2& operator=(const Vector2<T>& other);

		bool operator==(const Vector2<T>& other) const;
		bool operator!=(const Vector2<T>& other) const;
		bool operator>(const Vector2<T>& other) const;
		bool operator<(const Vector2<T>& other) const;
		bool operator>=(const Vector2<T>& other) const;
		bool operator<=(const Vector2<T>& other) const;
		
		Vector2<T> operator+(T number);
		Vector2<T> operator-(T number);
		Vector2<T> operator*(T number);
		Vector2<T> operator/(T number);
		Vector2<T> operator+(const Vector2<T>& other);
		Vector2<T> operator-(const Vector2<T>& other);
		
		Vector2<T>& operator+=(T number);
		Vector2<T>& operator-=(T number);
		Vector2<T>& operator*=(T number);
		Vector2<T>& operator/=(T number);
		Vector2<T>& operator+=(const Vector2<T>& other);
		Vector2<T>& operator-=(const Vector2<T>& other);

		static double CalculateValue(const Vector2<T>& vector);

	public:
		T x, y;
	};
}

typedef SGF::Core::Vector2<int> Vector2i;
typedef SGF::Core::Vector2<float> Vector2f;