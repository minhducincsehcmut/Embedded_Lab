#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#define TIMER1_PERIOD pdMS_TO_TICKS(2000) // ahihi
#define TIMER2_PERIOD pdMS_TO_TICKS(3000) // ihaha
#define TIMER1_COUNT 10
#define TIMER2_COUNT 5
volatile uint32_t ulIdleCycleCount = 0UL;
volatile uint32_t ulCallCount = 0UL;
TimerHandle_t xTimer1Printing, xTimer2Printing;

void vApplicationIdleHook ( void )
{
    ulIdleCycleCount++;
}

static void prvTimerCallback( TimerHandle_t xTimer )
        {
            TickType_t xTimeNow;
            uint32_t ulExecutionCount;
     // Count so lan chay
            ulExecutionCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
            ulExecutionCount++;
            vTimerSetTimerID( xTimer, ( void * ) ulExecutionCount );


            xTimeNow = xTaskGetTickCount();
          if( xTimer == xTimer1Printing){
                printf("print Ahihi %ld \r\n", xTimeNow);
                if( ulExecutionCount >= TIMER1_COUNT){
                    xTimerStop( xTimer, 0);
                    printf("Timer 1 stopped \n");
                }
          }
          else if( xTimer == xTimer2Printing){ // Print ihaha
            printf("print iHaha %ld \r\n", xTimeNow);
            if( ulExecutionCount >= TIMER2_COUNT)
            {
                    xTimerStop( xTimer, 0);
                    printf("Timer 2 stopped \n");
            }
          }
}

void app_main(void)
{
    BaseType_t xTimer1Started, xTimer2Started;

     xTimer1Printing = xTimerCreate("PrintAhihi", TIMER1_PERIOD, pdTRUE, 0, prvTimerCallback);


     xTimer2Printing = xTimerCreate("PrintiHaha", TIMER2_PERIOD, pdTRUE, 0, prvTimerCallback);

    if( ( xTimer1Printing != NULL ) && ( xTimer2Printing != NULL ) )
    {
        xTimer1Started = xTimerStart( xTimer1Printing, 0 );
        xTimer2Started = xTimerStart( xTimer2Printing, 0 );
    }
}
