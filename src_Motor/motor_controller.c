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
        leftDir = dir;
        rightDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        return;
    }
    void setDirectionL(bool dir){
        leftDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        return;
    }
    void setDirectionR(bool dir){
        rightDir = dir;
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        return;
    }
    
    void setPulseWidth(int val){
            DRV_OC0_Stop();    
            DRV_OC1_Stop();
            rightPower = val;
            leftPower = val;
            PLIB_OC_PulseWidth16BitSet(OC_ID_1, val);
            PLIB_OC_PulseWidth16BitSet(OC_ID_2, val);
            DRV_OC0_Start();
            DRV_OC1_Start();
    }

    void setPulseWidthL(int val){
        DRV_OC0_Stop();
        leftPower = val;
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, val);
        DRV_OC0_Start();
        return;
    }
    void setPulseWidthR(int val){
        DRV_OC1_Stop();
        rightPower = val;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, val);
        DRV_OC1_Start();
        return;
    }
    
    void setMotorL(bool dir, int val){
        DRV_OC0_Stop();
        if (val > 100) val = 100;
        leftPower = val*DRV_TMR0_PeriodValueGet()/100;
        leftDir = dir;
        PLIB_OC_PulseWidth16BitSet(OC_ID_1, val*DRV_TMR0_PeriodValueGet()/100);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14, !dir);
        DRV_OC0_Start();
        return;
    }
    
    void setMotorR(bool dir, int val){
        DRV_OC1_Stop();
        if (val > 100) val = 100;
        rightPower = val*DRV_TMR0_PeriodValueGet()/100;
        rightDir = dir;
        PLIB_OC_PulseWidth16BitSet(OC_ID_2, val*DRV_TMR0_PeriodValueGet()/100);
        PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1, !dir);
        DRV_OC1_Start();
        return;
    }
    void motorControllerInitialize(void){
        DRV_TMR0_Start();
        DRV_TMR1_Start();
        DRV_TMR2_Start();
        PLIB_USART_Enable(USART_ID_1);
        sensorq_createf();
        ENCODER_DEMO_RUNNING = true;
    }

    void motorDemo(void){
        enum stateVariable { Initialize, Wait, Forward1, Forward2, TurnLeft, TurnRight, Reverse1, Reverse2, Stop, END_MOTOR, INITIALIZE_ENCODER, RUN_ENCODER, END_DEMO } state, nextState;
        state = Initialize;
        nextState = Wait;
        while(true){
            switch(state)
            {
                case Initialize : {
                    while (MOTOR_DEMO_COUNT < 60);
                    ENCODER_DEMO_RUNNING = false;
                    setMotorR(FORWARD, 0);
                    setMotorL(FORWARD, 0);
                    state = nextState;
                    break;
                }
                case Wait : {
                    MOTOR_DEMO_COUNT = 0;
                    while (MOTOR_DEMO_COUNT < 30);
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
                case END_MOTOR : {
                    state = INITIALIZE_ENCODER;
                    break;
                }
                case INITIALIZE_ENCODER : {
                    while (MOTOR_DEMO_COUNT < 150);
                    sensorq_create();
                    setMotorL(FORWARD, 100);
                    ENCODER_DEMO_RUNNING = true;
                    state = RUN_ENCODER;
                    break;
                }
                case RUN_ENCODER : {
                    ENCODER_DEMO_TOGGLE = 0;
                    while(true){
                    float rightVal = 0;
                    float leftVal = 0;
                    struct AMessage *message;
                    message = sensorq_receive();
                    rightVal = message->right;
                    leftVal = message->left;
                    dbgOutputVal(rightVal);
                    MOTOR_DEMO_COUNT++;
                    if(MOTOR_DEMO_COUNT > 300) state = END_DEMO;
                    }
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
/* *****************************************************************************
 End of File
 */
