/** Header file for reading and defined imdb_2019.tsv
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <string>
#include <unordered_map>

#include "Actor.hpp"
#include "Movie.hpp"

// Maybe include some data structures here

using namespace std;

/** Actorgraph class containing all information of the Movies and Actors
 *  Also allows to find shortest weighted/unweighted path between Actors.
 */
class ActorGraph
{
public:
  unordered_map<string, Actor *> actors;
  unordered_map<string, Movie *> movies;

  /** Constuctor of the Actor graph
   */
  ActorGraph(void);

  /** Destructor of the Actor graph
   */
  ~ActorGraph(void);

  /** You can modify this method definition as you wish. Load the graph from a tab-delimited file of actor->movie relationships.
   *
   *  @param in_filename : input filename
   *            weighted : if true, compute edge weights as (2020 - movie_year),
   *                      otherwise all edge weights will be 1
   *
   *  @return : true if file loading was successful; false otherwise
   */
  bool loadFromFile(const string in_filename);

  /** Add actor, movie information to the graph check if the same movie is already added.
   *
   *  @return : true if successfuly added; false otherwise
   */
  bool addMovie(string actor, string movie, int year);

  /** find the shortest unweighted path from a to b.
   *
   *	@return : path containing all information of the path
   */
  string findPath(Actor *a, Actor *b);

  /** find the shortest weighted path from a to b.
   *
   *  @return : path containing all information of the path
   */
  string findWPath(Actor *a, Actor *b);
};

#endif // ACTORGRAPH_HPP
