#include "scheduler.h"

#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define TASKS_N 2
#define TICK_VAL 100

static Task_TypeDef tasks[TASKS_N];
static SCHEDULER_HandleTypeDef Sche;

void Init_500ms(void);
void Init_1000ms(void);
void Task_500ms(void);
void Task_1000ms(void);

int main(void) {
    unsigned char TaskID1;
    unsigned char TaskID2;

    /*init the scheduler with two tasks and a tick time of 100ms and run for 10
     * seconds only*/
    HIL_SCHEDULER_InitScheduler(&Sche, TASKS_N, TICK_VAL, tasks, 10000);

    /*register two task with thier corresponding init fucntions and their
     * periodicyt, 100ms and 500ms*/
    TaskID1 = HIL_SCHEDULER_RegisterTask(&Sche, Init_500ms, Task_500ms, 500);
    TaskID2 = HIL_SCHEDULER_RegisterTask(&Sche, Init_1000ms, Task_1000ms, 1000);

    /*run the scheduler for the amount of time stablished in Sche.timeout*/
    HIL_SCHEDULER_StartScheduler(&Sche);

    return 0;
}

void Init_500ms(void) {
    printf("Init task 500 millisecond\n");
}

void Init_1000ms(void) {
    printf("Init task 1000 millisecond\n");
}

void Task_500ms(void) {
    static int loop = 0;
    // printf("This is a counter from task 500ms: %d\n", loop++);
}

void Task_1000ms(void) {
    static int loop = 0;
    // printf("This is a counter from task 1000ms: %d\n", loop++);
}
long milliseconds(void) {
    return clock() / (CLOCKS_PER_SEC / 1000);
}

void HIL_SCHEDULER_InitScheduler(SCHEDULER_HandleTypeDef* hscheduler,
                                 unsigned char tasks_number,
                                 unsigned char base_tick,
                                 Task_TypeDef* task_tcb, unsigned int timeout) {
    if (hscheduler == NULL || task_tcb == NULL)
        return;

    hscheduler->tasks = tasks_number;
    hscheduler->tick = base_tick;
    hscheduler->taskPtr = task_tcb;
    hscheduler->timeout = timeout;
    hscheduler->tasksCount = 0;

    for (int i = 0; i < tasks_number; i++) {
        hscheduler->taskPtr[i].elapsed = 0;
        hscheduler->taskPtr[i].initFunc = NULL;
        hscheduler->taskPtr[i].period = 0;
        hscheduler->taskPtr[i].taskFunc = NULL;
        hscheduler->taskPtr[i].enabled = 0;
    }
}

uint8_t HIL_SCHEDULER_RegisterTask(SCHEDULER_HandleTypeDef* hscheduler,
                                   void (*initPtr)(void), void (*taskPtr)(void),
                                   uint32_t period) {
    if (hscheduler == NULL)
        return 0;

    if (taskPtr == NULL)
        return 0;

    if ((period < hscheduler->tick) || (period % hscheduler->tick != 0))
        return 0;

    if (hscheduler->tasksCount < hscheduler->tasks) {
        hscheduler->taskPtr[hscheduler->tasksCount].initFunc = initPtr;
        hscheduler->taskPtr[hscheduler->tasksCount].taskFunc = taskPtr;
        hscheduler->taskPtr[hscheduler->tasksCount].period = period;
        hscheduler->taskPtr[hscheduler->tasksCount].elapsed = 0;
        hscheduler->taskPtr[hscheduler->tasksCount].enabled = 1;
    }

    printf("Registration for task : %d , period %d , enabled %d, addr 0x%x, \n",
           hscheduler->tasksCount, period,
           hscheduler->taskPtr[hscheduler->tasksCount].enabled,
           hscheduler->taskPtr[hscheduler->tasksCount].taskFunc);
    return ++hscheduler->tasksCount;
}
uint8_t HIL_SCHEDULER_StopTask(SCHEDULER_HandleTypeDef* hscheduler,
                               uint8_t task) {
    if (hscheduler == NULL)
        return 0;
    if (task == 0)
        return 0;
    if (hscheduler->tasksCount < task)
        return 0;

    hscheduler->taskPtr[--task].enabled = 0;
    return 1;
}
uint8_t HIL_SCHEDULER_StartTask(SCHEDULER_HandleTypeDef* hscheduler,
                                uint8_t task) {
    if (hscheduler == NULL)
        return 0;
    if (task == 0)
        return 0;
    if (hscheduler->tasksCount < task)
        return 0;

    if (hscheduler->taskPtr[task - 1].enabled == 0)
        hscheduler->taskPtr[task - 1].enabled = 1;

    return hscheduler->taskPtr[task - 1].enabled == 1;
}
uint8_t HIL_SCHEDULER_PeriodTask(SCHEDULER_HandleTypeDef* hscheduler,
                                 uint8_t task, uint32_t period) {
    if (hscheduler == NULL)
        return 0;
    if (task == 0)
        return 0;
    if (hscheduler->tasksCount < task)
        return 0;
    if (period % hscheduler->tick != 0)
        return 0;

    hscheduler->taskPtr[task - 1].period = period;

    return 1;
}
void HIL_SCHEDULER_StartScheduler(SCHEDULER_HandleTypeDef* hscheduler) {
    if (hscheduler == NULL)
        return;
    printf("StartScheduler\n");
    for (int i = 0; i < hscheduler->tasksCount; i++) {
        printf("Init Functions\n");
        if (hscheduler->taskPtr[i].initFunc != NULL)
            hscheduler->taskPtr[i].initFunc();
    }
    uint8_t last_tick = 0;
    while (1) {
        // printf("Functions Execution\n");
        if (milliseconds() - last_tick >= hscheduler->tick) {
            last_tick = milliseconds();
            // printf("Milliseconds() = %d\n", last_tick);
            for (int i = 0; i < hscheduler->tasksCount; i++) {
                if (hscheduler->taskPtr[i].enabled == 1) {
                    hscheduler->taskPtr[i].elapsed += hscheduler->tick;
                    // printf("elapsed = %d, period = %d\n",
                    //    hscheduler->taskPtr[i].elapsed,
                    //    hscheduler->taskPtr[i].period);

                    if (hscheduler->taskPtr[i].elapsed >=
                        hscheduler->taskPtr[i].period) {
                        // printf("Task to be excecuted = %d\n", i);
                        hscheduler->taskPtr[i].taskFunc();
                        hscheduler->taskPtr[i].elapsed = 0;
                    }
                }
            }
        }
        if (milliseconds() >= hscheduler->timeout) {
            printf("Scheduler timeout\n");
            return;
        }
    }
}
