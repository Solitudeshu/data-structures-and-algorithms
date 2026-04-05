#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct Candidate {
    string name;
    double score1;
    double score2;
    double avg;
    vector<int> options;
};

bool readFile(const string &filename, int &m, vector<int> &candidatePerOpt, vector<Candidate> &candidates) {
    fstream fi(filename, ios::in);
    if (!fi) return false;
    
    fi >> m;
    candidatePerOpt.resize(m);
    for (int i = 0; i < m; i++) {
        int x, y;
        fi >> x >> y;
        candidatePerOpt[x - 1] = y;
    }

    string line;
    getline(fi, line);
    while (getline(fi, line)) {
        Candidate candidate;
        stringstream ss(line);
        getline(ss, candidate.name, '"');
        getline(ss, candidate.name, '"');

        char comma;
        ss >> comma >> candidate.score1 >> comma >> candidate.score2;
        candidate.avg = (candidate.score1 + candidate.score2) / 2.00;

        candidate.options.resize(m);
        for (int i = 0; i < m; i++) ss >> comma >> candidate.options[i];
        candidates.push_back(candidate);
    }

    fi.close();
    return true;
}

int compare(Candidate a, Candidate b) {
    if (a.avg != b.avg) {
        if (a.avg > b.avg) return 1;
        return 0;
    }
    if (a.score1 != b.score1) {
        if (a.score1 > b.score1) return 1;
        return 0;
    }
    if (a.score2 != b.score2) {
        if (a.score2 > b.score2) return 1;
        return 0;
    }
    return -1;
}

void selectionSort(vector<Candidate> &candidates) {
    int n = candidates.size();
    for (int i = 0; i < n - 1; i++) {
        int max = i;
        for (int j = i + 1; j < n; j++)
            if (compare(candidates[j], candidates[max]) > 0) max = j;
        swap(candidates[i], candidates[max]);
    }
}

int main() {
    int m;
    vector<int> candidatePerOpt;
    vector<Candidate> candidates;

    if (!readFile("exam.txt", m, candidatePerOpt, candidates)) {
        cerr << "Can not open file!";
        return 1;
    }

    selectionSort(candidates);

    vector<vector<Candidate>> admitted(m);
    vector<Candidate> rejected;
    int n = candidates.size();
    for (auto candidate : candidates) {
        bool check = false;
        for (int j : candidate.options) {
            if (admitted[j - 1].size() < candidatePerOpt[j - 1] || (compare(candidate, admitted[j - 1].back()) < 0)) {
                admitted[j - 1].push_back(candidate);
                check = true;
                break;
            }
        }
        if (!check) rejected.push_back(candidate);
    }

    for (int i = 1; i <= m; i++) {
        cout << "Successful candidates for option " << i << '\n';
        auto cand = admitted[i - 1];
        int sz = cand.size();
        for (int j = 0; j < sz; j++) {
            cout << j + 1 << ". " << cand[j].name << ' ' 
                << fixed << setprecision(2) << cand[j].avg << '\n';
        }
    }

    int sz = rejected.size();
    cout << "Unsuccessful candidates\n";
    for (int i = 0; i < sz; i++) {
        cout << i + 1 << ". " << rejected[i].name << ' ' 
            << fixed << setprecision(2) << rejected[i].avg << '\n';
    }

    return 0;   
}