#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

const double W = 500.0;

int xmin, ymin, xmax, ymax;
int xvmin, yvmin, xvmax, yvmax;

void display() {}

void drawRectangle(int points[][2]) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex2iv(points[i]);
	}
	glEnd();
}

void init() {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-W/2, W/2, -W/2, W/2);
	int window[][2] = {{xmin, ymin}, {xmax, ymin}, {xmax, ymax}, {xmin, ymax}};
	int viewport[][2] = {{xvmin, yvmin}, {xvmax, yvmin}, {xvmax, yvmax},
		{xvmin, yvmax}};
	glColor3f(1, 1, 0);
	drawRectangle(window);
	glColor3f(0, 1, 1);
	drawRectangle(viewport);
	glFlush();
}

double max(double x, double y) {
	return x > y ? x : y;
}

double min(double x, double y) {
	return x < y ? x : y;
}

// I remember as: p - direction, q - extent
// t1 - start parameter, t2 - end parameter
// Initially, t1 = 0, t2 = 1 (complete line)
int clipTest(int p, int q, double *t1, double *t2) {
	double t = (double)q/p;
	// 3 cases
	// p < 0 - clip lower parameter
	// p > 0 - clip upper parameter
	// p == 0, no clipping, but check q is non-negative
	if (p < 0) {
		*t1 = max(*t1, t);
		if (t > *t2) return 0;
	} else if (p > 0) {
		*t2 = min(*t2, t);
		if (t < *t1) return 0;
	} else if (p == 0) {
		return q >= 0;
	}
	return 1;
}

void liangBarskyClip(int x0, int y0, int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	double t1 = 0.0;
	double t2 = 1.0;
	if (clipTest(-dx, x0 - xmin, &t1, &t2)
			&& clipTest(dx, xmax - x0, &t1, &t2)
			&& clipTest(-dy, y0 - ymin, &t1, &t2)
			&& clipTest(dy, ymax - y0, &t1, &t2)) {
		if (t2 < 1.0) {
			x1 = x0 + t2 * dx;
			y1 = y0 + t2 * dy;
		}
		if (t1 > 0.0) {
			x0 = x0 + t1 * dx;
			y0 = y0 + t1 * dy;
		}
		// Draw line on the window.
		glLineWidth(3.0);
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2i(x0, y0);
		glVertex2i(x1, y1);
		glEnd();

		// map to viewport and draw there
		double sx = (double)(xvmax - xvmin) / (xmax - xmin);
		double sy = (double)(yvmax - yvmin) / (ymax - ymin);
		double vx0 = xvmin + (x0 - xmin) * sx;
		double vy0 = yvmin + (y0 - ymin) * sy;
		double vx1 = xvmin + (x1 - xmin) * sx;
		double vy1 = yvmin + (y1 - ymin) * sy;

		glLineWidth(2.0);
		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex2i(vx0, vy0);
		glVertex2i(vx1, vy1);
		glEnd();
		glFlush();
	}
}

int lx, ly;
void mouse(int btn, int state, int x, int y) {
	if (btn != GLUT_LEFT_BUTTON) return;
	x = x - W/2;
	y = W/2 -y;
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
		liangBarskyClip(lx, ly, x, y);
	}
}

int main(int argc, char **argv) {
	printf("Window [xmin ymin xmax ymax]:\n");
	scanf("%d%d%d%d",&xmin, &ymin, &xmax, &ymax);
	printf("Viewport [xvmin yvmin xvmax yvmax]:\n");
	scanf("%d%d%d%d", &xvmin, &yvmin, &xvmax, &yvmax);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);

	glutInitWindowSize(W, W);
	glutCreateWindow("Liang Tata Sky");

	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
}
