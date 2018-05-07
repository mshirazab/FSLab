// Write a C++ program to read and write student objects with fixed length records and the
// fields delimited by “|”. Implement pack ( ), unpack ( ), modify ( ) and search ( ) methods.
#include<iostream>
#include<fstream>
#include<sstream>
#define file_name "01.txt"
using namespace std;

class Student {
    string name, usn, branch, buffer;
    int max_size;
    void pack();
    void unpack();
    public:
    Student(int);
    void read();
    void write();
    void modify();
    int search(string);
};
Student::Student(int num){
    max_size = num;
}
void Student::pack(){
    buffer = name + '|' + usn + '|' + branch;
    if(buffer.length() >= max_size)
        throw "string larger than buffer";
    buffer += string(max_size - buffer.length(), '#');
}
void Student::unpack(){
    stringstream ss(buffer);
    getline(ss, name, '|');
    getline(ss, usn, '|');
    getline(ss, branch, '#');
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
    char temp [max_size];
    while(fin.read(temp, max_size)){
        buffer = temp;
        unpack();
        cout << "=========Student Record==========" << endl;
        cout << "Name: "<< name << endl;
        cout << "USN: "<< usn << endl;
        cout << "Branch: "<< branch << endl;
    }
}
void Student::modify(){
    string delete_usn;
    cout << "Enter the usn to be deleted: ";
    cin >> delete_usn;
    int position = search(delete_usn);
    if(position == -1)
        cout << "USN not found, try again!" << endl;
    else{
        fstream fp;
        char temp[max_size];
        fp.open(file_name, ios::in|ios::out);
        fp.seekp(position, ios_base::beg);
        usn = delete_usn;
        cout << "Enter new name: ";
        cin >> name;
        cout << "Enter new branch: ";
        cin >> branch;
        pack();
        fp.write(buffer.c_str(), max_size);
    }
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
    char temp[max_size];
    int position = 0;
    while(fin.read(temp, max_size)){
        buffer = temp;
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
    Student student(100);
    return 0;
}
