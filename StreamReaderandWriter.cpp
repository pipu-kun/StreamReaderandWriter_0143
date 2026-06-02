#include <iostream>
#include <fstream>
using namespace std;

int main(){
    string baris;

    // masuk mode menulis
    ofstream outfile;
    outfile.open("contoh.txt");
    cout << "writing... ketik \'x\' untuk keluar"<< endl;

    // unlimited loop for writing
    while(true){
        cout << "-> ";
        getline(cin, baris);
        // if user input is 'x', break the loop
        if(baris == "x"){
            break;
        }
        // write the line to the file
        outfile << baris << endl;
        
    }
    // close the file after writing
    outfile.close();


    //membuka file dalam mode membaca
    ifstream infile;
    //menunjuk ke sebuah file
    infile.open("contohfile.txt");

    cout << endl << ">=Membuka dan membaca file " << endl;
    //kondisi jika file ada
    if (infile.is_open()){
        //perulangan untuk memunculkan setip baris
        while (getline(infile, baris)) {
            cout << baris << endl;
     }

    //menutup file jika telah selesai
    infile.close();
    }
    //kondisi jika file tidak ada
    else cout << "Unable to open file";
    return 0;
}