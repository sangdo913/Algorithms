#include<iostream>
#include<fstream>

using namespace std;

int main() {
    ofstream f("c:\\Users\\SD\\Desktop\\Git\\Algorithms\\StudyAlone\\C_Practice\\2101\\text3.txt");
    if(!f.fail()) {
        f << "int b1[256] = {" ;
        for(int i = 0; i < (1<<8); ++i){
            int num = 0;
            int b = i >> 2;
            for(int j = 0; j < 8; ++j){
                if(b & (1<<j)) num++;
            }
            f<< num <<", ";
        }
        f<< "}" << endl;
        f << "int b21[256] = {";
        for(int i = 0; i < (1<<8); ++i){
            int b = i&0x3;
            int num = 0;
            for(int j = 0; j < 8; ++j){
                if(b&(1<<j))  num++;
            }
            f << num   << ", ";
        }
        f <<"}" << endl;
        f <<"int b22[256] = {";
        for(int i = 0; i < (1 << 8); ++i){
            int num = 0;
            int b = i>>4;
            for(int j = 0; j < 8; ++j) {
                if(b &(1 << j)) num++;
            }
            f << num << ", ";
        }
        f << "}" << endl;

        f <<"int b31[256] = {";
        for(int i = 0; i < (1 << 8); ++i){
            int num = 0;
            int b = i&0xf;
            for(int j = 0; j < 8; ++j) {
                if(b &(1 << j)) num++;
            }
            f << num << ", ";
        }
        f << "}" << endl;
        f <<"int b32[256] = {";
        for(int i = 0; i < (1 << 8); ++i){
            int num = 0;
            int b = i>>6;
            for(int j = 0; j < 8; ++j) {
                if(b &(1 << j)) num++;
            }
            f << num << ", ";
        }
        f << "}" << endl;
        f <<"int b4[256] = {";
        for(int i = 0; i < (1 << 8); ++i){
            int num = 0;
            int b = i&0x3f;
            for(int j = 0; j < 8; ++j) {
                if(b &(1 << j)) num++;
            }
            f << num << ", ";
        }
        f << "}" << endl;
        f.close();
    }
    return 0;
}