# Geometry

> Terms

* Euclidean
  * To draw a straight line from any point to any point
  * To produce (extend) a finite straight line continuously in a straight line
  * To describe a circle with any centre and distance (radius)
  * That all right angles are equal to one another
  * if a straight line falling on two straight lines make the interior angles on the same side less than two right angles
  * two straight lines, if indefinitely, meet on that side on which angles are less than two right angles [The parallel postulate]

* Convex Set: Given any collection of convex sets (finite, countable or uncountable), their intersection is a convex set
* Homeomorphism: a continuous function between topological spaces that has a continuous inverse function
* Inscribed square problem
  * Does every plane simple closed curve contain all four vertices of some square?

* Homeomorphism: a continuous function between topological spaces that has a continuous inverse function
* Inscribed square problem
  * Does every plane simple closed curve contain all four vertices of some square?

> Proof Convex set

* If the intersection is empty, or consists of a single point, the theorem is true by definition
* Otherwise, take any two points A, B in the intersection
* line AB joining these points must also lie wholly within each set in collection, hence must lie wholly within their intersection

{% tabs %}
{% tab title='python' %}

```py
# 1. Polygon Collision
### Point inside polygon
for i in range(2, n):
  if dot(line(p[i], q), line(p[i-1], p[i]) >= 0:
    return true
return false

### Polygon vs Polygon intersect
def polygon_intersection_algorithm
  if (any vertex of P1 belongs to P2) OR (any vertex of P2 belongs to P1)
    return collision
  if any edge of P1 intersect any edge of P2:
    return collision
  return no_collision

# 2. Distance
def dist_point2point(p1, p2):
  """Calculate distance between p1, p2.
  Args: p1 (float, float): coordinates of p1
        p2 (float, float): coordinates of p2
  Returns: float: distance
  """
  return ((p2[1] - p1[1]) ** 2 + (p2[0] - p1[0]) ** 2) ** 0.5

def general_two_point(p1, p2):
  a = p1[1] - p2[1]
  b = p2[0] - p1[0]
  c = (p1[0] - p2[0]) * p1[1] + (p2[1] - p1[1]) * p1[0]

  norm = (a ** 2 + b ** 2) ** 0.5

  return (a / norm, b / norm, c / norm)

def dist_point2segment(q, p1, p2):
  x1, y1 = p1
  x2, y2 = p2
  x3, y3 = q

  dx = x2 - x1
  dy = y2 - y1

  if dx == 0 and dy == 0:
    return -1, -1

  u = ((x3 - x1) * dx + (y3 - y1) * dy) / (dx * dx + dy * dy)
  u = min(1, max(0, u))

  return x1 + u * dx, y1 + u * dy

def distance_point_segment(q, p1, p2):
  return dist_point2point(dist_point2segment(q, p1, p2), q)

def computeDistancePointToPolygon(P, q):
  if len(P) < 3:
    raise(Exception("Polygon must have more than 2 vertices"))

  minDist = float('inf')
  for i in range(len(P)):
    minDist = min(minDist, distance_point_segment(
      q, P[i], P[(i + 1) % len(P)]))

  return minDist

# 3. Intersect
def computeTangentVectorToPolygon(P, q):
  minDist = computeDistancePointToPolygon(P, q)
  indices = []

  for i in range(len(P)):
    if minDist == distance_point_segment(q, P[i], P[(i + 1) % len(P)]):
      indices.append(i)

  if len(indices) == 2:
    px, py = P[indices[1]] if distance(q, P[indices[1]]) < distance(
      q, P[(indices[1] + 1) % len(P)]) else P[(indices[1] + 1) % len(P)]
    qx, qy = q
    dx = qx - px
    dy = qy - py
    x = -dy
    y = dx
    norm = (x ** 2 + y ** 2) ** 0.5
    return x / norm, y / norm
  else:
    a, b, c = computeLineThroughTwoPoints(
      P[indices[0]], P[(indices[0] + 1) % len(P)])
    return b, -a

def isPointInPolygon(q, Ps):
  for i in range(1, len(Ps)):
    x0, y0 = q
    x1, y1 = Ps[i - 1]
    x2, y2 = Ps[i]

    v1 = np.array([-(y2 - y1), x2 - x1])
    v2 = np.array([x0 - x1, y0 - y1])
    if (np.dot(v1, v2) >= 0):
      return True
  return False

def isLineIntersect(p1, p2, p3, p4):
  x1, y1 = p1
  x2, y2 = p2
  x3, y3 = p3
  x4, y4 = p4
  num = (x4 - x3) * (y1 - y3) - (y4 - y3)(x1 - x3)
  den = (y4 - y3) * (x2 - x1) - (x4 - x3)(y2 - y1)

  if num == 0 and den == 0:
    print("Two lines coincide")
    return True
  elif num != 0 and den == 0:
    print("Two lines are parallel")
    return False
  elif num != 0 and den != 0:
    return True

  return False

def calculateShortestPoint(q, p1, p2):
  x1, y1 = p1
  x2, y2 = p2
  x3, y3 = q

  dx = x2 - x1
  dy = y2 - y1

  if dx == 0 and dy == 0:
    return -1, -1

  u = ((x3 - x1) * dx + (y3 - y1) * dy) / (dx * dx + dy * dy)
  u = 1 if u > 1 else 0
  return x1 + u * dx, y1 + u * dy

def isPolygonIntersect(P1, P2):
  N = len(P1)
  M = len(P2)
  for q in P1:
    if isPointInPolygon(q, P2):
      return True

  for i in range(len(P1)):
    for j in range(len(P2)):
      if isLineIntersect((P1[i], P1[(i + 1) % N]), (P2[j], P2[(j + 1) % M])):
        return True

  return False
```

{% endtab %}
{% endtabs %}

{% include '.geometry.prob' %}

## Euler Characteristic

{% include '.euler-characteristic.prob' %}

## Pythagorean

{% include '.pythagorean.prob' %}

## Polygon

> Triangle

* SSS

$$ \sqrt{p(p-a)(p-b)(p-c)} $$

* SAS

$$ \frac{a \cdot b \cdot \sin (\theta)}{2} $$

* Pythagorean Theorem

![Pythagoream Theorem](images/20210218_231601.png)

$$
\text { hypotenuse }^{2}=\text { base }^{2}+\text { perpendicular }^{2}
$$

> Quadrillateral

![Type of Quadrillateral](images/20210218_231529.png)

* Area

$$
when s=\frac{a+b+c+d}{2}

S=\sqrt{(s-a)(s-b)(s-c)(s-d)}
$$

> Polygon area

$$
\text { Area }=\frac{1}{2}\left|\begin{array}{cc}
x_{1} & y_{1} \\
x_{2} & y_{2} \\
x_{3} & y_{3} \\
\vdots & \vdots \\
x_{n} & y_{n} \\
x_{1} & y_{1}
\end{array}\right|=\frac{1}{2}\left[\left(x_{1} y_{2}+x_{2} y_{3}+x_{3} y_{4}+\cdots+x_{n} y_{1}\right)-
\left(y_{1} x_{2}+y_{2} x_{3}+y_{3} x_{4}+\cdots+y_{n} x_{1}\right)\right]
$$

{% include '.polygon.prob' %}

### Triangle

{% include '.triangle.prob' %}

### Quadrilateral

{% include '.quadrilateral.prob' %}

## Circle

{% include '.circle.prob' %}

## Convex Haul

* monotone chain, O(n log n)
* Returns: a list of vertices of the convex hull in counter-clockwise order
* divide points into half and find convex hull recursively
* When merging two polygons, check whether extension of line intersects with boundary and pick next point in counter clockwise

![Convex Haul](images/20210218_004049.png)

{% tabs %}
{% tab title='python' %}

```py
from scipy.spatial import ConvexHull, convex_hull_plot_2d
import matplotlib.pyplot as plt
import numpy as np

points = np.random.rand(30, 2)   # 30 random points in 2-D
hull = ConvexHull(points)
plt.plot(points[:,0], points[:,1], 'o')
for simplex in hull.simplices:
    plt.plot(points[simplex, 0], points[simplex, 1], 'k-')

plt.plot(points[hull.vertices,0], points[hull.vertices,1], 'r--', lw=2)
plt.plot(points[hull.vertices[0],0], points[hull.vertices[0],1], 'ro')
plt.show()
```

{% endtab %}
{% endtabs %}

{% include '.convex-haul.prob' %}

### Convex Haul DP

* O(N logN)
* $$ DP[i] = min_{j < i}(A[j] * B[i] + DP[j]) $$

![Convex Haul](images/20210527_183246.png)

{% include '.convex-haul-dp.prob' %}

### Rotating Calipers

![rotating calipers](images/20210602_022101.png)

* solve optimization problems including finding the width or diameter of a set of points
* For all slopes determine if it contains all N points
* slopes can be calculated from convex haul

* Time: O(NlgN) Convex Haul + O(N) Rotating calipers

{% include '.rotating-calipers.prob' %}

## Trigonometry

{% include 'trigonometry.test' %}

![trigonometry](images/20210206_210016.png)

* Radian degree conversion

$$ b(d e g)=180 \cdot a(r a d) \mid \pi $$

$$ a(r a d)=\pi \cdot b(d e g) \mid 180 $$

{% include '.trigonometry.prob' %}
