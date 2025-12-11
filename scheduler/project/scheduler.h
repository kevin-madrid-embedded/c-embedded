
#include<stdint.h>

typedef struct _task
{
    uint32_t period;          /*How often the task shopud run in ms*/
    uint32_t elapsed;         /*the cuurent elapsed time*/
    void (*initFunc)(void);   /*pointer to init task function*/
    void (*taskFunc)(void);   /*pointer to task function*/
    uint8_t enabled;          /*Flag to stop/start the task*/
    //Add more elements if required
}Task_TypeDef;

typedef struct _scheduler
{
    uint8_t tasks;         /*number of task to handle*/
    uint32_t tick;          /*the time base in ms*/
    uint32_t timeout;       /*the number of milliseconds the scheduler should run*/
    uint8_t tasksCount;    /*internal task counter*/
    Task_TypeDef *taskPtr;  /*Pointer to buffer for the TCB tasks*/
    //Add more elements if required
}SCHEDULER_HandleTypeDef;

void HIL_SCHEDULER_InitScheduler( SCHEDULER_HandleTypeDef *hscheduler, 
                                        unsigned char tasks_number,unsigned char base_tick, 
                                        Task_TypeDef * task_tcb, unsigned int timeout);

uint8_t HIL_SCHEDULER_RegisterTask( SCHEDULER_HandleTypeDef *hscheduler, void (*initPtr)(void), void (*taskPtr)(void), uint32_t period );
uint8_t HIL_SCHEDULER_StopTask( SCHEDULER_HandleTypeDef *hscheduler, uint8_t task );
uint8_t HIL_SCHEDULER_StartTask( SCHEDULER_HandleTypeDef *hscheduler, uint8_t task );
uint8_t HIL_SCHEDULER_PeriodTask( SCHEDULER_HandleTypeDef *hscheduler, uint8_t task, uint32_t period );
void HIL_SCHEDULER_StartScheduler( SCHEDULER_HandleTypeDef *hscheduler );
