#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define WIN_SIZE 500
#define SWAP(x,y) do { typeof(x) temp = x; x = y; y = temp; } while (0)

typedef int point[2];

void drawPixels(int xc, int yc, int x, int y) {
	for (int i = 0; i < 8; i++) {
		int x1 = x, y1 = y;
		if (i & 1) x1 = -x1;
		if (i & 2) y1 = -y1;
		if (i & 4) SWAP(x1, y1);
		glVertex2i(xc + x1, yc + y1);
	}
}

void drawCircle(int xc, int yc, int r) {
	int x = 0, y = r;
	int d = 3 - 2*r; // decision parameter - toDecreaseYOrNot?
	glBegin(GL_POINTS);
	while (x < y) {
		x++;
		if (d > 0) {
			y--;
			d += 4 * (x - y) + 6;
		} else {
			d += 4 * x + 6;
		}
		drawPixels(xc, yc, x, y);
	}
	glEnd();
	glFlush();
}

void display();

int _xc, _yc, _x, _y;

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		// adjust coordinates wrt origin at center
		x = x - WIN_SIZE/2;
		y = WIN_SIZE/2 - y;
		if (state == GLUT_DOWN) {
			_xc = x;
			_yc = y;
		} else {
			int dx = x - _xc;
			int dy = y - _yc;
			int r = (int)(sqrt(dx*dx + dy*dy) + 0.5);
			drawCircle(_xc, _yc, r);
		}
	}
}

void display() {}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

	glutInitWindowSize(WIN_SIZE, WIN_SIZE);
	glutCreateWindow("Bresenham's Circle Drawing");

	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
}
