//
// Created by hejinyang on 2019/8/2.
//

#if 1

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

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


int main(int argc, char *argv[]) {

    string proPath = string(argv[1]);
    string filePath = string(argv[2]);
//    string proPath = "H:\\Program data\\CPP Data\\CppPro01";
//    string filePath = "H:\\Program data\\CPP Data\\CppPro01\\Study01\\test.cpp";
    filePath = repalce(filePath, '\\', '/');
    proPath = repalce(proPath, '\\','/');
    auto v = split(filePath, '/');
    auto v1 = split(v.at(v.size()-1), '.');

    fstream ff(proPath + "/CmakeLists.txt", ios::ate | ios::out);
    ff << "cmake_minimum_required(VERSION 3.12)\n"
          "project(CppPro01)\n"
          "set(CMAKE_CXX_STANDARD 17)" << endl;
    ff << "add_executable(" << v1.at(0) <<  " \"" << filePath << "\")" << endl;
    ff.flush();
    ff.close();
    cout << v1.at(0)<< "重新写入成功" << endl;

    return 0;
}

#endif