#include <GL/glut.h>

typedef int point[3];

point tetra[] = {
	{-120, 0, 0},
	{120, 0, 0},
	{0, 200, 0},
	{0, 100, -200},
};

const int K = 4;

void drawTriangleSurface(point a, point b, point c) {
	glBegin(GL_TRIANGLES);
	glVertex3iv(a);
	glVertex3iv(b);
	glVertex3iv(c);
	glEnd();
}

void computeMidPoint(point a, point b, point mid) {
	for (int i = 0; i < 3; i++) {
		mid[i] = (a[i] + b[i]) / 2;
	}
}

void divideTriangle(point a, point b, point c, int k) {
	point ab, bc, ca;
	if (k == 0) {
		return drawTriangleSurface(a, b, c);
	}
	computeMidPoint(a, b, ab);
	computeMidPoint(b, c, bc);
	computeMidPoint(c, a, ca);
	// A sub-triangle is made of 2 midpoints & their common vertex
	divideTriangle(ab, bc, b, k-1);
	divideTriangle(ab, ca, a, k-1);
	divideTriangle(bc, ca, c, k-1);
	// do not divide the middle triangle (ab, bc, ca)
}

void gasket(point a, point b, point c, point d) {
	glColor3f(1,0,0);
	divideTriangle(a, b, c, K);
	glColor3f(0,1,0);
	divideTriangle(a, b, d, K);
	glColor3f(0,0,1);
	divideTriangle(a, c, d, K);
	glColor3f(1,1,0);
	divideTriangle(b, c, d, K);
}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -250, 250);
	gasket(tetra[0], tetra[1], tetra[3], tetra[2]);
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);

	glutInitWindowSize(500, 500);
	glutCreateWindow("Serpieeeeeenksy Gaskeeet");

	glutDisplayFunc(display);
	glutMainLoop();
}
