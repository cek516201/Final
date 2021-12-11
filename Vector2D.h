#ifndef _Vector2D_H_
#define _Vector2D_H_

class Vector2D
{
public:
  Vector2D(float x, float y) : m_x(x), m_y(y) {}

  float getX() const { return m_x; }
  float getY() const { return m_y; }
  void setX(float x) { m_x = x; }
  void setY(float y) { m_y = y; }

  void normalize();
  float length();
  
  Vector2D operator+(const Vector2D& v2) const;
  Vector2D operator-(const Vector2D& v2) const;
  Vector2D operator*(float scalar);
  Vector2D operator/(float scalar);

  friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
  friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);
  Vector2D& operator*=(float scalar);
  Vector2D& operator/=(float scalar);

private:
  float m_x;
  float m_y;
};

#endif