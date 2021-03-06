# Summary
![](docs/img/f_totalview.jpg)
This report describes the Lego NXT robot built for GENE 121/MTE 100 final project. The robot was designed to sharpen a disordered series of coloured pencils and sort them according to the colour of their graphite tips in order to make use of coloured pencils in art projects more convenient for artists. 
The purpose of this report is to document the design process of the project and reflect on possible improvements in the design and project management. The sharpening subsystem loads pencils from a jam-proof cartridge onto a pencil feeder, which conveys the pencils into an electric sharpener. After a set period of sharpening time, the pencil is retracted, its colour is detected and the tray aligns the corresponding compartment of the container with the pencil feeder. The pencil is then ejected and the electric sharpener is realigned with the pencil feeder. 
It is concluded that oversight in the mechanical and software design prevented the robot from completing its objective, and improper project management led to delays that removed time for any significant adjustments. Specifically, the tray was unable to brace the sharpener against the force of pencils ejected by the pencil feeder and the program unexpectedly did not stop the tray at the correct alignment. Many suboptimal trade-offs of mechanical features are also discussed. Recommendations include attaching a supporting wall to the back of the tray, adding more checks for proper hardware operation in the code, and various small mechanical design improvements. 

# Index
* [Introduction](#1-introduction)
    * [Design Problem Definition](#11design-problem-definition) 
    * [Goals and Objective](#12goals-and-ojective) 
    *	[Constraints and Criteria](#13constraints-and-criteria) 
        * [Constraints](#131constraints)  
        * [Criteria](#132criteria) 
* [Mechanical Design](#2mechanical-design)  
    * [Cartridge Design](#21cartridge-design)  
        * [Reasoning for Design](#211reasoning-for-design) 
        * [Design Tradeoffs](#212design-tradeoffs) 
    * [Pencil Feeder Design](#22pencil-feeder-design)  
        * [Reasoning for Design](#221reasoning-for-design) 
        * [Design Tradeoffs](#222design-tradeoffs)  
        * [Extensions](#223extensions)  
    *	[Tray Design](#23tray-design) 
        * [Reasoning for Design](#231reasoning-for-design)  
        * [Design Tradeoffs](#232design-tradeoffs) 
        * [Extensions](#233extensions)  
* [Software Design and Implementation](#3software-design-and-implementation)  
    *	[Testing Overview](#31testing-overview)  
    *	[Problems Encountered and Resulting Redesign](#32problems-encountered-and-resulting-redesign) 
    *	[Software Design Tradeoffs](#33software-design-tradeoffs) 
* [Project Management](#4project-management)  
    *	[Task Delegation](#41task-delegation)  
    *	[Project Timeline](#42project-timeline)  
* [Conclusions and Recommendations](#5conclusions-and-recommendations)  
    *	[Conclusions](#51conclusions) 
    *	[Recommendations](#52-recommendations)  
        * [Mechanical Improvements](#521mechanical-improvements)  
        * [Software Improvements](#522software-improvements)  
        * [Project Management Improvements](#523project-management-improvements)  
* [Reference](#6references)  



# 1 Introduction 
## 1.1	Design Problem Definition
Using coloured pencils in an advanced art project often requires fine precision for detail and very heavy shading for desired intense hues. Also, since coloured pencils cannot easily mix their colors on paper, artists require a large variety of coloured pencils for different shades. As a result, artists using coloured pencils must frequently interrupt their creative process to sharpen and find the correct coloured pencil out of their large collection.
## 1.2	Goals and Objective
The objective of the robot is to reduce the inconvenience of working with coloured pencils by sharpening large quantities of coloured pencils to a high degree of sharpness and sorting them according to their graphite colour efficiently. The design aims to create a robot that could function as a tool in an artist’s studio. 
## 1.3	Constraints and Criteria
### 1.3.1	Constraints
The initial constraints were for the robot to avoid chipping pencils during operation, protect the user’s fingers from being pierced by ejected pencils, stand stable without user support, sharpen pencils to high degree of sharpness and sort pencils according to the colour of their graphite tips. To avoid chipping pencils, the tire system was designed to tightly grip each pencil after sharpening and eject it to the container, which was placed high enough for the pencil to fall without damaging its tip. To test this constraint, pencils were to be able to draw lines at least 0.25 cm after sharpening. The robot was also designed sharpen pencils to a high degree of sharpness by inserting them in the sharpener for slightly longer than the average pencil required sharpening time, which was estimated to be five seconds. For safety, the motors automatically stopped within three seconds of fingers being caught in the mechanism. The robot also stood on its own because all its components are mounted on a wooden base. As for pencil sorting, the robot was designed to first sense a pencil’s graphite colour and reposition the tray to the correct container compartment.
### 1.3.2	Criteria
The initial criteria were for the robot to handle various pencil sizes, have a jam-proof loading mechanism, be easily moved by one person, allow for easier access to sharpened pencils, sort for criteria besides colour and possess different sorting options. Since the ability to avoid jams and function regardless of pencil size is most important, the design of the cartridge and pencil feeder received the most attention and progressed through three preliminary designs. The final design would preferably be able to handle pencils between 3.5 to 7 inches long without jamming. Easier access to sorted pencils was accomplished by adding a removable container to the tray and the different colour settings of the colour sensor allows for implementation of different sorting options. However, as the complexity of detecting subtle features besides colour, such as graphite density, interfered with the meeting of constraints, this criterion was replaced with a desire for performance speed. Our new criterion is for the robot to sharpen and sort 30 pencils in 10 minutes.
 
# 2	Mechanical Design
 ![](docs/img/f_overview.png)
Figure 2.1: Mechanical Design of the Robot Full View

## 2.1	Cartridge Design
The cartridge holds at least 30 pencils for the robot to automatically feed to the sharpening and sorting mechanisms. The user drops horizontally oriented pencils, which stack up in the cartridge before dropping into the pencil feeder.
### 2.1.1	Reasoning for Design 
The tall, narrow shape of the cartridge holds pencils in a single column. As a result, it unloads only one pencil at a time and prevents pencils from jamming via lateral movement (See Figure 2.2).

 ![](docs/img/f_loader.png)
 
Figure 2.2: Cartridge Design Comparison: The left diagram illustrates the current cartridge design, viewing from the back of the cartridge. Note the ordered pencil stack.  The right diagram illustrates a possible jam situation with a wider cartridge design. Note the disorder allowed by the width of the cartridge.


### 2.1.2	 Design Tradeoffs
The cartridge’s tall design is unstable due to its high centre of gravity and thus, makes the robot difficult to transport. The height of the cartridge also forces the user to stand up from their work to reload, and the narrow opening requires the pencils to be loaded one at a time, which is inconvenient and time-consuming. However, the design cannot accommodate a funnel for faster pencil loading without further compromising its structural stability. The tall design remains in the final design despite these flaws for its simplicity, reliability and ease of manufacturing to meet the project deadline, which allows for more focus on the main mechanisms.
### 2.1.3	Extensions
Possible extensions include a method of scanning the colours of all loaded pencils before sharpening so they could be sorted according to the maximum and minimum RGB values of the loaded pencils instead of according to default colour readings. Pencils could also be checked for incorrect orientation and flipped around to avoid sharpening the back ends of pencils.
## 2.2	Pencil Feeder Design

 ![](docs/img/f_convey.png)
Figure 2.3 Pencil Feeder Design

The final pencil feeder receives a row of pencils dropped from the cartridge and moves them forward on a conveyor belt. The belt then stops and the tires drag the first pencil in the row to activate a touch sensor. Once the program senses the pencil’s colour, the tires push the pencil into the sharpener and pull it out after an arbitrary time period. Note that the tire system is referred to as “wheel” in the code, and is referenced differently in the report to highlight the mechanical importance of the rubber tires.
### 2.2.1	Reasoning for Design 
The two-step mechanism of the belt and tires allows the robot to handle the edge case of several short pencils being dropped at once, since the tires only pull the first pencil in the row. Also, since the entire row of pencils shifts forward, longer pencils above the conveyor belt row only partially drop into the back end of the row, which does not affect the pencil feeder (See Figure 2.4). 

![](docs/img/f_dropsol.png)
Figure 2.4: Illustration of Pencil Drop solution. The long pencil partially drops into the back of the row and causes no jams. Note that in a system where the pencil would drop in front of the row, the system would jam

This conveyor belt design eliminates the need for the long rear pencil stopper of previous slider-based designs (See Figure 2.5)
Next, the switch from a conveyor belt to a tire arrangement is necessary for the robot to firmly grip the pencil. The increased traction as the pencil is squeezed between two tires allows the robot to both push the pencil forcefully enough for the sharpener to activate as well as pull the pencil out when fully sharpened. This tight grip is also necessary for the light pencil to activate the touch sensor. 
 
![](docs/img/f_prevslide.png)

Figure 2.5: Previous Slider Design. Note the long extension at the back of the slider meant to stop long pencils from partially dropping behind it.
### 2.2.2	Design Tradeoffs
The trade-offs of this pencil feeder design are that it sacrifices speed and is more prone to assembly errors. Since the feeder cannot detect the length of pencils or if there are even multiple pencils in the row at all, the belt has to move forward for an arbitrary time period before the tires activate. In the robot, this inefficiency of the two-step mechanism results in roughly 1-2 seconds of wasted time per pencil. This design also heavily relies on the cartridge being correctly aligned with the conveyor belt, since the conveyor belt passively accepts pencils dropping from the cartridge instead of actively removing them with a piston or a similar mechanism. Additionally, the conveyor belt and tires need separate motors, which restricts the design of later components. Despite these flaws, this design’s simplicity and ability to easily handle varying lengths of pencils merit its inclusion in our robot.
### 2.2.3	Extensions
Possible extensions of the pencil feeder include creating a mechanism to sense the general sharpness of a pencil before and after sharpening. This could give the program input to estimate the minimum time the tires have to be in “push” mode to sharpen the pencil, and decrease sharpening time accordingly.
## 2.3	Tray Design

![](docs/img/f_totalrails.jpg)

![](docs/img/f_totalsystem.)
The pencil tray moves either the sharpener or the container for sorted pencils in front of the pencil feeder tires for the tires to push out the pencil into the sharpener or the correct compartment of the container. The tray moves via a rack and pinion underneath it and calibrates with a touch sensor below it.
### 2.3.1	Reasoning for Design
Combining the pencil sharpener and final container into one moving part allows the design to reuse the ejection mechanism of the tires, eliminating the need for a complex and error-prone ramp systems, which was a previous design idea. This design also made efficient use of resources, since the pencil feeder requires the other two motors. Furthermore, moving the sharpener and container on a tray is more stable than moving the pencil feeder because the tray’s lower centre of gravity and placing the tray perpendicular to the feeder allows for easy access to the container of sorted pencils. The container compartments are tall so as they can accommodate the edge case of all 30 pencils being the same colour. Placing the motor under the weight of the tray helps the rack engage the pinion, and as for the touch sensor location, attaching it below the tray instead of at the ends of the tray’s path prevents the sensor from being dislodged or damaged while transporting the robot.
### 2.3.2	Design Tradeoffs
Since the motor is beneath the tray, the tray is elevated on a platform of Tetrix pieces, which requires the feeder and cartridge to be elevated as well, and compromises the robot’s stability. The rack and pinion is difficult to access in this arrangement as well, so checking and adjusting the contact between the rack and pinion becomes inconvenient. Also, placing the tray perpendicular to the feeder is space-intensive, requiring a large base for the robot which is difficult to transport. Additionally, while the movable tray design allows for a stable stationary pencil feeder, it does not stabilize the sharpener against the force of pencils pushed out by the feeder. Placing the touch sensor below the tray destabilizes it as well, as it must depress the sensor button as it moves forward. As a result, the tray requires a large weight in the container for the robot to be operational. 
### 2.3.3	Extensions
Possible extensions include sensing when a compartment of the container is full. This could enable the program to stop the robot and prompt the user to empty it.


# 3	Software Design and Implementation
The program breaks down the robot’s task into the following functions. First it conveys a pencil from the conveyor belt to the tires, where it triggers a touch sensor. The colour sensor above it then reads the pencil colour and the robot feeds a pencil to the sharpener. Once the pencil is finished sharpening, the robot retracts the pencil, aligns the pencil feeder and the container compartment corresponding to the pencil colour, and ejects the pencil. In order to manage the many steps of this task, the program is broken down into 5 files: `ports.c`, `utils.c`, `actions.c`, and `main.c`.
ports.c contains constants representing the correct sensor configuration and the tasks corresponding with each motor and sensor. Each constant is named for the intended function of the motor and sensor and contains the correct port. Using the constants in ports.c provides a unified standard for referring to the sensors and ports elsewhere in the code. 
utils.c stores algorithmic and miscellaneous functions used in the program. It includes two algorithmic functions. The first is the swap function, which accepts 2 integers, and swaps their place in memory. The second is the sort function, which accepts an array pointer, and sorts it either in ascending or descending order. Miscellaneous functions include the overloaded function waitForBtnPress, which detects if button has been pressed. If called without parameters, int waitForBtnPress() returns the index of the button pressed, while `bool waitForBtnPress(int btn, timeoutMS =-1)` will indicate whether the specified button has been pressed in the given timeout interval. The functions in this file facilitate calculations and other generic tasks performed in other parts of the program. The file also contains constants that represent the NXT’s buttons. These are used in place of the integer button mappings, which are hard to recall and fail to indicate the buttons that they referred to. 
actions.c is the higher-level component of the program, and stores the functions that represent specific steps in the robot’s task. Such steps include sharpening the pencil, aligning the cartridge with a specific colour bin, and displaying the inventory of sharpened pencils. actions.c replaces repeated motor control code with simple function names, making the code in main.c much easier to understand and follow. 
The functions in controls.c allow for low level manipulation of the robot’s hardware such as motor control and sensor initialization. Each subsystem (e.g., tray, tires, etc) has its own function to allow for independent control, such as moveBelt, SpinWheels, and moveTray. These functions perform their designated action by facilitating the robot system according to a given motor power value. They also accept an optional timeout or distance value for the motors to be operated for a set time or distance, which allows the accurate timing crucial to the robot’s task. Furthermore, many functions have a boolean return type to return false in response to unexpected dips in motor speed, which could indicate a pencil jam or the user being poked by a pushed pencil. actions.c uses this information to determine any environmental disturbances. 
The functions are put together and executed in main.c by the high level sharpenAndsort method which prompts user input, executes the sharpening and sorting tasks by calling functions and displaying the final result returned by functions. Meanwhile, monitorTray checks for the tray’s presence during the course of operation and stops the robot if the tray has been removed. The design is summarized briefly in Figure 6.1.
 
![](docs/img/f_flowchart.jpg)
Figure 3.1: Main Program Flowchart
## 3.1	Testing Overview
Testing began with the low level hardware control functions in controls.c. Each function was called with and without the timeout parameter to test the program’s ability to accurately control the robot. actions.c was only tested after the functions in controls.c were fully debugged to ensure further issues would only be errors in the tested file. During this stage of testing, the motors were also obstructed to check if the program would automatically stop the robot during a pencil jam. Once actions.c was fully tested and debugged, main.c was also tested for the ability to stop the program when the tray was removed. 
## 3.2	Problems Encountered and Resulting Redesign
Testing revealed that the program was easily disrupted by environmental factors obstructing the robot’s mechanisms and disturbing its timing. As a result, each function was modified to return a value of the enumerated type Status to indicate whether it has experienced a jam, has been operating longer than the timeout period, or has executed successfully. This made it possible to handle specific real-world errors while maintaining the structure of the code.
## 3.3	Software Design Tradeoffs
This modular approach sacrifices some flexibility. Rather than setting motors directly, main.c is now limited to calling a set of predefined functions in order to perform a certain action. Furthermore, any errors in the low level functions transfer to the entire program. Debugging also becomes inconvenient since the functions are distributed across several different files. However, the ability to quickly modify functions repeated throughout the program and easily rearrange code blocks outweigh the disadvantages of this approach.
 
# 4	Project Management
## 4.1	Task Delegation
During design formulation, all group members were allowed to suggest mechanical subsystems to accomplish each subtask of the robot, such as extracting only one pencil at a time, and improvements on these subsystems. The group delegated the writing of the first design report to Felix Cheng due to the other group members’ student design team commitments and delegated proofreading and formatting tasks to the rest of the group. The group equally distributed presentation planning to ensure consistency. While the original plan delegated the software component to Eugene Wang and Feilan Jiang and the mechanical component to Felix Cheng and Kenta Morris, the unexpected inefficiencies of group member disengagement and frequent design changes resulted in a late start to building the robot. As a result, all group members worked on building the design, which includes building the cartridge, tray and pencil feeder, and adapting to sudden design changes, such as the switch from a slider-based pencil feeder to the current conveyor belt design. Feilan Jiang and Eugene Wang managed the entire robot code towards the last week of the project. 
## 4.2	Project Timeline
The project build period ostensibly began on November 3 with daily meetings from 6:00 pm to 12:00pm. However, due to frequent decisions to change subsystems and building materials, and consequently disassemble our progress, the build period effectively began on November 16. This severe delay due to inefficient meetings delayed coding to November 22, testing to November 24 and eliminated time for adjustments completely. 

 
# 5	Conclusions and Recommendations
## 5.1	Conclusions
The robot is ultimately unable to complete its objective of sharpening and sorting coloured pencils in bulk. While the robot is able to meet constraints and criteria such as automatically stopping motors for safety and avoiding pencil jams, oversight in the mechanical and software design prevented it from meeting constraints and criteria linked to the robot’s core task. While the cartridge, pencil feeder and tray met requirements alone, in the robot as an interconnected system, the tray’s inability to stabilize itself against the force of the fed pencil prevented the robot from sharpening pencils. The code, despite its three-level hierarchy of functions, is unexpectedly unable to stop the tray, preventing the robot from placing pencils in their appropriate compartments in the container. Essentially, faulty project management eliminated any time to adjust the robot after testing.
## 5.2	 Recommendations
### 5.2.1	Mechanical Improvements
A better cartridge design would allow pencils to stack within the cartridge in in two columns, similar to bullet storage in large gun magazines. The cartridge would be as reliable as our current design, but only about half as tall, which would solve the problems of structural stability and allow for a funnel to be added on its top for faster pencil loading. The funnel opening might be offset from the cartridge opening to prevent pencils inserted diagonally from becoming stuck inside the cartridge.  A better design would also have the walls of cartridge extend lightly beyond the output end to ensure no pencils slip off the conveyor belt.
A better feeder design could be built using a touch sensor between the conveyor belt and tire sections to detect when the latter section should activate. This could reduce the delay between the conveyor belt and tires activating. The design could also be improved by adding slanted walls just before the two vertical tires to guide the pencil to the correct orientation 
A better design of the tray would include walls at the back of the tray to stabilize the sharpener against pencils pushed out by the feeder and have the rack and pinion at the back as well to allow for a shorter and more space efficient robot. 
### 5.2.2	Software Improvements
The software’s high dependency on the mechanical components could be reduced by modifying the functions to reverse their action when a mechanical error occurs. Essentially, the program could be improved by adding more checks for mechanical errors. For example, the program currently only uses the touch sensor under the tray to detect whether the tray is in its correct initial condition. Better software design could also return an error if the motor encoder for the tray exceeded certain bounds and have the robot to retract the pencil between its tires.  
### 5.2.3	Project Management Improvements
In retrospect, during design formulation, each member should have separately created a design sketch and collectively discussed each other’s design for one day. Afterwards, each subsystem should have been assigned to a group member and no further design adjustments, regardless of how beneficial, should have been accepted until the group built a working proof of concept. This could have created a prototype to test real issues instead of merely predicting issues in unmade designs.
 
# 6	References
1. Robomatter. (2016, January 27). ROBOTC for LEGO Mindstorms 4.x – Users Manual [Online]. Available: http://help.robotc.net/WebHelpMindstorms/index.html

2. buffington. (2013, March 6). Customizable Lego Rack Gear [Online]. Available: http://www.thingiverse.com/thing:58194
 
 
