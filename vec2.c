#include "vec2.h"
#include <stdio.h>

static Vec2 result;

Vec2 vec_add(Vec2 v1, Vec2 v2) {
  result.x = v1.x + v2.x;
  result.y = v1.y + v2.y;

  return result;
}

void vec_add_inplace(Vec2 *v1, Vec2 v2) {
  *v1 = vec_add(*v1, v2);
}

Vec2 vec_mult_s(Vec2 v1, float f) {
  result.x = v1.x * f;
  result.y = v1.y * f;

  return result;
}

void vec_mult_s_inplace(Vec2 *v1, float f) {
  *v1 = vec_mult_s(*v1, f);
}

Vec2 vec_clamp_s(Vec2 v1, float limit) {
  if(limit < 0) {
    limit *= -1;
  }

  if (v1.x > limit) {
    result.x = limit;
  } else if (v1.x < limit * -1) {
    result.x = limit * -1;
  }

  if (v1.y > limit) {
    result.y = limit;
  } else if (v1.y < limit * -1) {
    result.y = limit * -1;
  }

  return result;
}

void vec_clamp_s_inplace(Vec2 *v1, float max) {
  *v1 = vec_clamp_s(*v1, max);
}

void vec_print(Vec2 v) {
  printf("x: %f, y: %f\n", v.x, v.y);
}
