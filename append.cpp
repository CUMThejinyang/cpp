//
// Created by hejinyang on 2019/8/2.
//

#if 1

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>


using namespace std;


string repalce(string oldstring, char old, char new_) {
    long long len = oldstring.length();
    char *tmp = new char[len + 1];
    long long i;
    for (i = 0; i < len; ++i) {
        if (oldstring[i] == old) {
            tmp[i] = new_;
        } else {
            tmp[i] = oldstring[i];
        }
    }
    tmp[i] = '\0';
    string s = string(tmp);
    free(tmp);
    return s;
}

vector<string> split(string old, char delim) {
    vector<string> v;
    stringstream ss;
    string s;
    ss << old;
    while (getline(ss, s, delim)) {
        v.push_back(s);
    }
    return v;
}

string getProName(string s) {
    unsigned long long int len = 15;
    long long int pos = s.find("add_executable(");
    if (pos == string::npos) {
        return "";
    }
    long long int pos_space = s.find(" ");
    return s.substr(len, pos_space - len);
}

set<string> getNameSet(string proPath){
    set<string> set1;
    string s;
    string proname;
    ifstream fi(proPath + "/CmakeLists.txt");
    while (getline(fi, s)){
        proname = getProName(s);
        set1.insert(proname);
    }
    return set1;
}




bool isExistsInFile(string proname, set<string> set1){
    return !(set1.find(proname) == set1.end());
}


void printNameInfo(set<string> set1){
    cout << "�Ѿ����ڵ���Ŀ������:" <<endl;
    cout << "------------------------------------------------------------" << endl;
    for (set<string>::iterator it = set1.begin(); it != set1.end();it++){
        cout << *it << endl;
    }
    cout << "------------------------------------------------------------" << endl;
}









int main(int argc, char *argv[]) {

    string proPath = string(argv[1]);
    string filePath = string(argv[2]);
//    string proPath = "H:\\Program data\\CPP Data\\CppPro01";
//    string filePath = "H:\\Program data\\CPP Data\\CppPro01\\Study01\\test.cpp";
    filePath = repalce(filePath, '\\', '/');
    proPath = repalce(proPath, '\\', '/');
    auto v = split(filePath, '/');
    auto v1 = split(v.at(v.size() - 1), '.');
    string proName = v1.at(0);
    char ch;
    ifstream ff(proPath + "/CmakeLists.txt");
    auto set1 = getNameSet(proPath);



    if (isExistsInFile(proName, set1)) {
        printNameInfo(set1);
        cout << "�Ѿ�������ͬ��Ŀ��"<< proName << " ȷ��Ҫ����������?<y/n>";
        cin >> ch;
        if (ch == 'y' || ch == 'Y') {
            cout << "�������µ���Ŀ��:";
            while (true) {
               cin >> proName;
               cout << "�µ���Ŀ����:" << proName << endl;
               if (!isExistsInFile(proName, set1)){
                   cout << "���θ�����Ŀ���ɹ�" << endl;
                   break;
               }else{
                   cout << "��������, ����������:";
               }
            }
        }else{
            cout << "���ʧ��" << endl;
            return -1;
        }
    }
    ff.close();




    fstream fo(proPath + "/CmakeLists.txt", ios::app | ios::out);
    fo << "add_executable(" << proName <<  " \"" << filePath << "\")" << endl;
    fo.flush();
    fo.close();
    cout << proName << "��ӳɹ�" << endl;



    return 0;
}

#endif