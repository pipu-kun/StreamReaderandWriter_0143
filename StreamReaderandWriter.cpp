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
}