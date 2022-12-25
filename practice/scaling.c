#include <GL/glut.h>
#include <stdio.h>

GLfloat factor = 1.00;

typedef int point[2];

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,1);
	int half = 4;
	point points[] = {
		{-half, -half},
		{half, -half},
		{half, half},
		{-half, half},
	};
	glPushMatrix();
	glLoadIdentity();
	glScalef(factor, factor, 1.0);
	gluOrtho2D(-5, 5, -5, 5);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 4; i++) {
		glVertex2iv(points[i]);
	}
	glEnd();
	glFlush();
	glPopMatrix();
}

void mouse(int button, int state, int x, int y) {
	if (state != GLUT_DOWN) return;
	if (button == GLUT_LEFT_BUTTON) factor *= 2.0; else factor *= 0.5;
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);

	glutInitWindowSize(500, 500);
	glutCreateWindow("Scaling");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
}
