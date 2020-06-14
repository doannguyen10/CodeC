
#include <stdio.h>
#include <string.h>


struct HocSinh;
void hienthiDSHS(struct HocSinh*, int);
void hienThiTenCot();

struct HoTen {
	char ho[20];
	char dem[21];
	char ten[20];
};

struct DiemMH {
	float toan;
	float van;
	float anh;
	float tbc;
};

struct HocSinh {
	int ma;
	struct HoTen hoVaTen;
	int tuoi;
	char gioiTinh[10];
	struct DiemMH diem;
};

void nhapDiem(struct DiemMH* diem) {
	printf("Toan: ");
	scanf("%f", &diem->toan);
	printf("Van: ");
	scanf("%f", &diem->van);
	printf("Anh: ");
	scanf("%f", &diem->anh);
	diem->tbc = (diem->toan + diem->van + diem->anh) / 3;
}

void nhapHoTen(struct HoTen* ten) {
	printf("Ho: ");
	scanf("%s", ten->ho);
	printf("Dem: ");
	getchar();
	gets(ten->dem);
	printf("Ten: ");
	scanf("%s", ten->ten);
}

struct HocSinh nhapHs() {
	struct HocSinh hs;
	printf("Nhap ma: ");
	scanf("%d", &hs.ma);
	nhapHoTen(&hs.hoVaTen);
	printf("Tuoi: ");
	scanf("%d", &hs.tuoi);
	printf("Gioi tinh: ");
	scanf("%s", hs.gioiTinh);
	nhapDiem(&hs.diem);
	return hs;
}
void hienThiTTHS(struct HocSinh hs){
	printf("%-10d %-10s %-20s %-10s %-10d %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n",
	hs.ma, hs.hoVaTen.ho, hs.hoVaTen.dem, hs.hoVaTen.ten, hs.tuoi, hs.gioiTinh,
	hs.diem.toan, hs.diem.van, hs.diem.anh, hs.diem.tbc);
}

void sapXepTheoTen(struct HocSinh * ds, int slhs) {
	int i, j;
	for(i = 0; i < slhs - 1; i++) {
		for(j = slhs - 1; j > i; j --) {
			if(strcmp(ds[j].hoVaTen.ten, ds[j-1].hoVaTen.ten) < 0) {
				struct HocSinh hs = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = hs;
			}
		}
	}
}

void sapXepTheoDiem(struct HocSinh* ds, int slhs) {
	int i, j;
	for(i = 0; i < slhs - 1; i++) {
		for(j = slhs - 1; j > i; j --) {
			if(ds[j].diem.tbc > ds[j - 1].diem.tbc) {
				struct HocSinh hs = ds[j];
				ds[j] = ds[j - 1];
				ds[j - 1] = hs;
			}
		}
	}
}


void timTheoTen(struct HocSinh* ds, int slhs) {
	char ten[20];
	printf("Nhap ten: ");
	scanf("%s", ten);
	hienThiTenCot();
	int i, timHs = 0;
	for(i = 0; i < slhs; i++) {
		if(strcmp(ten, ds[i].hoVaTen.ten) == 0) {
			hienThiTTHS(ds[i]);
			timHs = 1;
		}
	}
	if(timHs == 0) {
		printf("Khong co hoc sinh %s trong danh sach!\n", ten);
	}
}

void ghiFile(struct HocSinh * ds, int slhs) {
	getchar();
	char fName[26];
	printf("Nhap ten file: ");
	gets(fName);
	FILE* fOut = fopen(fName, "a");
	int i;
	for(i = 0; i < slhs; i++) {
		struct HocSinh hs = ds[i];
		fprintf(fOut, "%-10d %-10s %-20s %-10s %-10d %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n",
		hs.ma, hs.hoVaTen.ho, hs.hoVaTen.dem, hs.hoVaTen.ten, hs.tuoi, hs.gioiTinh,
		hs.diem.toan, hs.diem.van, hs.diem.anh, hs.diem.tbc);
	}
	fclose(fOut);
}
void docFile(struct HocSinh* ds, int* slhs){

	FILE* fOut = fopen("HS.txt", "r");
	int i = 0;
	if(fOut) {
		for(;;) {
			struct HocSinh hs;
			fscanf(fOut, "%10d %10s %20[^\n] %10s %10d %10s %10f %10f %10f %10f %10f\n",
			&hs.ma, hs.hoVaTen.ho, hs.hoVaTen.dem, hs.hoVaTen.ten, &hs.tuoi, hs.gioiTinh,
			&hs.diem.toan, &hs.diem.van, &hs.diem.anh, &hs.diem.tbc);
			
			ds[i++] = hs;
			if(feof(fOut)) { 
				break;
			}
		}
	}
	
	fclose(fOut);
	*slhs = i;
}

void hienThiTenCot() {
	printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
	printf("%-10s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", 
		"Ma HS", "Ho", "Dem", "Ten", "Tuoi", "Gioi Tinh", 
		"Diem Toan", "Diem Van", "Diem Anh", "Diem TBC");
}

void hienThiDSHS(struct HocSinh* ds, int slhs) {
	hienThiTenCot();
	int i;
	for(i = 0; i < slhs; i++) {
		hienThiTTHS(ds[i]);
	}
	printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
}

int main() {
	struct HocSinh dshs[100];
	int slhs = 0;
	int luaChon;
	
	docFile(dshs, &slhs);
	printf("DANH SACH HOC SINH HIEN THOI:\n");
	hienThiDSHS(dshs, slhs);
	
	int i;
				
	do {
		printf("=============== MENU ===============");
		printf("\n1. Them hoc sinh vao danh sach.");
		printf("\n2. Hien thi danh sach hoc sinh.");
		printf("\n3. Sap xep theo ten.");
		printf("\n4. Sap xep theo diem giam dan.");
		printf("\n5. Tim hoc sinh theo ten.");
		printf("\n6. Ghi thong tin hoc sinh ra file.");
		printf("\n0. Thoat chuong trinh.");
		printf("\nBan chon ? ");
		
		scanf("%d", &luaChon);
		struct HocSinh hs;
		
		switch(luaChon) {
			case 0:
				break;
				
			case 1:
				hs = nhapHs();
				dshs[slhs++] =hs;
				break;
				
			case 2:
				hienThiDSHS(dshs, slhs);
				break;
				
			case 3:
				sapXepTheoTen(dshs, slhs);
				printf("\nDanh sach hoc sinh sau khi sap xep theo ten a-z:\n");
				hienThiDSHS(dshs, slhs);
				break;
				
			case 4:
				sapXepTheoDiem(dshs, slhs);
				printf("\nDanh sach hoc sinh sau khi sap xep theo diem giam dan:\n");
				hienThiDSHS(dshs, slhs);
				break;
				
			case 5:
				timTheoTen(dshs, slhs);
				break;
			case 6:
				ghiFile(dshs, slhs);
				break;
				
			default:
				printf("Sai chuc nang, vui long chon lai!\n");
				break;
		}
		
	} while(luaChon);
	
	return 0;
}

