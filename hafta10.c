
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

typedef struct Node node;
node *head = NULL;

void yazdir();
void basaEkle(int veri);
void arayaEkle(int veri, int sira);
void sonaEkle(int veri);
void dugumSil(int sira);

int main()
{
    int secim, veri, sira;

    while(1)
    {
        printf("\n------MENU------\n");
        printf("1. Listeyi goruntule\n");
        printf("2. Basa eleman ekle\n");
        printf("3. Araya eleman ekle\n");
        printf("4. Sona eleman ekle\n");
        printf("6. Dugum Sil\n");
        printf("5. CIikis yap\n");
        scanf("%d", &secim);
        switch (secim)
        {
            case 1:
                yazdir();
                break;
            case 2:
                printf("Basa eklemek istediginiz elemani girin: ");
                scanf("%d", &veri);
                basaEkle(veri);
                break;
            case 3:
                printf("Araya eklemek istediginiz elemani girin: ");
                scanf("%d", &veri);
                printf("Eklemek istediginiz sirayi girin: ");
                scanf("%d", &sira);
                arayaEkle(veri, sira);
                break;
            case 4:
                printf("Sona eklemek istediginiz elemani girin: ");
                scanf("%d", &veri);
                sonaEkle(veri);
                break;
            case 5:
                exit(0);
                break;
            case 6:
                printf("Silmek istediginiz dugumun sirasini girin: ");
                scanf("%d", &sira);
                dugumSil(sira);
                printf("Guncel liste:\n");
                yazdir();
                
            default:
                printf("Gecersiz secim!\n");
        }
    }
}

void yazdir()
{
    node *temp = head;

    printf("Liste: ");
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void basaEkle(int veri)
{
    node *yeni = (node *)malloc(sizeof(node));

    yeni->data = veri;
    yeni->next = head;

    head = yeni;
}

void arayaEkle(int veri, int sira)
{
    node *yeni = (node *)malloc(sizeof(node));
    yeni->data = veri;
    yeni->next = NULL;

    if (sira == 0)
    {
        basaEkle(veri);
        return;
    }

    node *temp = head;
    for (int i = 0; i < sira - 1; i++)
    {
        if(temp == NULL)
        {
            printf("Girilen deger liste boyutundan buyuktur!\nEkleme yapilamadi.");
            free(yeni);
        }
        temp = temp->next;
    }

    yeni->next = temp->next;
    temp->next = yeni;

    printf("%d. indekse %d degeri eklendi.\n", sira, veri);
}

void sonaEkle(int veri)
{
    node *yeni = (node *)malloc(sizeof(node));
    yeni->data = veri;
    yeni->next = NULL;

    if (head == NULL)
    {
        head = yeni;
        return;
    }

    node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = yeni;
    printf("%d degeri sona eklendi.\n", veri);
}

void dugumSil(int sira)
{
    if (head == NULL)
    {
        printf("Liste bos!\n");
        return;
    }

    node *temp = head;

    if (sira == 1)
    {
        head = temp->next;
        free(temp);
        return;
    }

    for (int i = 1; i < sira - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL)
    {
        printf("Gecersiz sira!\n");
        return;
    }

    node *silinecek = temp->next;
    temp->next = silinecek->next;
    free(silinecek);
}
 fclose(file); 