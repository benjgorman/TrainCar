#include "parts.h"

GLfloat  eyex = 100.0;
GLfloat  eyey = 40.0;
GLfloat  eyez = -100.0;

/* Magic numbers for relationship b/w cylinder head and crankshaft. */
/* Step to be taken for each rotation. */
#define ANGLE_STEP 10
#define MAGNITUDE  120
#define PHASE      270.112
#define FREQ_DIV   58
#define ARC_LENGHT 2.7
#define ARC_RADIUS 0.15

/* Storage for the angle look up table and the texture map */
GLdouble head_look_up_table[361];

/* Rotation angles */
GLdouble view_h = 270, view_v = 0;

GLdouble head_angle = 0;
GLint crank_angle = 0;

/* Crank rotation step. */
GLdouble crank_step = 5;

int x;
int y;
static GLfloat angle = 0.0;
static GLint gear1, gear2, axle, axle_holder, handle_cage, handle, assem_handle, decking, wheels, axle_holders, frame;

static GLfloat pos[4] = {5.0f, 5.0f, 10.0f, 0.0f};
static GLfloat specular[3] = {1.0f, 1.0f, 1.0f};
static GLfloat ambient[3] = {0.1f, 0.1f, 0.1f};
static GLfloat diffuse[3] = {0.8f, 0.8f, 0.8f};

static GLfloat red[3] = {0.56f, 0.11f, 0.11f};
static GLfloat wood[3] = {0.76f, 0.62f, 0.36f};
static GLfloat dkgrey[3] = {0.31f, 0.33f, 0.35f};
static GLfloat black[3] = {0.13f, 0.14f, 0.16f};

void animation(void)
{
  if ((crank_angle += crank_step) >= 360)
    crank_angle = 0;
  head_angle = head_look_up_table[crank_angle];
  glutPostRedisplay();
}

//* Draws the crank bell, and the pivot pin for the piston. Also calls the
//   appropreate display list of a piston doing the nesacary rotations before
//   hand.  */
void 
draw_crankbell(void)
{
    glRotatef(25, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(1.0f, 0.0f, 0.0f);

		glTranslatef(0.0f, 0.0f, 1.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0);
		glRotatef(crank_angle - head_angle, 1.0f, 0.0f, 0.0f);
		  draw_piston();
	glPopMatrix();
}

//* Draws the complete crank. Piston also gets drawn through the crank bell
//   function. */
void 
draw_crank(void)
{
  glPushMatrix();
    glRotatef(crank_angle, 1.0f, 0.0f, 0.0f);

    glPushMatrix();
      glTranslatef(0.28f, 0.0f, 0.0f);
     draw_crankbell();
    glPopMatrix();
  glPopMatrix();
}

void draw_large_gear()
{
	gear2 = glGenLists(2);
		glNewList(gear2, GL_COMPILE);
		glColor3fv(dkgrey);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, dkgrey);
		 glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
		glMateriali(GL_FRONT, GL_SHININESS, 50); // how shiney it is
		gear(0.2f, 2.0f, 0.5f, 28, 0.2f);
	glEndList();
}

void draw_small_gear()
{
	gear1 = glGenLists(1);
		glNewList(gear1, GL_COMPILE);
		glColor3fv(wood);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, dkgrey);
		 glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
		glMateriali(GL_FRONT, GL_SHININESS, 50); // how shiney it is
		gear(0.3f, 1.0f, 0.5f, 14, 0.2f);
	glEndList();
}

void draw_axle()
{
	axle = glGenLists(3);
	glNewList(axle, GL_COMPILE);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -20.0f);
			glPushMatrix();
			glRotatef(180, 1.0, 0.0, 0.0);

			glColor3fv(dkgrey);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, dkgrey);
			 glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
			glMateriali(GL_FRONT, GL_SHININESS, 50); // how shiney it is

			wheel();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		wheel();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -22.0f);
		glTranslatef(0.0f, 0.0f, 1.0f);

		glColor3fv(wood);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wood);
		 glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
		glMateriali(GL_FRONT, GL_SHININESS, 10); // how shiney it is

		glutSolidCylinder(0.3, 22.00, 100, 100);
		glTranslatef(0.0f, 0.0f, 2.0f);
	glPopMatrix();
	glEndList();

}

void draw_axle_holder()
{
	axle_holder = glGenLists(4);
	glNewList(axle_holder, GL_COMPILE);
	glColor3fv(dkgrey);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, dkgrey);
	 glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
		glMateriali(GL_FRONT, GL_SHININESS, 50); // how shiney it is
		glPushMatrix();
		glutSolidTorus(0.32, 0.4,100,100);
		glTranslatef(0.0f, 0.2f, 0.0f);
		glScalef(1.2f, 0.8f, 0.8f);
		cube();
		glPopMatrix();
	glEndList();

}

void draw_decking()
{
	decking = glGenLists(7);
	glNewList(decking, GL_COMPILE);

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -2.0f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -3.1f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -4.2f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -5.3f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -6.4f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -7.5f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -8.6f);
	glScalef(18.0f, 0.1f, 0.5f);
	cube();
	glPopMatrix();

	//right

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -18.0f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -16.9f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -15.8f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -14.7f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -13.6f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -12.5f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -11.4f);
	glScalef(18.0f, 0.1f, 1.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.9f, -10.3f);
	glScalef(18.0f, 0.1f, 0.5f);
	cube();
	glPopMatrix();


	glEndList();
}


void draw_handle_cage()
{
	handle_cage = glGenLists(5);
	glNewList(handle_cage, GL_COMPILE);
	 glColor3fv(red);
	 glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	 glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	 glMateriali(GL_FRONT, GL_SHININESS, 30); //strength
		glPushMatrix();
		glTranslatef(3.5, 0.0f, 0.0f);
		glRotatef(15, 0.0f, 0.0f, 1.0f);
		//glTranslatef(4.0, 0.0, 0.0);
		glScalef(0.4f, 8.0f, 0.5f);
		cube();
		glPopMatrix();

		glPushMatrix();
		glRotatef(-15, 0.0f, 0.0f, 1.0f);
		glScalef(0.4f, 8.0f, 0.5f);
		cube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.75f, 3.5f, 0.0f);
		glRotatef(-90, 0.0f, 0.0f, 1.0f);
		glScalef(0.4f, 2.0f, 0.5f);
		cube();
		glPopMatrix();
	glEndList();
}

void draw_axle_holders()
{
	axle_holders = glGenLists(8);
	glNewList(axle_holders, GL_COMPILE);
	glPushMatrix();
		glTranslatef(3.0f, 0.0f, -2.0f);
		glCallList(axle_holder);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.0f, 0.0f, -18.0f);
		glCallList(axle_holder);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(13.0f, 0.0f, -2.0f);
		glCallList(axle_holder);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(13.0f, 0.0f, -18.0f);
		glCallList(axle_holder);
	glPopMatrix();

	glEndList();


}

void draw_frame()
{
	frame = glGenLists(9);
	glNewList(frame, GL_COMPILE);
	glPushMatrix();
	glColor3fv(red);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 30); // how shiney it is
	glPushMatrix();
	glTranslatef(8.0f, 1.0f, -2.0f);
	glScalef(20.0f, 0.8f, 1.0f);
	cube();
   glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0f, 1.0f, -8.0f);
	glScalef(20.0f, 0.8f, 1.0f);
	cube();
   glPopMatrix();

   glPushMatrix();
	glTranslatef(8.0f, 1.0f, -12.0f);
	glScalef(20.0f, 0.8f, 1.0);
	cube();
   glPopMatrix();

   glPushMatrix();
	glTranslatef(8.0f, 1.0f, -18.0f);
	glScalef(20.0f, 0.8f, 1.0f);
	cube();
   glPopMatrix();

   //other cross bars
   glPushMatrix();
   glTranslatef(9.0f, 1.6f, -10.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glScalef(18.0f, 0.6f, 0.5f);
	cube();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(16.0f, 1.6f, -10.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glScalef(18.0f, 0.6f, 1.0f);
	cube();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.0f, 1.6f, -10.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glScalef(18.0f, 0.6f, 1.0f);
	cube();
   glPopMatrix();
   glPopMatrix();

   glPushMatrix();
	glColor3fv(wood);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wood);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
	glMateriali(GL_FRONT, GL_SHININESS, 10); // how shiney it is
	glPushMatrix();
		glTranslatef(6.0f, 0.0f, -9.6f);		
		glutSolidCylinder(0.2f, 8, 100, 100);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(6.0f, 0.0f, -2.0f);
		glCallList(axle_holder);
	glPopMatrix();
	glPopMatrix();

   glPushMatrix();
	glTranslatef(6.0f, 5.0f, -8.0f);
	   glPushMatrix();
			glCallList(handle_cage);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -4.0f);
			glCallList(handle_cage);
		glPopMatrix();
	glPopMatrix();	

	glPushMatrix();
	glTranslatef(7.75f, 1.8f, -12.4f);
	glScalef(5.6f, 1.2f, 0.2f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.75f, 1.8f, -7.4f);
	glScalef(5.6f, 1.2f, 0.2f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.25f, 3.3f, -10);
	glRotatef(15, 0.0f, 0.0f, 1.0f);
	glScalef(0.2f, 2.0f, 5.0f);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.25f, 3.3f, -10);
	glRotatef(-15, 0.0f, 0.0f, 1.0f);
	glScalef(0.2f, 2.0f, 5.0f);
	cube();
	glPopMatrix();

	glCallList(decking);

	glEndList();
}


void display(void)
{
	glClearColor(0.0,0.0,0.0,1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

    // set up the camera position
	gluLookAt(eyex, eyey, eyez, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//draws all of the holders for the axles
	glCallList(axle_holders);

	//draws the smallest gear
	glPushMatrix();
		glTranslatef(3.0f, 0.0f, -9.5f);
		glRotatef(2*angle, 0.0f, 0.0f, 1.0f);
		glCallList(gear1);
	glPopMatrix();
	
	//draws large gear
	glPushMatrix();
		glTranslatef(6.0f, 0.0f, -9.2f);
		glRotatef(-angle, 0.0f, 0.0f, 1.0f);
		glCallList(gear2);
	glPopMatrix();

	//drive axle
	glPushMatrix();
		glTranslatef(3.0f, 0.0f, 0.0f);
		glRotatef(2*angle, 0.0f, 0.0f, 1.0f);
		glCallList(axle);
	glPopMatrix();

	//back axle
	glPushMatrix();
		glTranslatef(13.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glCallList(axle);
	glPopMatrix();

	//draws the rest of the cart
	glCallList(frame);

	//draws the crank angle, and rotates it like a piston
	glPushMatrix();
	glColor3fv(black);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	 glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
		glMateriali(GL_FRONT, GL_SHININESS, 120); // how shiney it is
		glTranslatef(6.0f, 0.0f, -8.5f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		draw_crank();
    glPopMatrix();

	//draws the handle rotating in a manner similar to the piston
	glPushMatrix();
	glTranslatef(7.7f, 8.5f, -10.3f);	
	glPushMatrix();
		glPushMatrix();
			glRotatef((5*-head_angle), 0.0f, 0.0f, 1.0f);
			glTranslatef(3.5f, 0.0f, 0.0f);
			glCallList(handle);
		glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//axle for handle
	glPushMatrix();
		glTranslatef(12.8f, 8.5f, -12.0f);		
		glTranslatef(-5.0f, 0.0f, 0.0f);
		glPushMatrix();
		glutSolidCylinder(0.2, 4.0, 100, 100);
		glPopMatrix();
	glPopMatrix();
  

   glutSwapBuffers();


}

void draw_handle()
{
	handle = glGenLists(6);
	glNewList(handle, GL_COMPILE);
	glColor3fv(black);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	 glMaterialfv(GL_FRONT, GL_SPECULAR, specular); // the specular light colour
		glMateriali(GL_FRONT, GL_SHININESS, 120); // how shiney it is
		glPushMatrix();
		
		glTranslatef(0.0f, 0.0f, 0.0f);
		glRotatef(30, 0.0f, 1.0f, 0.0f);
	   glScalef(1.5f, 0.8f, 0.1f);
	   cube();
	   glPopMatrix();

	   	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.8f);
		glRotatef(-30, 0.0f, 1.0f, 0.0f);
	   glScalef(1.5f, 0.8f, 0.1f);
	   cube();
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(0.8f, 0.0f, 1.15f);
	   glutSolidCylinder(0.45, 0.1, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(0.8f, 0.0f, -0.45f);
	   glutSolidCylinder(0.45, 0.1, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(-7.0f, 0.0f, 0.0f);
		glRotatef(-30, 0.0f, 1.0f, 0.0f);
	   glScalef(1.5f, 0.8f, 0.1f);
	   cube();
	   glPopMatrix();

	   	glPushMatrix();
		glTranslatef(-7.0f, 0.0f, 0.8f);
		glRotatef(30, 0.0f, 1.0f, 0.0f);
	   glScalef(1.5f, 0.8f, 0.1f);
	   cube();
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(-7.8f, 0.0f, 1.15f);
	   glutSolidCylinder(0.45, 0.1, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(-7.8f, 0.0f, -0.45f);
	   glutSolidCylinder(0.45, 0.1, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	   glColor3fv(wood);
	   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wood);
	   glTranslatef(-7.8f, 0.0f, -3.0f);
	   glutSolidCylinder(0.25, 7.0, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	   glColor3fv(wood);
	   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wood);
	   glTranslatef(0.8f, 0.0f, -3.0f);
	   glutSolidCylinder(0.25, 7.0, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	    glColor3fv(black);
	   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
		glTranslatef(-3.5f, 0.0f, 0.4f);
	   glScalef(6.0f, 0.8f, 0.1f);
	   cube();
	   glPopMatrix();
	glEndList();

}



//Makes the head look up table for all possible crank angles. (adapted from OpenGL Engine.c sample)
void 
make_table(void)
{
  GLint i;
  GLdouble k;

  for (i = 0, k = 0.0; i < 360; i++, k++) {
    head_look_up_table[i] =
      MAGNITUDE * atan(
      (ARC_RADIUS * sin(PHASE - k / FREQ_DIV)) /
      ((ARC_LENGHT - ARC_RADIUS * cos(PHASE - k / FREQ_DIV))));
  }
}

void init(void)
{

   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FILL);

   glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

   glLightfv(GL_LIGHT0, GL_POSITION, pos);
   glEnable(GL_CULL_FACE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);

   make_table();
   draw_large_gear();
   draw_small_gear();
   draw_axle();
   draw_axle_holder();
   draw_axle_holders();
   draw_handle_cage();
   draw_handle();
   draw_decking();
   draw_frame();
   
}


//new window size or exposure
static void reshape(int width, int height)
{
	GLfloat h = (GLfloat) height / (GLfloat) width;
	glViewport(0, 0, (GLint) width, (GLint) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -h, h, 5.0, 400.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* change view angle, exit upon ESC */
/* ARGSUSED1 */
static void key(unsigned char k, int x, int y) {
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);

	switch (k) {
	case 'w':
		eyez -= 3.0f;
		break;
	case 's':
		eyez += 3.0f;
		break;
	case 'a':
		eyex -= 3.0f;
		break;
	case 'd':
		eyex += 3.0f;
		break;
	case 'z':
		angle += 5;
		animation();
		break;
	case 27:  /* Escape */
		exit(0);
		break;
	default:
		return;
	}

	glutPostRedisplay();
}


static void special(int k, int x, int y)
{
  switch (k) {
  case GLUT_KEY_LEFT:
    eyey += 5.0;
    break;
  case GLUT_KEY_RIGHT:
    eyey -= 5.0;
    break;
  default:
    return;
  }
  glutPostRedisplay();
}

static void idle(void)
{
	//animation();
	//angle = angle + 0.5;	
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Ben's Really Red Railroad Handcar");

   printf("Ben's Really Red Railroad Handcar \n Controls: WASD to for forwards, backwards and strafing \n UP and DOWN on keyboard for moving on the z axis. \n Z and X speed up and slow down while C switches direction.");

   init ();
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(key);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}

