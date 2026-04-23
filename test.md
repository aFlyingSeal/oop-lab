# Báo cáo: Tìm hiểu công nghệ: Firebase và FastAPI

## 1. Tổng quan về Google Firebase

**Google Firebase** là một nền tảng phát triển ứng dụng di động và web (BaaS - Backend as a Service) do Google cung cấp. Nó giúp lập trình viên xây dựng ứng dụng nhanh chóng mà không cần tốn quá nhiều công sức thiết lập và quản lý hạ tầng server phức tạp.

Các nhóm dịch vụ chính:

- **Xây dựng (Build)**: Authentication, Cloud Firestore, Realtime Database, Cloud Functions, Storage.
- **Phát hành & Giám sát (Release & Monitor)**: Crashlytics, Analytics, Performance Monitoring, App Distribution.
- **Tương tác (Engage)**: Cloud Messaging (FCM), Remote Config, Dynamic Links.

## 2. Chi tiết dịch vụ Firebase Authentication

Dịch vụ này cung cấp các giải pháp xác thực người dùng (đăng nhập bằng Email/Password, Google, Facebook, Apple, Phone...)

Cơ chế xác thực bằng Firebase ID Token (Frontend + Backend API)

Khi kết hợp ứng dụng Frontend với một Backend API riêng (ví dụ: FastAPI), quy trình diễn ra như sau:

1. Đăng nhập (Frontend): Người dùng nhập thông tin trên giao diện. Frontend gửi thông tin đến Firebase Auth.
2. Nhận ID Token: Nếu thành công, Firebase trả về một ID Token (dưới dạng JWT - JSON Web Token) cho Frontend.
3. Gửi yêu cầu (Frontend → Backend): Khi gọi API, Frontend đính kèm ID Token này vào Header (thường là Authorization: Bearer <ID_TOKEN>).
4. Xác thực (Backend): Backend sử dụng Firebase Admin SDK để kiểm tra tính hợp lệ của Token này (check chữ ký, thời hạn).
5. Phản hồi: Nếu Token hợp lệ, Backend xử lý logic và trả kết quả về cho người dùng.

## 3. Chi tiết dịch vụ Firebase Cloud Firestore

Cloud Firestore là một cơ sở dữ liệu NoSQL linh hoạt, có khả năng mở rộng cực cao và dữ liệu được đồng bộ hóa theo thời gian thực.

Mô hình Collection - Document

- Document (Tài liệu): Đơn vị dữ liệu cơ bản, lưu trữ dưới dạng các cặp key-value (tương tự JSON).
- Collection (Bộ sưu tập): Là các "thùng chứa" các Document. Một Collection không chứa dữ liệu trực tiếp mà chỉ chứa các Document.
- Cấu trúc: Có thể lồng nhau (Collection > Document > Sub-collection > Document).

Khả năng Query dữ liệu theo Field

Firestore cho phép truy vấn linh hoạt nhờ vào cơ chế đánh chỉ mục (indexing):

- Lọc dữ liệu: Sử dụng các toán tử so sánh như ==, <, >, <=, >=, array-contains,... trên các trường (fields) cụ thể của Document.
- Kết hợp: Có thể thực hiện các truy vấn phức tạp (Compound Queries) trên nhiều field cùng lúc.
- Hiệu suất: Tốc độ truy vấn phụ thuộc vào kích thước tập kết quả trả về, không phụ thuộc vào tổng dung lượng dữ liệu hiện có trong Database.

## 4. Tìm hiểu về FastAPI và Hệ sinh thái ASGI

**FastAPI là gì?**

FastAPI là một Web Framework hiện đại, hiệu năng cao để xây dựng API với Python 3.8+. Nó dựa trên chuẩn Python type hints, giúp tự động tạo tài liệu (Swagger UI) và kiểm tra dữ liệu đầu vào.

Sử dụng cơ bản

Để sử dụng FastAPI, ta định nghĩa các "Path Operations":

```python
from fastapi import FastAPI

app = FastAPI()

@app.get("/")
def read_root():
    return {"Hello": "World"}
```

**Chuẩn ASGI và Server ASGI**

- ASGI (Asynchronous Server Gateway Interface): Là tiêu chuẩn kế thừa của WSGI. Nó cho phép các ứng dụng Python xử lý các kết nối bất đồng bộ (Asynchronous), hỗ trợ tốt cho WebSockets và HTTP/2.
- Server ASGI: Là phần mềm máy chủ có khả năng chạy các ứng dụng tuân thủ chuẩn ASGI. Khác với server truyền thống, nó không bị chặn (blocking) khi xử lý nhiều yêu cầu cùng lúc.

**Uvicorn là gì?**

Uvicorn là một trình thực thi Server ASGI cực nhanh cho Python. Nó được sử dụng để "chạy" ứng dụng FastAPI. Lệnh phổ biến để khởi chạy là:
uvicorn main:app --reload
