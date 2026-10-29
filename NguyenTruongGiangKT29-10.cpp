#include <iostream>
#include <string>

using namespace std;

struct HangHoa {
    string maHangHoa;
    string tenHangHoa;
    string ngayXuat;
    float giaXuat;
};

void nhapHangHoa(HangHoa &hh) {
    cout << "Nhap ma hang hoa: ";
    cin >> hh.maHangHoa;
    cin.ignore();
    cout << "Nhap ten hang hoa: ";
    getline(cin, hh.tenHangHoa);
    cout << "Nhap ngay xuat (VD: 10/10/2000): ";
    getline(cin, hh.ngayXuat);
    cout << "Nhap gia xuat (trieu dong): ";
    cin >> hh.giaXuat;
}

void nhapDanhSach(HangHoa ds[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << "\n--- Nhap thong tin hang hoa thu " << i + 1 << " ---" << endl;
        nhapHangHoa(ds[i]);
    }
}

void xuatHangHoa(const HangHoa &hh) {
    cout << "Ma hang: " << hh.maHangHoa 
         << " | Ten hang: " << hh.tenHangHoa 
         << " | Ngay xuat: " << hh.ngayXuat 
         << " | Gia xuat: " << hh.giaXuat << " trieu dong" << endl;
}

void xuatDanhSach(HangHoa ds[], int n) {
    for (int i = 0; i < n; ++i) {
        xuatHangHoa(ds[i]);
    }
}

void quickSort(HangHoa ds[], int left, int right) {
    if (left >= right) return;
    
    int i = left, j = right;
    float pivot = ds[(left + right) / 2].giaXuat;

    while (i <= j) {
        while (ds[i].giaXuat < pivot) i++;
        while (ds[j].giaXuat > pivot) j--;
        
        if (i <= j) {
            HangHoa temp = ds[i];
            ds[i] = ds[j];
            ds[j] = temp;
            i++;
            j--;
        }
    }
    
    quickSort(ds, left, j);
    quickSort(ds, i, right);
}

void timKiemNhiPhan(HangHoa ds[], int n, float X) {
    int left = 0, right = n - 1;
    bool found = false;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (ds[mid].giaXuat == X) {
            int l = mid, r = mid;
            while (l >= 0 && ds[l].giaXuat == X) l--;
            while (r < n && ds[r].giaXuat == X) r++;

            for (int i = l + 1; i < r; i++) {
                xuatHangHoa(ds[i]);
            }
            found = true;
            break;
        } 
        else if (ds[mid].giaXuat < X) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }

    if (!found) {
        cout << "-> Khong tim thay hang hoa nao co gia " << X << " trieu dong." << endl;
    }
}

int main() {
    int n;
    cout << "Nhap so luong hang hoa (n): ";
    cin >> n;

    HangHoa* ds = new HangHoa[n];

    nhapDanhSach(ds, n);
    cout << "\n===== DANH SACH HANG HOA VUA NHAP =====" << endl;
    xuatDanhSach(ds, n);

    quickSort(ds, 0, n - 1);
    cout << "\n===== DANH SACH SAU KHI SAP XEP TANG DAN THEO GIA XUAT =====" << endl;
    xuatDanhSach(ds, n);

    float X;
    cout << "\nNhap gia xuat X can tim (trieu dong): ";
    cin >> X;
    cout << "\n===== KET QUA TIM KIEM HANG HOA CO GIA " << X << " TRIEU DONG =====" << endl;
    timKiemNhiPhan(ds, n, X);

    delete[] ds;
    
    return 0;
}
