/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "motor_controller.h"

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
 
    void setDirection(bool dir){
        motor.leftDir = dir;
        motor.rightDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        return;
    }
    void setDirectionL(bool dir){
        motor.leftDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        return;
    }
    void setDirectionR(bool dir){
        motor.rightDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        return;
    }
    
    void setPulseWidth(int val){
            DRV_OC0_Stop();    
            DRV_OC1_Stop();
            motor.rightPower = val;
            motor.leftPower = val;
            PLIB_OC_PulseWidth16BitSet(OC_ID_1, val);
            PLIB_OC_PulseWidth16BitSet(OC_ID_2, val);
            DRV_OC0_Start();
            DRV_OC1_Start();
    }

    void setPulseWidthL(int val){
        DRV_OC0_Stop();
        motor.leftPower = val;
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, val);
        DRV_OC0_Start();
        return;
    }
    void setPulseWidthR(int val){
        DRV_OC1_Stop();
        motor.rightPower = val;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, val);
        DRV_OC1_Start();
        return;
    }
    
    void setMotorL(bool dir, int val){
        DRV_OC0_Stop();
        if (val > 100) val = 100;
        motor.leftPower = val*DRV_TMR0_PeriodValueGet()/100;
        motor.leftDir = dir;
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, val*DRV_TMR0_PeriodValueGet()/100);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        DRV_OC0_Start();
        return;
    }
    
    void setMotorR(bool dir, int val){
        DRV_OC1_Stop();
        if (val > 100) val = 100;
        motor.rightPower = val*DRV_TMR0_PeriodValueGet()/100;
        motor.rightDir = dir;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, val*DRV_TMR0_PeriodValueGet()/100);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        DRV_OC1_Start();
        return;
    }
    void motorControllerInitialize(void){
        DRV_TMR0_Start();
    }

    void motorDemo( void ){
        //configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
        motorControllerInitialize();
        enum stateVariable { Initialize, Wait, Forward1, Forward2, TurnLeft, TurnRight, Reverse1, Reverse2, Stop, END_MOTOR, END_DEMO } state, nextState;
        state = Initialize;
        nextState = Wait;
        for(;;){
            switch(state)
            {
                case Initialize : {
                    
                    motor.MOTOR_DEMO_COUNT = 0;
                    while (motor.MOTOR_DEMO_COUNT < 30);
                    setMotorR(FORWARD, 0);
                    setMotorL(FORWARD, 0);
                    state = nextState;
                    break;
                }
                case Wait : {
                    motor.MOTOR_DEMO_COUNT = 0;
                    while (motor.MOTOR_DEMO_COUNT < 15);
                    state = ++nextState;
                    break;
                }
                case Forward1 : {
                    setMotorR(FORWARD, 50);
                    setMotorL(FORWARD, 50);
                    state = Wait;
                    break;
                }
                case Forward2 : {
                    setMotorR(FORWARD, 100);
                    setMotorL(FORWARD, 100);
                    state = Wait;
                    break;
                }
                case TurnLeft : {
                    setMotorR(REVERSE, 50);
                    setMotorL(FORWARD, 50);
                    state = Wait;
                    break;
                }
                case TurnRight : {
                    setMotorR(FORWARD, 50);
                    setMotorL(REVERSE, 50);
                    state = Wait;
                    break;
                }
                case Reverse1 : {
                    setMotorR(REVERSE, 50);
                    setMotorL(REVERSE, 50);
                    state = Wait;
                    break;
                }
                case Reverse2 : {
                    setMotorR(REVERSE, 100);
                    setMotorL(REVERSE, 100);
                    state = Wait;
                    break;
                }
                case Stop : {
                    setMotorR(FORWARD, 0);
                    setMotorL(FORWARD, 0);
                    state = END_MOTOR;
                    break;
                }
                case END_DEMO : {
                    setMotorR(FORWARD, 0);
                    setMotorL(FORWARD, 0);
                    break;
                }
                default : {
                    setMotorR(FORWARD, 0);
                    setMotorL(FORWARD, 0);
                    break;
                }
            }
        }
    }
    
    void MOTOR(void){
        motorDemo();
    }
/* *****************************************************************************
 End of File
 */
