#include <iostream>
#include <fstream>
#include <array>
#include <exception>


using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    TokoElektronik() {
        etalase = {"LED TV", "HP bekas", "Monitor"};
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range& e) {
            string pesanError = "Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!";
            throw pesanError;
        }
    }

    void sinkronisasiKeFile() {
        ifstream cekFile("gudang.txt");
        bool isKosong = false;

        if (!cekFile.is_open()) {
            isKosong = true;
        } else {
            cekFile.seekg(0, ios::end);
            if (cekFile.tellg() == 0) {
                isKosong = true;
            }
            cekFile.close();
        }

        if (isKosong) {
            ofstream tulisFile("gudang.txt");
            for (size_t i = 0; i < etalase.size(); i++) {
                tulisFile << etalase.at(i) << endl;
            }
            tulisFile.close();
            cout << "[Sistem] Data awal dari etalase berhasil dimuat ke gudang!" << endl;
        }
    }
};

void tampilkanGudang() {
    ifstream infile("gudang.txt");
    if (!infile.is_open()) {
        cout << "[Info] Basis data gudang.txt masih kosong atau belum dibuat." << endl;
        return;
    }
    string baris;
    int no = 1;
    cout << "\n--- Daftar Barang di Gudang ---" << endl;
    while (getline(infile, baris)) {
        cout << no << ". " << baris << endl;
        no++;
    }
    infile.close();
    cout << "-------------------------------" << endl;
}

void tambahBarang() {
    ofstream outfile("gudang.txt", ios::app);
    string namaBarang;
    cout << "Masukkan nama barang baru: ";
    getline(cin >> ws, namaBarang);
    outfile << namaBarang << endl;
    outfile.close();
    cout << "Barang berhasil ditambahkan!" << endl;
}

void ubahBarang() {
    ifstream infile("gudang.txt");
    if (!infile.is_open()) {
        cout << "Gudang kosong, tidak ada yang bisa diubah." << endl;
        return;
    }

    int target;
    cout << "Pilih nomor urut barang yang ingin diubah: ";
    cin >> target;

    ofstream tempFile("temp.txt");
    string baris;
    int no = 1;
    bool ditemukan = false;

    while (getline(infile, baris)) {
        if (no == target) {
            string namaBaru;
            cout << "Masukkan nama barang pengganti: ";
            getline(cin >> ws, namaBaru);
            tempFile << namaBaru << endl;
            ditemukan = true;
        } else {
            tempFile << baris << endl;
        }
        no++;
    }
    infile.close();
    tempFile.close();

    remove("gudang.txt");
    rename("temp.txt", "gudang.txt");

    if (ditemukan) {
        cout << "Data barang berhasil diperbarui!" << endl;
    } else {
        cout << "Nomor barang tidak ditemukan!" << endl;
    }
}

void hapusBarang() {
    ifstream infile("gudang.txt");
    if (!infile.is_open()) {
        cout << "Gudang kosong, tidak ada yang bisa dihapus." << endl;
        return;
    }

    int target;
    cout << "Pilih nomor urut barang yang ingin dihapus: ";
    cin >> target;

    ofstream tempFile("temp.txt");
    string baris;
    int no = 1;
    bool ditemukan = false;

    while (getline(infile, baris)) {
        if (no == target) {
            ditemukan = true;
        } else {
            tempFile << baris << endl;
        }
        no++;
    }
    infile.close();
    tempFile.close();

    remove("gudang.txt");
    rename("temp.txt", "gudang.txt");

    if (ditemukan) {
        cout << "Data barang berhasil dihapus!" << endl;
    } else {
        cout << "Nomor barang tidak ditemukan!" << endl;
    }
}

int main() {
    TokoElektronik toko;
    
    toko.sinkronisasiKeFile();
    
    int pilihan;

    do {
        cout << "\n=========================================" << endl;
        cout << "    SISTEM MANAJEMEN TOKO GIBRAN JAYA    " << endl;
        cout << "=========================================" << endl;
        
        tampilkanGudang();

        cout << "Menu Pilihan:" << endl;
        cout << "1. Tambah Data Barang (Create)" << endl;
        cout << "2. Ubah Data Barang (Update)" << endl;
        cout << "3. Hapus Data Barang (Delete)" << endl;
        cout << "4. Simulasi Etalase (Uji Exception Handling)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                ubahBarang();
                break;
            case 3:
                hapusBarang();
                break;
            case 4:
                cout << "\n=== Menjalankan Simulasi Etalase ===" << endl;
                
                try {
                    cout << "[Skenario 1] Mengambil barang di rak indeks ke-1..." << endl;
                    string barang = toko.ambilProduk(1);
                    cout << "-> Berhasil! Anda mengambil: " << barang << endl;
                } catch (string& e) {
                    cout << "-> " << e << endl;
                }

                try {
                    cout << "\n[Skenario 2] Mengambil barang di rak indeks ke-5..." << endl;
                    string barang = toko.ambilProduk(5);
                    cout << "-> Berhasil! Anda mengambil: " << barang << endl;
                } catch (string& e) {
                    cout << "-> " << e << endl; 
                }
                break;
            case 0:
                cout << "Program selesai. Keluar dari sistem." << endl;
                break;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi." << endl;
                break;
        }
    } while (pilihan != 0);

    return 0;
}