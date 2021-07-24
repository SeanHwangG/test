/** read input file defined imdb_2019.tsv.
 */

#include "ActorGraph.hpp"

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Actor.hpp"
#include "Movie.hpp"

using namespace std;

ActorGraph::ActorGraph(void) { actors.clear(); }

ActorGraph::~ActorGraph(void)
{
  for (auto it : actors)
    delete it.second;
  for (auto it : movies)
    delete it.second;
}

bool ActorGraph::loadFromFile(const string in_filename)
{
  ifstream infile(in_filename);
  // skip file header
  string line;
  getline(infile, line);

  // keep reading lines until the end of file is reached
  while (getline(infile, line))
  {
    istringstream ss(line);
    vector<string> record;

    string next;
    while (getline(ss, next, '\t'))
    {
      record.push_back(next);
    }

    if (record.size() != 3)
    {
      // we should have exactly 3 columns
      continue;
    }

    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);

    addMovie(actor_name, movie_title + record[2], movie_year);
  }

  if (!infile.eof())
  {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();

  return true;
}

bool ActorGraph::addMovie(string actor, string movie, int year)
{
  if (!actors.count(actor))
    actors[actor] = new Actor(actor);
  if (!movies.count(movie))
    movies[movie] = new Movie(movie, year);

  Actor *curA = actors[actor];
  Movie *curM = movies[movie];

  for (Actor *sameA : curM->leads)
  {
    // if there is no connection or connection is newer, update
    if (!curA->path.count(sameA) || curA->path[sameA]->year < year)
    {
      (curA->path)[sameA] = curM;
      (sameA->path)[curA] = curM;
    }
  }

  curA->played.push_back(curM);
  curM->leads.push_back(curA);

  return true;
}

string ActorGraph::findPath(Actor *a, Actor *b)
{
  if (a == nullptr || b == nullptr)
    return "Not Found";

  // perform BFS
  queue<Actor *> q;
  unordered_set<Actor *> visit;
  unordered_map<Actor *, Actor *> prev; // if not found, -1
  q.push(a);
  visit.insert(a);

  while (q.size())
  {
    Actor *cA = q.front();
    q.pop();

    for (auto it : cA->path)
    {
      Actor *nA = it.first;
      if (!visit.count(nA))
      {
        visit.insert(nA);
        prev[nA] = cA;
        q.push(nA);
      }
    }
  }

  string ret;
  Actor *cA = b;
  while (cA != a)
  {
    ret = prev[cA]->toString() + "--" + (cA->path)[prev[cA]]->toString() + "-->" + ret;
    cA = prev[cA];
  }

  return ret + b->toString();
}

string ActorGraph::findWPath(Actor *a, Actor *b)
{
  if (a == nullptr || b == nullptr)
    return "Not Found";

  // perform Dijstra
  priority_queue<pair<int, Actor *>, vector<pair<int, Actor *> >, greater<pair<int, Actor *> > > pq;
  // empty is infinity
  unordered_map<Actor *, int> dist;
  // empty is -1
  unordered_map<Actor *, Actor *> prev;
  unordered_set<Actor *> done;

  // dist, Node
  pq.push({0, a});

  while (pq.size())
  {
    int curD = pq.top().first;
    Actor *curA = pq.top().second;
    pq.pop();

    if (done.count(curA) == 0)
    {
      done.insert(curA);
      for (auto it : curA->path)
      {
        Actor *nextA = it.first;
        Movie *nextM = it.second;

        int c = curD + nextM->weight();
        if (!dist.count(nextA) || c < dist[nextA])
        {
          prev[nextA] = curA;
          dist[nextA] = c;
          pq.push({c, nextA});
        }
      }
    }
  }

  string ret;
  Actor *cA = b;
  while (cA != a)
  {
    ret = prev[cA]->toString() + "--" + (cA->path)[prev[cA]]->toString() + "-->" + ret;
    cA = prev[cA];
  }

  return ret + b->toString();
}
