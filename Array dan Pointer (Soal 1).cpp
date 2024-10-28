#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string NIM;
    string nama;
    float IPK;
};

// Array of pointers to store data of up to 10 students
Mahasiswa* mahasiswaArray[10];
int jumlahMahasiswa = 0;

// Function to add a new student
void tambahMahasiswa(string nim, string nama, float ipk) {
    if (jumlahMahasiswa < 10) {
        mahasiswaArray[jumlahMahasiswa] = new Mahasiswa{nim, nama, ipk};
        jumlahMahasiswa++;
    } else {
        cout << "Kapasitas maksimum mahasiswa tercapai!" << endl;
    }
}

// Function to delete a student by NIM
void hapusMahasiswa(string nim) {
    bool found = false;
    for (int i = 0; i < jumlahMahasiswa; i++) {
        if (mahasiswaArray[i]->NIM == nim) {
            found = true;
            delete mahasiswaArray[i]; // Delete the specific student
            for (int j = i; j < jumlahMahasiswa - 1; j++) {
                mahasiswaArray[j] = mahasiswaArray[j + 1];
            }
            mahasiswaArray[jumlahMahasiswa - 1] = nullptr;
            jumlahMahasiswa--;
            cout << "Mahasiswa dengan NIM " << nim << " telah dihapus." << endl;
            break;
        }
    }
    if (!found) {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan!" << endl;
    }
}

// Function to display all students
void tampilkanMahasiswa() {
    cout << "Daftar Mahasiswa:" << endl;
    for (int i = 0; i < jumlahMahasiswa; i++) {
        cout << "NIM: " << mahasiswaArray[i]->NIM
             << ", Nama: " << mahasiswaArray[i]->nama
             << ", IPK: " << mahasiswaArray[i]->IPK << endl;
    }
}

// Function to sort students by IPK using bubble sort
void urutkanMahasiswa() {
    for (int i = 0; i < jumlahMahasiswa - 1; i++) {
        for (int j = 0; j < jumlahMahasiswa - i - 1; j++) {
            if (mahasiswaArray[j]->IPK < mahasiswaArray[j + 1]->IPK) {
                // Swap the pointers
                Mahasiswa* temp = mahasiswaArray[j];
                mahasiswaArray[j] = mahasiswaArray[j + 1];
                mahasiswaArray[j + 1] = temp;
            }
        }
    }
    cout << "Data mahasiswa telah diurutkan berdasarkan IPK." << endl;
}

int main() {
    tambahMahasiswa("A001", "Budi", 3.5);
    tambahMahasiswa("A002", "Ani", 3.8);
    tambahMahasiswa("A003", "Susi", 3.2);
    tampilkanMahasiswa();

    cout << "\nSetelah diurutkan:" << endl;
    urutkanMahasiswa();
    tampilkanMahasiswa();

    cout << "\nSetelah penghapusan mahasiswa dengan NIM A001:" << endl;
    hapusMahasiswa("A001");
    tampilkanMahasiswa();

    return 0;
}
