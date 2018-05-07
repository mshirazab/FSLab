#include<iostream>
using namespace std;

string reverse(string a){
    string b(a);
    cout << b;
    reverse(b);
}

int main(){
    string a,b="";
    cin >> a;
    while(!cin.fail()){
        b = "";
        for(int i = a.size() - 1; i >=0; i--)
            b += a[i];
        cout << b << endl;
        cin >> a;
    }
}