#include <iostream>
#include <exception>
#include <array>
using namespace std;

int main(){
    cout << "awal program" << endl;
    try{
        array<int, 3> data = {1, 2, 3};
        cout << data.at(4) << endl;
    }
}