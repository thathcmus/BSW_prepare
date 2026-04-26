Chào bạn, một tư duy cực kỳ chuẩn xác! Không có cách nào bẻ gãy sự phức tạp của Con trỏ hàm tốt hơn việc trực tiếp đặt tay lên bàn phím và tự cấu trúc nó. Trong thế giới BSW (Basic Software), đọc hiểu là một chuyện, nhưng tự tay thiết kế ra một kiến trúc an toàn bộ nhớ (Memory-safe) lại là một đẳng cấp khác.

Để giúp bạn thử lửa, tôi sẽ đưa ra một bài toán kinh điển mà mọi kỹ sư Automotive BSW đều phải vượt qua: **Thiết kế bộ định tuyến bản tin (PDU Router) cho mạng giao tiếp CAN.**

Hãy đọc kỹ yêu cầu dưới đây, tự viết code C trên máy tính của bạn (có thể dùng bất kỳ compiler nào như GCC, VS Code, hoặc online IDE), sau đó gửi toàn bộ mã nguồn lên đây. Tôi sẽ đóng vai trò là một System Architect để review (đánh giá) và chấm điểm code của bạn theo tiêu chuẩn công nghiệp (MISRA-C và Tối ưu hóa hiệu năng).

---

## BÀI KIỂM TRA THỰC CHIẾN: CAN MESSAGE DISPATCHER (O(1) ROUTING)

### 1. Bối Cảnh Hệ Thống (System Context)
Bạn đang viết lớp BSW cho một bộ điều khiển CAN (CAN Controller). Hệ thống phần cứng sẽ sinh ra một ngắt (Interrupt) mỗi khi có một bản tin CAN bay vào. 
Mỗi bản tin CAN bao gồm:
* **ID (Định danh):** Giả sử hệ thống hiện tại chỉ hỗ trợ các ID từ `0` đến `4` (Tối đa 5 loại bản tin).
* **Payload (Dữ liệu):** Một mảng số nguyên tối đa 8 byte.
* **Length (Độ dài):** Số lượng byte hợp lệ trong Payload (từ 1 đến 8).

Tầng Ứng dụng (Application Layer) bên trên có 2 module độc lập: 
1.  **Engine Control (Điều khiển động cơ):** Chỉ quan tâm đến bản tin có `ID = 0`.
2.  **Brake System (Hệ thống phanh):** Chỉ quan tâm đến bản tin có `ID = 2`.

### 2. Nỗi Đau Cần Tránh (Anti-Pattern)
Tuyệt đối **KHÔNG** được viết hàm ngắt theo kiểu Junior như sau:
```c
void CAN_Hardware_Interrupt_Handler(uint8_t rx_id, uint8_t* rx_data, uint8_t rx_len) {
    // VI PHẠM TƯ DUY KIẾN TRÚC: Tầng BSW không được phép biết Engine hay Brake là cái gì!
    if (rx_id == 0) { Engine_Process(rx_data, rx_len); }
    else if (rx_id == 2) { Brake_Process(rx_data, rx_len); }
    // ...
}
```

### 3. Yêu Cầu Thiết Kế (Requirements)

Bạn hãy phân chia file C của mình thành 2 phần rõ rệt: **TẦNG MCAL/BSW** và **TẦNG APPLICATION**.

**Nhiệm vụ tại Tầng MCAL/BSW:**
1.  Định nghĩa một kiểu dữ liệu Con trỏ hàm (Callback Type) phù hợp để xử lý một bản tin CAN (nhận vào `uint8_t* data` và `uint8_t len`).
2.  Tạo một mảng các con trỏ hàm (Lookup Table) để quản lý tối đa 5 ID (từ 0 đến 4). Mặc định khởi tạo mảng này bằng `NULL`.
3.  Viết hàm `CAN_Register_Callback(...)` để Tầng Application có thể đăng ký hàm xử lý của họ vào đúng ID tương ứng.
4.  Viết hàm `CAN_Hardware_Interrupt_Handler(...)`. Hàm này có thời gian thực thi $O(1)$, không dùng rẽ nhánh `if-else/switch-case` để kiểm tra ID. Nó tự động tra mảng và gọi đúng Callback.

**Nhiệm vụ tại Tầng Application:**
1.  Viết hàm `Engine_Handler` và `Brake_Handler` (chỉ cần `printf` ra ID và byte dữ liệu đầu tiên để chứng minh nó chạy đúng).
2.  Trong hàm `main()`, thực hiện việc Đăng ký (Register) 2 hàm trên vào hệ thống CAN.
3.  Trong hàm `main()`, giả lập phần cứng bắn ngắt bằng cách gọi trực tiếp hàm `CAN_Hardware_Interrupt_Handler` với các ID khác nhau (Thử gọi `ID = 0`, `ID = 2`, và thử một `ID = 1` chưa được đăng ký).

---

### 4. Tiêu Chí Chấm Điểm (Code Review Criteria)

Khi bạn nộp code, tôi sẽ dùng "kính lúp" soi vào 3 điểm tử huyệt sau:
* **Tính Đóng gói (Encapsulation):** Tầng MCAL của bạn có bị "nhiễm" logic của tầng App không?
* **Hiệu năng (Performance):** Hàm ngắt của bạn có thực sự đạt $O(1)$ và loại bỏ được `switch-case` không?
* **An toàn Bộ nhớ (Memory Safety - RẤT QUAN TRỌNG):** Điều gì xảy ra nếu phần cứng bị nhiễu và gửi đến một `ID = 99`? Điều gì xảy ra nếu `ID = 1` bay tới nhưng Application chưa đăng ký Callback nào (con trỏ đang là `NULL`)? Nếu code của bạn bị Crash (Segmentation Fault) ở các trường hợp này $\rightarrow$ **0 điểm lập tức**.

Bạn đã sẵn sàng mở Editor lên và cấu trúc các khối lệnh này chưa? Hãy gửi mã nguồn C của bạn lên đây khi hoàn tất nhé.