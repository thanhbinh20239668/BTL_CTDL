#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    char ID[10];
    char Name[50];
    char unitOfMeasurement[10];
    char Supplier[50];
    int Quantity;
    float Price;
};

struct Receipt {
    char productID[10];
    char type[10]; // "IMPORT" hoặc "EXPORT"
    int quantity;
    char date[15]; 
};

struct ProductNode {
    Product data;
    ProductNode* next;
};

struct ReceiptNode{
    Receipt data;
    ReceiptNode* next;
};

ProductNode* productList = NULL;
ReceiptNode* receiptNode = NULL;


// Hàm đọc chuỗi an toàn bằng fgets
void inputString(char* str, int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';  // Xóa newline nếu có
}

// Hàm tạo sản phẩm mới
Product createProduct() {
    Product p;
    printf("Nhap ID: "); inputString(p.ID, sizeof(p.ID));
    printf("Nhap ten: "); inputString(p.Name, sizeof(p.Name));
    printf("Nhap don vi tinh: "); inputString(p.unitOfMeasurement, sizeof(p.unitOfMeasurement));
    printf("Nhap nha cung cap: "); inputString(p.Supplier, sizeof(p.Supplier));
    printf("Nhap so luong: "); scanf("%d", &p.Quantity);
    getchar();
    printf("Nhap don gia: "); scanf("%f", &p.Price);
    getchar();
    return p;
}

// Thêm sản phẩm vào danh sách (sắp xếp theo ID tăng dần)
void addProduct() {
    Product p = createProduct();
    ProductNode* newNode = (ProductNode*)malloc(sizeof(ProductNode));
    newNode->data = p;
    newNode->next = NULL;

    if (productList == NULL || strcmp(p.ID, productList->data.ID) < 0) {
        newNode->next = productList;
        productList = newNode;
        return;
    }

    ProductNode* current = productList;
    while (current->next && strcmp(p.ID, current->next->data.ID) > 0) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

// Hiển thị toàn bộ sản phẩm
void displayProducts() {
    ProductNode* current = productList;
    printf("\n%-10s %-20s %-10s %-20s %-10s %-10s\n",
           "ID", "Name", "Unit", "Supplier", "Qty", "Price");
    while (current) {
        Product p = current->data;
        printf("%-10s %-20s %-10s %-20s %-10d %-10.2f\n",
               p.ID, p.Name, p.unitOfMeasurement, p.Supplier, p.Quantity, p.Price);
        current = current->next;
    }
}


void menu(){
	//readFile;
	int number;
	do {
        printf( "\n-------------------------------------------\n" ) ;
        printf("=============QUAN LI KHO HANG==============\n");
        printf("-------------------------------------------\n");
        printf ("[1]. Them hang hoa.\n");
        printf ("[2]. Nhap kho.\n");
        printf ("[3]. Xuat kho.\n");
        printf ("[4]. Sua thong tin hang hoa.\n") ;
        printf ("[5]. Tim kiem hang hoa.\n");
		printf ("[6]. Xoa hang hoa.\n");
        printf ("[7]. Sap xep hang hoa theo ID.\n");
        printf ("[8]. Hien thi hang hoa.\n" );
		printf ("[9]. Thong ke hang hoa.\n" );
        printf ("[0]. Thoat chuong trinh.\n");
        printf ("Chon tinh nang: ");
        scanf("%d", &number);
        getchar();

        switch (number) {
            case 1:
                system("cls");
                addProduct();
                printf("Da them san pham thanh cong!\n");
                break;
            case 2:
                system("cls");
                
                break;
            case 3:
                system("cls");
                
                break;
            case 4:
                system("cls");
                
                break;
            case 5:
                system("cls");

                break;
            case 6:
                system("cls");

                break;
            case 7:
                system("cls");

                break;
            case 8:
                system("cls");
                int choice;
                printf("Chon hien thi:\n");
                printf("[1].Hien thi hang hoa.\n");
                printf("[2].Hien thi phieu nhap xuat.\n");
                printf("Lua chon: ");
                scanf("%d", &choice);
                getchar(); 
                if (choice == 1) {
                    displayProducts();}
                else if (choice == 2) {}
                     
                else {
                     printf("Lua chon khong hop le.\n");
                }
                break;
            case 9:
                system("cls");

                break;
            case 0:
                printf("Thoat chuong trinh.\n") ;
                //saveFile();
                printf("Cam on ban da su dung chuong trinh!\n");
                break;
            default:
                system("cls");
                printf("Lua chon khong hop le. Vui long chon lai!\n");
                break;
        }
    } while (number != 0);
}

int main(){
	menu();
    return 0;
}
