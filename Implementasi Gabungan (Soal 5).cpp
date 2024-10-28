#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

struct Buku {
    string ISBN;
    string judul;
    string pengarang;
    int tahunTerbit;
};

// Array of pointers to store books (up to 10 books)
Buku* perpustakaan[10];
int jumlahBuku = 0;

// Stack to store loan history
stack<string> riwayatPeminjaman;

// Queue to manage loan requests
queue<string> antrianPeminjaman;

// Function to add a new book
void tambahBuku(string isbn, string judul, string pengarang, int tahunTerbit) {
    if (jumlahBuku < 10) {
        perpustakaan[jumlahBuku] = new Buku{isbn, judul, pengarang, tahunTerbit};
        jumlahBuku++;
        cout << "Buku berhasil ditambahkan." << endl;
    } else {
        cout << "Kapasitas maksimum perpustakaan tercapai!" << endl;
    }
}

// Function to search for a book by ISBN
void cariBuku(string isbn) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (perpustakaan[i]->ISBN == isbn) {
            cout << "Buku ditemukan:" << endl;
            cout << "ISBN: " << perpustakaan[i]->ISBN << endl;
            cout << "Judul: " << perpustakaan[i]->judul << endl;
            cout << "Pengarang: " << perpustakaan[i]->pengarang << endl;
            cout << "Tahun Terbit: " << perpustakaan[i]->tahunTerbit << endl;
            return;
        }
    }
    cout << "Buku dengan ISBN " << isbn << " tidak ditemukan." << endl;
}

// Function to display all books
void tampilkanBuku() {
    cout << "Daftar Buku di Perpustakaan:" << endl;
    for (int i = 0; i < jumlahBuku; i++) {
        cout << "ISBN: " << perpustakaan[i]->ISBN
             << ", Judul: " << perpustakaan[i]->judul
             << ", Pengarang: " << perpustakaan[i]->pengarang
             << ", Tahun Terbit: " << perpustakaan[i]->tahunTerbit << endl;
    }
}

// Function to loan a book (adds ISBN to loan queue)
void pinjamBuku(string isbn) {
    antrianPeminjaman.push(isbn);
    cout << "Permintaan peminjaman untuk ISBN " << isbn << " ditambahkan ke antrian." << endl;
}

// Function to process a book return
void kembalikanBuku(string isbn) {
    riwayatPeminjaman.push(isbn);
    cout << "Buku dengan ISBN " << isbn << " telah dikembalikan dan ditambahkan ke riwayat peminjaman." << endl;
}

// Function to process loan requests
void prosesPeminjaman() {
    while (!antrianPeminjaman.empty()) {
        string isbn = antrianPeminjaman.front();
        antrianPeminjaman.pop();
        cout << "Memproses peminjaman buku dengan ISBN " << isbn << "." << endl;
        riwayatPeminjaman.push(isbn);
    }
}

// Function to display loan history
void tampilkanRiwayatPeminjaman() {
    cout << "Riwayat Peminjaman Buku:" << endl;
    stack<string> tempStack = riwayatPeminjaman;
    while (!tempStack.empty()) {
        cout << "ISBN: " << tempStack.top() << endl;
        tempStack.pop();
    }
}

int main() {
    tambahBuku("978-1234", "Struktur Data", "A. Budi", 2021);
    tambahBuku("978-5678", "Algoritma Pemrograman", "C. Dewi", 2020);

    cout << "\nDaftar Buku Awal:" << endl;
    tampilkanBuku();

    cout << "\nCari Buku dengan ISBN 978-1234:" << endl;
    cariBuku("978-1234");

    cout << "\nProses Peminjaman Buku:" << endl;
    pinjamBuku("978-1234");
    pinjamBuku("978-5678");
    prosesPeminjaman();

    cout << "\nTampilkan Riwayat Peminjaman:" << endl;
    tampilkanRiwayatPeminjaman();

    cout << "\nProses Pengembalian Buku dengan ISBN 978-1234:" << endl;
    kembalikanBuku("978-1234");

    return 0;
}
