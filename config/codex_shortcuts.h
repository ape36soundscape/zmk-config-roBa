#pragma once

/* Change this one value to 0 for macOS Cmd/Option shortcuts. */
#define CODEX_OS_WINDOWS 1

#if CODEX_OS_WINDOWS
#define CX_QUICK_CHAT       &kp LC(LA(N))
#define CX_NEW_CHAT         &kp LC(N)
#define CX_PREVIOUS_CHAT    &kp LC(LS(LEFT_BRACKET))
#define CX_NEXT_CHAT        &kp LC(LS(RIGHT_BRACKET))
#define CX_COMMAND_MENU     &kp LC(LS(P))
#define CX_SETTINGS         &kp LC(COMMA)
#else
#define CX_QUICK_CHAT       &kp LG(LA(N))
#define CX_NEW_CHAT         &kp LG(N)
#define CX_PREVIOUS_CHAT    &kp LG(LS(LEFT_BRACKET))
#define CX_NEXT_CHAT        &kp LG(LS(RIGHT_BRACKET))
#define CX_COMMAND_MENU     &kp LG(LS(P))
#define CX_SETTINGS         &kp LG(COMMA)
#endif

/* These installed-app shortcuts are Ctrl-based on both platforms. */
#define CX_DICTATION        &kp LC(LS(D))
#define CX_SEND             &kp ENTER

/* The installed app exposes Search Chats but has no default keybinding. */
#define CX_SEARCH_CHATS     &none

/*
 * Reservation keys: bind these in ChatGPT Settings > Keyboard Shortcuts,
 * Settings > Voice, or a separately approved companion bridge.
 */
#define CX_FOCUS_RESERVED        &kp F13
#define CX_INTERRUPT_RESERVED    &kp F14
#define CX_VOICE_RESERVED        &kp F15
#define CX_REASON_DOWN_RESERVED  &kp F16
#define CX_REASON_UP_RESERVED    &kp F17
#define CX_REVIEW_RESERVED       &kp F18
#define CX_DEBUG_RESERVED        &kp F19
#define CX_REFACTOR_RESERVED     &kp F20
#define CX_AGENT_PREV_RESERVED   &kp F21
#define CX_AGENT_NEXT_RESERVED   &kp F22
#define CX_APPROVE_RESERVED      &kp F23
#define CX_DECLINE_RESERVED      &kp F24

/* Review has no verified default keybinding; use the explicit reservation. */
#define CX_REVIEW_TAB            CX_REVIEW_RESERVED
