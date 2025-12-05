#include <iostream>
#include <string>
#include <fstream>


using namespace std;

struct Barang {
    int id;
    string nama;
    long long harga;
    int stok;
};

const int Max = 1000;
Barang daftarBarang[Max];
int jumlahBarang = 0;
const string NAMA_FILE = "barang.txt";

void muatData();
void simpanData();
void tampilkanBarang();
void tambahBarang();
void editBarang();
void hapusBarang();
void transaksiKasir();
void clearScreen();
void pauseScreen();
int cariIndexBarang(int id);

int main() {
    muatData();

    int pilihan;
    do {
        clearScreen();
        cout << "=== SISTEM MANAJEMEN TOKO KELONTONG ===" << endl;
        cout << "1. Tampilkan Data Barang" << endl;
        cout << "2. Tambah Barang Baru" << endl;
        cout << "3. Edit Barang (Harga/Stok)" << endl;  
        cout << "4. Hapus Barang" << endl;
        cout << "5. Transaksi Kasir" << endl;
        cout << "6. Simpan & Keluar" << endl;
        cout << "==========================================" << endl;
        cout << "Pilih yang mana (1-6): ";
        cin >> pilihan;
    

        while (pilihan < 1 || pilihan >6) {
            cout << "Input tidak valid! Masukkan angka." << endl;
            cin.ignore();
            cin.clear();
            pauseScreen();
            continue;

        }

        switch (pilihan)
        {
        case 1:
            tampilkanBarang();
            pauseScreen();
            break;
        
        case 2:
            tambahBarang();
            pauseScreen();
            break;
        
        case 3:
            editBarang();
            pauseScreen();
            break;
        
        case 4:
            hapusBarang();
            pauseScreen();
            break;

        case 5:
            transaksiKasir();
            pauseScreen();
            break;

        case 6:
            simpanData();
            break;
        }
    }
    while (pilihan != 6);
    
    return 0;
    
}

void clearScreen() {
   system("cls");
}
void pauseScreen() {
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

int cariIndexBarang(int id) {
    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].id == id) {
            return i;
        }
    }
    return -1; // Tidak ditemukan
}

void muatData() {
    ifstream file(NAMA_FILE);
    if (!file.is_open()) {
        cout << "Gagal membuka file data. Memulai dengan data kosong." << endl;
        return;
    }

    jumlahBarang = 0;
    while (file >> daftarBarang[jumlahBarang].id 
                >> daftarBarang[jumlahBarang].nama 
                >> daftarBarang[jumlahBarang].harga 
                >> daftarBarang[jumlahBarang].stok) {
        jumlahBarang++;
    }
    file.close();
}

void simpanData() {
    ofstream file(NAMA_FILE);
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan data!" << endl;
        return;
    }

    for (int i = 0; i < jumlahBarang; i++) {
        file << daftarBarang[i].id << " "
             << daftarBarang[i].nama << " "
             << daftarBarang[i].harga << " "
             << daftarBarang[i].stok << endl;
    }
    file.close();
}

void tampilkanBarang() {
    clearScreen();
    cout << "=== DAFTAR BARANG ===" << endl;
    if (jumlahBarang == 0) {
        cout << "Belum ada data barang." << endl;
        return;
    }
    for (int i = 0; i < jumlahBarang; i++) {
        cout << "ID: " << daftarBarang[i].id << ", "
             << "Nama: " << daftarBarang[i].nama << ", "
             << "Harga: " << daftarBarang[i].harga << ", "
             << "Stok: " << daftarBarang[i].stok << endl;
    }
}

void tambahBarang() {
    clearScreen();
    cout << "=== TAMBAH BARANG BARU ===" << endl;
    if (jumlahBarang >= Max) {
        cout << "Kapasitas maksimum barang tercapai!" << endl;
        return;
    }
    Barang b;
    cout << "Masukkan ID Barang (Angka Unik): ";
    cin >> b.id;
    if (cariIndexBarang(b.id) != -1) {
        cout << "ID Barang sudah digunakan!" << endl;
        return;
    }
    cout << "Masukkan Nama Barang: ";
    cin >> b.nama;
    cout << "Masukkan Harga Barang: ";
    cin >> b.harga;
    cout << "Masukkan Stok Barang: ";
    cin >> b.stok;

    daftarBarang[jumlahBarang] = b;
    jumlahBarang++;
}

void editBarang() {
    clearScreen();
    tampilkanBarang();
    cout << "\n=== EDIT BARANG ===" << endl;
    int id;
    cout << "Masukkan ID Barang yang akan diedit: ";
    cin >> id;
    int index = cariIndexBarang(id);
    if (index == -1) {
        cout << "Barang dengan ID tersebut tidak ditemukan!" << endl;
        return;
    }
    cout << "Edit Harga (h) atau Stok (s)? ";
    char pilihan;
    cin >> pilihan;
    if (pilihan == 'h' || pilihan == 'H') {
        cout << "Masukkan Harga Baru: ";
        cin >> daftarBarang[index].harga;
    } else if (pilihan == 's' || pilihan == 'S') {
        cout << "Masukkan Stok Baru: ";
        cin >> daftarBarang[index].stok;
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }
}

void hapusBarang() {
    clearScreen();
    tampilkanBarang();
    cout << "\n=== HAPUS BARANG ===" << endl;
    int id;
    cout << "Masukkan ID Barang yang akan dihapus: ";
    cin >> id;
    int index = cariIndexBarang(id);
    if (index == -1) {
        cout << "Barang dengan ID tersebut tidak ditemukan!" << endl;
        return;
    }
    for (int i = index; i < jumlahBarang - 1; i++) {
        daftarBarang[i] = daftarBarang[i + 1];
    }
    jumlahBarang--;
}

void transaksiKasir() {
    clearScreen();
    cout << "=== TRANSAKSI KASIR ===" << endl;
    if (jumlahBarang == 0) {
        cout << "Tidak ada barang tersedia untuk transaksi." << endl;
        return;
    }
    int id, qty;
    cout << "Masukkan ID Barang yang dibeli: ";
    cin >> id;
    int index = cariIndexBarang(id);
    if (index == -1) {
        cout << "Barang dengan ID tersebut tidak ditemukan!" << endl;
        return;
    }
    cout << "Masukkan Jumlah yang dibeli: ";
    cin >> qty;
    if (qty > daftarBarang[index].stok) {
        cout << "Stok tidak mencukupi!" << endl;
        return;
    }
    long long totalHarga = qty * daftarBarang[index].harga;
    cout << "Total Harga: " << totalHarga << endl;

    cout << "Lanjutkan transaksi (y/n)? ";
    char konfirmasi;
    cin >> konfirmasi;
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        cout << "Masukkan nominal pembayaran: ";
        long long pembayaran;
        cin >> pembayaran;
        if (pembayaran < totalHarga) {
            cout << "Uang yang diberikan tidak mencukupi!" << endl;
            return;
        }
        long long kembalian = pembayaran - totalHarga;
        cout << "Kembalian: " << kembalian << endl;
        daftarBarang[index].stok -= qty;
        cout << "Transaksi berhasil! Stok barang telah diperbarui." << endl;
    } else {
        cout << "Transaksi dibatalkan." << endl;
    }
    simpanData();
}
