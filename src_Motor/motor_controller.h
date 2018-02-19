/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _MOTOR_CONTROLER_H    /* Guard against multiple inclusion */
#define _MOTOR_CONTROLER_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include <stdbool.h>
#include <bsp.h>
#include "encoder_queue.h"
#include "peripheral/oc/plib_oc.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/usart/plib_usart.h"
/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */
#define FORWARD false
#define REVERSE true


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    float error;
    float kp;
    uint32_t leftPower;
    bool leftDir;
    uint32_t rightPower;
    bool rightDir;
    volatile uint32_t MOTOR_DEMO_COUNT;
    volatile bool ENCODER_DEMO_TOGGLE;
    bool ENCODER_DEMO_RUNNING;
    // *****************************************************************************

    void setDirection(bool);
    void setDirectionL(bool);
    void setDirectionR(bool);
    
    void setPulseWidth(int);
    void setPulseWidthL(int);
    void setPulseWidthR(int);
    
    void setMotorL(bool, int);
    void setMotorR(bool, int);
    
    void motorControllerInitialize(void);
    
    void motorDemo(void);
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MOTOR_CONTROLER_H */

/* *****************************************************************************
 End of File
 */
