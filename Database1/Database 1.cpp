#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(0); cin.tie(0);
    string pointer,login,password,entrancel,entrancep,exitl;
    map<string, string> m;
    set<string> s;
    while (cin >> pointer) {
        if (pointer == "register") {
            cin >> login >> password;
            if (m.count(login) == 0) {
                m[login] = password;
                cout << "account created" << '\n';
            }
            else {
                cout << "login already in use" << '\n';
            }
        }
        else if (pointer == "login") {
            cin >> entrancel >> entrancep;
            if (m.count(entrancel) != 0) {
                if (m[entrancel] != entrancep) {
                    cout << "wrong account info" << '\n';
                }
                else if (s.count(entrancel) == 0) {
                    s.insert(entrancel);
                    cout << "logged in" << '\n';
                }
                else {
                    cout << "already logged in" << '\n';
                }
            }
            else{
                cout << "wrong account info" << '\n';
            }
        }
        else { //pointer == logout
            cin >> exitl;
            if (m.count(exitl) == 0 || s.count(exitl) == 0) {
                cout << "incorrect operation" << '\n';
            }
            else {
                s.erase(exitl);
                cout << "logged out" << '\n';
            }
        }
    }
}