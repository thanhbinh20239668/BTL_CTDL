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
ReceiptNode* receiptList = NULL;


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

    // Kiểm tra trùng ID
    ProductNode* temp = productList;
    while (temp != NULL) {
        if (strcmp(temp->data.ID, p.ID) == 0) {
            printf("Loi: Da ton tai san pham voi ID '%s'. Khong the them.\n", p.ID);
            return;
        }
        temp = temp->next;
    }


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
    printf("Da them san pham thanh cong!\n");
}
//Hàm sửa thông tin sản phẩm
void editProduct(){
    char id[10];
    printf("Nhap ID san pham can sua: ");
    inputString(id, sizeof(id));

    ProductNode* current = productList;
    while (current) {
        if (strcmp(current->data.ID, id) == 0) {
            int choice;
            printf("Da tim thay san pham: %s\n", current->data.Name);
            printf("Chon thong tin muon sua:\n");
            printf("[1] Ten\n");
            printf("[2] Don vi tinh\n");
            printf("[3] Nha cung cap\n");
            printf("[4] So luong\n");
            printf("[5] Don gia\n");
            printf("Lua chon: ");
            scanf("%d", &choice);
            getchar();
            switch (choice) {
            case 1:
                printf("Nhap ten moi: ");
                inputString(current->data.Name, sizeof(current->data.Name));
                break;
            case 2:
                printf("Nhap don vi tinh moi: ");
                inputString(current->data.unitOfMeasurement, sizeof(current->data.unitOfMeasurement));
                break;
            case 3:
                printf("Nhap nha cung cap moi: ");
                inputString(current->data.Supplier, sizeof(current->data.Supplier));
                break;
            case 4:
                printf("Nhap so luong moi: ");
                scanf("%d", &current->data.Quantity);
                getchar();
                break;
            case 5:
                printf("Nhap don gia moi: ");
                scanf("%f", &current->data.Price);
                getchar();
                break;
            default:
                printf("Lua chon khong hop le!\n");
                return;
            }
            printf("Da cap nhat thong tin san pham!\n");
            return;
        }
        current = current->next;
    }
    printf("Khong tim thay san pham co ID: %s\n", id);
}
// Hàm xóa sản phẩm 
void deleteProduct(){
    char id[10];
    printf("Nhap ID san pham muon xoa: ");
    inputString(id, sizeof(id));

    ProductNode* current = productList;
    ProductNode* prev = NULL;

    while (current) {
        if (strcmp(current->data.ID, id) == 0) {
            if (prev == NULL) {
                productList = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            printf("Da xoa san pham co ID: %s\n", id);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Khong tim thay san pham co ID: %s\n", id);
}
//Hàm tìm sản phẩm
void searchProduct() {
    char keyword[50];
    printf("Nhap ID hoac ten san pham de tim kiem: ");
    inputString(keyword, sizeof(keyword));

    int found = 0;
    ProductNode* current = productList;

    while (current) {
        Product p = current->data;
        if (strcmp(p.ID, keyword) == 0 || strstr(p.Name, keyword) != NULL) {
            if (!found) {
                printf("\n%-10s %-25s %-15s %-25s %-10s %-12s\n",
                       "ID", "Ten", "Don vi tinh", "Nha cung cap", "So luong", "Don gia");
                found = 1;
            }
            printf("%-10s %-25s %-15s %-25s %-10d %-12.2f\n",
                   p.ID, p.Name, p.unitOfMeasurement, p.Supplier, p.Quantity, p.Price);
        }
        current = current->next;
    }

    if (!found) {
        printf("Khong tim thay san pham voi tu khoa: \"%s\"\n", keyword);
    }
}
// Hiển thị toàn bộ sản phẩm
void displayProducts() {
    ProductNode* current = productList;
    printf("\n%-10s %-20s %-10s %-20s %-10s %-12s %-12s\n",
           "ID", "Ten sp", "Don vi", "Nha cung cap", "So luong", "Gia", "Tong");
    while (current) {
        Product p = current->data;
        float total = p.Quantity * p.Price;
        printf("%-10s %-20s %-10s %-20s %-10d %-12.2f %-12.2f\n",
               p.ID, p.Name, p.unitOfMeasurement, p.Supplier, p.Quantity, p.Price, total);
        current = current->next;
    }
}

void displayReceipt() {
    if (receiptList == NULL) {
        printf("Khong co phieu nao trong danh sach.\n");
        return;
    }

    printf("\n================ CHI TIET CAC PHIEU =================\n");
    printf("%-10s %-25s %-10s %-15s %-12s %-12s\n",
           "Ma SP", "Ten SP", "So luong", "Ngay", "Don gia", "Thanh tien");

    ReceiptNode* current = receiptList;
    while (current != NULL) {
        Receipt r = current->data;
        float thanhTien = r.quantity * r.price;
        printf("%-10s %-25s %-10d %-15s %-12.2f %-12.2f\n",
               r.ID, r.name, r.quantity, r.date, r.price, thanhTien);
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

    if (receiptList == NULL) {
        receiptList = newNode;
    } else {
        ReceiptNode* current = receiptList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
//Thong ke so phieu
void statisticsReceipt() {
    int soPhieuNhap = 0;
    int soPhieuXuat = 0;
    ReceiptNode* current = receiptList;
    while (current) {
        Receipt* p = &current->data;
        // Đếm số phiếu
        if (strcmp(p->type, "IMPORT") == 0) {
            soPhieuNhap++;
        } else if (strcmp(p->type, "EXPORT") == 0) {
            soPhieuXuat++;
        }
        current = current->next;
    }
    printf("\n===== Thong ke phieu =====\n");
    printf("So phieu nhap: %d\n", soPhieuNhap);
    printf("So phieu xuat: %d\n", soPhieuXuat);
}
//thong ke hang hoa
void statisticsProduct() {
    if (productList == NULL) {
        printf("Danh sach san pham rong.\n");
        return;
    }

    int tongLoai = 0;
    int tongSoLuong = 0;
    float tongGiaTri = 0;

    ProductNode* current = productList;
    while (current != NULL) {
        tongLoai++;
        tongSoLuong += current->data.Quantity;
        tongGiaTri += current->data.Quantity * current->data.Price;
        current = current->next;
    }

    int choice;
    do {
        printf("\n===== THONG KE HANG HOA =====\n");
        printf("[1]. Tong so loai mat hang\n");
        printf("[2]. Tong so luong hang\n");
        printf("[3]. Tong gia tri hang ton kho\n");
        printf("[4]. Thong ke theo nha cung cap\n");
        printf("[5]. San pham co gia tri ton kho cao nhat / thap nhat\n");
        printf("[0]. Thoat\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Tong so loai mat hang: %d\n", tongLoai);
                break;
            case 2:
                printf("Tong so luong hang: %d\n", tongSoLuong);
                break;
            case 3:
                printf("Tong gia tri hang ton kho: %.2f\n", tongGiaTri);
                break;
            case 4: {
                printf("\n--- Thong ke theo nha cung cap ---\n");
                ProductNode* outer = productList;
                while (outer != NULL) {
                    // Ki?m tra nhà cung c?p dã in ra chua
                    int daThongKe = 0;
                    ProductNode* tempCheck = productList;
                    while (tempCheck != outer) {
                        if (strcmp(tempCheck->data.Supplier, outer->data.Supplier) == 0) {
                            daThongKe = 1;
                            break;
                        }
                        tempCheck = tempCheck->next;
                    }
                    if (!daThongKe) {
                        int sl = 0;
                        float tongGT = 0;
                        ProductNode* inner = productList;
                        while (inner != NULL) {
                            if (strcmp(inner->data.Supplier, outer->data.Supplier) == 0) {
                                sl += inner->data.Quantity;
                                tongGT += inner->data.Quantity * inner->data.Price;
                            }
                            inner = inner->next;
                        }
                        printf("Nha cung cap: %s - So luong: %d - Gia tri: %.2f\n",
                               outer->data.Supplier, sl, tongGT);
                    }
                    outer = outer->next;
                }
                break;
            }
            case 5: {
                if (productList == NULL) {
                    printf("Danh sach rong.\n");
                    break;
                }

                ProductNode* maxNode = productList;
                ProductNode* minNode = productList;
                ProductNode* ptr = productList->next;

                while (ptr != NULL) {
                    float val = ptr->data.Price * ptr->data.Quantity;
                    if (val > maxNode->data.Price * maxNode->data.Quantity)
                        maxNode = ptr;
                    if (val < minNode->data.Price * minNode->data.Quantity)
                        minNode = ptr;
                    ptr = ptr->next;
                }

                printf("\n--- San pham co gia tri ton kho CAO NHAT ---\n");
                printf("ID: %s | Ten: %s | Gia tri: %.2f\n",
                       maxNode->data.ID, maxNode->data.Name,
                       maxNode->data.Price * maxNode->data.Quantity);

                printf("\n--- San pham co gia tri ton kho THAP NHAT ---\n");
                printf("ID: %s | Ten: %s | Gia tri: %.2f\n",
                       minNode->data.ID, minNode->data.Name,
                       minNode->data.Price * minNode->data.Quantity);
                break;
            }
            case 0:
                printf("Thoat thong ke.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
                break;
        }
    } while (choice != 0);
}
//doc du lieu tu File
void readFile(const char* tenFile) {
    FILE* f = fopen(tenFile, "r");
    if (f == NULL) {
        printf("Khong the mo file %s de doc du lieu.\n", tenFile);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        Product p;
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d,%f",
                   p.ID,
                   p.Name,
                   p.unitOfMeasurement,
                   p.Supplier,
                   &p.Quantity,
                   &p.Price) == 6) {

            ProductNode* newNode = (ProductNode*)malloc(sizeof(ProductNode));
            newNode->data = p;
            newNode->next = NULL;

            if (productList == NULL) {
                productList = newNode;
            } else {
                ProductNode* temp = productList;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = newNode;
            }
        }
    }

    fclose(f);
    printf("Da doc du lieu hang hoa tu file '%s'.\n", tenFile);
}
//ghi du lieu ra file
void saveFile(const char* tenFile) {
    FILE* f = fopen(tenFile, "w");
    if (f == NULL) {
        printf("Khong the mo file %s de ghi du lieu.\n", tenFile);
        return;
    }

    ProductNode* current = productList;
    while (current != NULL) {
        fprintf(f, "%s,%s,%s,%s,%d,%.2f\n",
                current->data.ID,
                current->data.Name,
                current->data.unitOfMeasurement,
                current->data.Supplier,
                current->data.Quantity,
                current->data.Price);
        current = current->next;
    }

    fclose(f);
    printf("Da luu du lieu hang hoa vao file '%s'.\n", tenFile);
}

void menu(){
	//readFile;
    productList = NULL;
    readFile("baocao.txt");
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
        printf ("[6]. Hien thi hang hoa/phieu.\n" );
		printf ("[7]. Thong ke hang hoa.\n" );
        printf ("[0]. Thoat chuong trinh.\n");
        printf ("Chon tinh nang: ");
        scanf("%d", &number);
        getchar();

        switch (number) {
            case 1:
                system("cls");
                addProduct();
                break;
            case 2:
                system("cls");
                int loaiPhieu;
                printf("Chon loai phieu:\n");
                printf("[1] Phieu nhap kho\n");
                printf("[2] Phieu xuat kho\n ");
                printf("Lua chon:");
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
            case 3:
                system("cls");
                editProduct();
                break;
            case 4:
                system("cls");
                searchProduct();
                break;
            case 5:
                system("cls");
				deleteProduct();
                break;
            case 6:
                system("cls");
                int choice;
                printf("Chon hien thi:\n");
                printf("[1].Hien thi hang hoa.\n");
                printf("[2].Hien thi chi tiet cac phieu.\n");
                printf("Lua chon: ");
                scanf("%d", &choice);
                getchar(); 
                if (choice == 1) {
                    displayProducts();}
                else if (choice == 2) {
                    displayReceipt(); 
                }
                else {
                     printf("Lua chon khong hop le.\n");
                }
                break;
            case 7:
                system("cls");
                int choices;
                printf("Chon thong ke:\n");
                printf("[1].Thong ke hang hoa.\n");
                printf("[2].Thong ke so phieu.\n");
                printf("Lua chon: ");
                scanf("%d", &choices);
                getchar(); 
                if (choices == 1) {
                    statisticsProduct();}
                else if (choices == 2) {
                    statisticsReceipt(); 
                }
                else {
                     printf("Lua chon khong hop le.\n");
                }
                break;

            case 0:
                //saveFile();
                saveFile("baocao.txt");
                printf("Thoat chuong trinh.\n") ;
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
