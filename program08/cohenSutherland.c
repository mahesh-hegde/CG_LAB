#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

int TOP = 1;
int BOTTOM = 2;
int RIGHT = 4;
int LEFT = 8;

int xmax, xmin, ymax, ymin;
int xvmax, xvmin, yvmax, yvmin;

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

int getOutcode(int x, int y) {
	int code = 0;
	code |= (x > xmax) * RIGHT;
	code |= (y > ymax) * TOP;
	code |= (x < xmin) * LEFT;
	code |= (y < ymin) * BOTTOM;
	return code;
}

int atX(double x0, double y0, double x1, double y1, double x) {
	return y0 + (y1 - y0) / (x1 - x0) * (x - x0);
}

int atY(double x0, double y0, double x1, double y1, double y) {
	return x0 + (x1 - x0) / (y1 - y0) * (y - y0);
}

void cohenSutherLand(int x0, int y0, int x1, int y1) {
	int accept = 1;
	int xnew, ynew;
	do {
		int out0 = getOutcode(x0, y0), out1 = getOutcode(x1, y1);
		int out = out0 ? out0 : out1;
		if (!(out0 | out1)) {
			accept = 1;
			break;
		} else if (out0 & out1) {
			accept = 0;
			break;
		} else if (out & TOP) {
			xnew = atY(x0, y0, x1, y1, ymax);
			ynew = ymax;
		} else if (out & BOTTOM) {
			xnew = atY(x0, y0, x1, y1, ymin);
			ynew = ymin;
		} else if (out & RIGHT) {
			ynew = atX(x0, y0, x1, y1, xmax);
			xnew = xmax;
		} else if (out & LEFT) {
			ynew = atX(x0, y0, x1, y1, xmin);
			xnew = xmin;
		} else {
			accept = 1;
			break;
		}

		if (out0) {
			x0 = xnew;
			y0 = ynew;
		} else {
			x1 = xnew;
			y1 = ynew;
		}
		printf("(%d, %d) - (%d, %d)\n", x0, y0, x1, y1);
	} while (1);

	glLineWidth(3.0);
	glColor3f(1, 0, 0);
	printf("%d,%d | %d,%d\n", x0, y0, x1, y1);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();
	glFlush();
	// map line to viewport
	double sx = (double)(xvmax - xvmin) / (double)(xmax - xmin);
	double sy = (double)(yvmax - yvmin) / (double)(ymax - ymin);
	int vx0 = xvmin + (x0 - xmin) * sx;
	int vy0 = yvmin + (y0 - ymin) * sy;
	int vx1 = xvmin + (x1 - xmin) * sx;
	int vy1 = yvmin + (y1 - ymin) * sy;

	// draw clipped line on viewport
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex2i(vx0, vy0);
	glVertex2i(vx1, vy1);
	glEnd();
	glFlush();
}

void drawRect(int points[][2]) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex2iv(points[i]);
	}
	glEnd();
	glFlush();
}

void init() {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-250, 250, -250, 250);
	int pw[][2] = {{xmin, ymin}, {xmax, ymin}, {xmax, ymax}, {xmin, ymax}};
	drawRect(pw);
	int pv[][2] = {{xvmin, yvmin}, {xvmax, yvmin}, {xvmax, yvmax}, {xvmin, yvmax}};
	drawRect(pv);
}

void display() {}

int lx, ly;
void mouse(int button, int state, int x, int y) {
	if (button != GLUT_LEFT_BUTTON) return;

	x = x - 250;
	y = 250 - y;

	if (state == GLUT_DOWN) {
		lx = x;
		ly = y;
	} else {
		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
		glVertex2i(lx, ly);
		glVertex2i(x, y);
		glEnd();
		glFlush();
		cohenSutherLand(lx, ly, x, y);
	}
}

int main(int argc, char **argv) {
	printf("Enter window coordinates (xmin, xmax, ymin, ymax): ");
	scanf("%d%d%d%d", &xmin, &xmax, &ymin, &ymax);
	printf("Enter viewport coordinates (xvmin, xvmax, yvmin, yvmax): ");
	scanf("%d%d%d%d", &xvmin, &xvmax, &yvmin, &yvmax);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cohen-sutherland line clipping");
	
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
}
