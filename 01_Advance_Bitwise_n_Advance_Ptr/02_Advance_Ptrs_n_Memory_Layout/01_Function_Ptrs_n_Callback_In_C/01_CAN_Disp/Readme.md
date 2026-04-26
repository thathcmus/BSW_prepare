Hello, friend, this is a very precise mindset! There is no better way to break down the complexity of function pointers than by putting your hands on the keyboard and structuring them yourself. In the world of BSW (Basic Software), reading and understanding is one thing, but designing a memory-safe architecture by hand is another level.

To help you test your skills, I am presenting a classic problem every Automotive BSW engineer must solve: **Designing a message router (PDU Router) for a CAN communication network.**

Read the requirements carefully, write the C code on your own machine (you may use any compiler such as GCC, VS Code, or an online IDE), then submit the complete source code here. I will act as a System Architect to review and grade your code according to industry standards (MISRA-C and performance optimization).

---

## PRACTICAL TEST: CAN MESSAGE DISPATCHER (O(1) ROUTING)

### 1. System Context
You are writing the BSW layer for a CAN controller. The hardware will generate an interrupt each time a CAN message arrives.
Each CAN message includes:
* **ID:** Assume the current system only supports IDs from `0` to `4` (a maximum of 5 message types).
* **Payload:** An array of up to 8 bytes.
* **Length:** The number of valid bytes in the payload (from 1 to 8).

The Application Layer above has 2 independent modules:
1.  **Engine Control:** Only cares about messages with `ID = 0`.
2.  **Brake System:** Only cares about messages with `ID = 2`.

### 2. Anti-Pattern
Under no circumstances should you write the interrupt handler like a junior developer as follows:
```c
void CAN_Hardware_Interrupt_Handler(uint8_t rx_id, uint8_t* rx_data, uint8_t rx_len) {
    // ARCHITECTURAL VIOLATION: The BSW layer must not know what Engine or Brake are!
    if (rx_id == 0) { Engine_Process(rx_data, rx_len); }
    else if (rx_id == 2) { Brake_Process(rx_data, rx_len); }
    // ...
}
```

### 3. Requirements

Divide your C file clearly into two parts: **MCAL/BSW LAYER** and **APPLICATION LAYER**.

**MCAL/BSW Layer tasks:**
1.  Define a function pointer type (callback type) suitable for handling a CAN message (accepting `uint8_t* data` and `uint8_t len`).
2.  Create an array of function pointers (lookup table) to manage up to 5 IDs (`0` through `4`). Initialize this array to `NULL` by default.
3.  Implement `CAN_Register_Callback(...)` so the Application Layer can register its handler for the correct ID.
4.  Implement `CAN_Hardware_Interrupt_Handler(...)`. This function must execute in O(1) time, without using `if-else` or `switch-case` to check the ID. It should automatically index the table and call the correct callback.

**Application Layer tasks:**
1.  Implement `Engine_Handler` and `Brake_Handler` (they only need to `printf` the ID and the first data byte to prove they ran correctly).
2.  In `main()`, register those two handlers with the CAN system.
3.  In `main()`, simulate hardware interrupts by calling `CAN_Hardware_Interrupt_Handler` with different IDs (try `ID = 0`, `ID = 2`, and `ID = 1` which is not registered).

---

### 4. Code Review Criteria

When you submit code, I will inspect three critical points:
* **Encapsulation:** Does the MCAL layer leak Application logic?
* **Performance:** Does your interrupt handler truly achieve O(1) and avoid `switch-case`?
* **Memory Safety (VERY IMPORTANT):** What happens if the hardware is noisy and sends `ID = 99`? What happens if `ID = 1` arrives but the Application has not registered a callback yet (`NULL` pointer)? If your code crashes (segfaults) in these cases → **0 points immediately**.

Are you ready to open the editor and structure these blocks? Submit your C source code here when finished.


==============================================================

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