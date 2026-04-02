# Báo cáo: Tìm hiểu công cụ hỗ trợ LLMs và tạo UI

## 1. Tìm hiểu Ollama và so sánh với LMStudio:

Ollama là một nền tảng mã nguồn mở cho phép chạy các mô hình ngôn ngữ lớn (LLMs) như Llama 3, Mistral, hay Phi-3 trực tiếp trên máy tính cá nhân một cách đơn giản nhất.

Các gói cung cấp & Nhu cầu sử dụng:

- Local Execution (Cá nhân): Chạy offline hoàn toàn, bảo mật dữ liệu tuyệt đối. Phù hợp cho việc học tập, thử nghiệm prompt mà không tốn phí API.
- Docker/Self-hosted: Phù hợp cho nhóm dự án cần triển khai một "AI Server" nội bộ để nhiều người cùng truy cập qua API.

Đề xuất cho môn học: Sử dụng Ollama để chạy các mô hình nhỏ (như Phi-3 3.8B hoặc Llama 3 8B) để hỗ trợ giải thích thuật toán, kiểm tra code Python/C++ ngay trên máy local mà không cần kết nối internet.

So sánh nhanh Ollama vs. LMStudio

|Tiêu chí|Ollama|LMStudio|
|---|---|---|
|Giao diện|Dòng lệnh (CLI) là chính|Giao diện đồ họa (GUI) rất trực quan|
|Quản lý mô hình|Đơn giản, dùng lệnh `ollama run`|Cho phép tùy chỉnh sâu các thông số kỹ thuật (Temperature, Context Length)|
|Hiệu suất|Nhẹ, tối ưu cực tốt cho macOS (Apple Silicon) và Linux|Đầy đủ nhưng chiếm nhiều tài nguyên hệ thống hơn để duy trì GUI|
|Tính ứng dụng|Phù hợp để tích hợp vào code (Backend, API)|Phù hợp để chat và trải nghiệm thử các mô hình mới|

## 2. Sử dụng Ollama với Google Colab

Để sử dụng Ollama trên Colab (môi trường không có sẵn Ollama), chúng ta thường dùng các cách sau:

1. Sử dụng Ngrok hoặc Cloudflare Tunnel: Cài đặt Ollama vào runtime của Colab, sau đó dùng tunnel để tạo một public URL kết nối với API của nó.

2. Sử dụng thư viện Python (như colab-xterm): Mở terminal ngay trong Colab để chạy lệnh cài đặt Ollama trực tiếp.

Phân tích & So sánh:
- Trình duyệt trực tiếp: Tiện lợi nhưng giới hạn thời gian runtime (thường bị ngắt sau một khoảng thời gian không tương tác)
- Kết nối API: Cho phép dùng GPU mạnh mẽ của Google để chạy các mô hình nặng mà máy cá nhân không gánh nổi

Kết luận: Nếu máy bạn có GPU yếu, hãy dùng Ollama trên Colab qua Ngrok. Nếu chỉ cần chạy các model nhẹ để học tập, nên dùng Ollama trực tiếp trên máy local để ổn định nhất.

## 3. Google Colab trên VS Code

Thao tác cơ bản:

1. Cài đặt Extension Jupyter trên VS Code.
2. Mở bảng lệnh (Ctrl+Shift+P), chọn "Jupyter: Specify Jupyter Server for Connections".
3. Chọn "Existing" và dán đường dẫn URL từ Google Colab (lấy từ mục "Connect to a local runtime" hoặc sử dụng Token).

So sánh VS Code vs. Trình duyệt:
- VS Code: Hỗ trợ IntelliSense (gợi ý code) mạnh mẽ, dễ quản lý file local, giao diện quen thuộc cho dân lập trình. Tuy nhiên, thiết lập ban đầu phức tạp hơn.
- Trình duyệt: Không cần cài đặt, dễ dàng chia sẻ file .ipynb cho bạn bè cùng nhóm, tích hợp sẵn Google Drive.
- Lựa chọn: Nên dùng VS Code khi viết code dự án phức tạp; dùng trình duyệt khi cần ghi chép nhanh hoặc nộp bài tập.

## 4. Gradio và Streamlit trong xây dựng ứng dụng

Cả hai đều là thư viện Python giúp tạo giao diện người dùng (UI) cho các dự án AI/Data Science một cách nhanh chóng.

Gradio
- Ứng dụng: Thích hợp tạo các bản Demo nhanh cho mô hình (ví dụ: một ô nhập văn bản và một ô trả kết quả từ chatbot).
- Ngữ cảnh: Dùng trong các buổi thuyết trình ngắn, cần giao diện cực kỳ đơn giản để test chức năng của mô hình AI.

Streamlit
- Ứng dụng: Thích hợp xây dựng các Dashboard dữ liệu phức tạp, có nhiều bảng biểu, thanh trượt và nhiều trang.
- Ngữ cảnh: Dùng khi làm đồ án môn học cuối kỳ, cần một ứng dụng hoàn chỉnh có cả phần xử lý dữ liệu và phần hiển thị kết quả chuyên nghiệp.
