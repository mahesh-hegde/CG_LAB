#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

typedef int point[2];

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

const double W = 500.0;

point leftWindow[] = {{-40, 45}, {-20, 45}, {-20, 60}, {-40, 60}};
point rightWindow[] = {{40, 45}, {20, 45}, {20, 60}, {40, 60}};
point door[] = {{0, 10}, {10, 0}, {10, 35}, {0, 25}};
point houseLoop[] = {{-50, 0}, {-10, 0}, {-10, 35}, {10, 35}, {10, 0},
	{50, 0}, {50, 80}, {-50, 80}};
point roof[] = {{-50, 80}, {50, 80}, {0, 120}};

void drawArray(GLenum primitive, point pts[], int size) {
	glBegin(primitive);
	for (int i = 0; i < size; i++) {
		glVertex2iv(pts[i]);
	}
	glEnd();
	glFlush();
}

void drawHouse() {
	glColor3f(1,1,0);
	drawArray(GL_POLYGON, leftWindow, ARRAYSIZE(leftWindow));
	drawArray(GL_POLYGON, rightWindow, ARRAYSIZE(rightWindow));
	glColor3f(0.5, 0, 0);
	drawArray(GL_POLYGON, door, ARRAYSIZE(door));
	glColor3f(1, 1, 1);
	drawArray(GL_LINE_LOOP, houseLoop, ARRAYSIZE(houseLoop));
	glColor3f(0.2, 0, 0);
	drawArray(GL_POLYGON, roof, ARRAYSIZE(roof));
	drawArray(GL_LINE_LOOP, roof, ARRAYSIZE(roof));
}

int reflect = 0;
int x, y, c, angle;
double m;

void display() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-W/2, W/2, -W/2, W/2);
	drawHouse();
	glColor3f(0, 0, 1);
	if (reflect) {
		// draw line
		glColor3f(0, 1, 1);
		glBegin(GL_LINES);
		glVertex2i(-W/2, -W/2 * m + c);
		glVertex2i(W/2, W/2 * m + c);
		glEnd();
		glFlush();

		glTranslatef(0, c, 0);
		glRotatef(180, 1, m, 0);
		glTranslatef(0, -c, 0);
	} else {
		glColor3f(0, 1, 1);
		glPointSize(4.0);
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		glFlush();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-x, -y, 0);
	}
	drawHouse();
	glPopMatrix();
}

int main(int argc, char **argv) {
	int choice;
	printf("1. Rotate around point; 2. Reflect around line: ");
	scanf("%d", &choice);
	if (choice == 1) {
		printf("Enter (x, y): ");
		scanf("%d%d", &x, &y);
		printf("Enter angle of rotation: ");
		scanf("%d", &angle);
	} else if (choice == 2) {
		reflect = 1;
		printf("Enter m, c: ");
		scanf("%lf%d", &m, &c);
	} else {
		printf("Invalid choice\n");
		return 1;
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);

	glutInitWindowSize(W, W);
	glutCreateWindow("Hale Mane");

	glutDisplayFunc(display);
	glutMainLoop();
}
