#ifndef RTE_SIGNAL_IF_H
#define RTE_SIGNAL_IF_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * RTE signal interface - lop trung gian giua Application va BSP/DeviceDrivers.
 * Application CHI duoc include file nay, KHONG duoc include ds18b20.h,
 * bsp_onewire.h, hay bat ky driver cu the nao khac truc tiep.
 *
 * Neu sau nay doi cam bien nhiet do (vi du sang loai I2C thay vi 1-Wire),
 * chi can sua rte_signal_if.c - app.c khong doi 1 dong nao.
 */

/* Goi 1 lan luc khoi dong he thong (truoc vong lap chinh / truoc khi tao task) */
void RTE_Init(void);

/* Non-blocking - tach lam 2 buoc de App_Run() khong bi chan boi delay 750ms:
 * 1. Goi RTE_StartTempConversion() de bat dau do
 * 2. Sau toi thieu 750ms (Application tu quan ly thoi gian cho bang
 *    HAL_GetTick(), KHONG dung HAL_Delay), goi RTE_ReadTempResult()
 *    de lay gia tri. Neu loi, tra ve -999.0f */
void  RTE_StartTempConversion(void);
float RTE_ReadTempResult(void);

#ifdef __cplusplus
}
#endif

#endif /* RTE_SIGNAL_IF_H */
