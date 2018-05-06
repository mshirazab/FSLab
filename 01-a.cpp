/**
 * Write a C++ program to read series of names, one per line, from standard input and write
 * these names spelled in reverse order to the standard output using I/O redirection and pipes.
 * Repeat the exercise using an input file specified by the user instead of the standard input and
 * using an output file specified by the user instead of the standard output.
**/

#include<iostream>
#include<fstream>
using namespace std;

int main(){
    string inputFileName, outputFileName;
    cout << "enter name of file to read from: ";
    cin >> inputFileName;
    cout << "enter name of file to write into: ";
    cin >> outputFileName;
    ifstream fin;
    ofstream fout;
    fin.open(inputFileName);
    fout.open(outputFileName);
    string buffer;
    while(fin>>buffer) fout << buffer << endl;
    return 0;
}