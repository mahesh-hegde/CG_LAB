// Draw 3-D sphere using tessellation
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

int R = 50;

typedef double point[3];

double toRadian(int degree) {
	return degree * (double)3.14 / (double)180.0;
}

void toCartesian(int theta, int phi, point out) {
		double cos_theta = cos(toRadian(theta));
		double sin_theta = sin(toRadian(theta));
		double cos_phi = cos(toRadian(phi));
		out[0] = R * sin_theta * cos_phi;
		out[1] = R * cos_theta * cos_phi;
		out[2] = R * sin(toRadian(phi));
}

void draw(void) {
	glColor3f(1,0,0);
	glLineWidth(2.0);

	// lattitudes
	point xyz;
	for (int phi = -80; phi <= 80; phi += 10) {
		glColor3f(0, 1, 0);
		glBegin(GL_LINE_LOOP);
		for (int theta = -180; theta <= 180; theta += 10) {
			toCartesian(theta, phi, xyz);
			glVertex3dv(xyz);
		}
		glEnd();
		glFlush();
	}

	for (int theta = -180; theta <= 180; theta +=10) {
		glColor3f(1, 0, 0);
		glBegin(GL_LINE_STRIP);
		for (int phi = -90; phi <= 90; phi += 10) {
			toCartesian(theta, phi, xyz);
			glVertex3dv(xyz);
		}
		glEnd();
		glFlush();
	}
}

int rotateAngle = 30;

// optional: mouse function to rotate sphere
void mouse(int button, int state, int x, int y) {
	if (state != GLUT_DOWN) return;
	rotateAngle += (button == GLUT_LEFT_BUTTON) ? 30 : -30;
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-R, R, -R, R, -R, R);
	glRotatef(rotateAngle, 0, 1, 0);
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
	// Optional: to rotate sphere on mouse click
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
}
