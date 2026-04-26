cmake_minimum_required(VERSION 3.10)

# Name of the entire workspace
project(BSW_Workspace C)

# (Optional) Collect all .exe files after build into a common bin/ directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- DECLARE SUB-MODULES ---
# Must write the relative path from 04_BSW directory to the location containing CMake sub-modules
add_subdirectory(01_Advance_Bitwise_n_Advance_Ptr/02_Advance_Ptrs_n_Memory_Layout/01_Function_Ptrs_n_Callback_In_C/01_CAN_Disp)

add_subdirectory(01_Advance_Bitwise_n_Advance_Ptr/02_Advance_Ptrs_n_Memory_Layout/01_Function_Ptrs_n_Callback_In_C/02_LIN)