#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Pelanggan {
    int nomorAntrian;
    int waktuLayanan; // waktu layanan dalam menit
};

class Queue {
private:
    queue<Pelanggan> q;

public:
    void enqueue(Pelanggan p) {
        q.push(p);
    }

    Pelanggan dequeue() {
        Pelanggan frontPelanggan = q.front();
        q.pop();
        return frontPelanggan;
    }

    bool isEmpty() {
        return q.empty();
    }

    int size() {
        return q.size();
    }
};

// Function to simulate customer service with 3 counters
void simulasiLayanan(Queue& antrian, int loketCount) {
    vector<int> waktuLoket(loketCount, 0); // Waktu yang teralokasi di tiap loket
    int totalWaktuTunggu = 0;
    int totalPelanggan = 0;

    while (!antrian.isEmpty()) {
        Pelanggan p = antrian.dequeue();

        // Tentukan loket dengan waktu layanan tersingkat yang tersedia
        int loketMin = 0;
        for (int i = 1; i < loketCount; i++) {
            if (waktuLoket[i] < waktuLoket[loketMin]) {
                loketMin = i;
            }
        }

        // Hitung waktu tunggu untuk pelanggan ini
        int waktuTunggu = waktuLoket[loketMin];
        totalWaktuTunggu += waktuTunggu;
        
        // Tambahkan waktu layanan pelanggan ini ke loket yang terpilih
        waktuLoket[loketMin] += p.waktuLayanan;

        // Increment jumlah pelanggan terlayani
        totalPelanggan++;

        cout << "Pelanggan " << p.nomorAntrian << " dilayani di loket " << (loketMin + 1)
             << " dengan waktu tunggu " << waktuTunggu << " menit." << endl;
    }

    // Hitung rata-rata waktu tunggu
    float rataWaktuTunggu = (totalPelanggan > 0) ? static_cast<float>(totalWaktuTunggu) / totalPelanggan : 0;

    // Menampilkan statistik
    cout << "\nStatistik Layanan:" << endl;
    cout << "Rata-rata waktu tunggu: " << rataWaktuTunggu << " menit" << endl;
    cout << "Jumlah pelanggan terlayani: " << totalPelanggan << endl;
    cout << "Sisa antrian: " << antrian.size() << endl;
}

int main() {
    Queue antrian;
    
    // Contoh data pelanggan
    antrian.enqueue({1, 5});
    antrian.enqueue({2, 3});
    antrian.enqueue({3, 4});
    antrian.enqueue({4, 2});
    antrian.enqueue({5, 6});

    // Simulasi layanan bank dengan 3 loket
    simulasiLayanan(antrian, 3);

    return 0;
}
