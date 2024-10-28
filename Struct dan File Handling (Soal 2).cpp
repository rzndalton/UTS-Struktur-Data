#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Peralatan {
    string kode;
    string nama;
    int jumlah;
    string kondisi;
};

// Vector to store equipment data in memory
vector<Peralatan> inventaris;

// Function to load equipment data from file
void bacaDariFile() {
    ifstream file("inventaris.txt");
    if (!file) {
        cout << "File tidak ditemukan atau belum ada." << endl;
        return;
    }
    Peralatan peralatan;
    while (file >> peralatan.kode >> peralatan.nama >> peralatan.jumlah >> peralatan.kondisi) {
        inventaris.push_back(peralatan);
    }
    file.close();
}

// Function to save equipment data to file
void simpanKeFile() {
    ofstream file("inventaris.txt", ios::trunc);
    for (const auto& peralatan : inventaris) {
        file << peralatan.kode << " " << peralatan.nama << " "
             << peralatan.jumlah << " " << peralatan.kondisi << endl;
    }
    file.close();
}

// Function to add new equipment
void tambahPeralatan(string kode, string nama, int jumlah, string kondisi) {
    Peralatan peralatan = {kode, nama, jumlah, kondisi};
    inventaris.push_back(peralatan);
    simpanKeFile();
    cout << "Peralatan berhasil ditambahkan." << endl;
}

// Function to update equipment data by code
void ubahPeralatan(string kode) {
    bool found = false;
    for (auto& peralatan : inventaris) {
        if (peralatan.kode == kode) {
            found = true;
            cout << "Masukkan nama baru: ";
            cin >> peralatan.nama;
            cout << "Masukkan jumlah baru: ";
            cin >> peralatan.jumlah;
            cout << "Masukkan kondisi baru: ";
            cin >> peralatan.kondisi;
            simpanKeFile();
            cout << "Peralatan berhasil diubah." << endl;
            break;
        }
    }
    if (!found) {
        cout << "Peralatan dengan kode " << kode << " tidak ditemukan." << endl;
    }
}

// Function to delete equipment by code
void hapusPeralatan(string kode) {
    auto it = remove_if(inventaris.begin(), inventaris.end(),
                        [kode](Peralatan& p) { return p.kode == kode; });
    if (it != inventaris.end()) {
        inventaris.erase(it, inventaris.end());
        simpanKeFile();
        cout << "Peralatan berhasil dihapus." << endl;
    } else {
        cout << "Peralatan dengan kode " << kode << " tidak ditemukan." << endl;
    }
}

// Function to display all equipment sorted by code
void tampilkanInventaris() {
    sort(inventaris.begin(), inventaris.end(),
         [](const Peralatan& a, const Peralatan& b) { return a.kode < b.kode; });
    cout << "Laporan Inventaris Peralatan:" << endl;
    for (const auto& peralatan : inventaris) {
        cout << "Kode: " << peralatan.kode
             << ", Nama: " << peralatan.nama
             << ", Jumlah: " << peralatan.jumlah
             << ", Kondisi: " << peralatan.kondisi << endl;
    }
}

int main() {
    // Load existing data from file at the start
    bacaDariFile();

    // Menu interface (simplified)
    int pilihan;
    string kode, nama, kondisi;
    int jumlah;
    do {
        cout << "\nMenu Inventaris Peralatan:" << endl;
        cout << "1. Tambah Peralatan" << endl;
        cout << "2. Ubah Peralatan" << endl;
        cout << "3. Hapus Peralatan" << endl;
        cout << "4. Tampilkan Inventaris" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan kode peralatan: ";
                cin >> kode;
                cout << "Masukkan nama peralatan: ";
                cin >> nama;
                cout << "Masukkan jumlah peralatan: ";
                cin >> jumlah;
                cout << "Masukkan kondisi peralatan: ";
                cin >> kondisi;
                tambahPeralatan(kode, nama, jumlah, kondisi);
                break;
            case 2:
                cout << "Masukkan kode peralatan yang akan diubah: ";
                cin >> kode;
                ubahPeralatan(kode);
                break;
            case 3:
                cout << "Masukkan kode peralatan yang akan dihapus: ";
                cin >> kode;
                hapusPeralatan(kode);
                break;
            case 4:
                tampilkanInventaris();
                break;
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (pilihan != 0);

    return 0;
}
