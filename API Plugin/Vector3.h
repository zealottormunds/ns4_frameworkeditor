#pragma once
#include <math.h>

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}

	static Vector3 Lerp(Vector3 * a, Vector3 * b, float t)
	{
		Vector3 c = Vector3(0, 0, 0);

		c.x = a->x + t * (b->x - a->x);
		c.y = a->y + t * (b->y - a->y);
		c.z = a->z + t * (b->z - a->z);

		return c;
	}

	Vector3 operator + (Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator - (Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator * (Vector3 v)
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	Vector3 operator / (Vector3 v)
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}

	Vector3 operator * (float m)
	{
		return Vector3(x * m, y * m, z * m);
	}

	Vector3 operator / (float m)
	{
		return Vector3(x / m, y / m, z / m);
	}

	bool operator == (Vector3 b)
	{
		return x == b.x && y == b.y && z == b.z;
	}

	bool operator != (Vector3 b)
	{
		return x != b.x && y != b.y && z != b.z;
	}

	float Magnitude()
	{
		float m = sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
		return m;
	}

	Vector3 Normalize()
	{
		float m = Magnitude();
		Vector3 n = Vector3(x / m, y / m, z / m);
		return n;
	}

	static float Distance(Vector3 a, Vector3 b)
	{
		return sqrtf(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	}
};

class Vector2
{
public:
	float x;
	float y;

	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2(float a, float b)
	{
		x = a;
		y = b;
	}
};

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	Vector4(float a, float b, float c, float d)
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}
};