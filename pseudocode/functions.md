Functions
----
1. `bool isCartridgeEmpty()`
    - Assigned to **Feilan**
    - Description: Use piston and its touch sensor to check if there are pencils in the cartridge
    - Testing: 
2. `int getPressedBtn()`
    - Assigned to **Feilan**
    - Description: Check each button and its change in state, then return the number of the button that was pressed
    - Testing:
3. `void sort(int ar[], int len, bool reverse = false)`
    - Assigned to **Feilan**
    - Description: Generic sorting algorithm
    - Testing:
4. `void moveTrayToColor(int color)`
    - Assigned to **Eugene**
    - Description: Align the cartridge ejection hole with the chosen color's designated section on the tray
    - Testing:
5. `void zeroPiston()`
    - Assigned to **Kenta**
    - Description: Move the piston to a point where its touch sensor is down; provides a consistent reference point for other functions that move the piston
    - Testing:
6. `void zeroTray()`
    - Assigned to **Kenta**
    - Description: Move the tray to a point where its touch sensor is down; provides a consistent reference point for other functions that move the piston
    - Testing:
7. `void sharpenPencil(int ms)`
    - Assigned to **Feilan**
    - Description: Push pencils into sharpener using wheels and piston, begin sharpening when piston touch sensor goes from `true` to `false`, sharpen for 
      specified duration, and eject pencil from sharpener back into cartridge
    - Testing:
8. `bool feedPencil()`
    - Assigned to **Eugene**
    - Description: Use the piston to push the pencil until it reaches the wheels, at which point the pressing of the piston's touch sensor will signal the end
      of the function
    - Testing:
9. `int getPencilColor()`
    - Assigned to **Kenta**
    - Description: Use the piston to align the pencil with the color sensor, get the pencil lead color, then return the pencil to its original position
    - Testing:
10. `void alignSharpener()`
    - Assigned to **Kenta**
    - Description: Align the cartridge ejection hole with the sharpener hole
    - Testing:
11. `void retractPiston(int percent = 100)`
    - Assigned to **Eugene**
    - Description: Move the piston backward for the specified distance; piston will extract fully by default
    - Testing:
12. `void spinWheels(int power, int ms = -1)`
    - Assigned to **Felix**
    - Description: Spin both sharpener-feeding wheels in the same direction, for the specified duration; wheels will spin indefinitely by default
    - Testing:
13. `void moveTray(int power, int cm = 0)`
    - Assigned to **Felix**
    - Description: Move tray at the specified power for the specified distance; moves tray to full extent by default
    - Testing:
14. `void movePiston(int power, int cm = 0)`
    - Assigned to **Eugene**
    - Description: Move piston at the specified power for the specified distance; moves piston to full extent by default
    - Testing:
