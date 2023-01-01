#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>

#define WIN_SIZE 500
#define MAX_PTS 32

#define SWAP(x,y) do { typeof(x) temp = x; x = y; y = temp; } while (0)

typedef int point[2];
const int AFFINITY = 10;

int yLow = 500, yHigh = -500;
// Can skip these if taking coordinates from scanf
int bx, by, isDrawing = 0;
// in C++, can just use a vector.
point pts[MAX_PTS];
int ptsSize = 0;

int abs(int x) {
	return x < 0 ? -x : x;
}

int isCloseToBegin(int x, int y) {
	return abs(bx - x) < AFFINITY && abs(by - y) < AFFINITY;
}

void init() {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-250, 250, -250, 250);
}

void drawPolygon(int, int, int, int);

int compareInt(const void *x, const void *y) {
	return (*(int *)x - *(int *)y);
}

void scanLineFill(int state) {
	glColor3f(1, 0, 0);
	int intersect[MAX_PTS];
	int intSize = 0;
	if (yHigh-2 > yLow) {
		for (int i = 0; i < ptsSize; i++) {
			double x1 = pts[i][0];
			double y1 = pts[i][1];
			double x2 = pts[(i+1)%ptsSize][0];
			double y2 = pts[(i+1)%ptsSize][1];
			if (y2 < y1) {
				SWAP(x1, x2);
				SWAP(y1, y2);
			}
			// Only if scan line (yLow) is in range of the line.
			if (yLow > y1 && yLow < y2)
				intersect[intSize++] = x1 + (x2 - x1) * (yLow - y1) / (y2 - y1);
		}
		qsort(intersect, intSize, sizeof(int), compareInt);
		glBegin(GL_LINES);
		for (int i = 0; i < intSize - 1; i += 2) {
			glVertex2i(intersect[i], yLow);
			glVertex2i(intersect[i+1], yLow);
		}
		glEnd();
		glFlush();

		yLow++;
		glutTimerFunc(100, scanLineFill, 0);
	} else {
		glutMouseFunc(drawPolygon);
		yHigh = -500;
		yLow = 500;
	}
}

// Optional - let user draw polygon on canvas, instead of taking input from scanf.
void drawPolygon(int button, int state, int x, int y) {
	glColor3f(0, 1, 0);
	glLineWidth(3.0);
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;
	x = x - WIN_SIZE/2;
	y = WIN_SIZE/2 - y;
	if (y < yLow) yLow = y;
	if (y > yHigh) yHigh = y;
	if (isDrawing) {
		if (isCloseToBegin(x, y)) {
			x = bx;
			y = by;
			isDrawing = 0;
			// Delay before next update, because we are not redrawing the display explicitly.
			// In case of a previous animation program, we would just call glutPostRedisplay
			// which will draw the change in next frame only.
			//
			// Now without timing, scan lines will be drawn instantly, since glutIdleFunc will be
			// called as frequently as possible.
			//
			// Can also us glutIdleFunc with a timeout or busy loop.
			// But glutTimerFunc is meant for this.
			glutTimerFunc(100, scanLineFill, 0);
			glutMouseFunc(NULL);
		} else if (abs(x - pts[ptsSize-1][0]) < AFFINITY) {
			// Make it easy to draw horizontal and vertical lines,
			// by adjusting some affinity.
			x = pts[ptsSize-1][0];
		} else if (abs(y - pts[ptsSize -1][1]) < AFFINITY) {
			y = pts[ptsSize-1][1];
		}
		glBegin(GL_LINES);
		glVertex2iv(pts[ptsSize-1]);
		glVertex2i(x, y);
		glEnd();
		glFlush();
	} else {
		isDrawing = 1;
		ptsSize = 0;
		bx = x;
		by = y;
	}
	if (isDrawing) {
		pts[ptsSize][0] = x;
		pts[ptsSize][1] = y;
		ptsSize++;
	}
}

void displayNone() {}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

	glutInitWindowSize(500, 500);
	glutCreateWindow("Scan line polygon filling");

	init();
	glutMouseFunc(drawPolygon);
	glutDisplayFunc(displayNone);
	glutMainLoop();
}
