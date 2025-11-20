#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

int main(){
    string filename="";
    cin>>filename;
    //filename="StudentInfo.tsv";
    ifstream infile;
    ofstream outfile;
    outfile.open("report.txt");
    infile.open(filename);
    if(!infile){
        cout<<"Error in opening the file"<<endl;
        return 1;
    }
    vector<vector<string>> grade_table;
    string val;
        while (!infile.eof()){
            vector<string> row(6);
            for(int j=0;j<5;j++){
                infile>>val;
                if(infile.eof()) break;
                row[j]=val;
            }
            grade_table.push_back(row);
        }

    for(int i=0;i<grade_table.size();i++){
        if(grade_table[i][0].empty()) break;
        int sum=stoi(grade_table[i][2])+stoi(grade_table[i][3])+stoi(grade_table[i][4]);
        double avg=sum/3.0;
        string grade;
        if(avg>=90) grade="A";
        else if(avg>=80) grade="B";
        else if(avg>=70) grade="C";
        else if(avg>=60) grade="D";
        else grade="F";
        grade_table[i][5]=grade;
    }

    for(int i=0;i<grade_table.size();i++){
        for(int j=0;j<6;j++)
            if(!grade_table[i][j].empty())
            if(j!=5) outfile<<grade_table[i][j]<<"\t";
            else outfile<<grade_table[i][j];
        outfile<<endl;
    }
    double avm1=0;
    double avm2=0;
    double avfinal=0;
    for(int i=0;i<grade_table.size();i++){
        if(grade_table[i][0].empty()) continue;
        avm1+=stof(grade_table[i][2]);
        //cout<<endl<<"Debug: avm1 after adding " << grade_table[i][2] << " is " << avm1 << endl; // Debug line
        avm2+=stof(grade_table[i][3]);
        //cout<<endl<<"Debug: avm2 after adding " << grade_table[i][3] << " is " << avm2 << endl; // Debug line
        avfinal+=stof(grade_table[i][4]);
        //cout<<endl <<"Debug: avfinal after adding " << grade_table[i][4] << " is " << avfinal << endl; // Debug line
    }
    avm1/=(grade_table.size()-1);
    //cout<<endl<<"Debug: avm1 after dividing by " << (grade_table.size()-1) << " is " << avm1 << endl; // Debug line
    avm2/=(grade_table.size()-1);
    avfinal/=(grade_table.size()-1);
    outfile<<fixed<<setprecision(2);
    outfile<<"Averages: midterm1 "<<avm1<<", midterm2 "<<avm2<<", final "<<avfinal<<endl;
    infile.close();
    outfile.close();
    return 0;
}