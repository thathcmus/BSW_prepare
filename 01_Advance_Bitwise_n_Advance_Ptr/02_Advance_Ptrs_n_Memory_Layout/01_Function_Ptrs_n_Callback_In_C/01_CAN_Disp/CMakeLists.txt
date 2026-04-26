# Khai báo file thực thi độc lập cho bài CAN
# Cú pháp: add_executable(<Tên_file_exe_muốn_tạo> <Các_file_source_code>)
add_executable(CAN_App 
    can_main.c 
    can_mcal_bsw.c 
    can_app.c
)

target_include_directories(CAN_App PRIVATE .)