#ifndef GAME_DEF_H
#define GAME_DEF_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        GAME_MODE_MUSIC,
        GAME_MODE_MATH,
        GAME_MODE_MENU
    } game_mode_t;

    typedef enum
    {
        GAME_STATE_INIT,
        GAME_STATE_RUNNING,
        GAME_STATE_OVER,
        GAME_STATE_WAITING_FOR_INPUT
    } game_state_t;

#ifdef __cplusplus
}
#endif

#endif // GAME_DEF_H
