#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_USERS 10 
#define MAX_STR_LEN 50
#define MAX_KATA 100

struct Dokter {
    char nama[MAX_STR_LEN];
    int tarif;
};

struct Kata {
    char kata[MAX_STR_LEN];
    char definisi[255];
};

static char usernames[MAX_USERS][MAX_STR_LEN];
static char passwords[MAX_USERS][MAX_STR_LEN];
static int jumlahUserTerdaftar = 0;

struct Dokter daftarDokter[] = {
    {"Dr. Budi", 150000},
    {"Dr. Ani", 175000},
    {"Dr. Citra", 200000}
};
const int jumlahDokter = 3;

struct Kata kamus[MAX_KATA];
int jumlahKata = 0;

void cetak_progress_bar(int progres, int total);
void inisialisasiDataAwal();
void clearScreen();
void pressEnterToContinue();

int fungsiRegistrasi();
int fungsiLogin();
void menuLoginRegister();

int getValidInt(const char* prompt);

void menuUtama();
void fiturKlinik();
void fiturPolaRumah();
void fiturBatuGuntingKertas();
void subMenuKamus();
void tambahKata();
void cariKata();

void cetak_progress_bar(int progres, int total){
    int bar = 25;
    int jumlah = (progres * bar) / total;
    int persentase = (progres * 100) / total;

    printf("\r[");
    for (int i = 0; i < jumlah; i++){
        printf("=");}
    for (int i = jumlah; i < bar; i++){
        printf(" ");}
    printf("] %d%%", persentase);
    fflush(stdout);
}

void inisialisasiDataAwal() {
    strcpy(usernames[0], "kheef");
    strcpy(passwords[0], "123");
    
    strcpy(usernames[1], "reza");
    strcpy(passwords[1], "456");
    
    strcpy(usernames[2], "wibi");
    strcpy(passwords[2], "111");
    jumlahUserTerdaftar = 3;
}

void pressEnterToContinue() {
    printf("\nTekan Enter untuk melanjutkan...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    getchar();
}

int getValidInt(const char* prompt) {
    int nilai;
    char buffer[256];
    char sisa;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d%c", &nilai, &sisa) == 2 && sisa == '\n') {
                return nilai;
            } else if (sscanf(buffer, "%d", &nilai) == 1 && buffer[strlen(buffer)-1] == '\n') {
                return nilai;
            }
        }
        printf("Input tidak valid. Harap masukkan angka saja.\n");
        if (feof(stdin)) {
            exit(0); 
        }
    }
}

int fungsiRegistrasi() {
    if (jumlahUserTerdaftar >= MAX_USERS) {
        printf("\nMaaf, kuota pendaftaran (%d user) sudah penuh!\n", MAX_USERS);
        return 0;
    }

    char inputUser[MAX_STR_LEN];
    char inputPass[MAX_STR_LEN];
    int userDuplikat = 0;

    clearScreen();
    printf("=====================================\n");
    printf("|           REGISTRASI AKUN         |\n");
    printf("=====================================\n");
    
    while(getchar() != '\n'); 

    printf("Masukkan Username Baru (Maks. %d karakter): ", MAX_STR_LEN - 1);
    scanf("%s", inputUser);

    for (int i = 0; i < jumlahUserTerdaftar; i++) {
        if (strcmp(inputUser, usernames[i]) == 0) {
            userDuplikat = 1;
            break;
        }
    }

    if (userDuplikat) {
        printf("\nERROR: Username '%s' sudah terdaftar. Pendaftaran gagal.\n", inputUser);
        return 0;
    }

    printf("Masukkan Password Baru (Maks. %d karakter): ", MAX_STR_LEN - 1);
    scanf("%s", inputPass);

    strcpy(usernames[jumlahUserTerdaftar], inputUser);
    strcpy(passwords[jumlahUserTerdaftar], inputPass);
    
    jumlahUserTerdaftar++;

    printf("\nREGISTRASI BERHASIL!\n");
    printf("Username '%s' telah ditambahkan. Silakan Login.\n", inputUser);
    
    return 1;
}

int fungsiLogin() {
    char inputUser[MAX_STR_LEN];
    char inputPass[MAX_STR_LEN];
    int percobaan = 0;
    int maksPercobaan = 3;
    int userDitemukan = 0;
    
    while(getchar() != '\n');

    do {
        clearScreen();
        printf("=====================================\n");
        printf("|            LOGIN AKUN             |\n");
        printf("=====================================\n");
        printf("Percobaan ( %d / %d ) | Total User Terdaftar: %d\n\n", 
               percobaan + 1, maksPercobaan, jumlahUserTerdaftar);
        
        printf("Masukkan Username: ");
        scanf("%s", inputUser);

        printf("Masukkan Password: ");
        scanf("%s", inputPass);

        userDitemukan = 0;

        for (int i = 0; i < jumlahUserTerdaftar; i++) {
            if (strcmp(inputUser, usernames[i]) == 0 && strcmp(inputPass, passwords[i]) == 0) {
                userDitemukan = 1; 
                break;
            }
        }

        if (userDitemukan) {
            printf("\nLogin berhasil! Selamat datang, %s.\n", inputUser);
            pressEnterToContinue();
            return 1;
        } else {
            printf("\nERROR: Username atau password salah!\n");
            percobaan++;
        }
        
    } while (percobaan < maksPercobaan);

    printf("\nAnda gagal login %d kali. Program berhenti.\n", maksPercobaan);
    pressEnterToContinue();
    return 0;
}

void menuLoginRegister() {
    int pilihan;
    int loggedIn = 0;

    do {
        clearScreen();
        printf("=====================================\n");
        printf("|   APLIKASI - LOGIN & REGISTRASI   |\n");
        printf("=====================================\n");
        printf("Total User Terdaftar: %d/%d\n", jumlahUserTerdaftar, MAX_USERS);
        printf("1. Login Akun\n");
        printf("2. Registrasi Akun Baru\n");
        printf("0. Keluar Aplikasi\n");
        printf("-------------------------------------\n");
        printf("Pilihan: ");
        
        while(getchar() != '\n');
        printf("Masukan Pilihan yang Dipilih: ");
        if (scanf("%d", &pilihan) != 1) {
            printf("\nInput tidak valid! Harap masukkan angka.\n");
            while(getchar() != '\n'); 
            pilihan = -1;
            pressEnterToContinue();
            continue;
        }

        switch (pilihan) {
            case 1:
                loggedIn = fungsiLogin();
                if (loggedIn) {
                    menuUtama();
                }
                break;
            case 2:
                fungsiRegistrasi();
                pressEnterToContinue();
                break;
            case 0:
                printf("\nprogram berakhir.\n");
                break;
            default:
                printf("\nmenu tidak valid\n");
                pressEnterToContinue();
                break;
        }
    } while (pilihan != 0);
}

void menuUtama() {
    int pilihan = 0;
    while (pilihan != 5) {
        clearScreen();
        printf("==============================================\n");
        printf("|         PROGRAM MENU UTAMA (KELOMPOK 4)    |\n");
        printf("==============================================\n");
        printf("1. Fitur Klinik (Biaya Konsultasi)\n");
        printf("2. Fitur Pola Grafis (Rumah)\n");
        printf("3. Fitur Game (Batu Gunting Kertas)\n");
        printf("4. Fitur Kamus Sederhana\n");
        printf("5. Logout & Kembali ke Menu Login\n");
        printf("----------------------------------------------\n");
        
        pilihan = getValidInt("Masukkan pilihan Anda (1-5): ");

        switch (pilihan) {
            case 1:
                fiturKlinik();
                break;
            case 2:
                fiturPolaRumah();
                break;
            case 3:
                fiturBatuGuntingKertas();
                break;
            case 4:
                subMenuKamus();
                break;
            case 5:
                printf("\nAnda telah logout. Kembali ke menu login/registrasi.\n");
                return;
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                pressEnterToContinue();
                break;
        }

        if (pilihan != 5) {
            pressEnterToContinue();
        }
    }
}

void fiturKlinik() {
    const int WAKTU_PER_PASIEN = 15;
    int pilihanDokter, jumlahPasien;
    long totalBiaya;
    int estimasiWaktu;

    clearScreen();
    printf("==============================================\n");
    printf("|       Fitur Klinik - Biaya Konsultasi      |\n");
    printf("==============================================\n");
    printf("Daftar Dokter (Nama & Tarif):\n");

    for (int i = 0; i < jumlahDokter; i++) {
        printf("%d. %s - Rp %d\n", i + 1, daftarDokter[i].nama, daftarDokter[i].tarif);
    }
    printf("----------------------------------------------\n");

    while (1) {
        pilihanDokter = getValidInt("Pilih dokter (1-3): ");
        if (pilihanDokter >= 1 && pilihanDokter <= jumlahDokter) {
            break;
        } else {
            printf("Pilihan tidak valid. Harap pilih antara 1 dan %d.\n", jumlahDokter);
        }
    }

    while (1) {
        jumlahPasien = getValidInt("Masukkan jumlah pasien sederhana: ");
        if (jumlahPasien > 0) {
            break;
        } else {
            printf("Jumlah pasien harus lebih dari 0.\n");
        }
    }

    totalBiaya = (long)daftarDokter[pilihanDokter - 1].tarif * jumlahPasien;
    estimasiWaktu = jumlahPasien * WAKTU_PER_PASIEN;

    printf("\n--- Hasil Perhitungan ---\n");
    printf("Dokter yang dipilih : %s\n", daftarDokter[pilihanDokter - 1].nama);
    printf("Jumlah pasien       : %d\n", jumlahPasien);
    printf("Total Biaya         : Rp %ld\n", totalBiaya);
    printf("Estimasi Waktu Tunggu: %d menit\n", estimasiWaktu);
}

void fiturPolaRumah() {
    int tinggi;
    char karakter;
    
    clearScreen();
    printf("==============================================\n");
    printf("|          Fitur Pola Grafis (Rumah)         |\n");
    printf("==============================================\n");

    while (1) {
        tinggi = getValidInt("Masukkan tinggi rumah (minimal 5): ");
        if (tinggi >= 5) {
            break;
        } else {
            printf("Tinggi minimal adalah 5 agar bentuknya proporsional.\n");
        }
    }

    printf("Masukkan karakter penyusun (misal:#,*,dll): ");
    while(getchar() != '\n');
    printf("masukan karakter yang dipilih: ");
    karakter = getchar();
    
    while(getchar() != '\n'); 
    
    printf("\n--- Pola Rumah ---\n");

    printf("\033[31m"); 
    for (int i = 0; i < tinggi; i++) {
        for (int j = 0; j < tinggi - i - 1; j++) {
            printf(" ");
        }
        for (int k = 0; k < 2 * i + 1; k++) {
            printf("%c", karakter);
        }
        printf("\n");
    }
    printf("\033[0m");

    printf("\033[33m");
    for (int i = 0; i < tinggi; i++) {
        printf(" ");
        for (int j = 0; j < (2 * tinggi - 3); j++) {
            if (i >= tinggi / 2 && 
                j > (2 * tinggi - 3) / 2 - (tinggi / 4) && 
                j < (2 * tinggi - 3) / 2 + (tinggi / 4) + 1) {
                printf("\033[34m%c\033[33m", karakter);
            } else {
                printf("%c", karakter);
            }
        }
        printf("\n");
    }
    printf("\033[0m");
}

void fiturBatuGuntingKertas() {
    int pilihanUser, pilihanKomp;
    char mainLagi;

    do {
        clearScreen();
        printf("==============================================\n");
        printf("|        Game Batu - Gunting - Kertas        |\n");
        printf("==============================================\n");
        printf("1. Batu\n");
        printf("2. Gunting\n");
        printf("3. Kertas\n");
        printf("----------------------------------------------\n");

        while (1) {
            pilihanUser = getValidInt("Masukkan pilihan Anda (1-3): ");
            if (pilihanUser >= 1 && pilihanUser <= 3) {
                break;
            } else {
                printf("Pilihan tidak valid. Harap pilih antara 1 dan 3.\n");
            }
        }

        pilihanKomp = (rand() % 3) + 1;

        const char* namaPilihan[] = {"", "Batu", "Gunting", "Kertas"};
        printf("\nAnda memilih    : %s\n", namaPilihan[pilihanUser]);
        printf("Komputer memilih: %s\n", namaPilihan[pilihanKomp]);

        if (pilihanUser == pilihanKomp) {
            printf("\n--- HASIL: SERI! ---\n");
        } else if ((pilihanUser == 1 && pilihanKomp == 2) ||
                   (pilihanUser == 2 && pilihanKomp == 3) ||
                   (pilihanUser == 3 && pilihanKomp == 1)) {
            printf("\n--- HASIL: Anda MENANG! ---\n");
        } else {
            printf("\n--- HASIL: Anda KALAH! ---\n");
        }

        printf("\nApakah Anda ingin bermain lagi? (y/n): ");
        while(getchar() != '\n');
        scanf(" %c", &mainLagi);
        while(getchar() != '\n');

    } while (mainLagi == 'y' || mainLagi == 'Y');
}

void subMenuKamus() {
    int pilihan = 0;
    while (pilihan != 3) {
        clearScreen();
        printf("==============================================\n");
        printf("|           Fitur Kamus Sederhana            |\n");
        printf("==============================================\n");
        printf("Jumlah Kata Terdaftar: %d/%d\n", jumlahKata, MAX_KATA);
        printf("1. Tambah Kata dan Definisi Baru\n");
        printf("2. Cari Kata\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("----------------------------------------------\n");
        
        pilihan = getValidInt("Masukkan pilihan Anda (1-3): ");

        switch (pilihan) {
            case 1:
                tambahKata();
                pressEnterToContinue();
                break;
            case 2:
                cariKata();
                pressEnterToContinue();
                break;
            case 3:
                break;
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                pressEnterToContinue();
                break;
        }
    }
}

void tambahKata() {
    clearScreen();
    printf("--- Tambah Kata Baru ---\n");

    if (jumlahKata >= MAX_KATA) {
        printf("Maaf, kamus sudah penuh.\n");
        return;
    }

    while(getchar() != '\n'); 

    printf("Masukkan kata baru: ");
    fgets(kamus[jumlahKata].kata, sizeof(kamus[jumlahKata].kata), stdin);
    kamus[jumlahKata].kata[strcspn(kamus[jumlahKata].kata, "\n")] = 0;

    printf("Masukkan definisi: ");
    fgets(kamus[jumlahKata].definisi, sizeof(kamus[jumlahKata].definisi), stdin);
    kamus[jumlahKata].definisi[strcspn(kamus[jumlahKata].definisi, "\n")] = 0;
    
    jumlahKata++;

    printf("\nKata '%s' berhasil ditambahkan ke kamus.\n", kamus[jumlahKata-1].kata);
}

void cariKata() {
    char kataCari[MAX_STR_LEN];
    int ditemukan = 0;

    clearScreen();
    printf("--- Cari Kata di Kamus ---\n");

    if (jumlahKata == 0) {
        printf("Kamus masih kosong. Silakan tambah kata terlebih dahulu.\n");
        return;
    }

    while(getchar() != '\n');

    printf("Masukkan kata yang ingin dicari: ");
    fgets(kataCari, sizeof(kataCari), stdin);
    kataCari[strcspn(kataCari, "\n")] = 0;

    printf("\n--- Hasil Pencarian ---\n");
    
    for (int i = 0; i < jumlahKata; i++) {
        if (strcmp(kamus[i].kata, kataCari) == 0) {
            printf("Kata     : %s\n", kamus[i].kata);
            printf("Definisi : %s\n", kamus[i].definisi);
            ditemukan = 1;
            break;
        }
    }

    if (!ditemukan) {
        printf("Kata '%s' tidak ditemukan dalam kamus.\n", kataCari);
    }
}

int main() {
    int total_langkah = 100;
    printf("Memuat Data...\n");
    for (int i = 0; i <= total_langkah; i++) {
        cetak_progress_bar(i, total_langkah);
        usleep(10000);
    }
    printf("\nSelesai Memuat!\n");
    pressEnterToContinue();
    
    inisialisasiDataAwal();
    srand(time(NULL));
    
    menuLoginRegister();

    return 0;
}