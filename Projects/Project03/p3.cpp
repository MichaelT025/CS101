#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Record{
    public:
    vector<string> fields;

};

class Table{
    public:
    vector<Record> data;
    string header;
    
};

class SortCrit{
    public:
    string colname;
    int col;
    int o; //0 is descend, 1 is ascend
    int t; //0 is string, 1 is int, 2 is float
};

void mergeSort(Table& table, vector<SortCrit>& criteria, int left, int right);
void merge(Table & table, vector<SortCrit>& criteria, int left, int mid, int right);
int compare(Record &r1, Record &r2, vector<SortCrit> &crit);
void output(Table& table, ofstream& out);

int main(int argc, char* argv[]){

    unordered_map<string, int>colidx;
    string line;
    ifstream in(argv[1]);
    ifstream order(argv[2]);
    ofstream out(argv[3]);
    if(!in.is_open() || !order.is_open() || !out.is_open()){
        cout << "Error opening file" << endl;
        return 1;
    }

    //store column names and their index
    string current;
    getline(in, line);
    istringstream iss(line);
    int size=0;
    while(getline(iss, current, ',')){
        colidx[current]=size;
        size++;
    }

    Table database;
    database.header=line;

    //read in and store records
    while(getline(in, line)){
        istringstream iss(line);
        Record r;
        while(getline(iss, current, ',')){
            r.fields.push_back(current);
        }
        database.data.push_back(r);
    }

    //parse sort criteria;
    vector<SortCrit> criteria;
    while(getline(order, line)){
        istringstream iss(line);
        SortCrit sc;
        string ord;
        string type;
        getline(iss, sc.colname, ',');
        getline(iss, ord, ',');
        getline(iss, type, ',');
        if(ord=="ascend") sc.o=1;
        else sc.o=0;
        if(type=="string") sc.t=0;
        else if(type=="int") sc.t=1;
        else if(type=="float") sc.t=2;
        else{ cout<<"INVALID TYPE IN ORDER FILE"<<endl; return 1;}
        sc.col=colidx[sc.colname];
        criteria.push_back(sc);
    }
    if(database.data.size()<=1){
        output(database, out);
        return 0;
    }

    mergeSort(database, criteria,0, (int)database.data.size()-1);
    output(database, out);


    in.close();
    order.close();
    out.close();
    return 0;

}



//functions:

void mergeSort(Table& table, vector<SortCrit>& criteria, int left, int right){
    if(left>=right) return;
    int mid=(left+right)/2;
    mergeSort(table, criteria, left, mid);
    mergeSort(table, criteria, mid+1, right);
    merge(table, criteria, left, mid, right);
}

void merge(Table & table, vector<SortCrit>& criteria, int left, int mid, int right){
    int lsize=mid-left+1;
    int rsize=right-mid;
    vector<Record> ltemp(lsize);
    vector<Record> rtemp(rsize);
    for(int i=0;i<lsize;i++){
        ltemp[i]=table.data[left+i];
    }
    for(int i=0;i<rsize;i++){
        rtemp[i]=table.data[mid+1+i];
    }
    int i=left;
    int j=0, k=0;
    while(j<lsize && k<rsize){
        if(compare(ltemp[j], rtemp[k], criteria)<=0){
            table.data[i]=ltemp[j];
            i++;
            j++; 
        }
        else{
            table.data[i]=rtemp[k];
            i++;
            k++; 
        }
    }
    while(j<lsize){
        table.data[i]=ltemp[j];
        i++;
        j++;
    }
    while(k<rsize){
        table.data[i]=rtemp[k];
        i++;
        k++;
    }
}

int compare(Record &r1, Record &r2, vector<SortCrit> &crit){
    for(int i=0;i<crit.size();i++){
        int idx=crit[i].col;
        int order=crit[i].o;
        int type=crit[i].t;
        
        int cmp = 0;  
        
        if(type==0){  // string
            if(r1.fields[idx]<r2.fields[idx]) cmp = -1;
            else if(r1.fields[idx]>r2.fields[idx]) cmp = 1;
        }
        else if(type==1){  // int
            int v1 = stoi(r1.fields[idx]);
            int v2 = stoi(r2.fields[idx]);
            if(v1 < v2) cmp = -1;
            else if(v1 > v2) cmp = 1;
        }
        else if(type==2){  // float
            float v1 = stof(r1.fields[idx]);
            float v2 = stof(r2.fields[idx]);
            if(v1 < v2) cmp = -1;
            else if(v1 > v2) cmp = 1;
        }
        
        // Apply order (flip for descending)
        if(cmp != 0) {
            return (order == 1) ? cmp : -cmp;
        }
    }
    return 0;
}

void output(Table& table, ofstream& out){
    out << table.header;
    out << endl;
    for(int i=0;i<table.data.size();i++){
        for(int j=0;j<table.data[i].fields.size();j++){
            out << table.data[i].fields[j];
            if(j<table.data[i].fields.size()-1) out << ",";
        }
        out << endl;
    }     
}


