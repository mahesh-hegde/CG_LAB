// Program 4: Draw parallelopiped and a cylinder

#include <GL/glut.h>
#define SWAP(x,y) do { typeof(x) t = x; x = y; y = t; } while (0)

typedef int point[2];

void drawCirclePoints(int xc, int yc, int x, int y) {
	for (int i = 0; i < 8; i++) {
		int x1 = x, y1 = y;
		if (i & 1) x1 = -x1;
		if (i & 2) y1 = -y1;
		if (i & 4) SWAP(x1, y1);
		glVertex2i(xc+x1, yc+y1);
	}
}

void drawCircle(int xc, int yc, int r) {
	int x = 0, y = r;
	int d = 3 - 2 * r;
	glBegin(GL_POINTS);
	drawCirclePoints(xc, yc, x, y);
	while (x < y) {
		x++;
		if (d > 0) {
			y --;
			d += 4 * (x - y) + 6;
		} else {
			d += 4 * x + 6;
		}
		drawCirclePoints(xc, yc, x, y);
	}
	glEnd();
	glFlush();
}

void drawQuad(int hW, int hH, int off) {
	point points[] = {{-hW, -hH}, {hW, -hH}, {hW, hH}, {-hW, hH}};
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex2i(points[i][0] + off, points[i][1]+off);
	}
	glEnd();
	glFlush();
}

void drawParallelopiped() {
	for (int off = -50; off <= 50; off+=5) {
		drawQuad(75, 75, off);
	}
}

void drawCylinder() {
	for (int y = -40; y <= 40; y+=5) {
		drawCircle(0, y, 100);
	}
}

void displayCommon() {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-250,250,-250,250);
	glColor3f(1, 0, 0);
	glPointSize(2.0);
}

void displayParallelopiped() {
	glPushMatrix();
	glLoadIdentity();
	displayCommon();
	drawParallelopiped();
	glPopMatrix();
}

void displayCylinder() {
	glPushMatrix();
	glLoadIdentity();
	displayCommon();
	drawCylinder();
	glPopMatrix();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cylinder");
	glutDisplayFunc(displayCylinder);
	glutCreateWindow("Parallelopiped");
	glutDisplayFunc(displayParallelopiped);
	glutMainLoop();
}
