#include "timer.h"
#include <GL/glut.h>
#include <cstdio>

static double cubes[2][4] = { //top-left, bottom-rigth
  {0.0, 0.0, 20.0, 20.0}, //blue
  {0.0, 40.0, 20.0, 60.0} //red
};

static Time::ITimer *timer = Time::createTimer();
static Time::ITimer *blue_timer = Time::createTimer();
static Time::ITimer *red_timer = Time::createTimer();

static int slow = false;

void reshape(int w, int h) {
  glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
  glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
  glLoadIdentity();             /* Reset project matrix. */
  glOrtho(0, w, 0, h, -1, 1);   /* Map abstract coords directly to window coords. */
  glScalef(1, -1, 1);           /* Invert Y axis so increasing Y goes down. */
  glTranslatef(0, -h, 0);       /* Shift origin up to upper-left corner. */
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_QUADS);
  glColor3f(0.0, 0.0, 1.0); //blue
  glVertex2f(cubes[0][0], cubes[0][1]);
  glVertex2f(cubes[0][2], cubes[0][1]);
  glVertex2f(cubes[0][2], cubes[0][3]);
  glVertex2f(cubes[0][0], cubes[0][3]);
  glEnd();
  
  glBegin(GL_QUADS);
  glColor3f(1.0, 0.0, 0.0); //red
  glVertex2f(cubes[1][0], cubes[1][1]);
  glVertex2f(cubes[1][2], cubes[1][1]);
  glVertex2f(cubes[1][2], cubes[1][3]);
  glVertex2f(cubes[1][0], cubes[1][3]);
  glEnd();

  glutSwapBuffers();
}

void keyboard(unsigned char key,int x, int y) {
  if (key == 115 && !slow) { // ascii 's'
	blue_timer->setSpeed(0.5);
	slow = true;
  } else {
	blue_timer->setSpeed(1.0);
	slow = false;
  }
}

void idle() {
  timer->tick();
  double time_blue = blue_timer->tick();
  double time_red = red_timer->tick();
  for (int i = 0; i < 4; ++i) {
	cubes[0][i] += time_blue / 10.0;
  }
  for (int i = 0; i < 4; ++i) {
	cubes[1][i] += time_red / 10.0;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("demo");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);

  blue_timer->setParent(timer);
  red_timer->setParent(timer);

  glutMainLoop();
  return 0;
}
