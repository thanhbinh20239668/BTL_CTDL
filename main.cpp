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
    char ID[10];
    char type[10]; //"IMPORT" hoặc "EXPORT"
    int quantity;
    char date[15];
    float price;
    char name[50];
    int isProcessed; //  Đánh dấu đã cập nhật vào kho chưa
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
    printf("Nhap so luong dang co: "); scanf("%d", &p.Quantity);
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
// phiếu nhập
Receipt taoPhieuNhapKho() {
    Receipt p;
    strcpy(p.type, "IMPORT");
     p.isProcessed = 0; //  đánh dấu chưa xử lý
    printf("=== Tao Phieu Nhap Kho ===\n");
    printf("Nhap ma hang (ID): "); inputString(p.ID, sizeof(p.ID));
    printf("Nhap so luong: "); scanf("%d", &p.quantity);
    getchar();
    ProductNode* prod = productList;
    while (prod) {
        if (strcmp(prod->data.ID, p.ID) == 0) {
            strcpy(p.name, prod->data.Name);
            p.price = prod->data.Price;
            break;
        }
        prod = prod->next;
    }
    if (prod == NULL) {
        strcpy(p.name, "");
        p.price = 0;
    }
    printf("Nhap ngay (dd/mm/yyyy): ");
    inputString(p.date, sizeof(p.date));
    return p;
}

// phiếu xuất
Receipt taoPhieuXuatKho() {
    Receipt p;
    strcpy(p.type, "EXPORT");
     p.isProcessed = 0; //  đánh dấu chưa xử lý
    printf("=== Tao Phieu Xuat Kho ===\n");
    printf("Nhap ma hang (ID): "); inputString(p.ID, sizeof(p.ID));
    printf("Nhap so luong: "); scanf("%d", &p.quantity);
    getchar();
    ProductNode* prod = productList;
    while (prod) {
        if (strcmp(prod->data.ID, p.ID) == 0) {
            strcpy(p.name, prod->data.Name);
            p.price = prod->data.Price;
            break;
        }
        prod = prod->next;
    }
    if (prod == NULL) {
        strcpy(p.name, "");
        p.price = 0;
    }

    printf("Nhap ngay (dd/mm/yyyy): ");
    inputString(p.date, sizeof(p.date));
    return p;
}
void xuLiPhieu(Receipt* p) {
    if (p->isProcessed == 1) return; // tránh xử lý lại phiếu đã xử lý
    ProductNode* prod = productList;
    while (prod) {
        if (strcmp(prod->data.ID, p->ID) == 0) {
            if (strcmp(p->type, "IMPORT") == 0) {
                prod->data.Quantity += p->quantity;
            } else if (strcmp(p->type, "EXPORT") == 0) {
                if (prod->data.Quantity >= p->quantity) {
                    prod->data.Quantity -= p->quantity;
                } else {
                    printf("Canh bao: Khong du hang de xuat kho (ID: %s, Yeu cau: %d, Ton kho: %d)\n",
                           p->ID, p->quantity, prod->data.Quantity);
                    return;
                }
            }
            break;
        }
        prod = prod->next;
    }
    p->isProcessed = 1; // đánh dấu đã xử lý
}
void themPhieuVaoDanhSach(Receipt p) {  // dùng đếm số phiếu đã thực hiện
    ReceiptNode* newNode = (ReceiptNode*)malloc(sizeof(ReceiptNode));
    if (newNode == NULL) {
        printf("Khong du bo nho !\n");
        return;
    }
    newNode->data = p; // p đã được đánh dấu isProcessed=1 rồi
    newNode->next = NULL;

    if (receiptNode == NULL) {
        receiptNode = newNode;
    } else {
        ReceiptNode* current = receiptNode;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
void hienThiPhieu() {
    int soPhieuNhap = 0;
    int soPhieuXuat = 0;
    ReceiptNode* current = receiptNode;
    while (current) {
        Receipt* p = &current->data;
        // Đếm số phiếu
        if (strcmp(p->type, "IMPORT") == 0) {
            soPhieuNhap++;
        } else if (strcmp(p->type, "EXPORT") == 0) {
            soPhieuXuat++;
        }
        // Cập nhật số lượng nếu chưa xử lý
        if (p->isProcessed == 0) {
            ProductNode* prod = productList;
            while (prod) {
                if (strcmp(prod->data.ID, p->ID) == 0) {
                    if (strcmp(p->type, "IMPORT") == 0) {
                        prod->data.Quantity += p->quantity;
                    } else if (strcmp(p->type, "EXPORT") == 0) {
                        if (prod->data.Quantity >= p->quantity) {
                            prod->data.Quantity -= p->quantity;
                        } else {
                            printf("⚠️  Khong du hang de xuat kho (ID: %s, Yeu cau: %d, Ton: %d)\n",
                                   p->ID, p->quantity, prod->data.Quantity);
                        }
                    }
                    break;
                }
                prod = prod->next;
            }
            p->isProcessed = 1; // ✅ đánh dấu đã xử lý
        }
        current = current->next;
    }
    printf("\n===== Thong ke phieu =====\n");
    printf("So phieu nhap: %d\n", soPhieuNhap);
    printf("So phieu xuat: %d\n", soPhieuXuat);
}
void menu(){
	//readFile;
	int number;
	do {
        printf( "\n-------------------------------------------\n" ) ;
        printf("=============QUAN LI KHO HANG==============\n");
        printf("-------------------------------------------\n");
        printf ("[1]. Them hang hoa.\n");
        printf ("[2]. Them phieu nhap/xuat.\n");
        printf ("[3]. Sua thong tin hang hoa.\n") ;
        printf ("[4]. Tim kiem hang hoa.\n");
		printf ("[5]. Xoa hang hoa.\n");
        printf ("[6]. Sap xep hang hoa theo ID.\n");
        printf ("[7]. Hien thi hang hoa/phieu.\n" );
		printf ("[8]. Thong ke hang hoa.\n" );
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
                int loaiPhieu;
                printf("Chon loai phieu:\n[1] Phieu nhap kho\n[2] Phieu xuat kho\nLua chon: ");
                scanf("%d", &loaiPhieu);
                getchar();

                Receipt p;
                if (loaiPhieu == 1) {
                p = taoPhieuNhapKho();
                xuLiPhieu(&p);
               } else if (loaiPhieu == 2) {
                  p = taoPhieuXuatKho();
                   xuLiPhieu(&p);
               } else {
                printf("Lua chon khong hop le.\n");
                break;
      }

           // Thêm phiếu vào danh sách
           themPhieuVaoDanhSach(p);

            printf("Da them va xu ly phieu thanh cong.\n");
            break;
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
                int choice;
                printf("Chon hien thi:\n");
                printf("[1].Hien thi hang hoa.\n");
                printf("[2].thong ke phieu nhap xuat.\n");
                printf("Lua chon: ");
                scanf("%d", &choice);
                getchar(); 
                if (choice == 1) {
                    displayProducts();}
                else if (choice == 2) {
                	hienThiPhieu();
				}
                     
                else {
                     printf("Lua chon khong hop le.\n");
                }
                break;
            case 8:
                system("cls");
               
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
