#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// Fungsi untuk mendapatkan waktu lokal dalam format "DD-MM-YYYY HH:MM"
string getLocalTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", ltm);
    
    return string(buffer);
}

// Kelas Akun (Informasi pengguna)
class Akun {
protected:
    string nama;
public:
    Akun(string n) : nama(n) {}

    void tampilkanInfo() {
        cout << "\n====================================\n";
        cout << "Pengguna: " << nama << endl;
        cout << "====================================\n";
    }
};

// Kelas Catatan (Mengelola catatan seperti Google Keep)
class Catatan {
protected:
    struct Note {
        string judul;
        string isi;
        string label;
        string waktuBuat;
        string waktuEdit;
    };
    vector<Note> daftarCatatan;
public:
    void tambahCatatan() {
        Note note;
        cin.ignore();
        cout << "\n====================================\n";
        cout << "\033[38;5;218mTambah Catatan Baru\033[0m\n";
        cout << "====================================\n";
        cout << "Masukkan judul catatan: ";
        getline(cin, note.judul);
        cout << "Masukkan isi catatan: ";
        getline(cin, note.isi);
        cout << "Tambahkan label (opsional): ";
        getline(cin, note.label);
        note.waktuBuat = getLocalTime();
        note.waktuEdit = note.waktuBuat;  // Saat awal, waktu buat & edit sama
        daftarCatatan.push_back(note);
        cout << "Catatan \"" << note.judul << "\" ditambahkan!\n";
    }

    void lihatCatatan() {
        cout << "\n====================================\n";
        cout << "\033[38;5;218mDaftar Catatan\033[0m\n";
        cout << "====================================\n";
        if (daftarCatatan.empty()) {
            cout << "Belum ada catatan.\n";
        } else {
            for (size_t i = 0; i < daftarCatatan.size(); i++) {
                cout << i + 1 << ". [" << daftarCatatan[i].label << "] " << daftarCatatan[i].judul 
                     << " - " << daftarCatatan[i].isi << endl;
                cout << "   Dibuat: " << daftarCatatan[i].waktuBuat 
                     << " | Terakhir diedit: " << daftarCatatan[i].waktuEdit << endl;
            }
        }
    }

    void hapusCatatan() {
        lihatCatatan();
        if (daftarCatatan.empty()) return;

        int indeks;
        cout << "\n====================================\n";
        cout << "\033[38;5;218mHapus Catatan\033[0m\n";
        cout << "====================================\n";
        cout << "Masukkan nomor catatan yang ingin dihapus: ";
        cin >> indeks;
        cin.ignore();

        if (indeks < 1 || indeks > daftarCatatan.size()) {
            cout << "Nomor tidak valid!\n";
            return;
        }

        daftarCatatan.erase(daftarCatatan.begin() + (indeks - 1));
        cout << "Catatan berhasil dihapus!\n";
    }

    void editCatatan() {
        lihatCatatan();
        if (daftarCatatan.empty()) return;

        int indeks;
        cout << "\n====================================\n";
        cout << "\033[38;5;218mEdit Catatan\033[0m\n";
        cout << "====================================\n";
        cout << "Masukkan nomor catatan yang ingin diedit: ";
        cin >> indeks;
        cin.ignore();

        if (indeks < 1 || indeks > daftarCatatan.size()) {
            cout << "Nomor tidak valid!\n";
            return;
        }

        int opsi;
        cout << "\n\033[38;5;218mPilih bagian yang ingin diedit:\033[0m\n";
        cout << "1. Judul\n";
        cout << "2. Label\n";
        cout << "3. Isi\n";
        cout << "Pilihan: ";
        cin >> opsi;
        cin.ignore();

        if (opsi == 1) {
            cout << "Masukkan judul baru: ";
            getline(cin, daftarCatatan[indeks - 1].judul);
        } 
        else if (opsi == 2) {
            cout << "Masukkan label baru: ";
            getline(cin, daftarCatatan[indeks - 1].label);
        } 
        else if (opsi == 3) {
            cout << "Masukkan isi baru: ";
            getline(cin, daftarCatatan[indeks - 1].isi);
        } 
        else {
            cout << "Pilihan tidak valid!\n";
            return;
        }

        daftarCatatan[indeks - 1].waktuEdit = getLocalTime();  // Perbarui waktu edit
        cout << "Catatan berhasil diperbarui!\n";
    }
};

// Kelas CatatanApp yang mewarisi Akun dan Catatan
class CatatanApp : public Akun, public Catatan {
public:
    CatatanApp(string n) : Akun(n) {}

    void interaksi() {
        int pilihan;
        do {
            cout << "\n====================================\n";
            cout << "\033[38;5;218mAplikasi Catatan\033[0m\n";
            cout << "====================================\n";
            cout << "1. Lihat Info Pengguna\n";
            cout << "2. Tambah Catatan\n";
            cout << "3. Lihat Daftar Catatan\n";
            cout << "4. Edit Catatan\n";
            cout << "5. Hapus Catatan\n";
            cout << "6. Keluar\n";
            cout << "Pilihan: ";
            cin >> pilihan;
            cin.ignore();

            if (pilihan == 1) {
                tampilkanInfo();
            }
            else if (pilihan == 2) {
                tambahCatatan();
            }
            else if (pilihan == 3) {
                lihatCatatan();
            }
            else if (pilihan == 4) {
                editCatatan();
            }
            else if (pilihan == 5) {
                hapusCatatan();
            }
            else if (pilihan == 6) {
                cout << "\n====================================\n";
                cout << "Keluar dari aplikasi catatan.\n";
                cout << "====================================\n";
            }
            else {
                cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 6);
    }
};

// Main Program
int main() {
    system("cls");
    string nama;
    cout << "Masukkan nama pengguna: ";
    getline(cin, nama);

    CatatanApp aplikasi(nama);
    aplikasi.interaksi();

    return 0;
}
