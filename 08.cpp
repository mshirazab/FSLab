#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

bool isEof(vector<bool> eofs){
    for(int i = 0; i < eofs.size() ; i++){
        if(!eofs[i]) return false;
    }
    return true;
}

int getSmallest(vector<string> buffers, vector<bool> error){
    int pos = 0;
    for(int i = 1; i < buffers.size(); i++){
        if(error[pos]){
            pos = i;
        }
        if(!error[i] && buffers[pos] > buffers[i]){
            pos = i;
        }
    }
    return pos;
}

void kWayMerge(string outpuFile, vector<string> inputFileNames){
    int n = inputFileNames.size();
    ifstream fins[n];
    vector<bool> errors(n);
    vector<string> buffers(n);
    string prev;
    ofstream fout;
    for(int i = 0; i < n; i++){
        fins[i].open(inputFileNames[i]);
        fins[i] >> buffers[i];
        errors[i] = fins[i].fail();
    }
    fout.open(outpuFile);
    while(!isEof(errors)){
        int curr = getSmallest(buffers, errors);
        if(prev != buffers[curr]){
            fout << buffers[curr] << endl;
            prev = buffers[curr];
        }
        fins[curr] >> buffers[curr];
        errors[curr] = fins[curr].fail();
    }
}

int main(){
    vector<string> inputFiles;
    inputFiles.push_back("8-in1.txt");
    inputFiles.push_back("8-in2.txt");
    inputFiles.push_back("8-in3.txt");
    kWayMerge("8-out.txt", inputFiles);
}