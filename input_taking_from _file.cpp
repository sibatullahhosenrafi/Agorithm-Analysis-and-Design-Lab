#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream fin("input.txt");
// taking input from file
/*
    int x;

    while (fin >> x)
    {
        cout << x << " ";
    }

    fin.close();

*/
string s;
while(getline(fin,s))
{
    cout<<s<<endl;
}
ofstream fout("output.txt");
fout<<s<<endl;
fin.close();
fout.close();

    return 0;
}
