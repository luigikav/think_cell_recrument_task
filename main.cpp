#include <string>
#include "interval_map.h"

void IntervalMapTest() {
    interval_map m = interval_map<A<int>, B<char>>(B<char>('A'));
    Print(m);
    m.assign(A<int>(3), A<int>(10), B<char>('B'));
    Print(m);
    m.assign(A<int>(1), A<int>(6), B<char>('B'));
    Print(m);
    m.assign(A<int>(15), A<int>(17), B<char>('B'));
    Print(m);
    m.assign(A<int>(0), A<int>(20), B<char>('A'));
    Print(m);
    m.assign(A<int>(7), A<int>(12), B<char>('B'));
    Print(m);
    m.assign(A<int>(12), A<int>(15), B<char>('x'));
    Print(m);
}
int main() {
    IntervalMapTest();
}