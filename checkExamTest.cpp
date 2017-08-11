#include <bits/stdc++.h>
#include <windows.h>
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif
using namespace std;
#define endl "\n";
string probName = "";
string numToStr(int n) {
    string res;
    ostringstream convert;
    convert << n;
    res = convert.str();
    return res;
}

void WriteInput(int id) {
    ifstream inputx;
    string fInput = "tests/" + numToStr(id) + ".inp";
    inputx.open(fInput.c_str());
    if (!inputx.good()) return ;
    cout << "Expected input:" << endl;
    while (!inputx.eof()) {
        string str;
        getline(inputx, str);
        cout << str << endl;
    }
    inputx.close();
}

int comp(int id) {
    string ids = numToStr(id);
    string test = "tests/" + ids + ".out";
    ifstream tsoutput;
    tsoutput.open(test.c_str());
    if (tsoutput.good()) {
        vector <string> urans;
        vector <string> tsans;
        string cOutput = probName + ".exe < tests/" + ids + ".inp > tests/output.txt";
        system(cOutput.c_str());

        ifstream uroutput;
        uroutput.open("tests/output.txt");
        while (!uroutput.eof()) {
            string str;
            getline(uroutput, str);
            if (str[(int)str.size()-1] == ' ') str.erase((int)str.size()-1);
            urans.push_back(str);
        }
        uroutput.close();

        ifstream tsoutput;
        string tempx = "tests/" + ids + ".out";
        tsoutput.open(tempx.c_str());
        while (!tsoutput.eof()) {
            string str;
            getline(tsoutput, str);
            if (str[(int)str.size()-1] == ' ') str.erase((int)str.size()-1);
            tsans.push_back(str);
        }
        tsoutput.close();

        cout << "Expected output:" << endl;
        for (int i = 0; i < (int)tsans.size(); i++) {
            cout << tsans[i] << endl;
        }
        cout << endl;
        cout << "Execution result:" << endl;
        for (int i = 0; i < (int)urans.size(); i++) {
            cout << urans[i] << endl;
        }

        for (int i = 0; i < min((int)urans.size(), (int)tsans.size()); i++) {
            if (tsans[i] != urans[i]) {
                return 0;
            }
        }
        return 1;
    } else {
        return -1;
    }
}

void check() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 11);
    cout << "Compiling..." << endl;
    SetConsoleTextAttribute(hConsole, 7);

    cout << endl;
    string compile = "g++ -m32 -o "+probName+".exe "+probName+".cpp";
    system(compile.c_str());
    cout << "=======================" << endl;
    cout << endl;

    int tcs = -1;
    int wrong = 0;
    while (1) {
        tcs++;
        WriteInput(tcs);
        cout << endl;
        int callback = comp(tcs);
        if (callback == -1) break;
        cout << endl;
        cout << "Verdict: ";
        if (callback == 0) {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Wrong answer";
            SetConsoleTextAttribute(hConsole, 7);
            wrong++;
        }
        if (callback == 1) {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "OK";
            SetConsoleTextAttribute(hConsole, 7);
        }
        cout << endl; cout << endl;
        cout << "=======================" << endl;
        cout << endl;
    }

    cout << "TOTAL: ";
    if (wrong > 0) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Wrong Answer!";
        SetConsoleTextAttribute(hConsole, 7);
    } else {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "Pass example test!";
        SetConsoleTextAttribute(hConsole, 7);
    }

    cout << endl;
    cout << endl;
}

string getPath() {
    char cCurrentPath[FILENAME_MAX];
    GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    return cCurrentPath;
}

string getDirName() {
    string path = getPath();
    string s = "";
    int local = -1;
    for (int i = (int)path.size()-1; i >= 0; i--) {
        if (path[i] == '\\') {
            local = i;
            break;
        }
    }
    for (int i = local+1; i < (int)path.size(); i++) s += path[i];
    return s;
}

int main() {
    probName = getDirName();
    check();
    return 0;
}
