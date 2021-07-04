#include <iostream>
#include <string>
#include <iostream>
using namespace std;

void make_shifts(char* s, int* shift) {
    int m = strlen(s);
    for (int i = 0; i < 128; i++) {
        shift[i] = m;
    }
    for (int i = 0; i < m - 1; i++) {
        shift[s[i]] = m - i - 1;
    }
}

int main() { // the length of mainString[] should be larger than pattern[] 's length 
    char mainString[] = "Hoola-hoola girls like hooligans";
    char pattern[] = "hoolig";
    int shifts[128];
    make_shifts(pattern, shifts);
    int n = strlen(mainString);
    int m = strlen(pattern);
    int k = 0;
    while (k < (n - m)) {
        int start = k;
        bool flag = true;
        for (int i = 0; i < m; i++) {
            if (pattern[i] != mainString[start]) {
                flag = false;
            }
            start++;
        }
        if (flag) {
            cout << "Yes" << '\n';
            return 0;
        }
        else {
            int last_letter = k + m - 1;
            k += shifts[mainString[last_letter]];
        }
    }
    cout << "No" << '\n';
    return 0;
}
