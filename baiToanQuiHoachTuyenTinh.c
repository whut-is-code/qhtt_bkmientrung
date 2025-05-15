#include <stdio.h>
#include <math.h>

// Cac ham cua pp hinh hoc

typedef struct {
	float x, y; // A(x; y)
} Diem;

typedef struct {
	float a, b, c; // ax + by <= c
} RangBuoc;

int timGiaoDiem(RangBuoc rb1, RangBuoc rb2, Diem *p) {
	float det = rb1.a*rb2.b - rb2.a*rb1.b; // tim dinh thuc
	if (det == 0)
		return 0; // neu dinh thuc bang 0 => vo nghiem
	
	p->x = (rb1.c*rb2.b - rb2.c*rb1.b) / det;
	p->y = (rb1.a*rb2.c - rb2.a*rb1.c) / det;
	return 1;
}

int trongMienXD(Diem p, int so_rb, RangBuoc Rang_buoc[]) {
	float value;
	int i;
	for (i = 0; i < so_rb; i++) {
		value = Rang_buoc[i].a * p.x + Rang_buoc[i].b * p.y;
		if (value > Rang_buoc[i].c) return 0;
	}
	return 1;
}

void xuatPA(float x, float y, float c1, float c2) {
	printf("(%.3f; %.3f) => z = %.3f\n", x, y, c1*x + c2*y);
}

void xuatRangBuocHinhHoc(RangBuoc Rang_buoc[], int n) {
	int i;
	for (i = 0; i < n - 2; i++) {
		if (Rang_buoc[i].a != 0) {
			if (Rang_buoc[i].a != 1)
				printf("%.3f*", Rang_buoc[i].a);
			printf("x ");
		}
		if (Rang_buoc[i].b != 0) {
			printf("%c ", (Rang_buoc[i].b > 0)? '+':'-');
			if (Rang_buoc[i].b != 1)
				printf("%.3f*", fabs(Rang_buoc[i].b));
			printf("y ");
		}
		printf("<= %.3f\n", Rang_buoc[i].c);
	}
	printf("x, y >= 0\n");
}

void xuatHamMucTieuHinhHoc(float c1, float c2) {
	if (c1 != 0) {
		if (c1 != 1)
			printf("%.3f*", c1);
		printf("x ");
	}
	if (c2 != 0) {
		printf("%c ", (c2 > 0)? '+':'-');
		if (c2 != 1)
			printf("%.3f*", fabs(c2));
		printf("y");
	}
}

void ppHinhHoc(RangBuoc Rang_buoc[], int n, float c1, float c2) {
	// Tim cac dinh cua mien xac dinh
	Diem dinh[100];
	int count = 0;
	
	Diem p;
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (timGiaoDiem(Rang_buoc[i], Rang_buoc[j], &p)) {
				if (trongMienXD(p, n, Rang_buoc)) {
					dinh[count] = p;
					count++;
				}
			}
		}
	}
	
	// Tim phuong an toi uu
	float max = c1 * dinh[0].x + c2 * dinh[0].y;
	Diem best_point; best_point = dinh[0];
	printf("Phuong an 1 la: ");
	xuatPA(dinh[0].x, dinh[0].y, c1, c2);
	
	float z;
	for (i = 1; i < count; i++) {
		z = c1 * dinh[i].x + c2 * dinh[i].y;
		printf("Phuong an %d la: ", i + 1);
		xuatPA(dinh[i].x, dinh[i].y, c1, c2);
		if (max < z) {
			max = z;
			best_point = dinh[i];
		}
	}
	
	// In ket qua
	printf("\nPhuong toi uu la: (%.3f; %.3f)", best_point.x, best_point.y);
	printf("\nGia tri toi uu z = %.3f", max);
}

void docDuLieuHinhHoc(RangBuoc Rang_buoc[], int *n_ptr, float *c1_ptr, float *c2_ptr) {
	printf("Nhap so rang buoc dang ax + by <= c: "); scanf("%d", n_ptr);
	
	int i;
	for (i = 0; i < *n_ptr; i++) {
		printf("Nhap a, b, c cho rang buoc %d: ", i + 1);
		scanf("%f%f%f", &Rang_buoc[i].a, &Rang_buoc[i].b, &Rang_buoc[i].c);
	}
	
	printf("Nhap c1, c2 cho ham muc tieu z = c1*x + c2*y: "); scanf("%f%f", c1_ptr, c2_ptr);
}

void docFile_HinhHoc(RangBuoc Rang_buoc[], int *n_ptr, float *c1_ptr, float *c2_ptr) {
	char s[100];
	printf("Nhap ten file: "); scanf("%s", s);
	printf("\n--------------------");
	FILE *fptr;
	fptr = fopen(s, "r");
	fscanf(fptr, "%d", n_ptr);
	int i;
	for (i = 0; i < *n_ptr; i++) {
		fscanf(fptr, "%f", &Rang_buoc[i].a);
		fscanf(fptr, "%f", &Rang_buoc[i].b);
		fscanf(fptr, "%f", &Rang_buoc[i].c);
	}
	fscanf(fptr, "%f", c1_ptr);
	fscanf(fptr, "%f", c2_ptr);
	
	fclose(fptr);
}

// Cac ham cua pp don hinh

void xuatHamMucTieu(float c[], int n) {
	printf("z = ");
	if (c[1] != 1) printf("%.3f*", c[1]);
	printf("x1 ");
	for (int i = 2; i <= n; i++) {
		if (c[i] != 0) {
			if (c[i] > 0) printf("+ ");
			else printf("- ");
			if (c[i] != 1) printf("%.3f*", fabs(c[i]));
			printf("x%d ", i);
		}
	}
}

void xuatRangBuoc(float A[100][100], int m, int n) {
	int i, j;
	for (i = 1; i <= n - 2; i++) {
		printf("x%d, ", i);
	}
	printf("x%d > 0\n", n - 1);
	for (i = 1; i <= m - 1; i++) {
		printf("%.3f*x1 ", A[i][1]);
		for (int j = 2; j <= n - 1; j++) {
			if (A[i][j] != 0) {
				if (A[i][j] > 0) printf("+ ");
				else printf("- ");
				if (A[i][j] != 1) printf("%.3f*", fabs(A[i][j]));
				printf("x%d ", j);
			}
		}
		printf("= 0\n");
	}
}

void nhapMaTran(float A[100][100], int m, int n) {
	int i, j;
	for (i = 1; i <= m - 1; i++) {
		for (j = 1; j <= n; j++) {
			scanf("%f", &A[i][j]);
		}
	}
}

float tich2Mang(float A[100][100], int m, int k, float cB[]) {
	float sum = 0; int i;
	for (i = 1; i <= m - 1; i++) sum += A[i][k] * cB[i];
	return sum;
}

void capNhatHangDelta(float A[100][100], int m, int n, float c[], float cB[]) {
	int i, j;
	for (j = 1; j <= n - 1; j++) {
		A[m][j] = tich2Mang(A, m, j, cB) - c[j];
	}
	// cập nhật giá trị của f tại A[m][n]
	A[m][n] = tich2Mang(A, m, n, cB);
}

void xuatBang(float A[100][100], int m, int n) {
	int i, j;
	for (i = 1; i <= n - 1; i++) {
		printf("A%d\t", i);
	}
	printf("b");
	for (i = 1; i <= m; i++) {
		printf("\n");
		for (j = 1; j <= n; j++) printf("%.3f\t", A[i][j]);
	}
	printf("delta[j]\n");
}

void timCotChuYeu(float A[100][100], int m, int n, int *ccy_ptr) {
	int j;
	float delta = A[m][1];
	int col_index = 1;
	for (j = 2; j <= n - 1; j++) {
		if (delta < A[m][j]) {
			delta = A[m][j];
			col_index = j;
		}
	}
	*ccy_ptr = col_index; // tim j sao cho delta[j] max
}

int timDongChuYeu(float A[100][100], int m, int n, int ccy, int *dcy_ptr) {
	int i;
	int row_index = 1, count = 0;
	float lamda = A[row_index][n] / A[row_index][ccy];
	float min = (lamda > 0)? lamda:-lamda;
	if (lamda > 0) count++;
	for (i = 2; i <= m - 1; i++) {
		if (A[i][ccy] != 0) {	
			lamda = A[i][n] / A[i][ccy];
			if (lamda > 0 && min > lamda) {
				min = lamda;
				row_index = i;
				count++;
			}
		}
	}
	if (count == 0) return 0;
	*dcy_ptr = row_index;
	return 1;
}

void timCotRa(float A[100][100], int m, int n, int dcy, int acb[], int *out_col_ptr) {
	int j;
	for (j = 1; j <= n - 1; j++) {
		if (acb[j] && A[dcy][j] == 1) {
			*out_col_ptr = j;
			return;
		}
	}
}

void capNhatCotVao_Ra(int m, int n, int in_col, int out_col, int acb_vi_tri[], float cB[], float c[], int acb[]) {
	int i, index;
	for (i = 1; i <= m - 1; i++) {
		if (acb_vi_tri[i] == out_col) {
			acb_vi_tri[i] = in_col;
			index = i;
			break;
		}
	}
	// thay đổi mảng cB
	cB[index] = c[in_col];
	acb[in_col] = 1;
	acb[out_col] = 0;
}

// biến đổi bảng để dòng vào trở thành 1 vector đơn vị
void bienDoiBang(float A[100][100], int m, int n, int ccy, int dcy) {
	int i, j;
	// biến đổi dòng chính
	float pivot = A[dcy][ccy];
	for (j = 1; j <= n; j++) {
		A[dcy][j] /= pivot;
	}
	// biến đổi các dòng còn lại # dòng chính
	for (i = 1; i <= m; i++) {
		if (i == dcy) continue;
		float a = A[i][ccy];	
		for (j = 1; j <= n; j++) {
			A[i][j] = A[i][j] - a*A[dcy][j];
		}
	}
}

int kiemTraPAToiUu(float A[100][100], int m, int n) {
	int j;
	for (j = 1; j <= n - 1; j++) {
		if (A[m][j] > 0) return 0;
	}
	return 1;
}

void xuatPACB(float A[100][100], int m, int n, int acb[]) {
	int i, j;
	for (j = 1; j <= n - 1; j++) {
		if(acb[j]) {
			for (i = 1; i <= m - 1; i++)
				if (A[i][j] == 1) {
					printf("x%d = %f\n", j, A[i][n]);
					break;
				}
		}//printf("x%d = %f\n", i, A[acb_vi_tri[i]][n]);
		else printf("x%d = 0\n", j);
	}
	printf("\nz = %f", -A[m][n]);
}

// bổ sung hàm xác định ẩn cơ bản
int xacDinhAnCoBan(float A[100][100], int m, int n, int acb[], int acb_vi_tri[]) {
	int dem_acb = 0;
    for (int j = 1; j <= n - 1; j++) {
        int dong1 = -1; // dòng chứa phần tử 1
        for (int i = 1; i <= m - 1; i++) {
            if (A[i][j] == 1 && dong1 == -1) {
                dong1 = i;
            } else if (A[i][j] != 0) {
                dong1 = -1; // Không phải vector đơn vị
                break;
            }
        }
        if (dong1 != -1) {
            acb[j] = 1;
            acb_vi_tri[dong1] = j;
            dem_acb++;
        }
    }
    
    if (dem_acb == m - 1) return 1;
    return 0;
}

void ppDonHinh(float A[100][100], int m, int n, int acb[], int acb_vi_tri[], float c[], float cB[]) {
	int i;
	printf("\n\n====================");
	printf("\nHam muc tieu la:\n");
	xuatHamMucTieu(c, n - 1); printf(" -> Max\n");
	printf("\nCac rang buoc la:\n");
	xuatRangBuoc(A, m, n);
	//đổi dấu hàm mục tiêu
	for (i = 1; i <= n - 1; i++) c[i] *= -1;
	printf("\nDoi dau ham muc tieu thanh dang Min:\n-");
	xuatHamMucTieu(c, n - 1); printf(" -> Min\n");
	printf("--------------------\n");
	// xác định ẩn cơ bản
	for (i = 1; i <= n - 1; i++) acb[i] = 0;
	if (!xacDinhAnCoBan(A, m, n, acb, acb_vi_tri)) {
		printf("\nKhong tim du cac an co ban => Bai toan khong the thuc hien.");
		return;
	}
	// cập nhật mảng cB chứa giá trị các hệ số ẩn cơ bản ở vị trí i tương ứng
	for (i = 1; i <= m - 1; i++)
		cB[i] = c[acb_vi_tri[i]];
	// cập nhật giá trị các số so sánh delta[j]	
	capNhatHangDelta(A, m, n, c, cB);
	printf("Bang don hinh ban dau:\n");
	xuatBang(A, m, n);
	printf("\nAn co ban la:\n");
	for (int i = 1; i <= n - 1; i++) {
		if (acb[i]) printf("x%d ", i);
	}
	// xuất phương án cực biên ban đầu
	printf("\n\nPhuong an cuc bien ban dau la:\n");
	xuatPACB(A, m, n, acb);
	int count = 1, ccy, dcy, out_col; // tạo các biến: đếm số lần thực hiện vòng lặp, cột chủ yếu, dòng chủ yếu, cột ra
	// tìm phương án cực biên tối ưu
	while (kiemTraPAToiUu(A, m, n) == 0) {
		timCotChuYeu(A, m, n, &ccy);
		printf("\n\nChi so cot chu yeu: %d => A%d vao", ccy, ccy);
		if (timDongChuYeu(A, m, n, ccy, &dcy) == 0) {
			printf("\nHam muc tieu khong bi chan => khong co phuong an toi uu.");
			return;
		}
		printf("\nDong chu yeu la: %d", dcy);
		timCotRa(A, m, n, dcy, acb, &out_col);
		printf("\n=> Cot ra la: A%d", out_col);
		printf("\n=> he so chu yeu la: A[%d][%d]", dcy, ccy);
		capNhatCotVao_Ra(m, n, ccy, out_col, acb_vi_tri, cB, c, acb);
		printf("\n--------------------\nBang don hinh thu %d la:\n", ++count);
		bienDoiBang(A, m, n, ccy, dcy);
		xuatBang(A, m, n);
		printf("\nAn co ban la:\n");
		for (int i = 1; i <= n - 1; i++) {
			if (acb[i]) printf("x%d ", i);
		}
		printf("\n\nPhuong an cuc bien la:\n");
		xuatPACB(A, m, n, acb);
	}
	printf("\n\n=> Day la phuong an toi uu.\n");
	printf("\n====================\n");
	printf("Vay PATU la:\n");
	xuatPACB(A, m, n, acb);
}

void nhapDuLieu(float A[100][100], int *m_ptr, int *n_ptr,int acb[], int acb_vi_tri[], float c[], float cB[]) {
	printf("Nhap so an: "); scanf("%d", n_ptr);
	printf("Nhap so phuong trinh: "); scanf("%d", m_ptr);
	(*m_ptr)++; // tạo thêm cột cho các hệ số tự do 
	(*n_ptr)++; // tạo thêm hàng cho các số kiểm tra
	
	int i;
	printf("Nhap ma tran A bieu dien he phuong trinh tuyen tinh:\n");
	
nhapMaTran(A, *m_ptr, *n_ptr); 
	for (i = 1; i <= (*n_ptr) - 1; i++) {
		printf("Nhap he so cua x%d trong ham muc tieu: ", i);
		scanf("%f", &c[i]);
	}
}

void docFile_donHinh(char s[], float A[100][100], int *m_ptr, int *n_ptr,int acb[], int acb_vi_tri[], float c[], float cB[]) {
	FILE *fptr = fopen(s, "r");
	fscanf(fptr, "%d", n_ptr); fscanf(fptr, "%d", m_ptr);
	(*m_ptr)++; (*n_ptr)++;
	
	int i, j;
	
	// Nhap ma tran A

	for (int i = 1; i <= (*m_ptr) - 1; i++) {
		for (int j = 1; j <= *n_ptr; j++) {
			fscanf(fptr, "%f", &A[i][j]);
		}
	}
	
	// Nhap he so ham muc tieu
	for (i = 1; i <= (*n_ptr) - 1; i++)
		fscanf(fptr, "%f", &c[i]);
	
	fclose(fptr);
}

int main() {
	int pp;
	printf("GIAI BAI TOAN QUY HOACH TUYEN TINH\n");
	printf("====================\n");
	printf("\nCac phuong phap:\n");
	printf("1. Hinh hoc.\n");
	printf("2. Don hinh (dang chuan tac).\n\n");
	printf("====================\n");
	printf("Chon phuong phap: "); scanf("%d", &pp);
	switch (pp) {
		case 1: {
			int n;
			float c1, c2;
			RangBuoc Rang_buoc[100];
			printf("\nNhap du lieu:\n");
			printf("1. Qua ban phim.\n");
			printf("2. Qua file.\n");
			printf("--------------------\n");
			printf("\nChon cach nhap du lieu: ");
			int nhap; scanf("%d", &nhap);
			if (nhap == 1)
				docDuLieuHinhHoc(Rang_buoc, &n, &c1, &c2);
			else if (nhap == 2) {
				docFile_HinhHoc(Rang_buoc, &n, &c1, &c2);
			}
			else {
				printf("\nCach nhap du lieu khong hop le.");
				return 1;
			}
			// Them cac rang buoc x, y >= 0
			n++;
			Rang_buoc[n - 1].a = -1; Rang_buoc[n - 1].b = 0; Rang_buoc[n - 1].c = 0; // x >= 0
			n++;
			Rang_buoc[n - 1].a = 0; Rang_buoc[n - 1].b = -1; Rang_buoc[n - 1].c = 0; // y >= 0
	
			// Su dung phuong phap hinh hoc
			printf("\nCac rang buoc la:\n");
			xuatRangBuocHinhHoc(Rang_buoc, n);
			printf("\nHam muc tieu la:\nz = ");
			xuatHamMucTieuHinhHoc(c1, c2); printf("\n\n");
			ppHinhHoc(Rang_buoc, n, c1, c2);
			
			break;
		}			
		case 2: {
			int i, j;
			float A[100][100];
			int m, n;
			int acb[100], acb_vi_tri[100];
			float c[100], cB[100]; // cB[i] = c[acb_vi_tri[i]]
			char s[100];
			printf("\nNhap du lieu:\n");
			printf("1. Qua ban phim.\n");
			printf("2. Qua file.\n");
			printf("--------------------\n");
			printf("\nChon cach nhap du lieu: ");
			int nhap; scanf("%d", &nhap);
			if (nhap == 1)
				nhapDuLieu(A, &m, &n, acb, acb_vi_tri, c, cB);
			else if (nhap == 2) {	
				printf("Nhap ten file: "); scanf("%s", s);
				docFile_donHinh(s, A, &m, &n, acb, acb_vi_tri, c, cB);
			}
			else {
				printf("\nCach nhap du lieu khong hop le.");
				return 1;
			}
			ppDonHinh(A, m, n, acb, acb_vi_tri, c, cB);
			break;
		}
		default:
			printf("Phuong phap khong hop le.");
			return 1;
	}
	return 0;
}