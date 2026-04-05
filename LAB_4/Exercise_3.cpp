#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Employee {
    int id;
    string name;
    int birthYear;
    int age;
};

bool readFile(const string &filename, vector<Employee> &a) {
    fstream fi(filename, ios::in);
    if (!fi) return false;

    string line;
    getline(fi, line);
    while (getline(fi, line)) {
        string name, strId, strBirthYear;
        stringstream ss(line);
        if (getline(ss, strId, ',') && getline(ss, name, ',') && getline(ss, strBirthYear)) {
            int id = stoi(strId);
            int birthYear = stoi(strBirthYear);
            time_t now = time(0);
            tm* ltm = localtime(&now);
            int year = 1900 + ltm->tm_year;
            if (birthYear > year) birthYear = 1900 + birthYear % 100;
            a.push_back({id, name, birthYear, year - birthYear});
        }
    }
    fi.close();
    return true;
}

void insertionSort(vector<Employee> &a, int n) {
    for (int i = 1; i < n; i++) {
        Employee tmp = a[i];
        int j = i - 1;
        while (j >= 0 && (a[j].age < tmp.age || (a[j].age == tmp.age && a[j].name > tmp.name))) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = tmp;
    }
}

void selectionSort(vector<Employee> &a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int max = i;
        for (int j = i + 1; j < n; j++) 
            if (a[j].age > a[max].age || (a[j].age == a[max].age && a[j].name < a[max].name)) max = j;
        swap(a[i], a[max]);
    }
}

void interchangeSort(vector<Employee> &a, int n) {
    for (int i = 0; i < n - 1; i++) 
        for (int j = i + 1; j < n; j++) 
        if (a[j].age > a[i].age || (a[j].age == a[i].age && a[j].name < a[i].name)) swap(a[i], a[j]);
}

bool writeFile(const string &filename, vector<Employee> a) {
    fstream fo(filename, ios::out);
    if (!fo) return false;

    fo << "id, name, birth year\n";
    for (auto x : a) {
        fo << x.id << ',' << x.name << ',' << x.birthYear << '\n';
    }
    fo.close();
    return true;
}

void printMenu() {
    cout << "1. Insertion Sort.\n";
    cout << "2. Selection Sort.\n";
    cout << "3. Interchange Sort.\n";
    cout << "Section (1 - 3): \n";
    cout << "Enter an interger for your selection: ";
}

int main() {
    vector<Employee> a;
    if (!readFile("employee.txt", a)) {
        cout << "Can not open file!";
        return 1;
    }
    
    int x, n = a.size();
    printMenu();
    cin >> x;
    if (x == 1) insertionSort(a, n);
    else if (x == 2) selectionSort(a, n);
    else if (x == 3) interchangeSort(a, n);
    else {
        cerr << "Invalid selection!";
        return 1;
    }

    if (!writeFile("sortedemponage.txt", a)) {
        cout << "Can not open file!";
        return 1;
    }
    return 0;
}