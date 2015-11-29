#define mGetTimerCounter()		GetTimerCounter()
#define MAX_TIMER_COUNT                 16

void InitTIM2(void);
void TIM2_IRQHandler(void);
void InitVTimers(void);
void EnableVTimers(void);
void DisableVTimers(void);
int ConvertTimerIDToVTimerIndex(int timerID);
void SetVTimerValue(int timerID, u32 ticks);
u32 GetVTimerValue(int timerID);
void ClearVTimer(int timerID);
int IsVTimerElapsed(int timerID);
void VTimersReset(void);
void VTimerTask(void);
u32 ResetTimerCounter(void);
u32 GetTimerCounter(void);
