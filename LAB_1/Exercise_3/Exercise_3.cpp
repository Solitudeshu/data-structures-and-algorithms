#include <iostream>
#include <string>

using namespace std;

void normalizeParagraph(string &s) {
    string r = "";
    int l = s.length();
    for (int i = 0, j = 0; i < l; i++) {
        if (s[i] == ' ' && !j) continue;
        if (s[i] == ' ' && s[i + 1] == ' ') continue;
        if (s[i] == ' ' && i == l - 1) continue;
        if (s[i] == ' ' && s[i + 1] != ' ' && !isalpha(s[i + 1])) continue;
        j = 1;
        r += s[i];
    }
    s = r;
}

int countWord(string s) {
    int count = 0;
    int l = s.length();
    for (int i = 0; i < l; i++) 
        if (s[i] == ' ') count++;
    return count + 1;
}

string longestWord(string s) {
    string maxWord, substr = "";
    int l = s.length(), count = 0, maxCount = 0;
    for (int i = 0; i < l; i++) {
        if (s[i] != ' ' && isalpha(s[i])) {
            ++count;
            substr += s[i];
            
        }
        if (s[i] == ' ' || i == l - 1) {
            if (maxCount < count) {
                maxCount = count;
                maxWord = substr;
            }
            count = 0;
            substr = "";
        }
    }
    return maxWord;
}

int main() {
    string s;
    getline(cin, s);
    normalizeParagraph(s);
    cout << "Normalized paragraph: \n" << s << '\n';
    cout << "Word count: " << countWord(s) << '\n';
    cout << "Longest word: " << longestWord(s) << '\n';
    return 0;
}