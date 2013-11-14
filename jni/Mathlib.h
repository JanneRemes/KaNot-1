#pragma once
#ifndef MATH_H

#define MATH_H

namespace Kuso
{
	class Vector2
	{
	public:
		Vector2();
		Vector2(float X, float Y);
		~Vector2();
		float getLength();
		float getAngle();
		float x,y;
	private:
	};

	Vector2 operator -(const Vector2& RightVal);

	Vector2 operator +(const Vector2& LeftVal,const Vector2& RightVal);

	Vector2 operator -(const Vector2& LeftVal,const Vector2& RightVal);

	Vector2 operator +=(Vector2& LeftVal,const Vector2& RightVal);

	Vector2 operator -=(Vector2& LeftVal,const Vector2& RightVal);

	Vector2 operator /(const Vector2& LeftVal,const float& RightVal);

	Vector2 operator /=(Vector2& LeftVal, const float& RightVal);

	bool operator ==(const Vector2& LeftVal, const Vector2& RightVal);

	bool operator !=(const Vector2& LeftVal, const Vector2& RightVal);

	Vector2 operator *(const float& LeftVal, const Vector2& RightVal);

	const Vector2 operator *=(Vector2& LeftVal, const float& RightVal);

	class Vector3
	{
	public:
		Vector3();
		Vector3(float X, float Y, float Z);
		~Vector3();
		float getLength();
		float getAngle();
		float x,y,z;
	private:
	};


	class Rectangle

	{
	public:

		Rectangle();

		Rectangle(float Left, float Top, float Width, float Height);

		Rectangle(Vector2 Position, float Width, float Height);

		Rectangle(Vector2 Position,Vector2 Size);
		
		bool intersects(Rectangle rectangle);
		bool contains(Vector2 Position);

		~Rectangle();

		float width, height, left, top;

		private:
	};
}

#endif