
#include <stdlib.h>

#include "gears.c"
#include "parts.c"


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
GLdouble view_h = 270, view_v = 0, head_angle = 0;
GLint crank_angle = 0;

/* Crank rotation step. */
GLdouble crank_step = 5;

int x;
int y;
static GLfloat angle = 0.0;
static GLint gear1, gear2, axle, axle_holder, handle_cage, handle, assem_handle;

void 
animation(void)
{
	printf ("\nCrank Angle: %f", crank_angle);
  if ((crank_angle += crank_step) >= 360)
    crank_angle = 0;
  head_angle = head_look_up_table[crank_angle];
  glutPostRedisplay();
}

void 
myCylinder(GLUquadricObj * object, GLdouble outerRadius,
  GLdouble innerRadius, GLdouble lenght)
{
  glPushMatrix();
    gluCylinder(object, outerRadius, outerRadius, lenght, 20, 1);
    glPushMatrix();
      glRotatef(180, 0.0, 1.0, 0.0);
      gluDisk(object, innerRadius, outerRadius, 20, 1);
    glPopMatrix();

    glTranslatef(0.0, 0.0, lenght);
    gluDisk(object, innerRadius, outerRadius, 20, 1);
  glPopMatrix();
}

/* Draws a piston.  */
void 
draw_piston(void)
{
  glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCylinder(0.2, 12.6, 100, 100);
    //myCylinder(obj, 0.06, 0.0, 0.6);
  glPopMatrix();

  glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
	glutSolidCylinder(0.2, 1.0, 100, 100);
    //myCylinder(obj, 0.06, 0.0, 0.6);
  glPopMatrix();

  glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -0.3);
	glutSolidCylinder(0.3, 0.5, 100, 100);
    //myCylinder(obj, 0.06, 0.0, 0.6);
  glPopMatrix();
}


/* Draws the crank bell, and the pivot pin for the piston. Also calls the
   appropreate display list of a piston doing the nesacary rotations before
   hand.  */
void 
draw_crankbell(void)
{
    glRotatef(40, 1.0, 0.0, 0.0);
	glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(1.0, 0.0, 0.0);

		glTranslatef(0.0, 0.0, 1.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		glRotatef(crank_angle - head_angle, 1.0, 0.0, 0.0);
		  draw_piston();
	glPopMatrix();
}

/* Draws the complete crank. Piston also gets drawn through the crank bell
   function. */
void 
draw_crank(void)
{
  glPushMatrix();
    glRotatef(crank_angle, 1.0, 0.0, 0.0);

    glPushMatrix();
      glTranslatef(0.28, 0.0, 0.0);
     draw_crankbell();
    glPopMatrix();
  glPopMatrix();
}

void draw_large_gear()
{
	gear2 = glGenLists(2);
		glNewList(gear2, GL_COMPILE);
		gear(0.2, 2.0, 1.0, 28, 0.2);
	glEndList();
}

void draw_small_gear()
{
	gear1 = glGenLists(1);
		glNewList(gear1, GL_COMPILE);
		gear(0.3, 1.0, 1.0, 14, 0.2);
	glEndList();
}

void draw_axle()
{
	axle = glGenLists(3);
	glNewList(axle, GL_COMPILE);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -20.0);
			glPushMatrix();
			glRotatef(180, 1.0, 0.0, 0.0);
			wheel();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		wheel();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.0, -22.0);
		glTranslatef(0.0, 0.0, 1.0);
		glutSolidCylinder(0.3, 22.00, 100, 100);
		glTranslatef(0.0, 0.0, 2.0);
	glPopMatrix();
	glEndList();

}

void draw_axle_holder()
{
	axle_holder = glGenLists(4);
	glNewList(axle_holder, GL_COMPILE);
		glPushMatrix();
		glutSolidTorus(0.32, 0.4,100,100);
		glTranslatef(0.0, 0.2, 0.0);
		glScalef(1.2, 0.8, 0.8);
		cube();
		glPopMatrix();
	glEndList();

}


void draw_handle_cage()
{
	handle_cage = glGenLists(5);
	glNewList(handle_cage, GL_COMPILE);
		glPushMatrix();
		glTranslatef(3.5, 0.0, 0.0);
		glRotatef(15, 0.0, 0.0, 1.0);
		//glTranslatef(4.0, 0.0, 0.0);
		glScalef(0.4, 8.0, 0.5);
		cube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.8, 3.6, 0.0);
		glRotatef(90, 0.0, 0.0, 1.0);
		//glTranslatef(4.0, 0.0, 0.0);
		glScalef(0.4, 1.8, 0.5);
		cube();
		glPopMatrix();

		glPushMatrix();
		glRotatef(-15, 0.0, 0.0, 1.0);
		//glTranslatef(4.0, 0.0, 0.0);
		glScalef(0.4, 8.0, 0.5);
		cube();
		glPopMatrix();
	glEndList();
}


void display(void)
{

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

    // set up the camera position
	gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
		glTranslatef(0.0, 0.0, -2.0);
		glCallList(axle_holder);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.0, -18.0);
		glCallList(axle_holder);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(16.0, 0.0, -2.0);
		glCallList(axle_holder);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(16.0, 0.0, -18.0);
		glCallList(axle_holder);
	glPopMatrix();



	

	glPushMatrix();
		glTranslatef(0.0, 0.0, -10.0);
		glRotatef(angle, 0.0, 0.0, 1.0);
		glCallList(gear1);
	glPopMatrix();
	  
	glPushMatrix();
		glTranslatef(3.0, 0.0, -10.0);
		glRotatef(-angle, 0.0, 0.0, 1.0);
		glCallList(gear2);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.0, 0.0, -11.0);
		glutSolidCylinder(0.2, 3.0, 100, 100);
	glPopMatrix();

	glPushMatrix();
		glRotatef(angle, 0.0, 0.0, 1.0);
		glCallList(axle);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(16.0, 0.0, 0.0);
		glRotatef(angle, 0.0, 0.0, 1.0);
		glCallList(axle);
	glPopMatrix();


	//cross bars
	glPushMatrix();
	glTranslatef(8.0, 1.0, -2.0);
	glScalef(20.0, 0.8, 1.0);
	cube();
   glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0, 1.0, -8.0);
	glScalef(20.0, 0.8, 1.0);
	cube();
   glPopMatrix();

   glPushMatrix();
	glTranslatef(13.0, 1.0, -12.0);
	glScalef(10.0, 0.8, 1.0);
	cube();
   glPopMatrix();

   glPushMatrix();
	glTranslatef(8.0, 1.0, -18.0);
	glScalef(20.0, 0.8, 1.0);
	cube();
   glPopMatrix();

   //other cross bars
   glPushMatrix();
   glTranslatef(8.0, 1.8, -10.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(18.0, 0.6, 0.5);
	cube();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(16.0, 1.8, -10.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(18.0, 0.6, 1.0);
	cube();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.0, 1.8, -10.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(18.0, 0.6, 1.0);
	cube();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.8, 2.1, -10.0);
   glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(18.0, 0.2, 3.0);
	cube();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(14.2, 2.1, -10.0);
   glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(18.0, 0.2, 5.0);
	cube();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(6.2, 2.1, -4.0);
   //glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(12.0, 0.2, 6.0);
	cube();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(6.2, 2.1, -16.0);
	glScalef(12.0, 0.2, 6.0);
	cube();
   glPopMatrix();

	glPushMatrix();
		glTranslatef(3.0, 0.0, -10.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		draw_crank();
    glPopMatrix();

	//glTranslatef(16.0, 8.5, -10.3);		
		//glTranslatef(-5.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(7.7, 8.5, -10.3);	
	//glTranslatef(-5.0, 0.0, 0.0);
	glPushMatrix();
		glPushMatrix();
			glRotatef(angle, 0.0, 0.0, 1.0);
			glTranslatef(3.5, 0.0, 0.0);
			glCallList(handle);
		glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.8, 8.5, -12.3);		
		//glRotatef((3* -head_angle), 0.0, 0.0, 1.0);
		glTranslatef(-5.0, 0.0, 0.0);
		glPushMatrix();
		glutSolidCylinder(0.25, 4.0, 100, 100);
		glPopMatrix();
	glPopMatrix();

   glPushMatrix();
	glTranslatef(6.0, 5.0, -8.0);
	   glPushMatrix();
			//glTranslatef(0.0, 0.0, -4.0);
			glCallList(handle_cage);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 0.0, -4.0);
			glCallList(handle_cage);
		glPopMatrix();
	glPopMatrix();	
  

   glutSwapBuffers();


}

void draw_handle()
{
	handle = glGenLists(6);
	glNewList(handle, GL_COMPILE);
		glPushMatrix();
		
		glTranslatef(0.0, 0.0, 0.0);
		glRotatef(30, 0.0, 1.0, 0.0);
	   glScalef(1.5, 0.8, 0.1);
	   cube();
	   glPopMatrix();

	   	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.8);
		glRotatef(-30, 0.0, 1.0, 0.0);
	   glScalef(1.5, 0.8, 0.1);
	   cube();
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(0.8, 0.0, 1.15);
	   glutSolidCylinder(0.45, 0.1, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(0.8, 0.0, -0.45);
	   glutSolidCylinder(0.45, 0.1, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(-7.0, 0.0, 0.0);
		glRotatef(-30, 0.0, 1.0, 0.0);
	   glScalef(1.5, 0.8, 0.1);
	   cube();
	   glPopMatrix();

	   	glPushMatrix();
		glTranslatef(-7.0, 0.0, 0.8);
		glRotatef(30, 0.0, 1.0, 0.0);
	   glScalef(1.5, 0.8, 0.1);
	   cube();
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(-7.8, 0.0, 1.15);
	   glutSolidCylinder(0.45, 0.1, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(-7.8, 0.0, -0.45);
	   glutSolidCylinder(0.45, 0.1, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(-7.8, 0.0, -3.0);
	   glutSolidCylinder(0.25, 7.0, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
	   glTranslatef(0.8, 0.0, -3.0);
	   glutSolidCylinder(0.25, 7.0, 100, 100);
	   glPopMatrix();

	   glPushMatrix();
		glTranslatef(-3.5, 0.0, 0.4);
	   glScalef(6.0, 0.8, 0.1);
	   cube();
	   glPopMatrix();
	glEndList();

}







/* Makes the head look up table for all possible crank angles. */
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

   static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0};
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FILL);

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
   draw_handle_cage();
   draw_handle();
   
}


/* new window size or exposure */
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


void keyboard(unsigned char key, int x, int y)
{
	x=y;
   switch (key) {
      case 27:
         exit(0);
         break;
	 case 'a':
		 eyex - 10;
	 // Modify some variable
	 glutPostRedisplay();
	 break;
   }
}

static void
special(int k, int x, int y)
{
  switch (k) {
  case GLUT_KEY_UP:
    eyex += 5.0;
    break;
  case GLUT_KEY_DOWN:
    eyex -= 5.0;
    break;
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



void mouse (int button, int state, int x, int y)
{
	x=y;
  switch (button)  {
    case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			eyez += 5.0;
		 // animation();
		  glutPostRedisplay();
		}
      break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {

		  glutPostRedisplay();
	}
      break;
    default:
      break;
  }
}

static void idle(void)
{
	//animation();
	angle = angle + 0.5;

	
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Simple 3-d program");

   init ();
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}

