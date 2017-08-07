/***********************************************************************
**  ██████╗ ███████╗██╗███████╗██╗    ██╗ █████╗ ██████╗ ███╗   ███╗  **
**  ██╔══██╗██╔════╝██║██╔════╝██║    ██║██╔══██╗██╔══██╗████╗ ████║  **
**  ██████╔╝███████╗██║███████╗██║ █╗ ██║███████║██████╔╝██╔████╔██║  **
**  ██╔═══╝ ╚════██║██║╚════██║██║███╗██║██╔══██║██╔══██╗██║╚██╔╝██║  **
**  ██║     ███████║██║███████║╚███╔███╔╝██║  ██║██║  ██║██║ ╚═╝ ██║  **
**  ╚═╝     ╚══════╝╚═╝╚══════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝  **
************************************************************************
** Copyright 2016 University of York - See notice at end of file      **
***********************************************************************/

/// PsiSwarm C++ Blank Example Code - Version 0.8
/// James Hilder, Alan Millard, Alexander Horsfield, Homero Elizondo, Jon Timmis

/// Include main.h - this includes psiswarm.h all the other necessary core files
#include "main.h"
#include <math.h>

Psiswarm psi;

char * program_name = "Blank";
char * author_name  = "YRL";
char * version_name = "0.80";

float sensorsToVector(unsigned short v[],float xy[], float *angle)
{
    //Converts the values of the 8 sensors in a normalised 2D vector and returns the module
    xy[0] = cos(22.5*3.1415/180)*(v[1] + v[2] - v[5] - v[6]) + cos(67.5*3.1415/180)*(v[0] + v[3] - v[4] - v[7]);
    xy[1] = cos(22.5*3.1415/180)*(v[0] + v[7] - v[3] - v[4]) + cos(67.5*3.1415/180)*(v[1] + v[6] - v[2] - v[5]);
    float module = sqrt( pow(xy[0],2) + pow(xy[1],2));
    xy[0]/=module;
    xy[1]/=module;

    *angle=atan(xy[0]/xy[1])*180.0/3.1415;
    if (xy[0] >=0.0 and xy[1]<= 0.0) *angle=180+*angle;
    if (xy[0] <=0.0 and xy[1]<= 0.0) *angle=-180+*angle;

    return module;
}

///User code loop:  This is where user code should go; it is run as an infinite loop
void user_code_loop()
{
//  Updating the IR-sensor values (ir_sensor_value: illuminated - background / ir_background = background value)
    unsigned short ir_sensor_value[8], ir_background_value[8];
    sensors.store_ir_values();


    //psi.debug("\n\r");
    for (int i=0;i<8;i++)
    {
        ir_sensor_value[i]=sensors.calculate_side_ir_value(i);
        ir_background_value[i]=sensors.get_background_raw_ir_value(i);
      //and printing in the serial port
        //psi.debug("s[%d] = %d\t",i+1,ir_sensor_value[i]);
    }
    //wait(1);

    //converting the sensor values to a vector
    float xy_final[2], xy_background[2];
    float module_final, module_background;
    float angle_final, angle_background;
    module_final = sensorsToVector(ir_sensor_value, xy_final, &angle_final);
    module_background = sensorsToVector(ir_background_value, xy_background, &angle_background);


//    if (xy_final[0] 0 and xy_final[1] 0) angle_final=;

    //Prints the variables that were modified by the function
//    psi.debug("\n");
    //for (int i=0; i<8; i++)
//    {
//        psi.debug("x_final = %f, y_final = %f, module = %f, angle = %f", xy_final[0], xy_final[1], module_final, angle_final);
//    }



    wait(1);
}

///Place user code here that should be run after initialisation but before the main loop
void user_code_setup()
{
    wait(1);
    display.clear_display();
    display.set_position(0,0);
    display.write_string("No Code");
}

/// Code goes here to handle what should happen when the user switch is pressed
void handle_switch_event(char switch_state)
{
    /// Switch_state = 1 if up is pressed, 2 if down is pressed, 4 if left is pressed, 8 if right is pressed and 16 if the center button is pressed
    /// NB For maximum compatability it is recommended to minimise reliance on center button press
}

void handle_user_serial_message(char * message, char length, char interface)
{
    // This is where user code for handling a (non-system) serial message should go
    //
    // message = pointer to message char array
    // length = length of message
    // interface = 0 for PC serial connection, 1 for Bluetooth
}

/// The main routine: it is recommended to leave this function alone and add user code to the above functions
int main()
{
    psi.init();             ///psi.init() in psiswarm.cpp sets up the robot
    user_code_setup();      ///run user code setup block
    user_code_running = 1;  ///nb. user code can be paused by external commands sent from PC\BT interfaces
    while(1) {
        user_code_loop();   ///run user code
    }
}


/***********************************************************************
** Copyright 2016 University of York                                  **
**                                                                    **
** Licensed under the Apache License, Version 2.0 (the "License")     **
** You may not use this file except in compliance with the License.   **
** You may obtain a copy of the License at                            **
** http://www.apache.org/licenses/LICENSE-2.0   Unless required by    **
** applicable law or agreed to in writing, software distributed under **
** under the License is distributed on an "AS IS" BASIS WITHOUT       **
** WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   **
** See the License for the specific language governing permissions    **
** and limitations under the License.                                 **
***********************************************************************/
