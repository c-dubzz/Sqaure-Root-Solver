//
//  AUTHOR: Cole Walgren
//  TITLE: Program 1
//  DESCRIPTION: Header file for PG1.cpp
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

int main(int argc, const char * argv[]);
void trim(string& a);
string add(string a, string b);
string subtract(string a, string b);
string multiply(string a, string b);
int compare(string a, string b);
string sqrt(string a[], string n, int len);
string sqrt2(string s, int a);

#endif /* Header_h */
