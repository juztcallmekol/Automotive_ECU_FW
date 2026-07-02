#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------*/

/* Exported Types ----------------------------------------------------*/
typedef enum
{
    LOG_LEVEL_INFO = 0,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,

    LOG_LEVEL_MAX
} DebugLevel_t;

/* Exported Functions ------------------------------------------------*/
void Debug_Log(DebugLevel_t level, const char *msg);

/* Exported Macros ---------------------------------------------------*/
#define LOG_INFO(msg)      Debug_Log(LOG_LEVEL_INFO,  (msg))
#define LOG_WARN(msg)      Debug_Log(LOG_LEVEL_WARN,  (msg))
#define LOG_ERROR(msg)     Debug_Log(LOG_LEVEL_ERROR, (msg))
#define LOG_FATAL(msg)     Debug_Log(LOG_LEVEL_FATAL, (msg))

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_H */
