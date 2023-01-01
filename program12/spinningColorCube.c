#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

typedef double point[3];

point corners[] = {{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},
				 {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}};

void polygon(int p, int q, int r, int s) {
	int indices[] = {p, q, r, s};
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		double *corner = corners[indices[i]];
		glColor3d((corner[0] + 1.0) / 2.0, (corner[1] + 1.0) / 2.0,
				(corner[2] + 1.0) / 2.0);
		glVertex3dv(corner);
	}
	glEnd();
}

void cube() {
	polygon(0, 1, 2, 3);
	polygon(2, 3, 7, 6);
	polygon(0, 3, 7, 4);
	polygon(4, 5, 6, 7);
	polygon(1, 2, 6, 5);
	polygon(0, 1, 5, 4);
}

int theta[3] = {0}, axis = -1;

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	cube();
	glutSwapBuffers();
	glPopMatrix();
}

void idle() {
	if (axis != -1)
		theta[axis] = (theta[axis] + 1) % 360;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (state != GLUT_DOWN) return;
	if (button == GLUT_LEFT_BUTTON) axis = 0;
	if (button == GLUT_MIDDLE_BUTTON) axis = 1;
	if (button == GLUT_RIGHT_BUTTON) axis = 2;
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1, 1, 1, 1);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);

	glutInitWindowSize(500, 500);
	glutCreateWindow("Spinning color cube");

	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
}
