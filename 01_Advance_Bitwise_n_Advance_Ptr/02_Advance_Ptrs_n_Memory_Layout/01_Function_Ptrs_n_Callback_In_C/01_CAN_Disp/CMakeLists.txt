add_executable(CAN_App 
    can_main.c 
    can_mcal_bsw.c 
    can_app.c
)

target_include_directories(CAN_App PRIVATE .)