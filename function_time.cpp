#include <bits/stdc++.h>

using namespace std;
using namespace chrono;
void func()
{
    for(int i=0;i<10000000;i++)
    {

    }
}
int main()
{ auto start = chrono::high_resolution_clock::now();

for(int i = 0; i < 10; i++)
{
    func();
}

auto end = chrono::high_resolution_clock::now();

auto total = chrono::duration_cast<chrono::microseconds>
             (end - start).count();

cout << "Average = "
     << (double)total / 10
     << " microseconds\n";
}
