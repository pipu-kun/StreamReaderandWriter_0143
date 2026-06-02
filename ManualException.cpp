#include <iostream>
#include <exception> // kalo manual gausah pake ini
using namespace std;

int main(){
    try{
        cout << "hidup jokowi" <<endl;
        //throw 0.5; buat ngelempar error, bisa pake tipe data apa aja
        cout << "ga akan tampil jika throw diaktifkan" << endl;
    }catch(int a){
        cout << "error tipe data int: " << a << endl;
    }catch(...){
        cout << "default catch, error tipe data apa saja" << endl; // karena throw pake double, maka catch yang dipanggil adalah catch default
    }
}