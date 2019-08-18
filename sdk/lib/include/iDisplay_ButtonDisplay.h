#ifndef IDISPLAY_BUTTONDISPLAY_H
#define IDISPLAY_BUTTONDISPLAY_H

#include "exportdef.h"
#include <stdint.h>
#include <stdbool.h>


#define IDISPLAY_BUTTONDISPLAY_H_Revision (180430001)

// ----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    No_Error,
    Err_NoMem,
    Err_DeviceNotFound,
    Err_DeviceNotOpen,
    Err_DeviceAlreadyOpened,
    Err_DevNotExist,
    Err_InvalidParameter,
    Err_Timeout,
    Err_TransferFailed,
    Err_IncorrectChecksum,
} iDRetCode;


/*
 */
void LIB_API_CALL iD_getVersionOfLibrary(uint8_t out_ver[32]);

/*
 */
iDRetCode LIB_API_CALL iD_USB_DeviceOpen(int vid, int pid);
iDRetCode LIB_API_CALL iD_USB_DeviceClose(void);
iDRetCode LIB_API_CALL iD_USB_FirmwareUpdate(uint8_t *fwBinPtr, uint32_t fwBinSize);

/*
 */
iDRetCode LIB_API_CALL iD_USB_ShowImageOnButton(uint8_t buttonIdx, uint8_t *bmpImgPtr);
iDRetCode LIB_API_CALL iD_USB_CleanScreen(uint8_t r, uint8_t g, uint8_t b);

/*
 */
iDRetCode LIB_API_CALL iD_USB_SetBrightness(uint8_t percentage);
iDRetCode LIB_API_CALL iD_USB_GetFirmwareVersion(uint8_t out_verStr[32]);
iDRetCode LIB_API_CALL iD_USB_GetCustomSerialNumber(uint8_t out_sn[32]);

/*
 */
typedef enum
{
    EVT_Button,
    EVT_ADC
}USB_EVT_TYPE;

typedef enum BtnState
{
    Btn_Unchanged = -1,
    Btn_Released,
    Btn_Pressed
}BtnState;

typedef struct
{
    uint16_t eventType;     // USB_EVT_TYPE
    uint16_t dataLength;    // bytes in data
    uint8_t  data[0];       // USB_Event_Button or USB_Event_ADC
}USB_EVENT_USER;

typedef struct
{
    int8_t buttonState[0];  // BtnState
}USB_Event_Button;

typedef struct
{
    uint16_t ch[0];
}USB_Event_ADC;

iDRetCode LIB_API_CALL iD_USB_WaitEvent(uint8_t out_eventBuf[256], int waitingTime_ms);

/*
 * Demo Mode
 */
iDRetCode LIB_API_CALL iD_USB_UpdateDemoImages(uint8_t frameIdx, uint16_t interval_ms, bool showFullImgFlag, const uint8_t *fullSizeOfScreenBMPBuf, int bufLen, bool isLastFrame);
iDRetCode LIB_API_CALL iD_USB_PerformDemoMode();
iDRetCode LIB_API_CALL iD_USB_ResetDemoFrameOfAll();


#ifdef __cplusplus
}   // extern "C"
#endif
#endif // IDISPLAY_BUTTONDISPLAY_H
