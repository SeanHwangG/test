#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Movie.hpp"

using namespace std;

class Movie;

/** Actor class that represents a node in a graph. contains actor information.
 */
class Actor
{
public:
  Actor(string name) : name(name) {}

  /** @return : toString method for printing
   */
  string toString();

  string name;
  unordered_map<Actor *, Movie *> path;
  vector<Movie *> played;
};

#endif
