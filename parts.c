#include <gl/freeglut.h>

static void cube(void) {

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

static void wheel(void)
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.5);
	glutSolidCylinder(1.5, 0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.4);
	glutSolidCylinder(1.0, 0.2, 100, 100);
	glPopMatrix();

	glutSolidTorus(0.3,3.0,100,100);

	/*Spokes at 60 degrees */
	glPushMatrix();
		glRotatef(60, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-60, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-120.0, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(120, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();


	/*Spokes at 30 degrees */

	glPushMatrix();
		glRotatef(150, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-150, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(30, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-30, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(180, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 1.4, -0.3);
		glPushMatrix();
		glRotatef(-10, -1.0, 0.0, 0.0);
		glScalef(0.4, 3.2, 0.1);
		cube();
		glPopMatrix();
	glPopMatrix();

}

