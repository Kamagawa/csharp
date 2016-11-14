Functions
----
1. `bool isCartridgeEmpty()`
    - Assigned to **Feilan**
    - Description: Use "piston" and its touch sensor to check if there are pencils in the cartridge
    - Testing:
      - Put pencils of varying lengths (all within our defined range) into the cartridge and check if the function's return value is consistent
      - Check for a consistent, `false` value when there are no pencils
2. `int getPressedBtn()`
    - Assigned to **Feilan**
    - Description: Check each button and its change in state, then return the number of the button that was pressed
    - Testing:
      - Press each button individually and verify that the returned value equals the button's `nNxtButtonPressed` value
3. `void sort(int ar[], int len, bool reverse = false)`
    - Assigned to **Feilan**
    - Description: Generic sorting algorithm
    - Testing: Sort arrays with varying range of values, degree of sorted-ness, and length, and check that each array is sorted properly within a reasonable number of
      "steps" (e.g. number of loop iterations, recursion depth depending on chosen algorithm, etc.)
4. `void moveTrayToColor(int color)`
    - Assigned to **Eugene**
    - Description: Align the cartridge ejection hole with the chosen color's designated section on the tray
    - Testing:
      - Test alignment for each color section of the tray and measure the error relative to the setpoint (i.e. centre of section right in front of cartridge opening)
5. `void zeroPiston()`
    - Assigned to **Kenta**
    - Description: Move the "piston" to a point where its touch sensor is down; provides a consistent reference point for other functions that move the "piston"
    - Testing:
      - Call the function from various starting positions and check accuracy of the final position
6. `void zeroTray()`
    - Assigned to **Kenta**
    - Description: Move the tray to a point where its touch sensor is down; provides a consistent reference point for other functions that move the "piston"
    - Testing:
      - Call the function from various starting positions and check accuracy of the final position
7. `void sharpenPencil(int ms)`
    - Assigned to **Feilan**
    - Description: Push pencils into sharpener using wheels and "piston", begin sharpening when "piston" touch sensor goes from `true` to `false`, sharpen for 
      specified duration, and eject pencil from sharpener back into cartridge
    - Testing:
      - Try different "piston" and wheel motor powers to ensure that the "piston" touch sensor is consistently down when working with wheels to push the pencil
      - Test with different pencil lengths (again, all within range) to confirm that touch sensor is released the moment the pencil enters the sharpener
8. `bool feedPencil()`
    - Assigned to **Eugene**
    - Description: Use the "piston" to push the pencil until it reaches the wheels, at which point the pressing of the "piston"'s touch sensor will signal the end
      of the function
    - Testing:
      - Load cartridge with pencils of varying lengths, then call function to see if "piston" touch sensor is pressed right when pencils reach the wheels
      - Experiment with different "piston" motor power levels to make sure the touch sensor isn't pressed upon contact with pencil (this would terminate the function
        prematurely)
9. `int getPencilColor()`
    - Assigned to **Kenta**
    - Description: Use the "piston" to align the pencil with the color sensor, get the pencil lead color, then return the pencil to its original position
    - Testing:
      - Call the function from various "piston" starting positions and with pencils of varying lengths and sharpnesses, then measure how accurately the pencil lead
        aligns with the color sensor
10. `void alignSharpener()`
    - Assigned to **Kenta**
    - Description: Align the cartridge ejection hole with the sharpener hole
    - Testing: Call the function from various tray positions and measure how accurately the sharpener hole lines up with the cartridge opening
11. `void retractPiston(int percent = 100)`
    - Assigned to **Eugene**
    - Description: Move the "piston" backward for the specified distance; "piston" will extract fully by default
    - Testing:
      - Test function from various starting positions and measure accuracy of final position
      - Experiment with various motor power levels to see which gives the most accurate results
12. `void spinWheels(int power, int ms = -1)`
    - Assigned to **Felix**
    - Description: Spin both sharpener-feeding wheels in the same direction, for the specified duration; wheels will spin indefinitely by default
    - Testing:
      - Check if both wheels are spinning in the same direction, for both positive and negative values of `power` (i.e. forward and backward spinning)
      - Test with different values for `ms` and verify that wheels run for that duration of time
13. `void moveTray(int power, int cm = 0)`
    - Assigned to **Felix**
    - Description: Move tray at the specified power for the specified distance; moves tray to full extent by default
    - Testing:
      - Test with varying distance values and check if the tray stops when out of bounds
      - Test with different motor power levels to see which travels a distance most consistent with encoder readings
14. `void movePiston(int power, int cm = 0)`
    - Assigned to **Eugene**
    - Description: Move "piston" at the specified power for the specified distance; moves "piston" to full extent by default
    - Testing:
      - Test with varying distance values and check if the "piston" stops when out of bounds
      - Test with different motor power levels to see which travels a distance most consistent with encoder readings
