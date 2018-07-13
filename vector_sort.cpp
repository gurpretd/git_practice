//
// Created by c_gdhami on 7/5/2018.
//

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int main()
{

    vector <int>  int_v;


    for( int i=0;i<10;i++) {
        int_v.push_back(i);

        int_v[i] = 2;
        cout << "vector " << "i = " << i << int_v.at(i);

    }

}
