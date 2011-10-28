#include "parts.h"

//static GLint gear1, gear2, axle, axle_holder, handle_cage, handle, assem_handle, decking, wheels;

void 
draw_piston(void)
{
  glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCylinder(0.2f, 7.0f, 100, 100);
  glPopMatrix();

  glPushMatrix();
    glRotatef(90, 0.0, 1.0f, 0.0f);
	glutSolidCylinder(0.2f, 1.0f, 100, 100);
  glPopMatrix();

  glPushMatrix();
    glRotatef(90, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -0.3f);
	glutSolidCylinder(0.3f, 0.5f, 100, 100);
  glPopMatrix();
}

void cube(void) {

	 //front
   glColor3f(1.0,0.0,0.0);
 
   glBegin(GL_POLYGON);
	 glNormal3f(0.0f, 0.0f, 1.0f);
     glVertex3f(0.5f,0.5f,0.5f);
     glVertex3f(-0.5f,0.5f,0.5f);
     glVertex3f(-0.5f,-0.5f,0.5f);
     glVertex3f(0.5f,-0.5f,0.5f);
   glEnd();

   //right

   glColor3f(0.0,1.0,0.0);
   glBegin(GL_POLYGON);
	 glNormal3f(1.0f, 0.0f, 0.0f);
     glVertex3f(0.5,0.5,0.5);
     glVertex3f(0.5,-0.5,0.5);
     glVertex3f(0.5,-0.5,-0.5);
     glVertex3f(0.5,0.5,-0.5);
   glEnd();
   //back
   glColor3f(0.0,1.0,1.0);
   glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, -1.0f);
     glVertex3f(0.5,0.5,-0.5);
     glVertex3f(0.5,-0.5,-0.5);
     glVertex3f(-0.5,-0.5,-0.5);
     glVertex3f(-0.5,0.5,-0.5);
   glEnd();
   //left
   glColor3f(1.0,0.0,1.0);
   glBegin(GL_POLYGON);
	 glNormal3f(-1.0f, 0.0f, 0.0f);
     glVertex3f(-0.5,0.5,0.5);
     glVertex3f(-0.5,0.5,-0.5);
     glVertex3f(-0.5,-0.5,-0.5);
     glVertex3f(-0.5,-0.5,0.5);
   glEnd();
   //top
   glColor3f(0.0,0.0,1.0);
   glBegin(GL_POLYGON);
	 glNormal3f(0.0f, 1.0f, 0.0f);
     glVertex3f(0.5,0.5,0.5);
     glVertex3f(0.5,0.5,-0.5);
     glVertex3f(-0.5,0.5,-0.5);
     glVertex3f(-0.5,0.5,0.5);
   glEnd();
   //bottom
   glColor3f(1.0,1.0,0.0);
   glBegin(GL_POLYGON);
	 glNormal3f(0.0f, -1.0f, 0.0f);
     glVertex3f(0.5,-0.5,0.5);
     glVertex3f(-0.5,-0.5,0.5);
     glVertex3f(-0.5,-0.5,-0.5);
     glVertex3f(0.5,-0.5,-0.5);
   glEnd();
}

void wheel(void)
{

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.5f);
	glutSolidCylinder(1.5f, 0.2f, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.4f);
	glutSolidCylinder(1.0f, 0.2f, 100, 100);
	glPopMatrix();

	glutSolidTorus(0.3,3.0,100,100);

	/*Spokes at 60 degrees */
	glPushMatrix();
		glRotatef(60, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-60, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-120.0, 0.0, 0.0, 1.0);
		glTranslatef(0.0f, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(120, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();


	/*Spokes at 30 degrees */

	glPushMatrix();
		glRotatef(150, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-150, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(30, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-30, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(180, 0.0, 0.0, 1.0);
		glTranslatef(0.0f, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 1.4f, -0.3f);
		glPushMatrix();
		glRotatef(-10, -1.0f, 0.0f, 0.0f);
		glScalef(0.4f, 3.2f, 0.1f);
		cube();
		glPopMatrix();
	glPopMatrix();

}

/** draw a gear */
void gear(GLfloat innerRadius, GLfloat outerRadius, GLfloat width, GLint teeth, GLfloat tooth_depth) {
	GLint i; //general purpose incrementer for loops
	GLfloat r0, r1, r2, u, v, len, da;
	GLdouble angle;

	width /= 2; // half width since it's half is always needed in this method

	r0 = innerRadius;
	r1 = outerRadius - tooth_depth / 2.0f;
	r2 = outerRadius + tooth_depth / 2.0f;
	da = 2.0f * (GLfloat)M_PI / teeth / 4.0f;
	glShadeModel(GL_SMOOTH); // set type of shading to smooth

	glNormal3f(0.0f, 0.0f, 1.0f); // normal for the front of the gear

	/* draw front face */
	glBegin(GL_QUAD_STRIP);

	for (i = 0; i <= teeth; i++) {
		angle = i * 2.0f * M_PI / teeth;
		glVertex3d(r0 * cos(angle), r0 * sin(angle), width);
		glVertex3d(r1 * cos(angle), r1 * sin(angle), width);
		glVertex3d(r0 * cos(angle), r0 * sin(angle), width);
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width);
	}

	glEnd();

	/* draw front sides of teeth */
	glBegin(GL_QUADS);

	for (i = 0; i < teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glVertex3d(r1 * cos(angle), r1 * sin(angle), width);
		glVertex3d(r2 * cos(angle + da), r2 * sin(angle + da), width);
		glVertex3d(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width);
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width);
	}

	glEnd();

	glNormal3f(0.0f, 0.0f, -1.0f); // normal for the back of the gear

	/* draw back face */
	glBegin(GL_QUAD_STRIP);

	for (i = 0; i <= teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glVertex3d(r1 * cos(angle), r1 * sin(angle), -width);
		glVertex3d(r0 * cos(angle), r0 * sin(angle), -width);
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width);
		glVertex3d(r0 * cos(angle), r0 * sin(angle), -width);
	}

	glEnd();

	/* draw back sides of teeth */
	glBegin(GL_QUADS);

	for (i = 0; i < teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width);
		glVertex3d(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width);
		glVertex3d(r2 * cos(angle + da), r2 * sin(angle + da), -width);
		glVertex3d(r1 * cos(angle), r1 * sin(angle), -width);
	}

	glEnd();

	/* draw outward faces of teeth */
	glBegin(GL_QUAD_STRIP);

	for (i = 0; i < teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glVertex3d(r1 * cos(angle), r1 * sin(angle), width);
		glVertex3d(r1 * cos(angle), r1 * sin(angle), -width);
		u = (GLfloat) (r2 * cos(angle + da) - r1 * cos(angle));
		v = (GLfloat) (r2 * sin(angle + da) - r1 * sin(angle));
		len = (GLfloat) (sqrt(u * u + v * v));
		u /= len;
		v /= len;
		glNormal3d(v, -u, 0.0);
		glVertex3d(r2 * cos(angle + da), r2 * sin(angle + da), width);
		glVertex3d(r2 * cos(angle + da), r2 * sin(angle + da), -width);
		glNormal3d(cos(angle), sin(angle), 0.0);
		glVertex3d(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width);
		glVertex3d(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width);
		u = (GLfloat) (r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da));
		v = (GLfloat) (r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da));
		glNormal3f(v, -u, 0.0f);
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width);
		glVertex3d(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width);
		glNormal3d(cos(angle), sin(angle), 0.0);
	}

	glVertex3d(r1 * cos(0.0), r1 * sin(0.0), width);
	glVertex3d(r1 * cos(0.0), r1 * sin(0.0), -width);

	glEnd();

	/* draw inside radius cylinder */
	glBegin(GL_QUAD_STRIP);

	for (i = 0; i <= teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glNormal3d(-cos(angle), -sin(angle), 0.0);
		glVertex3d(r0 * cos(angle), r0 * sin(angle), -width);
		glVertex3d(r0 * cos(angle), r0 * sin(angle), width);
	}

	glEnd();
}
