/** find closest movie path from given IDMD data
 *  the path can be wieghted and weighted by year
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#include <fstream>
#include <iostream>
#include <string>

#include "ActorGraph.hpp"

using namespace std;

/** Find shortest movie path between two actors
 *
 *  @param data_fname : tsv file containing IDMD movie data
 *         isWeighted : if true use (2020 - Y) when finding shortest path
 *        input_fname : tsv file containing two actors as a query
 *       output_fname : each line contains shortest path in input query
 */
void pathfinder(string data_fname, bool isWeighted, string in_fname, string out_fname) {
  cout << "Reading " << data_fname << "...\n";
  ActorGraph graph;
  graph.loadFromFile(data_fname);

  ifstream in(in_fname);
  ofstream out(out_fname);

  // skip file header
  string line;
  getline(in, line);

  out << "(actor)--[movie#@year]-->(actor)--...\n";
  while (getline(in, line)) {
    // split line using tab as delimiter
    string a(line.begin(), line.begin() + line.find('\t'));
    string b(line.begin() + line.find('\t') + 1, line.end());
    cout << "Computing path for (" << a << ") -> (" << b << ")\n";

    if (isWeighted)
      out << graph.findWPath(graph.actors[a], graph.actors[b]) << "\n";
    else
      out << graph.findPath(graph.actors[a], graph.actors[b]) << "\n";
  }

  in.close();
  out.close();
}

int main(int argc, char** argv) {
  if (argc != 5) {
    cout << "./pathfinder called with incorrect arguments.\n"
         << "Usage: ./pathfinder movie_cast_tsv_file u/w pairs_tsv_file output_paths_tsv_file\n";
    exit(-1);
  }

  pathfinder(string(argv[1]), *argv[2] == 'w', string(argv[3]), string(argv[4]));
}
