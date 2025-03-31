#ifndef BSP_TIMER_H_
#define BSP_TIMER_H_

#define TMR_COUNT 4

typedef enum
{
    TMR_ONCE_MODE = 0,  /*한번만 카운터만 동작 하는 모드*/
    TMR_AUTO_MODE = 1   /*자동 타이머 작동 모드*/
}TMR_MODE_E;

/*타이머 구조체 선언, 멤버변수는 C 컴파일러시 최적화 문제를 방지 하기 위해 volatile 선언*/
typedef struct
{
    volatile uint8_t Mode;      // 카운터 모드
    volatile uint8_t Flag;      // 타이머 도달 플래그
    volatile uint32_t Count;    // 카운터
    volatile uint32_t PreLoad;  // 카운터 사전 로드 값      
}SOFT_TMR;

void bsp_InitTimer(void);
void bsp_DelayMS(uint32_t n);

#endif