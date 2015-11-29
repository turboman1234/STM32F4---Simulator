/*
 * Copyright (c) 2010 All Right Reserved
 * Project: Multi Beverage Brewer
 * Author: Emanuil Markov
 * Summary: VTimers module.
 */
#include "stm32f4xx_conf.h"
#include "definitions.h"
#include "VTimer.h"

volatile u32 arrVTimers[MAX_TIMER_COUNT];
u16 vtimersRestartCount;
volatile u32 timerCounter = 1;

void InitTIM2(void)
{
    TIM_TimeBaseInitTypeDef TIM_2_TimeBaseInitStruct;
    NVIC_InitTypeDef MYNVIC;
    
    //AHB clock = 50, MHz
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    // Configure TIM2 IRQ
    MYNVIC.NVIC_IRQChannel = TIM2_IRQn;
    MYNVIC.NVIC_IRQChannelCmd = ENABLE;
    MYNVIC.NVIC_IRQChannelPreemptionPriority = 0;
    MYNVIC.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&MYNVIC);
   
    TIM_DeInit(TIM2);
    
    //TIM_2 clock = 50, MHz / prescaler = 50 000 000 / 500 = 100 000, Hz
    //time = TIM_2 period * (1 / TIM_2 clock) = 100 * (1 / 100 000) = 0.001, s
       
    TIM_2_TimeBaseInitStruct.TIM_Prescaler = 500;
    TIM_2_TimeBaseInitStruct.TIM_Period = 100;
    TIM_2_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // 0
    TIM_2_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_2_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    
    TIM_TimeBaseInit(TIM2, &TIM_2_TimeBaseInitStruct);
    
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void TIM2_IRQHandler(void)
{
    timerCounter = timerCounter + 1;
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void InitVTimers(void)
{
    int i;
   
    ResetTimerCounter();
    vtimersRestartCount = 0;
    
    for (i = 0; i < MAX_TIMER_COUNT; i++)
    {
        arrVTimers[i] = 0;
    }
    
    InitTIM2();
    EnableVTimers();
}

void EnableVTimers(void)
{
    TIM_Cmd(TIM2, ENABLE);
}

void DisableVTimers(void)
{
    TIM_Cmd(TIM2, DISABLE);
}

int ConvertTimerIDToVTimerIndex(int timerID)
{
    assert_param(IS_TIMER_ID_VALID(timerID));
    int index;
    
    //convert timerID to index for VTimers array
    index = timerID % 58; //58 is first timer's id
    
    return index;
}

void SetVTimerValue(int timerID, u32 ticks)
{
    int index = ConvertTimerIDToVTimerIndex(timerID);
    
    arrVTimers[index] = mGetTimerCounter() + ticks;
}

u32 GetVTimerValue(int timerID)
{
    int index = ConvertTimerIDToVTimerIndex(timerID);
    
    if (mGetTimerCounter() < arrVTimers[index])
    {
    	return arrVTimers[timerID] - mGetTimerCounter();
    }
    else
    {
        return 0;
    }
}

void ClearVTimer(int timerID)
{
    int index = ConvertTimerIDToVTimerIndex(timerID);
    
    arrVTimers[index] = 0;
}

int IsVTimerElapsed(int timerID)
{
    int index = ConvertTimerIDToVTimerIndex(timerID);
    
    if(arrVTimers[index] <= mGetTimerCounter())
    {
        return ELAPSED;
    }
    else
    {
        return NOT_ELAPSED;
    }
}

void VTimersReset(void)
{
    u32 tick = mGetTimerCounter(),
    newTick = ResetTimerCounter();
    
    vtimersRestartCount++;
    
    for (int i = 0; i < MAX_TIMER_COUNT; i++)
    {
        if (arrVTimers[i] > tick)
        {
            arrVTimers[i] = newTick + (arrVTimers[i] - tick);
        }
        else if (arrVTimers[i] != 0)
        {
            arrVTimers[i] = 0;
        }
    }
}
void VTimerTask(void)
{
    if (mGetTimerCounter() > 0xffff0000)
    {
        VTimersReset();
    }
}

u32 ResetTimerCounter(void)
{
    return timerCounter = 1;
}

u32 GetTimerCounter(void)
{
    return timerCounter;
}


