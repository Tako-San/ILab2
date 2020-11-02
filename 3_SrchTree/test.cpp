#include <vector>
#include "pair.h"
#include "tree.h"

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

int main( )
{
    Tree<Pair<string, string>> t1;

    string key{};
    string val{};

    unsigned num{};

    cout << "Input elem num: ";
    cin >> num;

    vector<string> keys{};

    for (unsigned i = 0; i < num; ++i)
    {
        cout << "Input key: ";
        cin >> key;

        keys.push_back(key);

        cout << "Input val: ";
        cin >> val;

        t1[key] = val;
    }

    for (const string & elem : keys)
    {
        cout << "t[" << elem << "] = " << t1[elem].get_val() << ";" << endl;
    }

    return 0;
}