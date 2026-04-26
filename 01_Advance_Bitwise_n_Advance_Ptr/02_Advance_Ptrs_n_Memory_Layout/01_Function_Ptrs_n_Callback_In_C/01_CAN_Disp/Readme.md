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
