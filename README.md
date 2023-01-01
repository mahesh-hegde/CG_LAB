## OpenGL programs (Computer Graphic lab).
The dreaded CG lab programs done to a best effort level.

## General mistakes
* Wrong formula or parenthesis
* Wrong data type (double vs int)
* calling gluOrtho before Identity matrix is loaded

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

