// Name        : Project 2 (Hash Table)
// Author      : Andre Burton
// Version     : 1.0
//============================================================================
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
// Above includes directives needed for code to work
// Below intiates structure and sets vairables used in code
using namespace std;
const unsigned int Size = 25;
// cN= CourseNumber, Name = Name of course, pR = course prerequisites, 
struct C {
    string cN;
    string Name;
    string pR;
};
// Below coverts string language from coursename to an intger making it easier to
// input into hashtable
int convertToASCII(string cN) {
    int number = 0;
    for (int i = 0; i < cN.length(); i++) {
        char x = cN.at(i);
        number = number + x;
    }
    return number;
}
// below intitates hashtable class
class HashTable {

private:
    // Creates strucutre for courses
    struct N {
        C course;
        unsigned int k;
        N* n;

        N() {
            k = UINT_MAX;
            n = nullptr;
        }

        N(C ac) : N() {
            course = ac;
        }

        N(C ac, unsigned int aKey) : N(ac) {
            k = aKey;
        }
        // Below starts to set order of course information
        int a = 0;
        int b = 0;
        int c = 0;
        int d = 0;
        bool operator < (const N& rhs) const
        {
            int a = 0;
            int b = 0;
            int c = 0;
            int d = 0;
            if (a < rhs.a) { return true; }
            else if (rhs.a < a) { return false; }

            if (b < rhs.b) { return true; }
            if (rhs.b < b) { return false; }
            if (c < rhs.c) { return true; }
            if (rhs.c < c) { return false; }
            if (d < rhs.d) { return true; }
            if (rhs.d < d) { return false; }
            return false;
        }
        // Above sets specific order of information 
    };

    unsigned int tS = Size;
    unsigned int hash(int key);

public:
    vector<N> ns;
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(C course);
    void selectionSort(vector <N> & ns);
    void readFile(HashTable* hashtable);
    C Search(string cN);
};
// Below sets permatiters for sorting through course information
void HashTable::selectionSort(vector<N>& vecToSort) {
    cout << "Here is a sample schedule:" << endl;
    cout << endl;

    vector <N> sortedVec;
    unsigned int e;
    unsigned int f;
    unsigned int lowestIndex = 0;
    N temp;
    vector <N> vecs;

    for (unsigned int g = 0; g < ns.size(); ++g){
        unsigned key = hash(convertToASCII(ns.at(g).course.cN));
        N* n = &(ns.at(key));

        if (ns.at(key).k != UINT_MAX) {
            sortedVec.push_back(ns.at(g));
            while (n->n != nullptr) {
                n = n->n;
                sortedVec.push_back(*n);
            }
        }
    }

    for (e = 0; e < sortedVec.size() - 1; ++e) {
        lowestIndex = e;
        for (f = e + 1; f < sortedVec.size(); ++f) {
            if (sortedVec[f].course.cN < sortedVec[lowestIndex].course.cN) {
                lowestIndex = f;
            }
        }

        temp = sortedVec[e];
        sortedVec[e] = sortedVec[lowestIndex];
        sortedVec[lowestIndex] = temp;
    }

    for (e = 0; e < sortedVec.size(); ++e) {
        cout << sortedVec.at(e).course.cN << " " << sortedVec.at(e).course.Name << endl;
    }
}

HashTable::HashTable() {

    ns.resize(tS);
}
// above edits strucuture and resizes accordenly to the information
// Below uses resized hashtable to impliment infromation
HashTable::HashTable(unsigned int size) {
    this->tS = size;
    ns.resize(tS);
}
// Below erases unused portions of the hash table
HashTable::~HashTable() {
    ns.erase(ns.begin());

}
// Below returns hash table values
unsigned int HashTable::hash(int key) {
    return key % tS;
    return key;
}

void HashTable::Insert(C course) {
    // Below creates and sets keys for hashtable
    // Below also insitiates key retrevival of information
    unsigned key = hash(convertToASCII(course.cN));
    N* prevNode = &(ns.at(key));
    if (prevNode == nullptr) {
        N* next = new N(course, key);
        ns.insert(ns.begin() + key, (*next));
    }
    // Below restructures keys depending on there usage
    else {
        if (prevNode->k == UINT_MAX) {
            prevNode->k = key;
            prevNode->course = course;
            prevNode->n = nullptr;
        }
        else {
            while (prevNode->n != nullptr) {
                prevNode = prevNode->n;
            }
            prevNode->n = new N(course, key);
        }
    }
}

C HashTable::Search(string cN) {
    C course;
    // Below uses assigned key to reteive specific course information
    unsigned key = hash(convertToASCII(cN));
    N* n = &(ns.at(key));
    if (n->k != UINT_MAX && n != nullptr && n->course.cN.compare(cN) == 0) {
        return n->course;
        if (n->k == UINT_MAX || n == nullptr) {
            return course;
    }
        while (n != nullptr) {
            if (n->course.cN.compare(cN) == 0 && n->k != UINT_MAX) {
                return n->course;
                n = n->n;
            }
        }
        }
    return course;
}
// Below reads input txt file and outptus message depening on if it opens or not
void HashTable::readFile(HashTable* hashTable) {
    ifstream infile;
    string fileName = "SNHUinput.txt";
        infile.open(fileName);
        if (!infile.is_open()) {
            cout << "Wrong file name or location, Verify Input File" << endl;
            return;
        }
        cout << "File Opened Successfully" << endl;
        string line;
        char seperator = ',';

        if (infile.is_open()) {
            while (!infile.eof()) {
                getline(infile, line);
                stringstream s_stream(line);
                vector <string> courseData;
                while (s_stream.good()) {
                    string substr;
                    getline(s_stream, substr, ',');
                    courseData.push_back(substr);
                }
                C singlecourse;

                singlecourse.cN = courseData.at(0);
                singlecourse.Name = courseData.at(1);

                if (courseData.size() > 2) {
                    for (int e = 2; e < courseData.size() - 1; ++e) {
                        singlecourse.pR = courseData.at(e) + '-' + courseData.at(e + 1);
                    }
                }
                hashTable->Insert(singlecourse);
            }
        }
}

int main() {
    C course;
    int choice = 0;
    HashTable* cT = nullptr;
    // Below prints out inital message to user with options and asks for choice
    while (choice != 9) {
        cout << "_______________________________" << endl;
        cout << "|Welcome to the course planner.|" << endl;
        cout << "|------------------------------|" << endl;
        cout << "|The Available Options:        |" << endl;
        cout << "|1. Load Data Structure.       |" << endl;
        cout << "|2. Print Course List.         |" << endl;
        cout << "|3. Print Course.              |" << endl;
        cout << "|9. Exit                       |" << endl;
        cout << "|______________________________|" << endl;
        cout << "What would you like to do? Enter number above." << endl;
        cin >> choice;
        choice = choice;
        // Below checks user choose aviable options and outputs correct option or sends error message
        while (choice != 1 && choice != 2 && choice != 3 && choice != 9) {
            cout << choice << " is not a valid option. Please Choose from the list Provided" << endl;
        }
        // Below loads data stucture as long as file exsists
        switch (choice) {
        case 1:
            cT = new HashTable();
            cT->readFile(cT);
            break;
            // Bellow prints all course information
        case 2:
            if (cT == nullptr) {
                cout << "Data structure isnt loaded Yet, Input option 1 first!" << endl;
                break;
            }
            cT->selectionSort(cT->ns);
            break;
            // Below takes input and prints out single curse information including preReqs if they exsist
        case 3:
            if (cT == nullptr) {
                cout << "Data structure isnt loaded Yet, Input option 1 first!" << endl;
                break;
            }

            string cN;
            cout << "What course do you want to know about?" << endl;
            cin >> cN;

            course = cT->Search(cN);

            if (!course.cN.empty()) {
                cout << course.cN << ", " << course.Name << endl;
                cout << "Prerequisites: " << course.pR << endl;
            }

            else {
                cout << cN << " Course does not excist" << endl;
            }
            break;
        }
    }
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        }