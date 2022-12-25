#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> point;

// Program to draw polygon using mouse

const int AFFINITY = 5;

void display() {}

void init() {
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-300,300,-300,300);
}

point last, polygonBegin;
bool isDrawingAPolygon = false;

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Adjust coordinates
		x = x - 300;
		y = 300 -y;
		if (isDrawingAPolygon) {
			glColor3f(0, 1, 0);
			glLineWidth(2.0);
			int lx = last.first, ly = last.second;
			if (abs(x - polygonBegin.first) < AFFINITY) {
				x = polygonBegin.first;
			}
			if (abs(y - polygonBegin.second) < AFFINITY) {
				y = polygonBegin.second;
			}
			glBegin(GL_LINES);
			glVertex2i(lx, ly);
			printf("(%d, %d) -> (%d, %d)\n", lx, ly, x, y);
			glVertex2i(x, y);
			glEnd();
			glFlush();

			if (polygonBegin == make_pair(x, y)) {
				cout << "Drawing complete" << endl;
				isDrawingAPolygon = false;
				// Maybe unregister mouse function,
				// If reusing this code in some other program.
			}
		} else {
			polygonBegin = {x, y};
			isDrawingAPolygon = true;
		}
		last = {x, y};
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

	glutInitWindowSize(600, 600);
	glutCreateWindow("Draw lines");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
}
