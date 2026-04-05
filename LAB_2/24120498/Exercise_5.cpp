#include <iostream>
#include <string>

using namespace std;

void Reverse(string &s, int left, int right)
{
    if (left >= right)
        return;
    swap(s[left], s[right]);
    Reverse(s, left + 1, right - 1);
}

int main()
{
    string s;
    getline(cin, s);
    Reverse(s, 0, s.length() - 1);
    cout << s;
    return 0;
}