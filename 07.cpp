#include<iostream>
#include<fstream>
using namespace std;

void CoSequentialSearch(string inputFile1, string inputFile2, string outputFile){
    ifstream fin1, fin2;
    ofstream fout;
    string buffer1, buffer2, prev="";
    fin1.open(inputFile1);
    fin2.open(inputFile2);
    fout.open(outputFile);
    fin1 >> buffer1;
    fin2 >> buffer2;
    while(!fin1.eof() && !fin2.eof()){
        if(buffer1>buffer2){
            fin2 >> buffer2;
        }
        else if(buffer2>buffer1){
            fin1 >> buffer1;
        }
        else{
            fout << buffer1 << endl;
            fin1 >> buffer1;
            fin2 >> buffer2;
        }
    }
    fin1.close();
    fin2.close();
    fout.close();
}
int main(){
    CoSequentialSearch("07-in1.txt", "07-in2.txt", "07-out.txt");
}