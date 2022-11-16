#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>

void display(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(-5, 5, -5, 5);
	glLineWidth(2.0);
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
		glVertex2i(10, 10);
		glVertex2i(20, 10);
		glVertex2i(20, 20);
		glVertex2i(10, 20);
	glEnd();
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("OPENGL");
	glutDisplayFunc(display);
	glutMainLoop();
}
