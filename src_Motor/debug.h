/* ************************************************************************** */
/* Milestone 1 Debug Header */
/* ************************************************************************** */

#ifndef _DEBUG_H    /* Guard against multiple inclusion */
#define _DEBUG_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <bsp.h>
#include "app.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
#define LOC_0 0     // 8'b 0 0 0 0 0 0 0 0
#define LOC_1 1     // 8'b 0 0 0 0 0 0 0 1
#define LOC_2 2     // 8'b 0 0 0 0 0 0 1 0
#define LOC_3 3     // 8'b 0 0 0 0 0 0 1 1
#define LOC_4 4     // 8'b 0 0 0 0 0 1 0 0
#define LOC_5 5     // 8'b 0 0 0 0 0 1 0 1
#define LOC_6 6     // 8'b 0 0 0 0 0 1 1 0
#define LOC_7 7     // 8'b 0 0 0 0 0 1 1 1
#define LOC_8 8     // 8'b 0 0 0 0 1 0 0 0
#define LOC_9 9     // 8'b 0 0 0 0 1 0 0 1
#define LOC_10 10   // 8'b 0 0 0 0 1 0 1 0  
#define LOC_11 11   // 8'b 0 0 0 0 1 0 1 1  
#define LOC_12 12   // 8'b 0 0 0 0 1 1 0 0  
#define LOC_13 13   // 8'b 0 0 0 0 1 1 0 1  
#define LOC_14 14   // 8'b 0 0 0 0 1 1 1 0  
#define LOC_15 15   // 8'b 0 0 0 0 1 1 1 1  
#define LOC_16 16   // 8'b 0 0 0 1 0 0 0 0  
#define LOC_17 17   // 8'b 0 0 0 1 0 0 0 1  
#define LOC_18 18   // 8'b 0 0 0 1 0 0 1 0  
#define LOC_19 19   // 8'b 0 0 0 1 0 0 1 1  
#define LOC_20 20   // 8'b 0 0 0 1 0 1 0 0  
#define LOC_21 21   // 8'b 0 0 0 1 0 1 0 1  
#define LOC_22 22   // 8'b 0 0 0 1 0 1 1 0  
#define LOC_23 23   // 8'b 0 0 0 1 0 1 1 1  
#define LOC_24 24   // 8'b 0 0 0 1 1 0 0 0  
#define LOC_25 25   // 8'b 0 0 0 1 1 0 0 1  
#define LOC_26 26   // 8'b 0 0 0 1 1 0 1 0  
#define LOC_27 27   // 8'b 0 0 0 1 1 0 1 1  
#define LOC_28 28   // 8'b 0 0 0 1 1 1 0 0  
#define LOC_29 29   // 8'b 0 0 0 1 1 1 0 1  
#define LOC_30 30   // 8'b 0 0 0 1 1 1 1 0  
#define LOC_31 31   // 8'b 0 0 0 1 1 1 1 1  
#define LOC_32 32   // 8'b 0 0 1 0 0 0 0 0  
#define LOC_33 33   // 8'b 0 0 1 0 0 0 0 1  
#define LOC_34 34   // 8'b 0 0 1 0 0 0 1 0  
#define LOC_35 35   // 8'b 0 0 1 0 0 0 1 1  
#define LOC_36 36   // 8'b 0 0 1 0 0 1 0 0  
#define LOC_37 37   // 8'b 0 0 1 0 0 1 0 1  
#define LOC_38 38   // 8'b 0 0 1 0 0 1 1 0  
#define LOC_39 39   // 8'b 0 0 1 0 0 1 1 1  
#define LOC_40 40   // 8'b 0 0 1 0 1 0 0 0  
#define LOC_41 41   // 8'b 0 0 1 0 1 0 0 1  
#define LOC_42 42   // 8'b 0 0 1 0 1 0 1 0  
#define LOC_43 43   // 8'b 0 0 1 0 1 0 1 1  
#define LOC_44 44   // 8'b 0 0 1 0 1 1 0 0  
#define LOC_45 45   // 8'b 0 0 1 0 1 1 0 1  
#define LOC_46 46   // 8'b 0 0 1 0 1 1 1 0  
#define LOC_47 47   // 8'b 0 0 1 0 1 1 1 1  
#define LOC_48 48   // 8'b 0 0 1 1 0 0 0 0  
#define LOC_49 49   // 8'b 0 0 1 1 0 0 0 1  
#define LOC_50 50   // 8'b 0 0 1 1 0 0 1 0  
#define LOC_51 51   // 8'b 0 0 1 1 0 0 1 1  
#define LOC_52 52   // 8'b 0 0 1 1 0 1 0 0  
#define LOC_53 53   // 8'b 0 0 1 1 0 1 0 1  
#define LOC_54 54   // 8'b 0 0 1 1 0 1 1 0  
#define LOC_55 55   // 8'b 0 0 1 1 0 1 1 1  
#define LOC_56 56   // 8'b 0 0 1 1 1 0 0 0  
#define LOC_57 57   // 8'b 0 0 1 1 1 0 0 1  
#define LOC_58 58   // 8'b 0 0 1 1 1 0 1 0  
#define LOC_59 59   // 8'b 0 0 1 1 1 0 1 1  
#define LOC_60 60   // 8'b 0 0 1 1 1 1 0 0  
#define LOC_61 61   // 8'b 0 0 1 1 1 1 0 1  
#define LOC_62 62   // 8'b 0 0 1 1 1 1 1 0  
#define LOC_63 63   // 8'b 0 0 1 1 1 1 1 1  
#define LOC_64 64   // 8'b 0 1 0 0 0 0 0 0  
#define LOC_65 65   // 8'b 0 1 0 0 0 0 0 1  
#define LOC_66 66   // 8'b 0 1 0 0 0 0 1 0  
#define LOC_67 67   // 8'b 0 1 0 0 0 0 1 1  
#define LOC_68 68   // 8'b 0 1 0 0 0 1 0 0  
#define LOC_69 69   // 8'b 0 1 0 0 0 1 0 1  
#define LOC_70 70   // 8'b 0 1 0 0 0 1 1 0  
#define LOC_71 71   // 8'b 0 1 0 0 0 1 1 1  
#define LOC_72 72   // 8'b 0 1 0 0 1 0 0 0  
#define LOC_73 73   // 8'b 0 1 0 0 1 0 0 1  
#define LOC_74 74   // 8'b 0 1 0 0 1 0 1 0  
#define LOC_75 75   // 8'b 0 1 0 0 1 0 1 1  
#define LOC_76 76   // 8'b 0 1 0 0 1 1 0 0  
#define LOC_77 77   // 8'b 0 1 0 0 1 1 0 1  
#define LOC_78 78   // 8'b 0 1 0 0 1 1 1 0  
#define LOC_79 79   // 8'b 0 1 0 0 1 1 1 1  
#define LOC_80 80   // 8'b 0 1 0 1 0 0 0 0  
#define LOC_81 81   // 8'b 0 1 0 1 0 0 0 1  
#define LOC_82 82   // 8'b 0 1 0 1 0 0 1 0  
#define LOC_83 83   // 8'b 0 1 0 1 0 0 1 1  
#define LOC_84 84   // 8'b 0 1 0 1 0 1 0 0  
#define LOC_85 85   // 8'b 0 1 0 1 0 1 0 1  
#define LOC_86 86   // 8'b 0 1 0 1 0 1 1 0  
#define LOC_87 87   // 8'b 0 1 0 1 0 1 1 1  
#define LOC_88 88   // 8'b 0 1 0 1 1 0 0 0  
#define LOC_89 89   // 8'b 0 1 0 1 1 0 0 1  
#define LOC_90 90   // 8'b 0 1 0 1 1 0 1 0  
#define LOC_91 91   // 8'b 0 1 0 1 1 0 1 1  
#define LOC_92 92   // 8'b 0 1 0 1 1 1 0 0  
#define LOC_93 93   // 8'b 0 1 0 1 1 1 0 1  
#define LOC_94 94   // 8'b 0 1 0 1 1 1 1 0  
#define LOC_95 95   // 8'b 0 1 0 1 1 1 1 1  
#define LOC_96 96   // 8'b 0 1 1 0 0 0 0 0  
#define LOC_97 97   // 8'b 0 1 1 0 0 0 0 1  
#define LOC_98 98   // 8'b 0 1 1 0 0 0 1 0  
#define LOC_99 99   // 8'b 0 1 1 0 0 0 1 1  
#define LOC_100 100 // 8'b 0 1 1 0 0 1 0 0    
#define LOC_101 101 // 8'b 0 1 1 0 0 1 0 1    
#define LOC_102 102 // 8'b 0 1 1 0 0 1 1 0    
#define LOC_103 103 // 8'b 0 1 1 0 0 1 1 1    
#define LOC_104 104 // 8'b 0 1 1 0 1 0 0 0    
#define LOC_105 105 // 8'b 0 1 1 0 1 0 0 1    
#define LOC_106 106 // 8'b 0 1 1 0 1 0 1 0    
#define LOC_107 107 // 8'b 0 1 1 0 1 0 1 1    
#define LOC_108 108 // 8'b 0 1 1 0 1 1 0 0    
#define LOC_109 109 // 8'b 0 1 1 0 1 1 0 1    
#define LOC_110 110 // 8'b 0 1 1 0 1 1 1 0    
#define LOC_111 111 // 8'b 0 1 1 0 1 1 1 1    
#define LOC_112 112 // 8'b 0 1 1 1 0 0 0 0    
#define LOC_113 113 // 8'b 0 1 1 1 0 0 0 1    
#define LOC_114 114 // 8'b 0 1 1 1 0 0 1 0    
#define LOC_115 115 // 8'b 0 1 1 1 0 0 1 1    
#define LOC_116 116 // 8'b 0 1 1 1 0 1 0 0    
#define LOC_117 117 // 8'b 0 1 1 1 0 1 0 1    
#define LOC_118 118 // 8'b 0 1 1 1 0 1 1 0    
#define LOC_119 119 // 8'b 0 1 1 1 0 1 1 1    
#define LOC_120 120 // 8'b 0 1 1 1 1 0 0 0    
#define LOC_121 121 // 8'b 0 1 1 1 1 0 0 1    
#define LOC_122 122 // 8'b 0 1 1 1 1 0 1 0    
#define LOC_123 123 // 8'b 0 1 1 1 1 0 1 1    
#define LOC_124 124 // 8'b 0 1 1 1 1 1 0 0    
#define LOC_125 125 // 8'b 0 1 1 1 1 1 0 1    
#define LOC_126 126 // 8'b 0 1 1 1 1 1 1 0    
#define LOC_127 127 // 8'b 0 1 1 1 1 1 1 1    

    
    void dbgOutputLoc(uint32_t outVal);
    
// *****************************************************************************
/**
@Function
    void dbgOutputValue ( unsigned int outVal ) 

  @Summary
    Used to output the sensor value read from the
    message queue.

  @Description
    Used to output the value that is read from a sensor and stored to the 
    message queue. This routine outputs to 8 PIC i/o lines. When called, the 
    routine writes the value to 7 of those 8 lines.
    The 8th line is toggled to indicate that a new value has been written.

  @Precondition
    The value of outVal must be <= 127.

  @Parameters
    @param outVal is the value that is to be sent to the PIC i/o lines

  @Example
    @code
        uint32_t value = 2;
        dbgOutputVal(value);
 */
void dbgOutputVal(uint32_t outVal);

// *****************************************************************************
/**
@Function
    void dbgUARTVal(unsigned char outVal)

  @Summary
    Used to output average of every 4 sensor value reads from the
    message queue.

  @Description
    Used to output the average of the last values read from the sensor message queue.
    This routine outputs to UART. 

  @Precondition
    The value of outVal must be an 8 bit ASCI char.

  @Parameters
    @param outVal is the value that is to be sent to the UART interface

  @Example
    @code
        unsigned char value = 'a';
        dbgUARTVal(value);
 */
void dbgUARTVal(unsigned char outVal);
        
void ohNoh(void);

void writeIntTo1(uint8_t value);

void writeIntTo2(uint8_t value);

void UARTstringPLZ(const char *string);
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif




#endif /* _DEBUG_H */

/* *****************************************************************************
 End of File
 */
