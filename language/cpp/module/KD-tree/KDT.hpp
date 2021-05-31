/** Implementation of KDTree
 *  Build once with vector, and access data in Nlog(N) time
 *
 *  name  : Gyuseung Hwang
 *  Email : g5hwand@ucsd.edu
 */

#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>

#include <algorithm>
#include <climits>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

#include "BST.hpp"

using namespace std;

/** 2D Point Class that will be used in KDTree.
 */
class Point {
 private:
  /** Points within difference of delta considered equal*/
  double delta = 0.00005;

 public:
  double x, y;
  Point() : x(0.0), y(0.0) {}
  Point(double x, double y) : x(x), y(y) {}

  bool operator==(const Point &other) const { return abs(x - other.x) < delta && abs(y - other.y) < delta; }

  bool operator!=(const Point &other) const { return abs(x - other.x) > delta || abs(y - other.y) > delta; }

  /** [INVALID] Compare x and y coordinates respectively
   *
   *  @param other : Point to compare
   */
  bool operator<(const Point &other) const {
    cerr << "This operator should not be called, you will need "
         << "check the x and y components each time" << endl;
    return false;
  }

  /** Calculate and return the distance between two points p1 and p2
   *
   *  @p1 : one point to calculate distance
   *  @p2 : another point to calculate distance
   */
  static double squareDistance(const Point &p1, const Point &p2) { return pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2); }
};

std::ostream &operator<<(std::ostream &out, const Point &data) {
  out << "(" << data.x << ", " << data.y << ")";
  return out;
}

bool xLessThan(const Point &p1, const Point &p2) { return p1.x < p2.x; }
bool yLessThan(const Point &p1, const Point &p2) { return p1.y < p2.y; }

/** KDTree inheriting BSTclass
 *  You can find nearest point in average of N(log(N)) time
 */
class KDT : public BST<Point> {
 public:
  /** Create a KDtree with given vector
   *
   *  @param items : items to be added in KDTree
   *  @return      : the number of element in items
   */
  virtual unsigned int build(vector<Point> items) {
    root = buildSubset(items, 0, items.size(), 0, 1);
    isize = items.size();
    return items.size();
  }

  virtual iterator findNearestNeighbor(const Point &item) const {
    if (root == nullptr) return end();

    double shortest = MAX;
    BSTNode<Point> *closest;

    findNNHelper(root, item, &shortest, &closest, 0);

    return BSTIterator<Point>(closest);
  }

  virtual iterator find(const Point &item) const override {
    cerr << "The KD Tree find method should not be called" << endl;
    cerr << "Use findNearestNeighbor instead" << endl;
    return 0;
  }

  /** For the kd-tree, the insert method should not be used.  The tree is
   *  built all at once.  There should be no scenario where you add individual points.
   */
  virtual bool insert(const Point &item) override {
    cerr << "The KD Tree insert method should not be called" << endl;
    return false;
  }

 private:
  const double MAX = (double)INT_MAX;

  /** Recursively add a subset of the array to the KD tree
   *  Alternatively sort each layer with x and y axis, and choose median as root
   *
   *  @param items : the list of points that are used to build the kd tree
   *         start : the starting index for this subsection of the tree
   *           end : the non-inclusive ending index for this subtree
   *     dimension : 0 if sorted along the x-axis, 1 if y
   *        height : height of the tree
   *  @return      : KDTree built with given vector
   */
  BSTNode<Point> *buildSubset(vector<Point> &items, unsigned int start, unsigned int end, unsigned int dimension,
                              unsigned int height) {
    // there is no element to build tree
    if (start >= end) {
      return nullptr;
    }

    iheight = max(iheight, height);
    int mid = (start + end) / 2;

    // sort the given part respect to the dimension
    sort(items.begin() + start, items.begin() + end, (height % 2 == 1 ? xLessThan : yLessThan));

    // create current node with median
    BSTNode<Point> *ret = new BSTNode<Point>(items[mid]), *leftNode = buildSubset(items, start, mid, 1 ^ dimension, height + 1),
                   *rightNode = buildSubset(items, mid + 1, end, 1 ^ dimension, height + 1);

    // add left node if it is not nullptr
    if (leftNode != nullptr) {
      ret->left = leftNode;
      leftNode->parent = ret;
    }

    // add right node if it is not nullptr
    if (rightNode != nullptr) {
      ret->right = rightNode;
      rightNode->parent = ret;
    }

    return ret;
  }

  /** Find the node in the subtree with that is closes to the given point p
   *
   *  @param            node : the root of the subtree being searched
   *              queryPoint : the point whose nearest neighbor should be found
   *  smallestSquareDistance : the smallest distance value found in
   *            closestPoint : the node corresponding to the current closest
   *               dimension : 0 if split along x, 1 if y
   *  @return   : a BSTNode object that represents the point in the subtree
   *              closest to the given point p (including the root node)
   */
  void findNNHelper(BSTNode<Point> *node, const Point &queryPoint, double *smallestSquareDistance, BSTNode<Point> **closestPoint,
                    unsigned int dimension) const {
    if (node == nullptr) return;

    // distance from current point
    double curDist = Point::squareDistance(queryPoint, node->data);

    // distance to the line parallel to x/y axis (depends on dimension)
    double lineDist = (dimension == 0 ? queryPoint.x - node->data.x : queryPoint.y - node->data.y);

    // if the distance is smaller, update smallest
    if (curDist < *smallestSquareDistance) {
      *smallestSquareDistance = curDist;
      *closestPoint = node;
    }

    // if it is leaf, no need to go down
    if (node->left == nullptr && node->right == nullptr) {
      return;
    }

    // search left / down where the query point is located
    if (lineDist < 0) {
      findNNHelper(node->left, queryPoint, smallestSquareDistance, closestPoint, 1 ^ dimension);
      // there is possibility that closer point is on right / up
      if (abs(lineDist) < sqrt(*smallestSquareDistance))
        findNNHelper(node->right, queryPoint, smallestSquareDistance, closestPoint, 1 ^ dimension);
    }
    // search right / up where the query point is located
    else {
      findNNHelper(node->right, queryPoint, smallestSquareDistance, closestPoint, 1 ^ dimension);
      // there is possibility that closer point is on left / down
      if (abs(lineDist) < sqrt(*smallestSquareDistance))
        findNNHelper(node->left, queryPoint, smallestSquareDistance, closestPoint, 1 ^ dimension);
    }
  }
};

#endif  // KDT_HPP
