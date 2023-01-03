#include <stdio.h>
#include <GL/glut.h>

typedef int point[2];
typedef GLfloat color[3];

const GLfloat WIN_SIZE = 500;

int width = 8, height = 6;

// For mutliple windows
int wStatic, wSpin, wCurrent;

int spin = 0, isSpinning = 1;

void drawRectangle() {
	// gluOrtho2D must come after pushing new matrix to opengl transform stack.
	gluOrtho2D(-WIN_SIZE/2, WIN_SIZE/2, -WIN_SIZE/2, WIN_SIZE/2);
	int h = WIN_SIZE / 4;
	int w = h + h / 2;
	point points[] = {{-w, -h}, {w, -h}, {w, h}, {-w, h}};
	color colors[] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glColor3fv(colors[i]);
		glVertex2iv(points[i]);
	}
	glEnd();
}

// We pass single display function to both windows.
// In display function, we set which window will be updated on next time.
// by swapping wCurrent.
void displayStatic() {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	drawRectangle();
	glFlush();
}

void displaySpinning() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(spin, 0, 0, 1);
	drawRectangle();
	glPopMatrix();
	glutSwapBuffers();
}

void spinRectangle(void) {
	glutSetWindow(wSpin);
	spin = (spin + 1) % 360;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		glutSetWindow(wSpin);
		glutIdleFunc(isSpinning ? NULL : spinRectangle);
		isSpinning = !isSpinning;
	}
}

int main(int argc, char **argv) {
	if (argc > 1) {
		width = atoi(argv[1]);
	}
	if (argc > 2) {
		height = atoi(argv[2]);
	}
	if (argc > 3 || !height || !width) {
		fprintf(stderr, "usage: %s [w] [h]\n", argv[0]);
		return 1;
	}

	glutInit(&argc, argv);

	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	wStatic = glutCreateWindow("Static Rectangle (Single buffered)");
	glutDisplayFunc(displayStatic);

	glutInitWindowSize(500, 500);
	// IMPORTANT: GLUT_DOUBLE
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	wSpin = glutCreateWindow("Spinning Rectangle (Double buffered)");
	glutDisplayFunc(displaySpinning);
	// The idle callback is continuously called when events are not being received.
	// alternative: glutTimerFunc
	glutIdleFunc(spinRectangle);
	glutMouseFunc(mouse);

	wCurrent = wSpin;
	glutMainLoop();
}
