// Write a C++ program to read and write student objects with fixed length records and the
// fields delimited by “|”. Implement pack ( ), unpack ( ), modify ( ) and search ( ) methods.
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
const string file_name = "03.txt";

class Student {
    string name, usn, branch, buffer;
    void pack();
    void unpack();
    public:
    void read();
    void write();
    void modify();
    int search(string);
};
void Student::pack(){
    buffer = name + '|' + usn + '|' + branch + '\n';
}
void Student::unpack(){
    stringstream ss(buffer);
    getline(ss, name, '|');
    getline(ss, usn, '|');
    getline(ss, branch, '\0');
}
void Student::write(){
   cout << "Enter Student details:\n";
   cout << "Name: ";
   cin >> name;
   cout << "USN: ";
   cin >> usn;
   cout << "Branch: ";
   cin >> branch;
   pack();
   fstream fp;
   fp.open(file_name, ios::app);
   fp << buffer;
   fp.close();
}
void Student::read(){
    ifstream fin;
    fin.open(file_name);
    while(fin >> buffer){
        unpack();
        cout << "=========Student Record==========" << endl;
        cout << "Name: "<< name << endl;
        cout << "USN: "<< usn << endl;
        cout << "Branch: "<< branch << endl;
    }
}
void Student::modify(){
    string delete_usn;
    bool found = false;
    cout << "Enter the usn to be deleted: ";
    cin >> delete_usn;
    ifstream fin;
    ofstream fout;
    fin.open(file_name);
    fout.open(file_name+".tmp");
    while(fin >> buffer){
        unpack();
        if(usn == delete_usn){
            cout << "Enter new name: ";
            cin >> name;
            cout << "Enter new branch: ";
            cin >> branch;
            pack();
            found = true;
            fout << buffer;
        }
        else{
            fout << buffer << endl;
        }
    }
    if(!found){
        cout << "USN not found";
    }
    rename((file_name+".tmp").c_str(), file_name.c_str());
}
int Student::search(string given_search = ""){
    string search_usn;
    if(given_search == ""){
        cout << "Enter the usn to be searched: ";
        cin >> search_usn;
    }
    else{
        search_usn = given_search;
    }
    ifstream fin;
    fin.open(file_name);
    int position = 0;
    while(fin >> buffer){
        unpack();
        if(usn == search_usn){
            if(given_search == ""){
                cout << "=========Student Record Found==========" << endl;
                cout << "Name: "<< name << endl;
                cout << "USN: "<< usn << endl;
                cout << "Branch: "<< branch << endl;
            }
            return position;
        }
        position = fin.tellg();
    }
    return -1;
}
int main(){
    Student student;
    student.modify();
    return 0;
}
