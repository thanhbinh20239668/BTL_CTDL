//Hệ thống quản lý kho hàng: Quản lý các loại hàng hóa, phiếu nhập / xuất kho, thống kê và báo cáo hàng hóa…
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf ("[0]. Thoat chuong trinh");
        scanf("%d", &number);

        switch (number) {
            case 1:
                system("cls");
                
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
    } while (number != '0');
}

int main(){
	menu();
    return 0;
}
