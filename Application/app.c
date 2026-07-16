#include "app.h"
#include "debug.h"
#include "main.h"
#include <stdio.h>
#include "i2c.h"
#include "rte_signal_if.h"
/* CHI include RTE - KHONG include ds18b20.h */

/* ------------------------------------------------------------------------
 * State machine doc nhiet do khong chan (non-blocking).
 * Nhiet do dong co bien thien cham, khong can doc lien tuc moi vong lap -
 * chi can doc dinh ky vai giay 1 lan, khong lam cham cac tac vu khac
 * (doc khoang cach/toc do, xu ly TTC...) trong App_Run().
 * ------------------------------------------------------------------------ */
typedef enum {
    TEMP_STATE_IDLE,
    TEMP_STATE_WAIT_CONVERSION,
} TempReadState_t;

static TempReadState_t s_temp_state = TEMP_STATE_IDLE;
static uint32_t         s_temp_last_action_tick = 0;
static float             s_engine_temp_cached = -999.0f;

#define TEMP_READ_PERIOD_MS   3000U  /* Doc lai moi 3 giay */
#define TEMP_CONVERT_WAIT_MS  750U   /* Thoi gian cho DS18B20 convert xong */

static void Temp_Update(void)
{
    uint32_t now = HAL_GetTick();

    switch (s_temp_state) {

    case TEMP_STATE_IDLE:
        /* Toi chu ky doc moi thi bat dau 1 lan convert */
        if ((now - s_temp_last_action_tick) >= TEMP_READ_PERIOD_MS) {
            RTE_StartTempConversion();   /* xem ghi chu ben duoi ve ham nay */
            s_temp_last_action_tick = now;
            s_temp_state = TEMP_STATE_WAIT_CONVERSION;
        }
        break;

    case TEMP_STATE_WAIT_CONVERSION:
        /* Cho du 750ms KHONG dung HAL_Delay - chi kiem tra tick */
        if ((now - s_temp_last_action_tick) >= TEMP_CONVERT_WAIT_MS) {
            s_engine_temp_cached = RTE_ReadTempResult();

            if (s_engine_temp_cached <= -999.0f) {
                LOG_ERROR("DS18B20: loi doc hoac khong phat hien thiet bi");
            } else {
                char msg[64];
                snprintf(msg, sizeof(msg), "DS18B20: engine_temp = %.2f C",
                         s_engine_temp_cached);
                LOG_INFO(msg);
            }

            s_temp_last_action_tick = now;
            s_temp_state = TEMP_STATE_IDLE;
        }
        break;
    }
}

void App_Init(void)
{
    RTE_Init();
    s_temp_last_action_tick = HAL_GetTick();
}

void App_Run(void)
{
    Temp_Update();

    /* TODO: cac tac vu khac cua app se them vao day sau -
     * doc khoang cach/toc do, tinh TTC, gui CAN...
     * Tat ca deu phai theo kieu non-blocking tuong tu Temp_Update() o tren,
     * khong dung HAL_Delay() truc tiep trong App_Run(). */
}
