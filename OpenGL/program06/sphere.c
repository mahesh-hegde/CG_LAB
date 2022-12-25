// Draw 3-D sphere using tessellation
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

int R = 50;

double toRadian(int degree) {
	return degree * (double)3.14 / (double)180.0;
}

void draw(void) {
	glColor3f(1,0,0);
	glLineWidth(2.0);

	// lattitudes
	for (int phi = -80; phi <= 80; phi += 20) {
		float z = R * sin(toRadian(phi));
		glBegin(GL_QUAD_STRIP);
		for (int theta = -180; theta <= 180; theta += 20) {
			double cos_theta = cos(toRadian(theta));
			double sin_theta = sin(toRadian(theta));
			double cos_phi = cos(toRadian(phi));
			double x = R * sin_theta * cos_phi;
			double y = R * cos_theta * cos_phi;
			int isOddIter = (theta % 40) / 20;
			glColor3f(isOddIter, !isOddIter, isOddIter);
			glVertex3d(x, y, z);
			cos_phi = cos(toRadian(phi+20));
			x = R * sin_theta * cos_phi;
			y = R * cos_theta * cos_phi;
			double z1 = R * sin(toRadian(phi+20));
			glColor3f(isOddIter, isOddIter, isOddIter);
			glVertex3d(x, y, z1);
		}
		glEnd();
		glFlush();
	}
	// poles
	for (int side = -1; side <= 1; side += 2) { // side = 1, -1
		int z = R * sin(toRadian(80)) * side;
		glBegin(GL_TRIANGLE_FAN);
		for (int theta = -180; theta <= 180; theta += 20) {
			int x = R * sin(toRadian(theta)) * cos(toRadian(80));
			int y = R * cos(toRadian(theta)) * cos(toRadian(80));
			glVertex3i(x, y, z);
		}
		glEnd();
		glFlush();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-R, R, -R, R, -R, R);
	glRotatef(-60, 0, 1, 0);
	draw();
	glPopMatrix();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);

	glutInitWindowSize(500, 500);
	glutCreateWindow("Sphere by tesselation");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutDisplayFunc(display);
	glutMainLoop();
}
