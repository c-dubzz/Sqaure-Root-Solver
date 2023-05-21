//
//  AUTHOR: Cole Walgren
//  TITLE: Program 1
//  DESCRIPTION: User enters a number they wish to square root, as well as the
//  number of decimal places they wish the final answer to be set to.
//
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "PG1.h"

using namespace std;

void trim(string& a) {
    
    // takes "a" and removes any zeros at the beginning of the string

    while (a.length() > 1 && a[0] == '0') a = a.substr(1);
}

string add(string a, string b) {
    
    // takes two strings, trims them both, then arithmetically adds
    // them together
    
    trim(a);
    trim(b);
    while (a.length() < b.length()) a = "0" + a;
    while (b.length() < a.length()) b = "0" + b;
    a = "0" + a; //We put an extra zero at the beginning just in case
    b = "0" + b; //we end with a carry
    string ans = "";
    int carry = 0;
    for (int i = (int) a.length() - 1; i >= 0; i--) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        ans = (char)(sum % 10 + '0') + ans;
        carry = sum / 10;
    }
    trim(ans);
    return ans;
}

string subtract(string a, string b) {
    
    // takes two strings, trims them both, then arithmetically
    // subtracts "b" from "a"

    trim(a);
    trim(b);
    while (a.length() < b.length()) a = "0" + a;
    while (b.length() < a.length()) b = "0" + b;
    for (int i = 0; i < b.length(); i++)
        b[i] = (char)('9' - b[i] + '0'); //Finding 9's complement
    string diff = add(add(a, b), "1").substr(1);
    trim(diff);
    return diff;
}

string multiply(string a, string b) {

    // takes two strings, trims them both, then arithmetically
    // multiplies them together
    
    trim(a);
    trim(b);
    string sum = "0";
    for (int i=0; i < a.length(); i++)
        for (int j = 0; j < b.length(); j++) {
            int prod = (a[i] - '0') * (b[j] - '0');
            string addend = to_string(prod);
            for (int k = 0; k < a.length() - 1 - i + b.length() - 1 - j; k++)
                addend += "0";
            sum = add(sum, addend);
        }
    return sum;
}

int compare(string a, string b){
    
    // takes two strings, trims them both, then compares them by length
    // first, then compares them by individual character second
    
    // returns 1 if a is greater
    // returns 2 if b is greater
    // returns 0 if equal
    
        trim(a);
        trim(b);

        if (a.length() > b.length()) return 1;
        else if (a.length() < b.length()) return 2;


        for (int i = 0; i < a.length() - 1; i++) {
            if (a[i] > b[i]) return 1;
            else if (a[i] < b[i]) return 2;
        }

        return 0;}

string sqrt(string n, int z){
    
    // n = original value you wish to sqrt
    // z = zeros (# of decimal places)
    
    // takes a string "n", and using the twos compliment method,
    // finds the square root of n, to "z" decimal places
    
    z = z*2;
    for(int i = 0; i < z; i++){
        n = n + '0';
    }
    
    //Build fours array
    int foursLength = n.length() * 2;
    string * fours = new string[foursLength];
    fours[0] = "1";
    int foursCt = 0;
    for(int i = 1; i < foursLength; i++){
        string foursVal = multiply(fours[i-1],"4");
        if(compare(foursVal, n) == 1){
            break;
        }else{
            fours[i] = foursVal;
            foursCt ++;
        }
    }

    //Begins solving process, cycles through fours array backwards
    // if n - (fours[i] * (4*ans+1)) works, replace ans with (2*ans+1)
    // else replace ans with (2*ans)
    string ans = "0";
    for (int i = foursCt; i >= 0; i--){ //cycles through fours array backwards
            string x = multiply("4",ans);
            string y = add(x,"1");
            string val = multiply(fours[i],y);
            if (compare(n,val) != 2){
                string sub = subtract(n,val);
                string ans2 = multiply(ans,"2");
                ans = add(ans2,"1");
                n = sub;
            }else{
                ans = multiply(ans,"2");
            }
    }
    
    //Memory deallocation
    delete[] fours;
    
    return ans;
}

string addZeros(string answer, int zeros){
    
    // takes "answer", seperates into two substrings at index
    // given by "zeros", then inserts a dot inbetween them,
    // then finally appends the first substring onto the "." onto the
    // second substring
    
    int pos = answer.length()-zeros;
    string sub1 = answer.substr(0, pos);
    string sub2 = answer.substr(pos, answer.length());
    string fin = sub1 + "." + sub2;
    return fin;
}

int main(int argc, const char * argv[]) {
    
    string value;
    string value2;
    cout << "Enter the number you wish to take the square root of: " << endl;
    getline(cin, value);
    
    int zeros = 0;
    cout<< "Enter the amount of digits you would like: " << endl;
    cin >> zeros;
    
    string t = "0.";
        if(value == "0"){
            for(int i = 0; i < zeros; i++){
                t = t + "0";
            }
            cout << "Square root of "<<value<<" to "<<zeros<<" digits is "<<t<<endl;
            return 0;
        }
    
    string answer = sqrt(value, zeros);
    string done = addZeros(answer, zeros);
    
    cout << "Square root of "<<value<<" to "<<zeros<<" digits is "<<done<<endl;
    
    return 0;
}
