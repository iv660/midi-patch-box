## Quick TDD Guide for Cursor AI  
*Project: C++ / RP2040 Pico / Arduino / PlatformIO*  
*Test framework: PlatformIO Unity*  

---  

### 1. Architectural Constraints  

| Layer | Dependency direction | Test‑time handling |
|-------|----------------------|--------------------|
| **app** | **No** direct dependence on `hardware` or Arduino libraries. It only uses abstract interfaces that `hardware` implements. | All hardware‑level calls are **mocked**. Mocks are compiled in the native test environment. |
| **hardware** | Implements the interfaces defined by `app`. | Not tested directly; its concrete code is replaced by the mocks during unit tests. |

---  

### 2. Workflow Overview  

| Phase | Action | Outcome |
|-------|--------|---------|
| **Plan** | AI drafts a short implementation plan, breaking the feature into **elementary pieces of functionality** (methods, classes). Test simulates usage of the desired piece of functionality as if it was already implemented. | User reviews & approves. |
| **RGR Loop** (repeat for each piece) | 1️⃣ Propose a **red test** that uses the app‑level functionality with hardware calls **mocked**. <br>2️⃣ Run the test (`pio test -e native …`) – it must fail (red). <br>3️⃣ Fix any compilation errors (e.g., missing mock headers). <br>4️⃣ Implement the minimal app code to satisfy the test. <br>5️⃣ Run the test – it should pass (green). <br>6️⃣ Refactor if needed, then re‑run to keep it green. | Incremental, verified app logic, isolated from hardware. |

---  

### 3. Detailed RGR Steps  

1. **Test Proposal**  
   - AI writes a Unity test file that:  
     * Includes the app header(s).  
     * Instantiates the class under test.  
     * Supplies **mock objects** for any hardware interfaces (e.g., `IADC`, `IGPIO`).  
     * Calls the target method and asserts the expected result.  
   - Sends the test to the user for approval or adjustments.  

2. **Red Confirmation**  
   - After approval, AI runs:  
     ```bash
     pio test -e native -f test_my_feature
     ```  
   - The test must fail (red) because the functionality is not yet implemented.  

3. **Compile‑Error Fix**  
   - If the build fails, AI adds missing includes, forward declarations, or stub mock definitions **without adding real logic**.  
   - Re‑run to ensure the test still fails for the intended reason.  

4. **Minimal Implementation**  
   - AI writes the smallest amount of app‑level code (methods, class members) needed for the test to succeed.  
   - The mock objects remain unchanged; they simply provide the expected responses.  

5. **Green Verification**  
   - Run the same command; the test should now pass (green).  

6. **Refactor (optional)**  
   - Apply style, extract helpers, improve naming, etc., while keeping the mocks untouched.  
   - Re‑run to confirm the test stays green.  

---  

### 4. Test Execution Commands  

- **Run all tests:**  
  ```bash
  pio test -e native
  ```  

- **Run a specific suite:**  
  ```bash
  pio test -e native -f test_state_machine
  ```  

---  

Follow this RGR cycle for every elementary piece of functionality in the plan. The approach guarantees **test‑first development**, full isolation from hardware via mocks, and clean OOP code that respects the app‑hardware dependency direction.