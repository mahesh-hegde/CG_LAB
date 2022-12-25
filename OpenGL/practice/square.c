#include <GL/glut.h>

#include <stdio.h>

typedef int point[2];

void init(void) {}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(-10, 10, -10, 10);

	glLineWidth(2.0);
	glColor3f(1, 1, 1);
	int half = 10;
	point points[] = {{-half, -half}, {half, -half}, {half, half}, {-half, half},};
	glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 4; i++) {
			glVertex2d(points[i][0], points[i][1]);
		}
	glEnd();
	glColor3f(0.5, 0.5, 0);
	glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < 4; i++) {
			glVertex2d(points[i][0], points[i][1]);
		}
	glEnd();
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);

	glutInitWindowSize(500, 500);
	glutCreateWindow("OPENGL");

	glutDisplayFunc(display);
	init();
	glutMainLoop();
}
