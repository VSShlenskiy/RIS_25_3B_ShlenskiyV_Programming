#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

void convert(string& str) {
    for (int i = 0; i < str.length(); i++) {
        if (!(isspace(str[i]))) {
            if (isalpha(str[i]) || str[i] == '_') {
                while (str[i] != ' ' && i < str.length()) {
                    i++;
                }
            }
            else {
                int l = i, len = 0;
                while (!(isspace(str[i])) && i < str.length()) {
                    i++;
                    len++;
                }
                str.erase(l, len);
                i = l;
            }
        }
    }

}

int main() {
    string s;
    while (1) {
        getline(cin, s);
        convert(s);
        cout << s << "\n\n";
    }
    return 0;
}