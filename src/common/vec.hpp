#ifndef CASTOR_VEC3_H
#define CASTOR_VEC3_H

template<typename T>
struct Vec2
{
  T x;
  T y;

  Vec2()
    :x{},y{} {}

  Vec2(T x_,T y_)
    :x{x_},y{y_} {}
};

template<typename T>
struct Vec3
{
  T x;
  T y;
  T z;

  Vec3()
    :x{},y{},z{} {}

  Vec3(T x_,T y_,T z_)
    :x{x_},y{y_},z{z_} {}
};

template<typename T>
struct Vec4
{
  T x;
  T y;
  T z;
  T t;

  Vec4()
    :x{},y{},z{},t{} {}
  Vec4(T x_,T y_, T z_, T t_)
    :x{x_},y{y_},z{z_},t{t_} {}
};

#endif /* CASTOR_VEC3_H */
