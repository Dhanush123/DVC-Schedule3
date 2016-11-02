// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

#include <cstring> // for strtok and strcpy

#include "AssociativeArray.h"

int main() {
  cout << "Programmer: Dhanush Patel\n";
  cout << "Programmer's ID: 1553428\n";
  cout << "File: " << __FILE__ << endl;
  // for parsing the inputfile
  char *token;
  char buf[1000];
  const char *const tab = "\t";
  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";
  AssociativeArray<string, AssociativeArray<string, bool> > alreadySeen;
  AssociativeArray<string, AssociativeArray<string, int> > record;
  int duprecord = 0;
  // read the input file
  while (fin.good()) {
    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue; // skip blank lines
    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
    const string subjectCode(course.begin(), course.begin() + course.find('-'));
    
    if (alreadySeen[term].containsKey(section)){
      duprecord++;
    }
    else{
      alreadySeen[term][section] = true;
      record[subjectCode][course]++;
    }
  }
  fin.close();
  
//---------------------------------------------------------------------------------------------------------- finished parse file
  //outer set of keys, is all the subjects, i.e. SUBJ
  AssociativeArray<int, string> rsKeys;
  queue<string> qs = record.keys();
  for(unsigned int i = 0; i < qs.size(); i++){
    rsKeys[i] = qs.front();
    qs.pop();
  }
  
  for(int i = 0; i < rsKeys.size(); i++){
    for(int j = i + 1; j < rsKeys.size(); j++){
      if(rsKeys[i] > rsKeys[j]){
        swap(rsKeys[i], rsKeys[j]);
      }
    }
  }  
//---------------------------------------------------------------------------------------------------------- subjects got and sorted, starting big loop
  for(int i = 0; i < record.size(); i++){
    int numBlank = 0;

    //innner set of keys, is all actual classes, i.e. SUBJ-###
    AssociativeArray<int, string> rcKeys;
    queue<string> qc = record[rsKeys[i]].keys();
    for(unsigned int i = 0; i < qc.size(); i++){
      rcKeys[i] = qc.front();
      qc.pop();
    }
    
    for(int x = 0; x < record[rsKeys[i]].size(); x++){
      for(int y = x + 1; y < record[rsKeys[i]].size(); y++){
        if(rcKeys[x] > rcKeys[y]){
          swap(rcKeys[x], rcKeys[y]);
        }
      }
    }
//------------------------------------------------------------------ actual classes got and sorted
    AssociativeArray<int, string> outputs;
  
    for(int j = 0; j < record[rsKeys[i]].size(); j++){
      if(rcKeys[j] != "" && record[rsKeys[i]][rcKeys[j]] != 0){
        string s = "  " + rcKeys[j] + ", " + to_string(record[rsKeys[i]][rcKeys[j]]) + " section(s)";
        outputs[j] = s;
      }
      else{
        numBlank++;
      }
    }
//------------------------------------------------------------------ parsed all classes & their sections
    if(rsKeys[i] != "" && (record[rsKeys[i]].size() - numBlank) > 0){
      cout << rsKeys[i] << ", " << record[rsKeys[i]].size() - numBlank << " course(s)" << endl;
    }
    for(int z = 0; z < outputs.size(); z++){
      if(outputs[z] != "")
      cout << outputs[z] << endl;
    }
  }
//---------------------------------------------------------------------------------------------------------- did all output, for subject + classes; big loop done
  cout  << "Number of duplicates: " << duprecord << endl;
}