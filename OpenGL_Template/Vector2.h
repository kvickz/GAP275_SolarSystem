#ifndef __VECTOR2_H__
#define __VECTOR2_H__

//-------------------------------------------------------------------------------------- -
// Vector2 of Floats
//-------------------------------------------------------------------------------------- -
class Vector2_f
{
public:
    Vector2_f();
	Vector2_f(float x, float y);

	float x, y;

	//operator overloads
	Vector2_f operator=(Vector2_f b)
	{
		Vector2_f result;
		result.x = b.x;
		result.y = b.y;
		return result;
	}

	Vector2_f operator+(Vector2_f b)
	{
		Vector2_f result;
		result.x = x;
		result.y = y;

		result.x += b.x;
		result.y += b.y;
		return result;
	}

	Vector2_f operator+=(Vector2_f b)
	{
        Vector2_f result;
		x += b.x;
		y += b.y;

		result.x = x;
		result.y = y;
		return result;
	}

	Vector2_f operator-(Vector2_f b)
	{
		Vector2_f result;
		result.x = x;
		result.y = y;

		result.x -= b.x;
		result.y -= b.y;
		return result;
	}

	Vector2_f operator-=(Vector2_f b)
	{
		Vector2_f result;
		x -= x;
		y -= y;

		result.x = b.x;
		result.y = b.y;
		return result;
	}

	Vector2_f operator*(int b)
	{
		Vector2_f result;
		result.x = x;
		result.y = y;

		result.x *= b;
		result.y *= b;
		return result;
	}
};

//-------------------------------------------------------------------------------------- -
// Vector2 of Ints
//-------------------------------------------------------------------------------------- -
class Vector2_i
{
public:
    Vector2_i();
    Vector2_i(int x, int y);

    int x, y;

    //operator overloads
    Vector2_i operator=(Vector2_i b)
    {
        Vector2_i result;
        result.x = b.x;
        result.y = b.y;
        return result;
    }

    Vector2_i operator+(Vector2_i b)
    {
        Vector2_i result;
        result.x = x;
        result.y = y;

        result.x += b.x;
        result.y += b.y;
        return result;
    }

    Vector2_i operator+=(Vector2_i b)
    {
        Vector2_i result;
        x += b.x;
        y += b.y;

        result.x = x;
        result.y = y;
        return result;
    }

    Vector2_i operator-(Vector2_i b)
    {
        Vector2_i result;
        result.x = x;
        result.y = y;

        result.x -= b.x;
        result.y -= b.y;
        return result;
    }

    Vector2_i operator-=(Vector2_i b)
    {
        Vector2_i result;
        x -= x;
        y -= y;

        result.x = b.x;
        result.y = b.y;
        return result;
    }

    Vector2_i operator*(int b)
    {
        Vector2_i result;
        result.x = x;
        result.y = y;

        result.x *= b;
        result.y *= b;
        return result;
    }
};

#endif // !__VECTOR2_H__
