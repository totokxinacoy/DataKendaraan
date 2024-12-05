/* PROGRAM ArsipDataKendaraan */
/* Membuat Program mencetak pola segitiga berlian dengan jumlah baris yang sesuai inputan */

#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef struct {
    int id;
    char noplat[20];
    char jenis[20];
    int year;
} kendaraan;

void tambahData(FILE *kendaraanFile);
void lihatData(FILE *kendaraanFile);
void ubahData(FILE *kendaraanFile, char *newplat);
void hapusData(FILE *kendaraanFile, int deleteID);


void main() {
    FILE *kendaraanFile;
    char newplat[20];
    int deleteID;
    int menuNumber;

    /* ALGORITHM: */
    do {
        printf("********** DATA KENDARAAN **********\n");
        printf("1. Tambah Data Kendaraan \n");
        printf("2. Lihat Data Kendaraan \n");
        printf("3. Ubah Data Kendaraan \n");
        printf("4. Hapus Data Kendaraan \n");
        printf("5. Keluar Program \n");
        scanf("%d", &menuNumber);

        switch (menuNumber) {
            case 1: tambahData(kendaraanFile);
                break;
            case 2: lihatData(kendaraanFile);
                break;
            case 3: ubahData(kendaraanFile, newplat);
                break;
            case 4: printf("Masukkan ID kendaraan yang ingin dihapus: ");
                    scanf("%d", &deleteID);
                    hapusData(kendaraanFile, deleteID);
                break;
            case 5: printf("Exit Program\n");break;
        }
    } while (menuNumber != 5);
}

void tambahData(FILE *kendaraanFile) {
    kendaraan aKendaraan;

    printf("--- Tambah Data Kendaraan ---\n");
    kendaraanFile = fopen("KendaraanFile.dat","ab");
    printf("ID Kendaraan     : "); scanf("%d",&aKendaraan.id);fflush(stdin);
    while (aKendaraan.id != 9999) {
        printf("Nomor Plat       : "); scanf(" %[^\n]",&aKendaraan.noplat);
        printf("Jenis Kendaraan  : "); scanf(" %[^\n]",&aKendaraan.jenis);
        printf("Tahun Produksi   : "); scanf("%d",&aKendaraan.year);
        fwrite(&aKendaraan,sizeof(kendaraan),1,kendaraanFile);
        printf("ID Kendaraan     : "); scanf("%d",&aKendaraan.id);
    }
    fclose(kendaraanFile);
}

void lihatData(FILE *kendaraanFile) {
    kendaraan aKendaraan;

    printf("--- Lihat Data Kendaraan ---\n");
    kendaraanFile = fopen("KendaraanFile.dat","rb");
    while (fread(&aKendaraan, sizeof(kendaraan), 1, kendaraanFile) == 1){
        printf("ID Kendaraan    : %d\n",aKendaraan.id);
        printf("Nomor Plat      : %s\n",aKendaraan.noplat);
        printf("Jenis Kendaraan : %s\n",aKendaraan.jenis);
        printf("Tahun Produksi  : %d\n",aKendaraan.year);
    }
    fclose(kendaraanFile);
}

void ubahData(FILE *kendaraanFile, char *newplat) {
    kendaraan aKendaraan;
    FILE *tempFile;
    int id, found = 0;

    printf("--- Ubah Data Kendaraan ---\n");
    printf("ID Kendaraan :"); scanf("%d", &id);
    printf("Masukkan plat nomor baru: ");
    scanf(" %[^\n]", newplat);
    kendaraanFile = fopen("KendaraanFile.dat", "rb");
    tempFile = fopen("tempFile.dat", "wb");

    if (kendaraanFile == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&aKendaraan, sizeof(kendaraan), 1, kendaraanFile)) {
        if (aKendaraan.id == id) {
            found = 1;
            strcpy(aKendaraan.noplat, newplat); // Correct order for copying new plate number
        }
        fwrite(&aKendaraan, sizeof(kendaraan), 1, tempFile);
    }

    fclose(kendaraanFile);
    fclose(tempFile);

    remove("KendaraanFile.dat");
    rename("tempFile.dat", "KendaraanFile.dat");

    if (found) {
        printf("Data kendaraan dengan ID %d berhasil diubah.\n", id);
    } else {
        printf("Data kendaraan dengan ID %d tidak ditemukan.\n", id);
    }
}

void hapusData(FILE *kendaraanFile, int deleteID) {
    kendaraan aKendaraan;
    FILE *tempFile;
    int found = 0;

    kendaraanFile = fopen("KendaraanFile.dat", "rb");
    tempFile = fopen("TempFile.dat", "wb");

    while (fread(&aKendaraan, sizeof(kendaraan), 1, kendaraanFile)) {
        if (aKendaraan.id != deleteID) {
            fwrite(&aKendaraan, sizeof(kendaraan), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(kendaraanFile);
    fclose(tempFile);

    remove("KendaraanFile.dat");
    rename(
        "TempFile.dat", "KendaraanFile.dat");

    if (found) {
        printf("Data kendaraan dengan ID %d berhasil dihapus.\n", deleteID);
    } else {
        printf("Data kendaraan dengan ID %d tidak ditemukan.\n", deleteID);
    }
}