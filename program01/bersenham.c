#include <GL/glut.h>
#include <stdio.h>
#define SWAP(x,y) do { typeof(x) temp = x; x = y; y = temp; } while (0)

#define WINDOW_WIDTH 500

typedef int point[2];

int abs(int n) {
	return n < 0 ? -n : n;
}

void drawPoint(int x, int y, int inv) {
	inv ? glVertex2i(y, x) : glVertex2i(x, y);
}

void drawLine(point a, point b) {
	// Convert to a canonical form.
	// 1. |m| < 1, so we can always increment x by 1.
	// 2. first point is always before second point.

	int dx = abs(b[0] - a[0]);
	int dy = abs(b[1] - a[1]);
	int inv = 0;

	if (dx < dy) {
		inv = 1;
		SWAP(a[0], a[1]);
		SWAP(b[0], b[1]);
		SWAP(dx, dy);
	}

	if (a[0] > b[0]) SWAP(a, b);

	int x = a[0], y = a[1];

	int incY = b[1] > a[1] ? 1 : -1;

	// decision parameter. (whether to increment dependent value (y).)
	int e = 2*dy - dx;
	int twoDy = 2*dy;
	int twoDyMinusDx = 2*(dy-dx);
	glColor3f(1,0,0);
	glBegin(GL_POINTS);
	for (int i = 1; i <= dx; i++) {
		if (e > 0) {
			y += incY;
			e += twoDyMinusDx;
		} else {
			e += twoDy;
		}
		x ++;
		drawPoint(x, y, inv);
	}
	glEnd();
	glFlush();
}

void init() {
	// This has to be in init() and not in display().
	// On some systems, this can cause inconsistencies, eg: when switching
	// between windows.
	//
	// A better solution might be to store the line endpoints and persist them
	// between redrawings. But this is a lab program.
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-250, 250, -250, 250);
	glColor3f(1,0,0);
	glPointSize(2.0);
}

point a, b;
void mouse(int button, int state, int x, int y) {
	if (button != GLUT_LEFT_BUTTON) return;
	if (state == GLUT_DOWN) {
		// We have to convert between openGL coordinate system
		// (origin at bottom left) & our coordinate system (origin at center).
		a[0] = x - WINDOW_WIDTH / 2;
		a[1] = WINDOW_WIDTH / 2 - y;
	} else {
		b[0] = x - WINDOW_WIDTH / 2;
		b[1] = WINDOW_WIDTH / 2 - y;
		printf("(%d, %d) - (%d, %d)\n", a[0], a[1], b[0], b[1]);
		drawLine(a, b);
	}
}

void display() {
	printf("display called\n");
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
	glutCreateWindow("Bersenham Line Drawing");

	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
}
