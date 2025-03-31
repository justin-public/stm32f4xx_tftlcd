#include "bsp.h"

static volatile uint32_t s_uiDelayCount = 0;
static volatile uint8_t s_ucTimeOutFlag = 0;

/*구조체를 통해서 s_tTmr 4개의 타이머에 한개씩 고유 정보를 저장*/
static SOFT_TMR s_tTmr[TMR_COUNT];

__IO int32_t g_iRunTime = 0;

/*이 코드 내부에서만 사용하는 함수들을 선언*/
static void bsp_SoftTimerDec(SOFT_TMR *_tmr);


/*
*********************************************************************************************************
* 함수 이름: bsp_InitTimer
* 기능 설명: 시스템 틱 중단을 구성하고, 펌웨어 타이머 변수를 초기화
* 형 매개: 없음
* 반환 값: 없음
*********************************************************************************************************
*/
void bsp_InitTimer(void)
{
    uint8_t i;

    for(i=0; i<TMR_COUNT; i++)
    {
        s_tTmr[i].Count = 0;      // 4개의 타이머 카운터 값 모두 0으로 초기화
        s_tTmr[i].PreLoad = 0;    
        s_tTmr[i].Flag = 0;       // 플래그값 모두 0으로 초기화
        s_tTmr[i].Mode = TMR_ONCE_MODE; 
    }
    /*SystemCoreClock 를 168MHz 로 할경우 1000Hz 1ms(1/1000초) 주기를 가짐 
      1ms 주기당 168,000 클록 사이클 동작
      초당 1000번에 인터럽트가 발생
      각 인터럽트 사이 간격 1ms 
    */
    SysTick_Config(SystemCoreClock/1000);   
}

/*
*********************************************************************************************************
* 함수 이름: SysTick_ISR
* 기능 설명: 주기마다 인터럽트 서비스 루틴을 실행하는 함수
* 형 매개: 없음
* 반환 값: 없음
*********************************************************************************************************
*/
extern void bsp_RunPer1ms(void);
extern void bsp_RunPer10ms(void);

void SysTick_ISR(void)
{
    //static uint8_t s_sount = 0;
    //uint8_t i;

    if(s_uiDelayCount > 0)
    {
        if(--s_uiDelayCount == 0)     
        {
            s_ucTimeOutFlag = 1;
        }    
    }
#if 0    
    for(i=0; i<TMR_COUNT; i++)
    {
        bsp_SoftTimerDec(&s_tTmr[i]);
    }

    g_iRunTime++;
    if (g_iRunTime == 0x7FFFFFFF)
    {
        g_iRunTime = 0;
    }

    if(++s_sount >= 10)
    {
        s_sount = 0;
    }
#endif    
}

/*
*********************************************************************************************************
* 함수 이름: bsp_SoftTimerDec
* 기능 설명: 매 1ms마다 모든 타이머 변수를 1씩 감소. SysTick_ISR 주기적으로 호출됨.
* 형 매개: SOFT_TMR *_tmr 타이머 변수 관련 정보 
* 반환 값: 없음
*********************************************************************************************************
*/
#if 0
static void bsp_SoftTimerDec(SOFT_TMR *_tmr)
{
    if(_tmr->Count > 0)
    {
        if (--_tmr->Count == 0)
        {
            _tmr->Flag = 1;

            if(_tmr->Mode == TMR_AUTO_MODE)
            {
                _tmr->Count = _tmr->PreLoad;
            }
        }
    }
}
#endif
/*
*********************************************************************************************************
* 함수 이름: bsp_DelayMS
* 기능 설명: 값을 입력 하면 1ms 단위로 동작하는 함수
* 형 매개: uint32_t  
* 반환 값: 없음
*********************************************************************************************************
*/
void bsp_DelayMS(uint32_t n)
{
    if(n == 0){
        return; 
    }
    else if(n == 1)
    {
        n = 2;   
    }
    DISABLE_INT();          // 인터럽트 비활성화

    s_uiDelayCount = n;     // 1000 ms
    //s_ucTimeOutFlag = 0;

    ENABLE_INT();          // 인터럽트 활성화

    while(s_uiDelayCount > 0)
    {
        if (s_ucTimeOutFlag == 1){
            s_ucTimeOutFlag = 0;
        }
    }

}