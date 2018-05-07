#include<iostream>
#include <iomanip>
#include<fstream>
#include<sstream>
using namespace std;
const string file_name = "04.txt";
const string index_name = "04-index.txt";

class Student {
    string name, usn, branch, buffer;
    int max_records = 5;
    void pack();
    void unpack();
    public:
    void read();
    void write();
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
   getline(cin, name);
   cout << "USN: ";
   getline(cin, usn);
   cout << "Branch: ";
   getline(cin, branch);
   pack();
   fstream fp, findex;
   fp.open(file_name, ios::app);
   findex.open(index_name, ios::app);
   findex << setfill('0') << setw(max_records) << fp.tellp();
   fp << buffer;
   fp.close();
   findex.close();
}
void Student::read(){
    ifstream fin, findex;
    fin.open(file_name);
    findex.open(index_name);
    int rrn;
    cout << "Enter RRN: ";
    cin >> rrn;
    if(rrn < 0)
        cout << "Error: RRN cannot be lesser than 0";
    else{
        findex.seekg(rrn*max_records);
        char pos[max_records];
        findex.read(pos, max_records);
        fin.seekg(atoi(pos));
        getline(fin, buffer);
        unpack();
        cout << "=========Student Record==========" << endl;
        cout << "Name: "<< name << endl;
        cout << "USN: "<< usn << endl;
        cout << "Branch: "<< branch << endl;
    }
}

int main(){
    Student student;
    return 0;
}