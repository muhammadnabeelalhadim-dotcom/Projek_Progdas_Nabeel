#ifndef BARANG_H
#define BARANG_H


#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Barang {
private:
    int id;
    string nama;
    long long harga;
    int stok;
public:
        Barang(int id = 0, string nama = "", long long harga = 0, int stok = 0)
            : id(id), nama(nama), harga(harga), stok(stok) {}

        int getId() const {
            return id;
        }
        string getNama() const {
            return nama;
        }  
        long long getHarga() const {
            return harga;
        }
        int getStok() const {
            return stok;
        }

        void setHarga(long long harga) { this->harga = harga;}
        void setStok(int stok) { this->stok = stok; }

        bool kurangiStok(int qty) {
            if (qty > stok)
                return false;
            stok -= qty;
            return true;

        }

        void tampilkan() const {
            cout << "ID: " << id << ", Nama: " << nama << ", Harga: " << harga << ", Stok: " << stok << endl;
        }

        friend ofstream& operator<<(ofstream &out, const Barang& b) {
            out << b.id << ' ' << b.nama << ' ' << b.harga << ' ' << b.stok << endl;
            return out;
        }

        friend ifstream& operator>>(ifstream& in, Barang& b) {
            in >> b.id >> b.nama >> b.harga  >> b.stok; 
            return in;
        }

}; 
#endif // BARANG_H
