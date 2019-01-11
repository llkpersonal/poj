#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
    string command, url;
    stack<string> back_stack, forward_stack;
    back_stack.push("http://www.acm.org/");
    while(cin >> command) {
        if(command == "QUIT") break;
        if(command == "VISIT") {
            while(!forward_stack.empty()) forward_stack.pop();
            cin >> url;
            cout << url << endl;
            back_stack.push(url);
        }
        else if(command == "BACK") {
            if(back_stack.size() == 1) {
                cout << "Ignored" << endl;
                continue;
            }
            forward_stack.push(back_stack.top());
            back_stack.pop();
            cout << back_stack.top() << endl;
        }
        else if(command == "FORWARD") {
            if(forward_stack.empty()) {
                cout << "Ignored" << endl;
                continue;
            }
            back_stack.push(forward_stack.top());
            forward_stack.pop();
            cout << back_stack.top() << endl;
        }
    }
    return 0;
}
