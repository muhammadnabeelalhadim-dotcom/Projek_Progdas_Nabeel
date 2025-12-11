/** Ini adalah sebuah program Kasir yang bisa berfungsi untuk melakukan transaksi, 
    menambahkan barang dan juga bisa untuk menghapus dan mengedit barang. Barang
    yang di tambahkan akan disimpan kedalam suatu file yang kami namakan barang.txt
    yang akan dibuat ketika program ini dijalankan pertama kali.
**/

#include <iostream>
#include <string>
#include <limits>
#include "Toko.h"


using namespace std;

void clearScreen() {
    system("cls");
}
void pauseScreen() {
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore();
    cin.get();
};

bool loginAdmin() {
    const string USERNAME = "admin";
    const string PASSWORD = "password123";
    const int MAX_ATTEMPTS = 3;
    
    int attempts = 0;
    
    while (attempts < MAX_ATTEMPTS) {
        clearScreen();
        cout << "=== SISTEM LOGIN ADMIN ===" << endl;
        cout << "Percobaan ke-" << (attempts + 1) << " dari " << MAX_ATTEMPTS << endl;
        cout << "===========================" << endl;
        
        string username, password;
        
        cout << "Username: ";
        getline(cin, username);
        
        cout << "Password: ";
        getline(cin, password);
        
        if (username == USERNAME && password == PASSWORD) {
            clearScreen();
            cout << "\n=== LOGIN BERHASIL ===" << endl;
            cout << "Selamat datang, Admin!" << endl;
            cout << "======================" << endl << endl;
            return true;
        } else {
            attempts++;
            if (attempts < MAX_ATTEMPTS) {
                cout << "\nUsername atau password salah!" << endl;
                cout << "Silakan coba lagi." << endl << endl;
            }
        }
    }
    
    clearScreen();
    cout << "\n=== LOGIN GAGAL ===" << endl;
    cout << "Anda telah mencapai batas maksimal percobaan login." << endl;
    cout << "Program akan keluar." << endl;
    cout << "====================" << endl;
    
    return false;
}

int main() {
    // Login admin sebelum akses ke menu
    if (!loginAdmin()) {
        return 1; // Keluar jika login gagal
    }
    
    Toko toko;

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

        if (cin.fail()) {
            cin.clear();
            cout << "Input tidak valid! Masukkan angka." << endl;
            pauseScreen();
            continue;
        }
    

        if (pilihan < 1 || pilihan >6) {
            cout << "Input tidak valid! Masukkan angka." << endl;
            pauseScreen();
            continue;

        }

        switch (pilihan)
        {
        case 1:
            clearScreen();
            toko.tampilkanBarang();
            pauseScreen();
            break;
        
        case 2:
            clearScreen();
            toko.tambahBarang();
            pauseScreen();
            break;
        
        case 3:
            clearScreen();
            toko.editBarang();
            pauseScreen();
            break;
        
        case 4:
            clearScreen();
            toko.hapusBarang();
            pauseScreen();
            break;

        case 5:
            clearScreen();
            toko.transaksiKasir();
            pauseScreen();
            break;

        case 6:
            toko.simpanData();
            break;
        }
    }
    while (pilihan != 6);
    
    return 0;
    
}

