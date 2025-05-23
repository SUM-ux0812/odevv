#include <stdio.h>
#include <stdlib.h>


#define FILENAME "product.txt"

struct product {
    int id;
    char name[20];
    float price;
    int stock;
};

void menu();
void addProduct();
void updateProducts();
void showProducts();
void deleteProduct();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    while (1) {
        printf("****urun yonetimi****\n");
        printf("1. urun ekleme\n");
        printf("2. urun guncelleme\n");
        printf("3. urun goster\n");
        printf("4. urun sil\n");
        printf("5. cikis\n");
        printf("secim yapiniz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProducts();
                break;
            case 3:
                showProducts();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                exit(0);
            default:
                printf("Gecersiz secenek, tekrar deneyin.\n");
        }
    }
}

void addProduct() {
    struct product p;
    FILE *file = fopen(FILENAME, "ab");
    
    printf("urun ID: ");
    scanf("%d", &p.id);
    printf("urun adi: ");
    scanf("%s", p.name);
    printf("urun fiyati: ");
    scanf("%f", &p.price);
    printf("urun miktari: ");
    scanf("%d", &p.stock);

    fwrite(&p, sizeof(struct product), 1, file);
    fclose(file);
    printf("urun basari ile eklendi.\n");
}

void updateProducts() {
      struct product p;
        int id, newStock = 0;

        FILE *file = fopen(FILENAME, "rb+");

        printf("guncellemek istenilen urun ID sini girin : \n");
        scanf("%d" , &id);
        fseek(file, (id -1) *sizeof(struct product ), SEEK_SET);
        fread(&p , sizeof(struct product) , 1, file );

        printf("yeni stock miktari: \n");
        scanf("%d" , &newStock);
        p.stock = newStock;
        fseek(file , (id -1) *sizeof(struct product) , SEEK_CUR);
        fwrite(&p , sizeof( struct product ) , 1, file);
        fclose(file);
        printf("dosya basari ile guncellendi ! \n");
}

void showProducts() {
    FILE *file = fopen(FILENAME, "rb");
    
    struct product p;
    printf("\nUrun Listesi:\n");
    printf("urun ID: ");
    printf("urun adi: ");
    printf("urun fiyati: ");
    printf("urun miktari: ");
    
    //printf("ID\tName\tPrice\tStock\n");
    while (fread(&p, sizeof(struct product), 1, file) == 1) {
        printf("%d\t%s\t%.2f\t%d\n", p.id, p.name, p.price, p.stock);
    }
    fclose(file);
}

void deleteProduct() {
    int deleteId;
    FILE *file = fopen(FILENAME, "rb");
    
    FILE *tempFile = fopen("temp.txt", "wb");
    if (tempFile == NULL) {
        printf("Geçici dosya acilmadi.\n");
        fclose(file);
        return;
    }
    printf("Silmek istedigin urun ID'sini girin: ");
    scanf("%d", &deleteId);
    struct product p;
    int found = 0;
    while (fread(&p, sizeof(struct product), 1, file) == 1) {
        if (p.id == deleteId) {
            found = 1;
            continue; 
        }
        fwrite(&p, sizeof(struct product), 1, tempFile);
    }
    fclose(file);
    fclose(tempFile);
    if (found) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("Urun silindi.\n");
    } else {
        printf("Urun bulunamadi.\n");
        remove("temp.txt");
    }
}