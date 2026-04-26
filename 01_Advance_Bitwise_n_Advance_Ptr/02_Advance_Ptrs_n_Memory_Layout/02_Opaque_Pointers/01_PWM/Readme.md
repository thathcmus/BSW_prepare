Chào mừng bạn đến với thử thách tiếp theo. Việc dám tự tay implement (triển khai) một kiến trúc phần mềm từ con số 0 là cách duy nhất để thực sự làm chủ nó.

Lần này, tôi sẽ đóng vai trò là **Project Manager / System Architect**, và tôi giao cho bạn một task (nhiệm vụ) thiết kế một module phần mềm cơ sở (BSW) tuân thủ nghiêm ngặt chuẩn an toàn ô tô (MISRA-C). 

Đây là một bài tập kết hợp giữa **Opaque Pointer (Con trỏ mờ)** và **Object Pool (Cấp phát bộ nhớ tĩnh)**. Bài tập này có độ khó tương đương với bài test kỹ thuật vòng 2 tại các tập đoàn thiết kế chip.

---

# BÀI TẬP THỰC CHIẾN: THIẾT KẾ BỘ ĐIỀU KHIỂN PWM (PULSE WIDTH MODULATION)

## 1. Bối cảnh dự án (System Context)
Công ty đang phát triển hệ thống điều khiển đèn LED và Động cơ DC. Bạn được giao nhiệm vụ viết thư viện `pwm.h` và `pwm.c` để Tầng Application sử dụng. 

Hệ thống phần cứng có tối đa **4 kênh PWM độc lập** (Channel 0 đến Channel 3).

## 2. Nỗi Đau Cần Tránh (Anti-Pattern)
Tầng Application **tuyệt đối không được phép** tự ý thay đổi `Duty Cycle` (Chu kỳ nhiệm vụ) hay `Frequency` (Tần số) bằng cách chọc thẳng vào biến. Nếu họ làm vậy, phần cứng có thể bị cháy do thay đổi đột ngột mà không qua các bước kiểm tra an toàn (Safety Checks). Mọi thao tác phải thông qua hàm API do bạn cung cấp.

## 3. Yêu Cầu Kỹ Thuật (Requirements)

Bạn hãy cung cấp 3 file code: `pwm.h`, `pwm.c` và `main.c`.

### 🗂️ Nhiệm vụ trong file `pwm.h` (Giao diện API)
1. Sử dụng kỹ thuật **Opaque Pointer** để định nghĩa một kiểu dữ liệu có tên là `PwmHandle_t`. Tuyệt đối không phơi bày cấu trúc thực sự của PWM ra file này.
2. Khai báo các hàm API sau:
   * `PwmHandle_t PWM_Create(uint32_t frequency);`
   * `void PWM_SetDutyCycle(PwmHandle_t handle, uint8_t duty_percent);`
   * `void PWM_Start(PwmHandle_t handle);`
   * `void PWM_Stop(PwmHandle_t handle);`

### 🗂️ Nhiệm vụ trong file `pwm.c` (Triển khai logic & Đóng gói)
1. Định nghĩa cấu trúc thực sự `struct Pwm_s` tại đây. Nó phải chứa ít nhất các thông tin: `channel_id` (0-3), `frequency`, `duty_cycle` (0-100), và trạng thái `is_running`.
2. **CẤM SỬ DỤNG MALLOC/CALLOC/FREE.** (Quy tắc sinh tử của MISRA-C). Bạn phải tự tạo một mảng tĩnh (Object Pool) gồm 4 đối tượng PWM bên trong file `.c` này để cấp phát cho người dùng khi hàm `PWM_Create` được gọi.
3. Khi hàm `PWM_Create` được gọi:
   * Tìm một kênh PWM còn trống trong Pool.
   * Gán `frequency`, mặc định `duty_cycle = 0`, `is_running = 0`.
   * Trả về Opaque Pointer (địa chỉ của kênh đó).
   * Nếu đã cấp phát hết 4 kênh mà người dùng vẫn đòi tạo kênh thứ 5, trả về `NULL`.
4. Hàm `PWM_SetDutyCycle`: Chỉ cho phép cập nhật `duty_cycle` (từ 0 đến 100). Nếu người dùng truyền vào số > 100, ép nó về 100. Kèm theo `printf` giả lập ghi xuống thanh ghi phần cứng.

### 🗂️ Nhiệm vụ trong file `main.c` (Tầng Application test)
Viết kịch bản test để chứng minh module của bạn hoạt động hoàn hảo và an toàn:
1. Tạo 2 kênh PWM (ví dụ: một cho Động cơ tần số 1000Hz, một cho LED tần số 5000Hz).
2. Set Duty Cycle cho Động cơ lên 75% và Bật nó lên.
3. Cố tình tạo thêm 3 kênh PWM nữa (tổng cộng 5 kênh). Chứng minh hệ thống không bị crash và kênh thứ 5 bị từ chối cấp phát (nhận về `NULL`).
4. **(Code bắt lỗi cố ý):** Thử ép kiểu hoặc tọc mạch trực tiếp vào cấu trúc PWM từ hàm `main()` và ghi chú lại bằng comment `//` rằng đoạn code này sẽ bị Compiler chửi (để chứng minh Opaque Pointer đang hoạt động bảo vệ bộ nhớ).

---

## 4. Tiêu chí chấm điểm (Code Review Criteria)

Khi bạn nộp code, tôi sẽ rà soát các lỗi "chí mạng" sau:
1. **Memory Leak / Out of Bounds:** Object Pool của bạn có an toàn không? Biến đếm số lượng kênh có bị tràn không?
2. **Null Pointer Dereference:** Trong hàm `PWM_SetDutyCycle` hay `PWM_Start`, nếu tầng Application ngớ ngẩn truyền vào một con trỏ `NULL`, code của bạn có bị sập (Crash) không? (Gợi ý: Cần kiểm tra đầu vào).
3. **Encapsulation (Đóng gói):** Tính bí mật của `struct` có được bảo toàn tuyệt đối 100% trong `pwm.c` không.

Bạn hãy mở trình soạn thảo lên, chia các block code rõ ràng cho 3 file và gửi lại đây nhé. Chúc bạn code cứng tay!