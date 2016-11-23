Functions
====
"Low-level" hardware functions (all found in `controls.c`)
----
1. `void spinWheels(int power, int ms = -1)`
    - Assigned to **Felix**
    - Description: Spin both sharpener-feeding wheels in the same direction, for the specified duration; wheels will spin indefinitely by default
    - Testing:
      - Check if both wheels are spinning in the same direction, for both positive and negative values of `power` (i.e. forward and backward spinning)
      - Test with different values for `ms` and verify that wheels run for that duration of time
2. `void moveTray(int power, int cm = 0)`
    - Assigned to **Felix**
    - Description: Move tray at the specified power for the specified distance; moves tray to full extent by default
    - Testing:
      - Test with varying distance values and check if the tray stops when out of bounds
      - Test with different motor power levels to see which travels a distance most consistent with encoder readings
3. `void movePiston(int power, int cm = 0)`
    - Assigned to **Eugene**
    - Description: Move conveyor belt at the specified power for the specified distance; moves conveyor belt to full extent by default
    - Testing:
      - Test with varying distance values and check if the conveyor belt stops when out of bounds
      - Test with different motor power levels to see which travels a distance most consistent with encoder readings
4. `int getColorReading()`
    - Assigned to **Felix**
    - Return sensor value of color sensor

"High-level" task functions (all found in `actions.c`)
----
1. `void zeroTray()`
    - Assigned to **Kenta**
    - Description: Move the tray to a point where its touch sensor is down; provides a consistent reference point for other functions that move the conveyor belt
    - Testing:
      - Call the function from various starting positions and check accuracy of the final position
2. `bool feedPencil()`
    - Assigned to **Eugene**
    - Description: Use the conveyor belt to push the pencil until it reaches the wheels, at which point the pressing of the conveyor belt's touch sensor will signal the end
      of the function
    - Testing:
      - Load cartridge with pencils of varying lengths, then call function to see if conveyor belt touch sensor is pressed right when pencils reach the wheels
      - Experiment with different conveyor belt motor power levels to make sure the touch sensor isn't pressed upon contact with pencil (this would terminate the function
        prematurely)
3. `void sharpenPencil(int ms)`
    - Assigned to **Feilan**
    - Description: Push pencils into sharpener using wheels and conveyor belt, begin sharpening when encoder reading for wheels drops (this signifies the pencil's entry into the sharpener), sharpen for 
      specified duration, and roll wheels backward until touch sensor is released (this will happen right when the pencil retracts past the touch sensor)
    - Testing:
      - Try different conveyor belt and wheel motor powers to ensure that the conveyor belt touch sensor is consistently down when working with wheels to push the pencil
      - Test with different pencil lengths (again, all within range) to confirm that touch sensor is released the moment the pencil enters the sharpener
4. `void moveTrayToColor(int color)`
    - Assigned to **Eugene**
    - Description: Align the cartridge ejection hole with the chosen color's designated section on the tray
    - Testing:
      - Test alignment for each color section of the tray and measure the error relative to the setpoint (i.e. centre of section right in front of cartridge opening)
5. `void ejectPencil()`
    - Assigned to **Kenta**
    - Call when corresponding color bin has been aligned with cartridge 
    - Steps (pencil begins right behind wheel touch sensor)
      1. Spin motors forward until wheel touch sensor down
      2. Continue spinning motors forward until above touch sensor goes back up (i.e. pencil has exited cartridge)
      3. Continue spinning motors forward for a set time period (until pencil enters tray)
6. `int getPencilColor()`
    - Assigned to **Kenta**
    - Description: Use the conveyor belt to align the pencil with the color sensor, get the pencil lead color, then return the pencil to its original position
    - Testing:
      - Call the function from various conveyor belt starting positions and with pencils of varying lengths and sharpnesses, then measure how accurately the pencil lead
        aligns with the color sensor
7. `bool isCartridgeEmpty()`
    - Assigned to **Feilan**
    - Description: Use conveyor belt and its touch sensor to check if there are pencils in the cartridge
    - Testing:
      - Put pencils of varying lengths (all within our defined range) into the cartridge and check if the function's return value is consistent
      - Check for a consistent, `false` value when there are no pencils

Miscellaneous functions
----
1. `int getPressedBtn()` (all found in `nxtToggleBtn.c`)` 
    - Assigned to **Feilan**
    - Description: Check each button and its change in state, then return the number of the button that was pressed
    - Testing:
      - Press each button individually and verify that the returned value equals the button's `nNxtButtonPressed` value
2. `void sort(int ar[], int len, bool reverse = false)` (all found in `util.c`)
    - Assigned to **Feilan**
    - Description: Generic sorting algorithm
    - Testing: Sort arrays with varying range of values, degree of sorted-ness, and length, and check that each array is sorted properly within a reasonable number of
