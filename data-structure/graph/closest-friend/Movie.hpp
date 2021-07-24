/** Header file for movie class
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Actor.hpp"

using namespace std;

class Actor;

/** Movie class containing movie information. Also stores all actors on the movie.
 */
class Movie {
 public:
  Movie(string name, int year) : name(name), year(year) {}
  string name;
  int year;
  vector<Actor*> leads;

  string toString();
  /** @return : weight of the Movie (2020 - year)
   */
  int weight();
};

#endif
