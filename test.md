# Báo cáo: Tìm hiểu cơ sở dữ liệu, công cụ trực quan hóa và ứng dụng LLM trong việc lập kế hoạch

## 1. Công cụ trực quan hóa Mermaid và tích hợp hệ thống

**Mermaid.js**: Là công cụ mã nguồn mở sử dụng cú pháp dựa trên văn bản để tạo biểu đồ. Điều này giúp cho việc quản lý phiên bản (giống như `git`) dễ dàng hơn vì thực chất biểu đồ chính là các dòng code.

Các loại biểu đồ tiêu biểu:

- **Flowcharts**: Mô tả thuật toán hoặc quy trình nghiệp vụ (sử dụng `graph TD` hoặc `graph LR`)
- **Sequence Diagrams**: Đặc biệt hữu ích trong việc mô tả tương tác giữa các Object/Service trong lập trình.
- **ER Diagrams**: Đóng vai trò quan trọng trong việc phân tích, thiết kế Database (thực thể - quan hệ)
- **Mind Maps**: Hỗ trợ hệ thống hóa ý tưởng nhanh chóng.

Tích hợp **Notion**: Notion hỗ trợ Native Mermaid. Bằng cách sử dụng khối mã (code block) và chọn ngôn ngữ Mermaid, người dùng có thể chỉnh sửa trực tiếp nội dung văn bản và xem kết quả hiển thị ngay lập tức mà không cần export ảnh từ bên ngoài.

## 2. Định dạng dữ liệu và sức mạnh xử lý của Pandas

Một số loại định dạng dữ liệu được sử dụng phổ biến:

- **CSV (Comma-Seperated Values)**: Định dạng phẳng, dung lượng tối ưu cho các bảng dữ liệu đơn giản. Tuy nhiên, không hỗ trợ kiểu dữ liệu phức tạp hoặc phân cấp.
- **JSON (JavaScript Object Notation)**: Hỗ trợ cấu trúc dữ liệu lồng nhau hoặc phân cấp, phù hợp cho API hiện đại. Dễ đọc với người dùng nhưng chiếm nhiều dung lượng hơn CSV.
- **JSONL (JSON Lines)**: Giải pháp cho **Big Data**. Thay vì đọc toàn bộ một mảng JSON với kích thước khổng lồ vào RAM (có thể gây crash), JSONL cho phép đọc và xử lý theo từng dòng (streaming), rất quan trọng khi làm việc với tập dữ liệu lên đến hàng triệu dòng.

Thư viện Pandas (Python):

- Xử lý dữ liệu: Pandas chuyển đổi các định dạng trên thành **DataFrame** (một dạng cấu trúc bảng xử lý khá tốt)
- Tính năng chính: Dùng `df.filter()` để lọc dữ liệu, `df.sort_values()` để sắp xếp và `df.describe()` để tạo báo cáo thống kê nhanh (min, max, mean, std). Các phương thức trên đều là những tính năng vô cùng quan trọng và cơ bản cho bước tiền xử lý dữ liệu trước khi đưa chúng vào các mô hình máy học.

## 3. Khai thác Kaggle Datasets cho du lịch Việt Nam

Ý nghĩa: Kaggle không chỉ là nơi lưu trữ mà còn là cộng đồng đánh giá dữ liệu thông qua "Usability Score".

Đề xuất Dataset phù hợp:...?


## 4. Tối ưu hóa Context Window trong ứng dụng LLM

**Context Window** (Cửa sổ ngữ cảnh): Mỗi Model (như GPT-4 hay Gemini) có một giới hạn token nhất định (ví dụ 32k, 128k hoặc hơn). Nếu nạp toàn bộ Dataset vượt quá giới hạn này, Model sẽ "quên" các thông tin quan trọng ở đầu prompt hoặc không thể xử lý.

Giải pháp đề xuất cho bài toán lập kế hoạch:

- Không nên: Đưa trực tiếp toàn bộ file CSV/JSON vào prompt. Điều này làm tăng chi phí (token) và gây nhiễu cho AI.
- Nên (Quy trình tiền xử lý):
  - Trích xuất đặc trưng (Feature Extraction): Dùng Pandas để lọc ra những thông tin thực sự cần thiết (ví dụ: chỉ lấy các địa điểm ở Hà Nội nếu người dùng muốn đi Hà Nội).
  - RAG (Retrieval-Augmented Generation): Chuyển đổi dataset thành Vector Database. Khi người dùng hỏi, hệ thống chỉ lấy ra các "mẩu" dữ liệu liên quan nhất để đưa vào Context Window.
  - Prompt Engineering: Cung cấp cho LLM cấu trúc dữ liệu dưới dạng tóm tắt (Metadata) kèm theo một vài ví dụ mẫu thay vì toàn bộ dữ liệu thô.
