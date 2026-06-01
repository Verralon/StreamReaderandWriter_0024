#include <iostream>
#include <fstream>
#include <string>
#include <array>        // Dipakai khusus untuk fitur .at() sesuai ketentuan soal
#include <stdexcept>

using namespace std;

// ==========================================
// 1. STRUKTUR KELAS TOKO ELEKTRONIK (OOP)
// ==========================================
class TokoElektronik {
private:
    array<string, 3> etalase; // Enkapsulasi: Array etasale kapasitas 3

public:
    // Constructor: Mengisi data awal secara otomatis
    TokoElektronik() {
        etalase[0] = "Televisi LED 32 Inch";
        etalase[1] = "Kulkas 2 Pintu";
        etalase[2] = "Mesin Cuci Otomatis";
    }

    // Method untuk mengambil produk
    string ambilProduk(size_t nomorRak) {
        try {
            // Wajib menggunakan .at() untuk memicu out_of_range jika indeks kelewatan
            return etalase.at(nomorRak);
        }
        catch (const out_of_range& e) {
            // Lemparkan kembali (throw) pesan error kustom sesuai perintah soal
            throw runtime_error("Gagal Mengambil Barang : Rak nomor [" + to_string(nomorRak) + "] kosong atau tidak tersedia!");
        }
    }
};

// ==========================================
// 2. FUNGSI UTAMA (MAIN) & MENU CRUD
// ==========================================
int main() {
    TokoElektronik toko;
    int pilihanMenu;

    do {
        // --------------------------------------------------
        // READ OLEH SISTEM: Otomatis membaca & menampilkan isi file
        // --------------------------------------------------
        string gudang[100];
        int jumlahBarang = 0;

        ifstream fileIn("gudang.txt");
        if (fileIn.is_open()) {
            while (jumlahBarang < 100 && getline(fileIn, gudang[jumlahBarang])) {
                if (!gudang[jumlahBarang].empty()) {
                    jumlahBarang++;
                }
            }
            fileIn.close();
        }

        // Cetak daftar barang ke layar otomatis saat menu terbuka
        cout << "\n==================================================" << endl;
        cout << "   DAFTAR BARANG DI GUDANG (gudang.txt)           " << endl;
        cout << "==================================================" << endl;
        if (jumlahBarang == 0) {
            cout << " [Gudang Kosong / Belum Ada Data Barang] " << endl;
        } else {
            for (int i = 0; i < jumlahBarang; i++) {
                cout << " " << i + 1 << ". " << gudang[i] << endl;
            }
        }
        cout << "==================================================" << endl;

        // Tampilan pilihan menu interaktif
        cout << "\n--- MENU UTAMA TOKO ELEKTRONIK GIBRAN JAYA ---" << endl;
        cout << "1. Create (Tambah Barang Gudang)" << endl;
        cout << "2. Update (Ubah Barang Gudang)" << endl;
        cout << "3. Delete (Hapus Barang Gudang)" << endl;
        cout << "4. Jalankan Simulasi Etalase (Exception Handling)" << endl;
        cout << "5. Keluar Sistem" << endl;
        cout << "Pilih menu (1-5): ";
        cin >> pilihanMenu;

        // Antisipasi jika user salah input huruf (biar tidak loop terus-menerus)
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[Error] Input salah! Harus berupa angka." << endl;
            continue;
        }

        switch (pilihanMenu) {
            case 1: {
                // CREATE: Menambahkan data langsung ke akhir file teks
                string barangBaru;
                cout << "Masukkan nama barang baru: ";
                cin.ignore();
                getline(cin, barangBaru);

                ofstream fileOut("gudang.txt", ios::app); // ios::app untuk menambah di baris baru
                if (fileOut.is_open()) {
                    fileOut << barangBaru << endl;
                    fileOut.close();
                    cout << "-> Sukses: Barang berhasil ditambahkan!" << endl;
                }
                break;
            }
            case 2: {
                // UPDATE: Mengubah nama barang berdasarkan nomor urut
                if (jumlahBarang == 0) {
                    cout << "-> Gagal: Gudang masih kosong!" << endl;
                } else {
                    int nomorUbah;
                    cout << "Masukkan nomor urut barang yang ingin diubah: ";
                    cin >> nomorUbah;

                    if (nomorUbah > 0 && nomorUbah <= jumlahBarang) {
                        string namaBaru;
                        cout << "Masukkan nama baru: ";
                        cin.ignore();
                        getline(cin, namaBaru);

                        gudang[nomorUbah - 1] = namaBaru; // Ubah data di array lokal

                        // Tulis ulang seluruh isi file dengan data yang sudah diubah
                        ofstream fileOut("gudang.txt");
                        for (int i = 0; i < jumlahBarang; i++) {
                            fileOut << gudang[i] << endl;
                        }
                        fileOut.close();
                        cout << "-> Sukses: Data barang berhasil diperbarui!" << endl;
                    } else {
                        cout << "-> Gagal: Nomor urut tidak ditemukan!" << endl;
                    }
                }
                break;
            }
            case 3: {
                // DELETE: Menghapus data barang
                if (jumlahBarang == 0) {
                    cout << "-> Gagal: Gudang masih kosong!" << endl;
                } else {
                    int nomorHapus;
                    cout << "Masukkan nomor urut barang yang ingin dihapus: ";
                    cin >> nomorHapus;

                    if (nomorHapus > 0 && nomorHapus <= jumlahBarang) {
                        // Tulis ulang file, tapi LEWATKAN (skip) barang yang mau dihapus
                        ofstream fileOut("gudang.txt");
                        for (int i = 0; i < jumlahBarang; i++) {
                            if (i != (nomorHapus - 1)) { 
                                fileOut << gudang[i] << endl;
                            }
                        }
                        fileOut.close();
                        cout << "-> Sukses: Barang berhasil dihapus!" << endl;
                    } else {
                        cout << "-> Gagal: Nomor urut tidak ditemukan!" << endl;
                    }
                }
                break;
            }
            case 4: {
                // SIMULASI EXCEPTION HANDLING (Skenario 1 & Skenario 2)
                cout << "\n==================================================" << endl;
                cout << "          SIMULASI PENANGKAPAN ERROR ETALASE      " << endl;
                cout << "==================================================" << endl;

                // Skenario 1: Rak indeks ke-1 (Harus Sukses)
                cout << "[Skenario 1] Mengambil produk pada etalase rak indeks ke-1..." << endl;
                try {
                    string produk = toko.ambilProduk(1);
                    cout << "Hasil Skenario 1 -> Berhasil! Barang ditemukan: " << produk << endl;
                }
                catch (const runtime_error& e) {
                    cout << "Hasil Skenario 1 -> " << e.what() << endl;
                }

                cout << "--------------------------------------------------" << endl;

                // Skenario 2: Rak indeks ke-5 (Harus Gagal & keluar pesan kustom)
                cout << "[Skenario 2] Mengambil produk pada etalase rak indeks ke-5..." << endl;
                try {
                    string produk = toko.ambilProduk(5);
                    cout << "Hasil Skenario 2 -> Berhasil! Barang ditemukan: " << produk << endl;
                }
                catch (const runtime_error& e) {
                    cout << "Hasil Skenario 2 -> Terjadi Exception!" << endl;
                    cout << "Pesan Error Kustom: " << e.what() << endl;
                }
                cout << "==================================================" << endl;
                break;
            }
            case 5:
                cout << "\nKeluar dari sistem Gibran Jaya. Terima kasih!" << endl;
                break;
            default:
                cout << "\nPilihan menu salah! Gunakan angka 1-5." << endl;
                break;
        }

    } while (pilihanMenu != 5);

    return 0;
}