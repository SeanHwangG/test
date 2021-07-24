/** Implementation file for movie class
 *
 *  name  : Gyuseung Hwang
 *  email : g5hwang@ucsd.edu
 */

#include <string>
#include "Movie.hpp"

/** @return : toString method for printing
 */
string Movie::toString() {
	// movie name contains year, so get rid of last 4 characters
	return "[" + name.substr(0, name.size() - 4) + "#@" + to_string(year) + "]";
}

/** @return : weight of the Movie (2020 - year)
 */
int Movie::weight() {
	return 2020 - year;
}
