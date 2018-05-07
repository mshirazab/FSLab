#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;
const string file_name = "05.txt";
const string index_name = "05-index.txt";

class Student{
	vector<int> indexes;
	vector<string> usns;
	string name, usn, branch, buffer;
	void pack();
	void unpack();
	void insert_into_index(int);
	public:
		Student();
		~Student();
		void write();
		void modify();
		int search();
};


void Student::insert_into_index(int position){
	vector<int>::iterator i;
	vector<string>::iterator j;
	for(i = indexes.begin(), j = usns.begin(); i != indexes.end(); i++, j++)
	{
		if(usn < *j)
		{
			indexes.insert(i, position);
			usns.insert(j, usn);
			return;
		}
	}
	indexes.push_back(position);
	usns.push_back(usn);	
}

void Student::pack()
{
	buffer = name + '|' + usn + '|' + branch + '\n';
}
void Student::unpack()
{
	stringstream ss(buffer);
	getline(ss, name, '|');
	getline(ss, usn, '|');
	getline(ss, branch, '\0');
}
Student::Student()
{
	ifstream fin;
	fin.open(index_name);
	string temp;
	int temp_index;
	string temp_usn;
	fin >> temp_usn;
	fin >> temp_index;
	while(!fin.fail()){
		indexes.push_back(temp_index);
		usns.push_back(temp_usn);
		fin >> temp_usn;
		fin >> temp_index;
	}
	fin.close();
}
Student::~Student()
{
	ofstream fout;
	fout.open(index_name);
	vector<int>::iterator i;
	vector<string>::iterator j;
	for(int i=0; i < usns.size(); i++)
		fout << usns[i] << '\t' << indexes[i] << endl;
	fout.close();
}
void Student::write()
{
   cout << "Enter Student details:\n";
   cout << "Name: ";
   getline(cin, name);
   cout << "USN: ";
   getline(cin, usn);
   cout << "Branch: ";
   getline(cin, branch);
   pack();
   ofstream fout;
   fout.open(file_name, ios::app);
   insert_into_index(fout.tellp());
   fout << buffer << endl;
   fout.close();
}
void Student::modify()
{
	
}
int Student::search()
{
	string search_usn;
	cout << "Enter USN: ";
	cin >> search_usn;
	int l,m,h;
	l=0;h=indexes.size();
	while(l<h)
	{
		m = (l+h)/2;
		if(search_usn == usns[m]){
			ifstream fin;
			fin.open(file_name);
			fin.seekg(indexes[m]);
			getline(fin, buffer);
			unpack();
		    cout << "=========Student Record==========" << endl;
		    cout << "Name: "<< name << endl;
		    cout << "USN: "<< usn << endl;
		    cout << "Branch: "<< branch << endl;
		    return indexes[m];
		}
		else if(search_usn < usns[m])
			h = m;
		else
			l = m + 1;
	}
	return -1;
}
int main(){
	Student student;
	student.search();
	return 0;
}
