#include <iostream>
#include <iterator>

using namespace std;
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v)
{
    if (!v.empty())
    {
        out << '[';
        std::copy(v.begin(), v.end(), ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

template <typename T>
ostream &operator<<(std::ostream &out, const vector<std::vector<T>> &G)
{
    out << "[";
    for (int i = 0; i < G.size(); i++)
    {
        out << G[i];
        if (i != G.size() - 1)
            out << "\n";
    }
    out << "]";
    return out;
}
