/** Find minimal spanning tree gvein IDMD data
 *  Total edge weights must be minimal.
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#include <fstream>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <unordered_map>
#include "ActorGraph.hpp"
#include "Actor.hpp"
#include "Movie.hpp"

using namespace std;

unordered_map<Actor*, Actor*> head;

/** Compare struct for max_heap of year from Movie pointer
 */
struct comp {
    bool operator() (Movie* a, Movie* b) const {
        return a->year < b->year;
    }
};

/** Find the head of the actor. Use path compression.
 *
 *  @return : head of the given actor pointer
 */
Actor* find(Actor* a) {
	if (!head.count(a))		return a;
    if (head[a] != a)		return head[a] = find(head[a]);
    return a;
}

/** Connect two actors
 *  @param a : Actor to connect
 *         b : Actor to connect, should be different from a
 */
void unions(Actor* a, Actor* b) {
    head[find(b)] = find(a);
}

/** given data file name print minimum spanning tree to out_fname
 *
 *  @param data_fname : data_fname 
 *          out_fname : output file name
 */
void movietraveler(string data_fname, string out_fname) {
    ActorGraph graph;
    graph.loadFromFile(data_fname);

    ifstream in(data_fname);
    ofstream out(out_fname);

    priority_queue<Movie*, vector<Movie*>, comp> pq;
	int edge = 0, weight = 0;

	for (auto it : graph.movies)
		pq.push(it.second);

    out << "(actor)<--[movie#@year]-->(actor)\n";
    while (pq.size()){
		Movie* cur = pq.top();
        pq.pop();

		Actor* a1 = cur->leads[0], *a2;
		for (int i = 1; i < cur->leads.size(); i++) {
			a2 = cur->leads[i];
			if (find(a1) != find(a2)) {
				edge++;
				weight += cur->weight();
				out << a1->toString() << "<--"
				    << cur->toString() << "-->"
				    << a2->toString() << "\n";
				unions(a1, a2);
			}
		}
    }
	out << "#NODE CONNECTED: " << edge + 1 << endl;
	out << "#EDGE CHOSEN: " << edge << endl;
	out << "TOTAL EDGE WEIGHTS: " << weight << endl;

	in.close();
	out.close();
}

/** Main driver function for testing compress.
 *
 *  @param argc : number of argument + 1 (include run command)
 *		   argv : pointer to char pointer that stores argument
 *  @return     : -1 if number of argument is not 5, 0 otherwise
 */
 int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "./movietraveler called with incorrect arguments.\n"
             << "Usage: ./movietraveler movie_cast.txt outputfile\n";

        exit(-1);
    }

    movietraveler(argv[1], argv[2]);
 }
