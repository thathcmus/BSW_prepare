cmake_minimum_required(VERSION 3.10)

# Tên của toàn bộ không gian làm việc (Workspace)
project(BSW_Workspace C)

# (Tùy chọn) Gom tất cả các file .exe sau khi build vào chung một thư mục bin/ cho gọn
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- KHAI BÁO CÁC MODULE CON ---
# Phải ghi đường dẫn tương đối từ thư mục 04_BSW vào đến tận nơi chứa CMake con
add_subdirectory(01_Advance_Bitwise_n_Advance_Ptr/02_Advance_Ptrs_n_Memory_Layout/01_Function_Ptrs_n_Callback_In_C/01_CAN_Disp)

add_subdirectory(01_Advance_Bitwise_n_Advance_Ptr/02_Advance_Ptrs_n_Memory_Layout/01_Function_Ptrs_n_Callback_In_C/02_LIN)