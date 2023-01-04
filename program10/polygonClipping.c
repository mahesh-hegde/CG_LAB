#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

typedef int point[2];

const double W = 500;

const int drawPoly = 0;
const int drawWindow = 1;
int drawingState = drawPoly;

#define MAX_PTS 64
const int AFFINITY = 5;

int lx, ly, bx, by, isDrawing = 0;

int abs(int x) { return x < 0 ? -x : x; }

int isClose(int x, int y) {
	return (abs(bx -x) < AFFINITY && abs(by - y) < AFFINITY);
}

point poly[MAX_PTS];
point clipper[MAX_PTS];
int poly_size, clipper_size;

// check if (x, y) is to the left of point a;
int isInside(point a, point b, point p) {
	return ((b[0] - a[0]) * (p[1] - a[1]) - 
			(b[1] - a[1]) * (p[0] - a[0])) >= 0;
}

// compute intersection of points
void intersection(point a, point b, point c, point d, point out) {
	int dx1 = b[0] - a[0];
	int dy1 = b[1] - a[1];
	int dx2 = d[0] - c[0];
	int dy2 = d[1] - c[1];
	int denom = dx2*dy1 - dx1*dy2;
	int cross1 = (a[0] * b[1] - b[0] * a[1]);
	int cross2 = (c[0] * d[1] - d[0] * c[1]);
	out[0] = (cross1 * dx2 - cross2 * dx1) / denom;
	out[1] = (cross1 * dy2 - cross2 * dy1) / denom;
}

// clip polygon with respect to an edge (a, b)
void clipWithEdge(point poly[], int *size, point a, point b) {
	point ptsd[MAX_PTS] = {0};
	int ptsdSize = 0;
	for (int i = 0; i < *size; i++) {
		int k = (i+1) % *size;
		int isIInside = isInside(a, b, poly[i]);
		int isKInside = isInside(a, b, poly[k]);
		if (isIInside && isKInside) {
			// add 2nd point only
			memcpy(&ptsd[ptsdSize++], &poly[k], sizeof(poly[k]));
		} else if (isIInside) {
			// add intersection point
			point intersect;
			intersection(a, b, poly[i], poly[k], intersect);
			memcpy(&ptsd[ptsdSize++], intersect, sizeof(intersect));
		} else if (isKInside) {
			// add both intersection and endpoint
			point intersect;
			intersection(a, b, poly[i], poly[k], intersect);
			memcpy(&ptsd[ptsdSize++], intersect, sizeof(intersect));
			memcpy(&ptsd[ptsdSize++], poly[k], sizeof(poly[k]));
		} else {
			// add no point
		}
	}
	memcpy(poly, ptsd, sizeof(ptsd));
	*size = ptsdSize;
}

void clipAll() {
	printf("clipper_size = %d\n", clipper_size);
	for (int i = 0; i < clipper_size; i++) {
		clipWithEdge(poly, &poly_size, clipper[i], clipper[(i+1)%clipper_size]);
	}
	glColor3f(0, 1, 1);
	glPointSize(4.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < poly_size; i++) {
		glVertex2iv(poly[i]);
	}
	glEnd();
	glFlush();
}

void init() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-W/2, W/2, -W/2, W/2);
	glFlush();
}

void display() {}

// Optional: Draw polygon and clipper shape using mouse
void mouse(int button, int state, int x, int y) {
	point *pts;
	int *size;
	if (drawingState == drawPoly) {
		pts = poly;
		size = &poly_size;
		glColor3f(0, 1, 0);
	} else {
		pts = clipper;
		size = &clipper_size;
		glColor3f(1, 0, 0);
	}
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;
	x = x - W/2;
	y = W/2 - y;
	int clipNow = 0;
	if (isDrawing) {
		if (isClose(x, y)) {
			x = bx;
			y = by;
			isDrawing = 0;
			if (drawingState == drawWindow) {
				clipNow = 1;
			}
			drawingState = (drawingState + 1) % 2;
		}
		glBegin(GL_LINES);
		glVertex2iv(pts[*size-1]);
		glVertex2i(x, y);
		glEnd();
		glFlush();
	} else {
		bx = x;
		by = y;
		isDrawing = 1;
		*size = 0;
	}
	pts[*size][0] = x;
	pts[*size][1] = y;
	if (isDrawing) {
		*size += 1;
	}
	if (clipNow) {
		clipAll();
		clipNow = 0;
	}
}

int main(int argc, char **argv) {
	printf("Please draw polygon in anticlockwise only\n");
	printf("First draw polygon to be clipped, then the clipper window; Both can have arbitrary shape.\n");
	printf("To draw a polygon, click the points in anticlockwise order.\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	
	glutInitWindowSize(W, W);
	glutCreateWindow("Poligon clipping");

	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
}
