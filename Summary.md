# Programs summary
## 1. Bersenham Line Drawing
* adjust points such that, dx > dy, and a comes before b
* compute incY
* main code:
``` cpp
// repeat dx times
x++
if (e > 0) {
	y += incY
	e += twoDyMinusDx
} else {
	e += twoDy
}
```

## 2. Bersenham Circle Drawing
```cpp
int x = 0, y = r;
int d = 3 - 2*r
while (x < y) {
	x++;
	if (d > 0) {
		y--;
		d += 4 * (x-y) + 6
	} else {
		d += 4 * x + 6;
	}
}
```

## 3. Spinning & static rectangle
* Use double buffer for one window, single buffer for another
* Call glutSetWindow in the beginning of the function
* Pass single display function to both, swap on display complete
__OR__
* Use separate functions, but do glutSetWindow() in idle function.

## 4. 3D shapes
* Use bersenham circle and GL_LINE_LOOP for shapes
* Extract circle and square into separate functions. I think its good to take [bx, by, h, w] as parameters since there's less chance to mess up the order.
* Draw n 2D shapes. In case of cylinder, It's a good idea to ensure (n * gap) `<`diameter, since otherwise it looks like a spring instead of cylinder.

## 5. Tata sky gasket
* draw 4 surfaces separately.
* There will be 4 possible triangles when dividing
	* any one corner and two midpoints - RECURSE
	* 3 midpoints - SKIP
* if k == 0, draw triangle.

* 3-D program checklist in README

## 6. Sphere
### Polygon Tesselation sphere
* Phi in [-80, 80], theta in [-180, 180]

* Formula
    x = R sin theta cos phi
    y = R cos theta cos phi
    z = R sin phi

* for lattitudes, use formula for each phi and phi + D
* for caps, both side = 1 and -1, draw triangle fan

* glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
* glEnbale(GL_CULL_FACE), glCullFace(GL_BACK);

### Line tesselation sphere
* Same formulae as above. Draw longtitude and lattitude separately.
* Vary phi from -90 to 90 in later case.

## 7. Scan line polygon filling
* For each line
  - Normalize so that y(p2) > y(p1)
  - If line intersects with scan line y = Y, (i.e `y1 < Y <= y2`), then compute x intersect and add to the intersection points.
  - qsort(intersections, n, sizeof_int, compareInt)
  - join every 2 points with GL_LINE
  - use glutTimerFunc(ms, fn, 0) for animation.

## 8. Cohen-Sutherland line clipping algorithm
* Outcode order: TOP, BOTTOM, RIGHT, LEFT
* algorithm
```
do {
	if totally inside or totally outside
		done = 1
	else
		clip one of the points with one of the possible windows
} while (not done)
```

## 9. Liang - Barksy line clipping algorithm
let t1, t2 be limiting parameters of the line, you have to limit parameters so that `0.0 <= t1 < t2 <= 1.0`.

clip in 4 directions

| direction (p) | extent (q) |
| :-----------: | :--------: |
| dx            | xmax - x0  |
| -dx           | x0 - xmin  |
| dy            | ymax - y0  |
| -dy           | y0 - ymax  |
```
t = q/p
case p < 0:                     ## ADJUST LOWER BOUND PARAM
	if (t > *t1) *t1 = t;
	if (t > t2) return false
case p > 0:                     ## ADJUST UPPER BOUND PARAM
	if (t < *t2) *t2 = t;
	if (t < t1) return false;
case p == 0
	if (q < 0) return false;
return true;
```

Check for all pairs of p,q above

Adjust x0, y0, x1, y1 according to t1 and t2.

## 10. Polygon clipping
Belgge odte.

## 11. House
* Rotate against point:
	* translate point to origin, rotate, translate back
	* In openGL, these should be given in reverse order
* Reflect against line y = mx + c
	* This is same as rotating 180 degrees around the axis (1, m, 0)
	* translate the line to origin (0, -c, 0), rotate, translate back(0, c, 0)
	* As before, in reverse order.

## 12. Cube spinning
* Each face to be painted separately. 3 rotation angles to be maintained.
* Color can be mapped from coordinates, no big deal.
* Good idea to keep sides 1 or 2 units, and appropriate glOrtho parameters. With large values I haven't got correct output.
* Points can be listed so that it is easier to group them into faces
	* `{{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}} // front face, z = 0`
	* `{{0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {1, 1, 1}} // back face, z = 1`
	* Other faces can be written similarly from these points
	* The trick - a face is 1 constant coordinate, other 2 varying like a rectangle.

## Miscellaneous

### Find x when given y:
	x = x0 + (x1 - x0) / (y1 - y0) * (y - y0)
	initial + change in X per unit change in Y * change in Y

	Similarly for finding Y when given X.

### Mapping to viewport
* viewport_minimum + scaled point wrt window
* scale can be computed once for each axis.
