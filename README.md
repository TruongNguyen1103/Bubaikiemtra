# Bài 5 – Đồng bộ hóa tiến trình, tiểu trình (Hệ điều hành)

Bài thực hành mục 5.4 – Trường ĐH Công nghệ Thông tin – ĐHQG TP.HCM.
MSSV: **CT240041**

## Cấu trúc thư mục

| Thư mục | Nội dung |
|---|---|
| `bai1_ban_hang/` | Đồng bộ 2 process bán hàng (A) / sản xuất (B) bằng semaphore, đảm bảo `sells <= products <= sells + K` với `K = 2 số cuối MSSV + 10 = 51` |
| `bai2_mang_toan_cuc/` | Mảng toàn cục `a[]` dùng chung giữa 2 thread (1 thread thêm phần tử ngẫu nhiên, 1 thread lấy phần tử bất kỳ). Có bản **chưa đồng bộ** để thấy lỗi race condition và bản **đã đồng bộ** bằng semaphore |
| `bai3_race_condition/` | 2 thread cùng tăng biến `x` dùng chung không đồng bộ – minh họa lỗi mất cập nhật (lost update) |
| `bai4_mutex_fix/` | Sửa lỗi của bài 3 bằng `pthread_mutex` |

## Yêu cầu môi trường

- Hệ điều hành Linux
- `gcc` đã cài đặt

## Cách build & chạy

Mỗi bài có 1 file `.c`, build bằng lệnh chung:

```bash
gcc -o output_name file_name.c -lpthread -lrt
./output_name
```

Ví dụ với bài 1:

```bash
cd bai1_ban_hang
gcc -o bai1 bai1_ban_hang.c -lpthread -lrt
./bai1
```

Các chương trình đều chạy vòng lặp vô hạn (`while(1)`) để minh họa liên tục — nhấn `Ctrl + C` để dừng.

## Ghi chú

- `bai2_mang_toan_cuc/bai2_khong_dong_bo.c`: chạy thử bản này trước để quan sát lỗi (số đếm `count` sai, có thể truy xuất mảng không hợp lệ) do 2 thread tranh chấp tài nguyên chung mà không có cơ chế đồng bộ.
- `bai2_mang_toan_cuc/bai2_dong_bo.c`: bản đã sửa bằng 1 semaphore nhị phân đóng vai trò mutex.
- `bai3_race_condition/bai3_race_condition.c` và `bai4_mutex_fix/bai4_mutex_fix.c`: so sánh trực tiếp kết quả trước/sau khi đồng bộ bằng `pthread_mutex_lock/unlock`.
