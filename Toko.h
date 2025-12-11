#ifndef TOKO_H
#define TOKO_H


#include "Barang.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


const int Max = 1000;
const string NAMA_FILE = "barang.txt";

class Toko {
    private:
        Barang daftarBarang[Max];
        int jumlahBarang;

        int cariIndexBarang(int id) const {
            for (int i = 0; i < jumlahBarang; ++i) {
                if (daftarBarang[i].getId() == id) {
                    return i;
                }
            }
            return -1;
        }

    public:
        Toko() : jumlahBarang(0) { muatData(); }
        ~Toko() { simpanData(); }

        void muatData() {
            ifstream file(NAMA_FILE);
            if (!file.is_open()) {
                cout << "Gagal membuka file data. Memulai dengan data kosong." << endl;
                return;
            }jumlahBarang = 0;
            Barang b;
            while (file >> b && jumlahBarang < Max) {
            daftarBarang[jumlahBarang] = b;
            jumlahBarang++;
            }
            file.close();
        }
        
        void simpanData() {
            ofstream file(NAMA_FILE);
            if (!file.is_open()) {
                cout << "Gagal membuka file untuk menyimoan data." << endl;
                return;
            }
            for (int i = 0; i < jumlahBarang; ++i) {
                file << daftarBarang[i];
            }
            file.close();
        }

        void tampilkanBarang() {
            cout << "=== Daftar Barang ===" << endl;
            if (jumlahBarang == 0) {
                cout << "Belum ada data barang." << endl;
                return;
            }
            for (int i = 0; i < jumlahBarang; ++i) {
                daftarBarang[i].tampilkan();
            }
        }

        void editBarang() {
            tampilkanBarang();
            cout << "\n=== EDIT BARANG ===" << endl;
            int id;
            cout << "Masukkan ID Barang yang akan diedit: ";
            cin >> id;
            int index = cariIndexBarang(id);
            if (index == -1) {
                cout << "Barang dengan ID tersebut tidak ditemukan." << endl;
                return;
            }
        
            cout << "Edit Harga (h) atau Stok (s)? ";
            char pilihan;
            cin >> pilihan;
            if (pilihan == 'h' || pilihan == 'H') {
                long long hargaBaru;
                cout << "Masukkan Harga Baru: ";
                cin >> hargaBaru;
                daftarBarang[index].setHarga(hargaBaru);
                cout << "Harga berhasil diupdate." << endl;
            } else if (pilihan == 's' || pilihan == 'S') {
                int stokBaru;
                cout << "Masukkan Stok Baru: ";
                cin >> stokBaru;
                daftarBarang[index].setStok(stokBaru);
                cout << "Stok berhasil diupdate." << endl;
            } else {
                cout << "Pilihan tidak valid." << endl;
            }
        }

        void tambahBarang() {
            cout << "\n=== TAMBAH BARANG BARU ===" << endl;
            if (jumlahBarang >= Max) {
                cout << "Kapasitas maksimum barang tercapai." << endl;
                return;
            }
            int id;
            string nama;
            long long harga;
            int stok;
            cout << "Masukkan ID Barang (Angka Unik): ";
            cin >> id;
            if (cariIndexBarang(id) != -1) {
                cout << "ID Barang sudah digunakan." << endl;
                return;
            }
            cout << "Masukkan Nama Barang: ";
            cin >> nama;
            cout << "Masukkan Harga Barang: ";
            cin >> harga;
            cout << "Masukkan Stok Barang: ";
            cin >> stok;
            daftarBarang[jumlahBarang] = Barang(id, nama, harga, stok);
            jumlahBarang++;
            cout << "Barang berhasil ditambahkan." << endl;
        }

        void hapusBarang() {
            tampilkanBarang();
            cout << "\n=== HAPUS BARANG ===" << endl;
            int id;
            cout << "Masukkan ID Barang yang akan dihapus: ";
            cin >> id;
            int index = cariIndexBarang(id);
            if (index == -1) {
                cout << "Barang dengan ID tersebut tidak ditemukan." << endl;
                return;
            }
            for (int i = index; i < jumlahBarang - 1; ++i) {
                daftarBarang[i] = daftarBarang[i + 1];
            }
            jumlahBarang--;
            cout << "Barang berhasil dihapus." << endl;
        }

        void transaksiKasir() {
            cout << "\n=== TRANSAKSI KASIR ===" << endl;
            if (jumlahBarang == 0) {
                cout << "Belum ada data barang." << endl;
                return;
            }
            int id, qty;
            cout << "Masukkan ID Barang yang dibeli: ";
            cin >> id;
            int index = cariIndexBarang(id);
            if (index == -1) {
                cout << "Barang dengan ID tersebut tidak ditemukan." << endl;
                return;
            }
            cout << "Masukkan Jumlah yang dibeli: ";
            cin >> qty;
            if (!daftarBarang[index].kurangiStok(qty)) {
                cout << "Stok tidak mencukupi." << endl;
                return;
            }
            long long totalHarga = qty * daftarBarang[index].getHarga();
            cout << "Total Harga: " << totalHarga << endl;
            cout << "Lanjutkan ke pembayaran? (y/n): ";
            char konfirmasi;
            cin >> konfirmasi;
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                cout << "Masukkan nominal pembayaran: ";
                long long pembayaran;
                cin >> pembayaran;
                if (pembayaran < totalHarga) {
                    cout << "Pembayaran tidak mencukupi. Transaksi dibatalkan." << endl;
                    daftarBarang[index].setStok(daftarBarang[index].getStok() + qty);
                    return;
                }
                long long kembalian = pembayaran - totalHarga;
                cout << "Kembalian: " << kembalian << endl;
                cout << "Pembayaran berhasil." << endl;
                simpanData();
            } else {
                cout << "Transaksi dibatalkan." << endl;
                daftarBarang[index].setStok(daftarBarang[index].getStok() + qty);
            }
        }
    
};
#endif // TOKO_H
