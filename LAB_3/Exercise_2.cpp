#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct WORD {
    string word;
    string definition;
};

bool readFile(const string &filename, vector<WORD> &dict) {
    fstream fi(filename, ios::in);
    if (!fi) return false;
    string line;
    while (getline(fi, line)) {
        stringstream ss(line);
        string word, definition;
        if (getline(ss, word, ':') && getline(ss, definition))
            dict.push_back({word, definition});
    }
    fi.close();
    return true;
}

string findDefinition(const string &w, vector<WORD> dict) {
    int l = 0, r = dict.size() - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (dict[mid].word == w) {
            while (mid > 0 && dict[mid - 1].word == w) mid--;
            return dict[mid].definition;
        }
        if (dict[mid].word > w) r = mid - 1;
        else l = mid + 1;
    }
    return "Definition not found!";
}

bool writeFile(const string &filename, vector<WORD> words) {
    fstream fo(filename, ios::out);
    if (!fo) return false;
    for (WORD w : words) {
        fo << w.word << ':' << w.definition << '\n';
    }
    fo.close();
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Invalid syntax!";
        return 1;
    }
    
    vector<WORD> dictionary;
    if (!readFile("English-Vietnamese Dictionary.txt", dictionary)) {
        cerr << "Cannot open file!";
        return 1;
    }
    
    vector<WORD> words;
    for (int i = 1; i < argc - 1; i++) {
        WORD w;
        w.word = argv[i];
        w.definition = (findDefinition(argv[i], dictionary));
        words.push_back(w);
    }
    
    if (!writeFile(argv[argc - 1], words)) {
        cerr << "Cannot open file!";
        return 1;
    }
    return 0;
}