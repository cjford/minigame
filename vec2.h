#ifndef VEC2_H
#define VEC2_H

typedef struct vec2 {
  float x;
  float y;
} Vec2;

Vec2 vec_add(Vec2 v1, Vec2 v2);
void vec_add_inplace(Vec2 *v1, Vec2 v2);

Vec2 vec_mult_s(Vec2 v1, float f);
void vec_mult_s_inplace(Vec2 *v1, float f);

Vec2 vec_clamp_s(Vec2 v1, float max);
void vec_clamp_s_inplace(Vec2 *v1, float max);

void vec_print(Vec2 v);

#endif // VEC2_H
