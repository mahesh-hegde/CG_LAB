## OpenGL programs (Computer Graphic lab).
The dreaded CG lab programs done to a best effort level.

## General techniques (when desperate).

* glPushMatrix, glLoadIdentity, glPopMatrix when something doesn't work

## Some other common mistakes
* not calling glClearColor
* using int with loss of FP precision.

## CheckList for 3D programs
These are the hardest to get right.

* Enable GLUT_DEPTH and glEnable(DEPTH_TEST)

* clear depth buffer along with color buffer in display()

* __Use glOrtho not gluOrtho2D__ - IMP

* one-time init (usually):
```c
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glMatrixMode(GL_MODELVIEW);
```

