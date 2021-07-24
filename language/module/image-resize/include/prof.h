#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#ifdef DEBUG_BUILD
#define DEBUG(x) cerr << x
#else
#define DEBUG(x) \
    do {         \
    } while (0)
#endif

#ifdef DEBUG_BUILD
#define PROF_INIT() Prof::Init()
#define PROF_START() Prof::Start()
#define PROF_END() Prof::End()
#define PROF_FLUSH() Prof::Flush()
#else
#define PROF_START()
#define PROF_END()
#endif

map<thread_id, Prof> thread2prof;
mutex lock;

class Prof {
    class ProfData {
        string name;
        int depth;
        vector<int> time;
    };
    void GetInstance();
    void Init();
    void Start();
    void End();
    void Flush();
    vector<ProfData> headList;
    stack<ProfData> curStack;
};