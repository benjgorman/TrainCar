#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>

#ifndef M_PI
#define M_PI 3.14159265
#endif

static GLint T0 = 0;
static GLint Frames = 0;

void gear(GLfloat innerRadius, GLfloat outerRadius, GLfloat width, GLint teeth, GLfloat tooth_depth);
void cube();
void wheel();
void draw_piston();

