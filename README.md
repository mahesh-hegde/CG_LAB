## OpenGL programs (Computer Graphic lab).
The dreaded CG lab programs done to a best effort level.

## CheckList for 3D programs
These are the hardest to get right.

* Enable GLUT_DEPTH and glEnable(DEPTH_TEST)

* clear depth buffer along with color buffer in display()

* Use glOrtho not gluOrtho2D

* one-time init (usually):
```c
glClearColor(0, 0, 0, 1);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glEnable(GL_DEPTH_TEST);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

glOrtho(-W/2, W/2, -W/2, W/2, -W/2, W/2);
```

