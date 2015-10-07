#include <iostream>
#include <list>

using namespace std;

class C {
public:
    C() {}
    static list <int> l;
};

list <int> C::l;

int main()
{
    C c = C();
    C b = C();
    for (int i = 0; i < 10; ++i)
        c.l.push_back(i);
    list <int>::iterator it = c.l.begin(), it2;
    ++it;
    ++it;
    ++it;
    it2 = it;
    --it;
    cout << (*it2) << endl;
    c.l.sort();
    c.l.insert(it, -1);
    c.l.insert(it, 10);
    cout << (*it2) << endl;

    for (it = c.l.begin(); it != c.l.end(); ++it)
        cout << (*it) << " ";
}
