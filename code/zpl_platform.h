/*

ZPL - Platform module

License:
    This software is dual-licensed to the public domain and under the following
    license: you are granted a perpetual, irrevocable license to copy, modify,
    publish, and distribute this file as you see fit.
    
Warranty:
    No warranty is implied, use at your own risk.
    
Usage:
    #define ZPL_PLATFORM_IMPLEMENTATION exactly in ONE source file right BEFORE including the library, like:
    
    #define ZPL_PLATFRM_IMPLEMENTATION
    #include"zpl_platform.h"
    
Credits:
    Dominik Madarasz (GitHub: zaklaus)
    Ginger Bill (GitHub: gingerBill)
    
Version History:
    1.00 - Initial version
    
*/

#ifndef ZPL_INCLUDE_ZPL_PLATFORM_H
#define ZPL_INCLUDE_ZPL_PLATFORM_H

#if defined(__cplusplus)
extern "C" {
#endif
    
    ////////////////////////////////////////////////////////////
    //
    // NOTE:
    // Coordinate system - +ve x - left to right
    //                  - +ve y - bottom to top
    //                  - Relative to window
    //
    // TODO: 
    //
    // Proper documentation for this with code examples
    //
    // Windows Support - Complete
    // OS X Support - Missing:
    //     * Sofware framebuffer
    //     * (show|hide) window
    //     * show_cursor
    //     * toggle (fullscreen|borderless)
    //     * set window position
    //     * Clipboard
    //     * Game controllers
    // Linux Support - None
    //
    
#ifndef ZPL_MAX_GAME_CONTROLLER_COUNT
#define ZPL_MAX_GAME_CONTROLLER_COUNT 4
#endif
    
    typedef enum zplKeyType {
        zplKey_Unknown = 0,  // Unhandled key
        
        // NOTE: Allow the basic printable keys to be aliased with their chars
        zplKey_0 = '0',
        zplKey_1,
        zplKey_2,
        zplKey_3,
        zplKey_4,
        zplKey_5,
        zplKey_6,
        zplKey_7,
        zplKey_8,
        zplKey_9,
        
        zplKey_A = 'A',
        zplKey_B,
        zplKey_C,
        zplKey_D,
        zplKey_E,
        zplKey_F,
        zplKey_G,
        zplKey_H,
        zplKey_I,
        zplKey_J,
        zplKey_K,
        zplKey_L,
        zplKey_M,
        zplKey_N,
        zplKey_O,
        zplKey_P,
        zplKey_Q,
        zplKey_R,
        zplKey_S,
        zplKey_T,
        zplKey_U,
        zplKey_V,
        zplKey_W,
        zplKey_X,
        zplKey_Y,
        zplKey_Z,
        
        zplKey_Lbracket  = '[',
        zplKey_Rbracket  = ']',
        zplKey_Semicolon = ';',
        zplKey_Comma     = ',',
        zplKey_Period    = '.',
        zplKey_Quote     = '\'',
        zplKey_Slash     = '/',
        zplKey_Backslash = '\\',
        zplKey_Grave     = '`',
        zplKey_Equals    = '=',
        zplKey_Minus     = '-',
        zplKey_Space     = ' ',
        
        zplKey__Pad = 128,   // NOTE: make sure ASCII is reserved
        
        zplKey_Escape,       // Escape
        zplKey_Lcontrol,     // Left Control
        zplKey_Lshift,       // Left Shift
        zplKey_Lalt,         // Left Alt
        zplKey_Lsystem,      // Left OS specific: window (Windows and Linux), apple/cmd (MacOS X), ...
        zplKey_Rcontrol,     // Right Control
        zplKey_Rshift,       // Right Shift
        zplKey_Ralt,         // Right Alt
        zplKey_Rsystem,      // Right OS specific: window (Windows and Linux), apple/cmd (MacOS X), ...
        zplKey_Menu,         // Menu
        zplKey_Return,       // Return
        zplKey_Backspace,    // Backspace
        zplKey_Tab,          // Tabulation
        zplKey_Pageup,       // Page up
        zplKey_Pagedown,     // Page down
        zplKey_End,          // End
        zplKey_Home,         // Home
        zplKey_Insert,       // Insert
        zplKey_Delete,       // Delete
        zplKey_Plus,         // +
        zplKey_Subtract,     // -
        zplKey_Multiply,     // *
        zplKey_Divide,       // /
        zplKey_Left,         // Left arrow
        zplKey_Right,        // Right arrow
        zplKey_Up,           // Up arrow
        zplKey_Down,         // Down arrow
        zplKey_Numpad0,      // Numpad 0
        zplKey_Numpad1,      // Numpad 1
        zplKey_Numpad2,      // Numpad 2
        zplKey_Numpad3,      // Numpad 3
        zplKey_Numpad4,      // Numpad 4
        zplKey_Numpad5,      // Numpad 5
        zplKey_Numpad6,      // Numpad 6
        zplKey_Numpad7,      // Numpad 7
        zplKey_Numpad8,      // Numpad 8
        zplKey_Numpad9,      // Numpad 9
        zplKey_NumpadDot,    // Numpad .
        zplKey_NumpadEnter,  // Numpad Enter
        zplKey_F1,           // F1
        zplKey_F2,           // F2
        zplKey_F3,           // F3
        zplKey_F4,           // F4
        zplKey_F5,           // F5
        zplKey_F6,           // F6
        zplKey_F7,           // F7
        zplKey_F8,           // F8
        zplKey_F9,           // F8
        zplKey_F10,          // F10
        zplKey_F11,          // F11
        zplKey_F12,          // F12
        zplKey_F13,          // F13
        zplKey_F14,          // F14
        zplKey_F15,          // F15
        zplKey_Pause,        // Pause
        
        zplKey_Count,
    } zplKeyType;
    
    /* TODO: Change name? */
    typedef u8 zplKeyState;
    typedef enum zplKeyStateFlag {
        zplKeyState_Down     = ZPL_BIT(0),
        zplKeyState_Pressed  = ZPL_BIT(1),
        zplKeyState_Released = ZPL_BIT(2)
    } zplKeyStateFlag;
    
    ZPL_DEF void zpl_key_state_update(zplKeyState *s, b32 is_down);
    
    typedef enum zplMouseButtonType {
        zplMouseButton_Left,
        zplMouseButton_Middle,
        zplMouseButton_Right,
        zplMouseButton_X1,
        zplMouseButton_X2,
        
        zplMouseButton_Count
    } zplMouseButtonType;
    
    typedef enum zplControllerAxisType {
        zplControllerAxis_LeftX,
        zplControllerAxis_LeftY,
        zplControllerAxis_RightX,
        zplControllerAxis_RightY,
        zplControllerAxis_LeftTrigger,
        zplControllerAxis_RightTrigger,
        
        zplControllerAxis_Count
    } zplControllerAxisType;
    
    typedef enum zplControllerButtonType {
        zplControllerButton_Up,
        zplControllerButton_Down,
        zplControllerButton_Left,
        zplControllerButton_Right,
        zplControllerButton_A,
        zplControllerButton_B,
        zplControllerButton_X,
        zplControllerButton_Y,
        zplControllerButton_LeftShoulder,
        zplControllerButton_RightShoulder,
        zplControllerButton_Back,
        zplControllerButton_Start,
        zplControllerButton_LeftThumb,
        zplControllerButton_RightThumb,
        
        zplControllerButton_Count
    } zplControllerButtonType;
    
    typedef struct zplGameController {
        b16 is_connected, is_analog;
        
        f32        axes[zplControllerAxis_Count];
        zplKeyState buttons[zplControllerButton_Count];
    } zplGameController;
    
#if defined(ZPL_SYSTEM_WINDOWS)
    typedef struct _XINPUT_GAMEPAD XINPUT_GAMEPAD;
    typedef struct _XINPUT_STATE   XINPUT_STATE;
    typedef struct _XINPUT_VIBRATION XINPUT_VIBRATION;
    
#define ZPL_XINPUT_GET_STATE(name) unsigned long __stdcall name(unsigned long dwUserIndex, XINPUT_STATE *pState)
    typedef ZPL_XINPUT_GET_STATE(zplXInputGetStateProc);
    
#define ZPL_XINPUT_SET_STATE(name) unsigned long __stdcall name(unsigned long dwUserIndex, XINPUT_VIBRATION *pVibration)
    typedef ZPL_XINPUT_SET_STATE(zplXInputSetStateProc);
#endif
    
    
    typedef enum zplWindowFlag {
        zplWindow_Fullscreen        = ZPL_BIT(0),
        zplWindow_Hidden            = ZPL_BIT(1),
        zplWindow_Borderless        = ZPL_BIT(2),
        zplWindow_Resizable         = ZPL_BIT(3),
        zplWindow_Minimized         = ZPL_BIT(4),
        zplWindow_Maximized         = ZPL_BIT(5),
        zplWindow_FullscreenDesktop = zplWindow_Fullscreen | zplWindow_Borderless,
    } zplWindowFlag;
    
    typedef enum zplRendererType {
        zplRenderer_Opengl,
        zplRenderer_Software,
        
        zplRenderer_Count,
    } zplRendererType;
    
    
    
#if defined(ZPL_SYSTEM_WINDOWS) && !defined(_WINDOWS_)
    typedef struct tagBITMAPINFOHEADER {
        unsigned long biSize;
        long          biWidth;
        long          biHeight;
        u16           biPlanes;
        u16           biBitCount;
        unsigned long biCompression;
        unsigned long biSizeImage;
        long          biXPelsPerMeter;
        long          biYPelsPerMeter;
        unsigned long biClrUsed;
        unsigned long biClrImportant;
    } BITMAPINFOHEADER, *PBITMAPINFOHEADER;
    typedef struct tagRZPLQUAD {
        u8 rzplBlue;
        u8 rzplGreen;
        u8 rzplRed;
        u8 rzplReserved;
    } RZPLQUAD;
    typedef struct tagBITMAPINFO {
        BITMAPINFOHEADER bmiHeader;
        RZPLQUAD          bmiColors[1];
    } BITMAPINFO, *PBITMAPINFO;
#endif
    
    typedef struct zplPlatform {
        b32 is_initialized;
        
        void *window_handle;
        i32   window_x, window_y;
        i32   window_width, window_height;
        u32   window_flags;
        b16   window_is_closed, window_has_focus;
        
#if defined(ZPL_SYSTEM_WINDOWS)
        void *win32_dc;
#elif defined(ZPL_SYSTEM_OSX)
        void *osx_autorelease_pool; // TODO: Is this really needed?
#endif
        
        zplRendererType renderer_type;
        union {
            struct {
                void *      context;
                i32         major;
                i32         minor;
                b16         core, compatible;
                zplDllHandle dll_handle;
            } opengl;
            
            // NOTE: Software rendering
            struct {
#if defined(ZPL_SYSTEM_WINDOWS)
                BITMAPINFO win32_bmi;
#endif
                void *     memory;
                isize      memory_size;
                i32        pitch;
                i32        bits_per_pixel;
            } sw_framebuffer;
        };
        
        zplKeyState keys[zplKey_Count];
        struct {
            zplKeyState control;
            zplKeyState alt;
            zplKeyState shift;
        } key_modifiers;
        
        Rune  char_buffer[256];
        isize char_buffer_count;
        
        b32 mouse_clip;
        i32 mouse_x, mouse_y;
        i32 mouse_dx, mouse_dy; // NOTE: Not raw mouse movement
        i32 mouse_raw_dx, mouse_raw_dy; // NOTE: Raw mouse movement
        f32 mouse_wheel_delta;
        zplKeyState mouse_buttons[zplMouseButton_Count];
        
        zplGameController game_controllers[ZPL_MAX_GAME_CONTROLLER_COUNT];
        
        f64              curr_time;
        f64              dt_for_frame;
        b32              quit_requested;
        
#if defined(ZPL_SYSTEM_WINDOWS)
        struct {
            zplXInputGetStateProc *get_state;
            zplXInputSetStateProc *set_state;
        } xinput;
#endif
    } zplPlatform;
    
    
    typedef struct zplVideoMode {
        i32 width, height;
        i32 bits_per_pixel;
    } zplVideoMode;
    
    ZPL_DEF zplVideoMode zpl_video_mode                     (i32 width, i32 height, i32 bits_per_pixel);
    ZPL_DEF b32         zpl_video_mode_is_valid            (zplVideoMode mode);
    ZPL_DEF zplVideoMode zpl_video_mode_get_desktop         (void);
    ZPL_DEF isize       zpl_video_mode_get_fullscreen_modes(zplVideoMode *modes, isize max_mode_count); // NOTE: returns mode count
    ZPL_DEF ZPL_COMPARE_PROC(zpl_video_mode_cmp);     // NOTE: Sort smallest to largest (Ascending)
    ZPL_DEF ZPL_COMPARE_PROC(zpl_video_mode_dsc_cmp); // NOTE: Sort largest to smallest (Descending)
    
    
    // NOTE: Software rendering
    ZPL_DEF b32   zpl_platform_init_with_software         (zplPlatform *p, char const *window_title, i32 width, i32 height, u32 window_flags);
    // NOTE: OpenGL Rendering
    ZPL_DEF b32   zpl_platform_init_with_opengl           (zplPlatform *p, char const *window_title, i32 width, i32 height, u32 window_flags, i32 major, i32 minor, b32 core, b32 compatible);
    ZPL_DEF void  zpl_platform_update                     (zplPlatform *p);
    ZPL_DEF void  zpl_platform_display                    (zplPlatform *p);
    ZPL_DEF void  zpl_platform_destroy                    (zplPlatform *p);
    ZPL_DEF void  zpl_platform_show_cursor                (zplPlatform *p, b32 show);
    ZPL_DEF void  zpl_platform_set_mouse_position         (zplPlatform *p, i32 x, i32 y);
    ZPL_DEF void  zpl_platform_set_controller_vibration   (zplPlatform *p, isize index, f32 left_motor, f32 right_motor);
    ZPL_DEF b32   zpl_platform_has_clipboard_text         (zplPlatform *p);
    ZPL_DEF void  zpl_platform_set_clipboard_text         (zplPlatform *p, char const *str);
    ZPL_DEF char *zpl_platform_get_clipboard_text         (zplPlatform *p, zplAllocator a);
    ZPL_DEF void  zpl_platform_set_window_position        (zplPlatform *p, i32 x, i32 y);
    ZPL_DEF void  zpl_platform_set_window_title           (zplPlatform *p, char const *title, ...) ZPL_PRINTF_ARGS(2);
    ZPL_DEF void  zpl_platform_toggle_fullscreen          (zplPlatform *p, b32 fullscreen_desktop);
    ZPL_DEF void  zpl_platform_toggle_borderless          (zplPlatform *p);
    ZPL_DEF void  zpl_platform_make_opengl_context_current(zplPlatform *p);
    ZPL_DEF void  zpl_platform_show_window                (zplPlatform *p);
    ZPL_DEF void  zpl_platform_hide_window                (zplPlatform *p);
    
#if defined(__cplusplus)
}
#endif

#if defined(ZPL_PLATFORM_IMPLEMENTATION) && !defined(ZPL_PLATFORM_IMPLEMENTATION_DONE)
#define ZPL_PLATFORM_IMPLEMENTATION_DONE

#if defined(__cplusplus)
extern "C" {
#endif
    
    zpl_inline void zpl_key_state_update(zplKeyState *s, b32 is_down) {
        b32 was_down = (*s & zplKeyState_Down) != 0;
        is_down = is_down != 0; // NOTE: Make sure it's a boolean
        ZPL_MASK_SET(*s, is_down,               zplKeyState_Down);
        ZPL_MASK_SET(*s, !was_down &&  is_down, zplKeyState_Pressed);
        ZPL_MASK_SET(*s,  was_down && !is_down, zplKeyState_Released);
    }
    
#if defined(ZPL_SYSTEM_WINDOWS)
    
#ifndef ERROR_DEVICE_NOT_CONNECTED
#define ERROR_DEVICE_NOT_CONNECTED 1167
#endif
    
    ZPL_XINPUT_GET_STATE(zplXInputGetState_Stub) {
        zpl_unused(dwUserIndex); zpl_unused(pState);
        return ERROR_DEVICE_NOT_CONNECTED;
    }
    ZPL_XINPUT_SET_STATE(zplXInputSetState_Stub) {
        zpl_unused(dwUserIndex); zpl_unused(pVibration);
        return ERROR_DEVICE_NOT_CONNECTED;
    }
    
    
    zpl_internal zpl_inline f32 zpl__process_xinput_stick_value(i16 value, i16 dead_zone_threshold) {
        f32 result = 0;
        
        if (value < -dead_zone_threshold)
            result = cast(f32) (value + dead_zone_threshold) / (32768.0f - dead_zone_threshold);
        else if (value > dead_zone_threshold)
            result = cast(f32) (value - dead_zone_threshold) / (32767.0f - dead_zone_threshold);
        
        return result;
    }
    
    zpl_internal void zpl__platform_resize_dib_section(zplPlatform *p, i32 width, i32 height) {
        if ((p->renderer_type == zplRenderer_Software) &&
            !(p->window_width == width && p->window_height == height)) {
            BITMAPINFO bmi = {0};
            
            if (width == 0 || height == 0)
                return;
            
            p->window_width  = width;
            p->window_height = height;
            
            // TODO: Is this slow to get the desktop mode everytime?
            p->sw_framebuffer.bits_per_pixel = zpl_video_mode_get_desktop().bits_per_pixel;
            p->sw_framebuffer.pitch = (p->sw_framebuffer.bits_per_pixel * width / 8);
            
            bmi.bmiHeader.biSize = zpl_size_of(bmi.bmiHeader);
            bmi.bmiHeader.biWidth       = width;
            bmi.bmiHeader.biHeight      = height; // NOTE: -ve is top-down, +ve is bottom-up
            bmi.bmiHeader.biPlanes      = 1;
            bmi.bmiHeader.biBitCount    = cast(u16)p->sw_framebuffer.bits_per_pixel;
            bmi.bmiHeader.biCompression = 0 /*BI_RZPL*/;
            
            p->sw_framebuffer.win32_bmi = bmi;
            
            
            if (p->sw_framebuffer.memory)
                zpl_vm_free(zpl_virtual_memory(p->sw_framebuffer.memory, p->sw_framebuffer.memory_size));
            
            {
                isize memory_size = p->sw_framebuffer.pitch * height;
                zplVirtualMemory vm = zpl_vm_alloc(0, memory_size);
                p->sw_framebuffer.memory      = vm.data;
                p->sw_framebuffer.memory_size = vm.size;
            }
        }
    }
    
    
    zpl_internal zplKeyType zpl__win32_from_vk(unsigned int key) {
        // NOTE: Letters and numbers are defined the same for VK_* and ZPL_*
        if (key >= 'A' && key < 'Z') return cast(zplKeyType)key;
        if (key >= '0' && key < '9') return cast(zplKeyType)key;
        switch (key) {
            case VK_ESCAPE: return zplKey_Escape;
            
            case VK_LCONTROL: return zplKey_Lcontrol;
            case VK_LSHIFT:   return zplKey_Lshift;
            case VK_LMENU:    return zplKey_Lalt;
            case VK_LWIN:     return zplKey_Lsystem;
            case VK_RCONTROL: return zplKey_Rcontrol;
            case VK_RSHIFT:   return zplKey_Rshift;
            case VK_RMENU:    return zplKey_Ralt;
            case VK_RWIN:     return zplKey_Rsystem;
            case VK_MENU:     return zplKey_Menu;
            
            case VK_OEM_4:      return zplKey_Lbracket;
            case VK_OEM_6:      return zplKey_Rbracket;
            case VK_OEM_1:      return zplKey_Semicolon;
            case VK_OEM_COMMA:  return zplKey_Comma;
            case VK_OEM_PERIOD: return zplKey_Period;
            case VK_OEM_7:      return zplKey_Quote;
            case VK_OEM_2:      return zplKey_Slash;
            case VK_OEM_5:      return zplKey_Backslash;
            case VK_OEM_3:      return zplKey_Grave;
            case VK_OEM_PLUS:   return zplKey_Equals;
            case VK_OEM_MINUS:  return zplKey_Minus;
            
            case VK_SPACE:  return zplKey_Space;
            case VK_RETURN: return zplKey_Return;
            case VK_BACK:   return zplKey_Backspace;
            case VK_TAB:    return zplKey_Tab;
            
            case VK_PRIOR:  return zplKey_Pageup;
            case VK_NEXT:   return zplKey_Pagedown;
            case VK_END:    return zplKey_End;
            case VK_HOME:   return zplKey_Home;
            case VK_INSERT: return zplKey_Insert;
            case VK_DELETE: return zplKey_Delete;
            
            case VK_ADD:      return zplKey_Plus;
            case VK_SUBTRACT: return zplKey_Subtract;
            case VK_MULTIPLY: return zplKey_Multiply;
            case VK_DIVIDE:   return zplKey_Divide;
            
            case VK_LEFT:  return zplKey_Left;
            case VK_RIGHT: return zplKey_Right;
            case VK_UP:    return zplKey_Up;
            case VK_DOWN:  return zplKey_Down;
            
            case VK_NUMPAD0:   return zplKey_Numpad0;
            case VK_NUMPAD1:   return zplKey_Numpad1;
            case VK_NUMPAD2:   return zplKey_Numpad2;
            case VK_NUMPAD3:   return zplKey_Numpad3;
            case VK_NUMPAD4:   return zplKey_Numpad4;
            case VK_NUMPAD5:   return zplKey_Numpad5;
            case VK_NUMPAD6:   return zplKey_Numpad6;
            case VK_NUMPAD7:   return zplKey_Numpad7;
            case VK_NUMPAD8:   return zplKey_Numpad8;
            case VK_NUMPAD9:   return zplKey_Numpad9;
            case VK_SEPARATOR: return zplKey_NumpadEnter;
            case VK_DECIMAL:   return zplKey_NumpadDot;
            
            case VK_F1:  return zplKey_F1;
            case VK_F2:  return zplKey_F2;
            case VK_F3:  return zplKey_F3;
            case VK_F4:  return zplKey_F4;
            case VK_F5:  return zplKey_F5;
            case VK_F6:  return zplKey_F6;
            case VK_F7:  return zplKey_F7;
            case VK_F8:  return zplKey_F8;
            case VK_F9:  return zplKey_F9;
            case VK_F10: return zplKey_F10;
            case VK_F11: return zplKey_F11;
            case VK_F12: return zplKey_F12;
            case VK_F13: return zplKey_F13;
            case VK_F14: return zplKey_F14;
            case VK_F15: return zplKey_F15;
            
            case VK_PAUSE: return zplKey_Pause;
        }
        return zplKey_Unknown;
    }
    LRESULT CALLBACK zpl__win32_window_callback(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        // NOTE: Silly callbacks
        zplPlatform *platform = cast(zplPlatform *)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
        b32 window_has_focus = (platform != NULL) && platform->window_has_focus;
        
        if (msg == WM_CREATE) { // NOTE: Doesn't need the platform
            // NOTE: https://msdn.microsoft.com/en-us/library/windows/desktop/ms645536(v=vs.85).aspx
            RAWINPUTDEVICE rid[2] = {0};
            
            // NOTE: Keyboard
            rid[0].usUsagePage = 0x01;
            rid[0].usUsage     = 0x06;
            rid[0].dwFlags     = 0x00000030/*RIDEV_NOLEGACY*/; // NOTE: Do not generate legacy messages such as WM_KEYDOWN
            rid[0].hwndTarget  = hWnd;
            
            // NOTE: Mouse
            rid[1].usUsagePage = 0x01;
            rid[1].usUsage     = 0x02;
            rid[1].dwFlags     = 0; // NOTE: adds HID mouse and also allows legacy mouse messages to allow for window movement etc.
            rid[1].hwndTarget  = hWnd;
            
            if (RegisterRawInputDevices(rid, zpl_count_of(rid), zpl_size_of(rid[0])) == false) {
                DWORD err = GetLastError();
                ZPL_PANIC("Failed to initialize raw input device for win32."
                          "Err: %u", err);
            }
        }
        
        if (!platform)
            return DefWindowProcW(hWnd, msg, wParam, lParam);
        
        switch (msg) {
            case WM_CLOSE:
            case WM_DESTROY:
            platform->window_is_closed = true;
            return 0;
            
            case WM_QUIT: {
                platform->quit_requested = true;
            } break;
            
            case WM_UNICHAR: {
                if (window_has_focus) {
                    if (wParam == '\r')
                        wParam = '\n';
                    // TODO: Does this need to be thread-safe?
                    platform->char_buffer[platform->char_buffer_count++] = cast(Rune)wParam;
                }
            } break;
            
            
            case WM_INPUT: {
                RAWINPUT raw = {0};
                unsigned int size = zpl_size_of(RAWINPUT);
                
                if (!GetRawInputData(cast(HRAWINPUT)lParam, RID_INPUT, &raw, &size, zpl_size_of(RAWINPUTHEADER))) {
                    return 0;
                }
                switch (raw.header.dwType) {
                    case RIM_TYPEKEYBOARD: {
                        // NOTE: Many thanks to https://blog.molecular-matters.com/2011/09/05/properly-handling-keyboard-input/
                        // for the
                        RAWKEYBOARD *raw_kb = &raw.data.keyboard;
                        unsigned int vk = raw_kb->VKey;
                        unsigned int scan_code = raw_kb->MakeCode;
                        unsigned int flags = raw_kb->Flags;
                        // NOTE: e0 and e1 are escape sequences used for certain special keys, such as PRINT and PAUSE/BREAK.
                        // NOTE: http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
                        b32 is_e0   = (flags & RI_KEY_E0) != 0;
                        b32 is_e1   = (flags & RI_KEY_E1) != 0;
                        b32 is_up   = (flags & RI_KEY_BREAK) != 0;
                        b32 is_down = !is_up;
                        
                        // TODO: Should I handle scan codes?
                        
                        if (vk == 255) {
                            // NOTE: Discard "fake keys"
                            return 0;
                        } else if (vk == VK_SHIFT) {
                            // NOTE: Correct left/right shift
                            vk = MapVirtualKeyW(scan_code, MAPVK_VSC_TO_VK_EX);
                        } else if (vk == VK_NUMLOCK) {
                            // NOTE: Correct PAUSE/BREAK and NUM LOCK and set the extended bit
                            scan_code = MapVirtualKeyW(vk, MAPVK_VK_TO_VSC) | 0x100;
                        }
                        
                        if (is_e1) {
                            // NOTE: Escaped sequences, turn vk into the correct scan code
                            // except for VK_PAUSE (it's a bug)
                            if (vk == VK_PAUSE)
                                scan_code = 0x45;
                            else
                                scan_code = MapVirtualKeyW(vk, MAPVK_VK_TO_VSC);
                        }
                        
                        switch (vk) {
                            case VK_CONTROL: vk = (is_e0) ? VK_RCONTROL : VK_LCONTROL; break;
                            case VK_MENU:    vk = (is_e0) ? VK_RMENU    : VK_LMENU;   break;
                            
                            case VK_RETURN: if (is_e0)  vk = VK_SEPARATOR; break; // NOTE: Numpad return
                            case VK_DELETE: if (!is_e0) vk = VK_DECIMAL;   break; // NOTE: Numpad dot
                            case VK_INSERT: if (!is_e0) vk = VK_NUMPAD0;   break;
                            case VK_HOME:   if (!is_e0) vk = VK_NUMPAD7;   break;
                            case VK_END:    if (!is_e0) vk = VK_NUMPAD1;   break;
                            case VK_PRIOR:  if (!is_e0) vk = VK_NUMPAD9;   break;
                            case VK_NEXT:   if (!is_e0) vk = VK_NUMPAD3;   break;
                            
                            // NOTE: The standard arrow keys will always have their e0 bit set, but the
                            // corresponding keys on the NUMPAD will not.
                            case VK_LEFT:  if (!is_e0) vk = VK_NUMPAD4; break;
                            case VK_RIGHT: if (!is_e0) vk = VK_NUMPAD6; break;
                            case VK_UP:    if (!is_e0) vk = VK_NUMPAD8; break;
                            case VK_DOWN:  if (!is_e0) vk = VK_NUMPAD2; break;
                            
                            // NUMPAD 5 doesn't have its e0 bit set
                            case VK_CLEAR: if (!is_e0) vk = VK_NUMPAD5; break;
                        }
                        
                        // NOTE: Set appropriate key state flags
                        zpl_key_state_update(&platform->keys[zpl__win32_from_vk(vk)], is_down);
                        
                    } break;
                    case RIM_TYPEMOUSE: {
                        RAWMOUSE *raw_mouse = &raw.data.mouse;
                        u16 flags = raw_mouse->usButtonFlags;
                        long dx = +raw_mouse->lLastX;
                        long dy = -raw_mouse->lLastY;
                        
                        if (flags & RI_MOUSE_WHEEL)
                            platform->mouse_wheel_delta = cast(i16)raw_mouse->usButtonData;
                        
                        platform->mouse_raw_dx = dx;
                        platform->mouse_raw_dy = dy;
                    } break;
                }
            } break;
            
            default: break;
        }
        
        return DefWindowProcW(hWnd, msg, wParam, lParam);
    }
    
    
    typedef void *wglCreateContextAttribsARB_Proc(void *hDC, void *hshareContext, int const *attribList);
    
    
    b32 zpl__platform_init(zplPlatform *p, char const *window_title, zplVideoMode mode, zplRendererType type, u32 window_flags) {
        WNDCLASSEXW wc = {zpl_size_of(WNDCLASSEXW)};
        DWORD ex_style = 0, style = 0;
        RECT wr;
        u16 title_buffer[256] = {0}; // TODO: zpl_local_persist this?
        
        wc.style = CS_HREDRAW | CS_VREDRAW; // | CS_OWNDC
        wc.lpfnWndProc   = zpl__win32_window_callback;
        wc.hbrBackground = cast(HBRUSH)GetStockObject(0/*WHITE_BRUSH*/);
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = L"zpl-win32-wndclass"; // TODO: Is this enough?
        wc.hInstance     = GetModuleHandleW(NULL);
        
        if (RegisterClassExW(&wc) == 0) {
            MessageBoxW(NULL, L"Failed to register the window class", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
            return false;
        }
        
        if ((window_flags & zplWindow_Fullscreen) && !(window_flags & zplWindow_Borderless)) {
            DEVMODEW screen_settings = {zpl_size_of(DEVMODEW)};
            screen_settings.dmPelsWidth	 = mode.width;
            screen_settings.dmPelsHeight = mode.height;
            screen_settings.dmBitsPerPel = mode.bits_per_pixel;
            screen_settings.dmFields     = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
            
            if (ChangeDisplaySettingsW(&screen_settings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
                if (MessageBoxW(NULL, L"The requested fullscreen mode is not supported by\n"
                                L"your video card. Use windowed mode instead?",
                                L"",
                                MB_YESNO|MB_ICONEXCLAMATION) == IDYES) {
                    window_flags &= ~zplWindow_Fullscreen;
                } else {
                    mode = zpl_video_mode_get_desktop();
                    screen_settings.dmPelsWidth	 = mode.width;
                    screen_settings.dmPelsHeight = mode.height;
                    screen_settings.dmBitsPerPel = mode.bits_per_pixel;
                    ChangeDisplaySettingsW(&screen_settings, CDS_FULLSCREEN);
                }
            }
        }
        
        
        // ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        // style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
        
        style |= WS_VISIBLE;
        
        if (window_flags & zplWindow_Hidden)       style &= ~WS_VISIBLE;
        if (window_flags & zplWindow_Resizable)    style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
        if (window_flags & zplWindow_Maximized)    style |=  WS_MAXIMIZE;
        if (window_flags & zplWindow_Minimized)    style |=  WS_MINIMIZE;
        
        // NOTE: Completely ignore the given mode and just change it
        if (window_flags & zplWindow_FullscreenDesktop) {
            mode = zpl_video_mode_get_desktop();
        }
        
        if ((window_flags & zplWindow_Fullscreen) || (window_flags & zplWindow_Borderless)) {
            style |= WS_POPUP;
        } else {
            style |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
        }
        
        
        wr.left   = 0;
        wr.top    = 0;
        wr.right  = mode.width;
        wr.bottom = mode.height;
        AdjustWindowRect(&wr, style, false);
        
        p->window_flags  = window_flags;
        p->window_handle = CreateWindowExW(ex_style,
                                           wc.lpszClassName,
                                           cast(wchar_t const *)zpl_utf8_to_ucs2(title_buffer, zpl_size_of(title_buffer), window_title),
                                           style,
                                           CW_USEDEFAULT, CW_USEDEFAULT,
                                           wr.right - wr.left, wr.bottom - wr.top,
                                           0, 0,
                                           GetModuleHandleW(NULL),
                                           NULL);
        
        if (!p->window_handle) {
            MessageBoxW(NULL, L"Window creation failed", L"Error", MB_OK|MB_ICONEXCLAMATION);
            return false;
        }
        
        p->win32_dc = GetDC(cast(HWND)p->window_handle);
        
        p->renderer_type = type;
        switch (p->renderer_type) {
            case zplRenderer_Opengl: {
                wglCreateContextAttribsARB_Proc *wglCreateContextAttribsARB;
                i32 attribs[8] = {0};
                isize c = 0;
                
                PIXELFORMATDESCRIPTOR pfd = {zpl_size_of(PIXELFORMATDESCRIPTOR)};
                pfd.nVersion     = 1;
                pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
                pfd.iPixelType   = PFD_TYPE_RGBA;
                pfd.cColorBits   = 32;
                pfd.cAlphaBits   = 8;
                pfd.cDepthBits   = 24;
                pfd.cStencilBits = 8;
                pfd.iLayerType   = PFD_MAIN_PLANE;
                
                SetPixelFormat(cast(HDC)p->win32_dc, ChoosePixelFormat(cast(HDC)p->win32_dc, &pfd), NULL);
                p->opengl.context = cast(void *)wglCreateContext(cast(HDC)p->win32_dc);
                wglMakeCurrent(cast(HDC)p->win32_dc, cast(HGLRC)p->opengl.context);
                
                if (p->opengl.major > 0) {
                    attribs[c++] = 0x2091; // WGL_CONTEXT_MAJOR_VERSION_ARB
                    attribs[c++] = zpl_max(p->opengl.major, 1);
                }
                if (p->opengl.major > 0 && p->opengl.minor >= 0) {
                    attribs[c++] = 0x2092; // WGL_CONTEXT_MINOR_VERSION_ARB
                    attribs[c++] = zpl_max(p->opengl.minor, 0);
                }
                
                if (p->opengl.core) {
                    attribs[c++] = 0x9126; // WGL_CONTEXT_PROFILE_MASK_ARB
                    attribs[c++] = 0x0001; // WGL_CONTEXT_CORE_PROFILE_BIT_ARB
                } else if (p->opengl.compatible) {
                    attribs[c++] = 0x9126; // WGL_CONTEXT_PROFILE_MASK_ARB
                    attribs[c++] = 0x0002; // WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
                }
                attribs[c++] = 0; // NOTE: tells the proc that this is the end of attribs
                
                wglCreateContextAttribsARB = cast(wglCreateContextAttribsARB_Proc *)wglGetProcAddress("wglCreateContextAttribsARB");
                if (wglCreateContextAttribsARB) {
                    HGLRC rc = cast(HGLRC)wglCreateContextAttribsARB(p->win32_dc, 0, attribs);
                    if (rc && wglMakeCurrent(cast(HDC)p->win32_dc, rc)) {
                        p->opengl.context = rc;
                    } else {
                        // TODO: Handle errors from GetLastError
                        // ERROR_INVALID_VERSION_ARB 0x2095
                        // ERROR_INVALID_PROFILE_ARB 0x2096
                    }
                }
                
            } break;
            
            case zplRenderer_Software:
            zpl__platform_resize_dib_section(p, mode.width, mode.height);
            break;
            
            default:
            ZPL_PANIC("Unknown window type");
            break;
        }
        
        SetForegroundWindow(cast(HWND)p->window_handle);
        SetFocus(cast(HWND)p->window_handle);
        SetWindowLongPtrW(cast(HWND)p->window_handle, GWLP_USERDATA, cast(LONG_PTR)p);
        
        p->window_width  = mode.width;
        p->window_height = mode.height;
        
        if (p->renderer_type == zplRenderer_Opengl) {
            p->opengl.dll_handle = zpl_dll_load("opengl32.dll");
        }
        
        { // Load XInput
            // TODO: What other dlls should I look for?
            zplDllHandle xinput_library = zpl_dll_load("xinput1_4.dll");
            p->xinput.get_state = zplXInputGetState_Stub;
            p->xinput.set_state = zplXInputSetState_Stub;
            
            if (!xinput_library) xinput_library = zpl_dll_load("xinput9_1_0.dll");
            if (!xinput_library) xinput_library = zpl_dll_load("xinput1_3.dll");
            if (!xinput_library) {
                // TODO: Proper Diagnostic
                zpl_printf_err("XInput could not be loaded. Controllers will not work!\n");
            } else {
                p->xinput.get_state = cast(zplXInputGetStateProc *)zpl_dll_proc_address(xinput_library, "XInputGetState");
                p->xinput.set_state = cast(zplXInputSetStateProc *)zpl_dll_proc_address(xinput_library, "XInputSetState");
            }
        }
        
        // Init keys
        zpl_zero_array(p->keys, zpl_count_of(p->keys));
        
        p->is_initialized = true;
        return true;
    }
    
    zpl_inline b32 zpl_platform_init_with_software(zplPlatform *p, char const *window_title,
                                                   i32 width, i32 height, u32 window_flags) {
        zplVideoMode mode;
        mode.width          = width;
        mode.height         = height;
        mode.bits_per_pixel = 32;
        return zpl__platform_init(p, window_title, mode, zplRenderer_Software, window_flags);
    }
    
    zpl_inline b32 zpl_platform_init_with_opengl(zplPlatform *p, char const *window_title,
                                                 i32 width, i32 height, u32 window_flags, i32 major, i32 minor, b32 core, b32 compatible) {
        zplVideoMode mode;
        mode.width          = width;
        mode.height         = height;
        mode.bits_per_pixel = 32;
        p->opengl.major      = major;
        p->opengl.minor      = minor;
        p->opengl.core       = cast(b16)core;
        p->opengl.compatible = cast(b16)compatible;
        return zpl__platform_init(p, window_title, mode, zplRenderer_Opengl, window_flags);
    }
    
#ifndef _XINPUT_H_
    typedef struct _XINPUT_GAMEPAD {
        u16 wButtons;
        u8  bLeftTrigger;
        u8  bRightTrigger;
        u16 sThumbLX;
        u16 sThumbLY;
        u16 sThumbRX;
        u16 sThumbRY;
    } XINPUT_GAMEPAD;
    
    typedef struct _XINPUT_STATE {
        DWORD          dwPacketNumber;
        XINPUT_GAMEPAD Gamepad;
    } XINPUT_STATE;
    
    typedef struct _XINPUT_VIBRATION {
        u16 wLeftMotorSpeed;
        u16 wRightMotorSpeed;
    } XINPUT_VIBRATION;
    
#define XINPUT_GAMEPAD_DPAD_UP              0x00000001
#define XINPUT_GAMEPAD_DPAD_DOWN            0x00000002
#define XINPUT_GAMEPAD_DPAD_LEFT            0x00000004
#define XINPUT_GAMEPAD_DPAD_RIGHT           0x00000008
#define XINPUT_GAMEPAD_START                0x00000010
#define XINPUT_GAMEPAD_BACK                 0x00000020
#define XINPUT_GAMEPAD_LEFT_THUMB           0x00000040
#define XINPUT_GAMEPAD_RIGHT_THUMB          0x00000080
#define XINPUT_GAMEPAD_LEFT_SHOULDER        0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER       0x0200
#define XINPUT_GAMEPAD_A                    0x1000
#define XINPUT_GAMEPAD_B                    0x2000
#define XINPUT_GAMEPAD_X                    0x4000
#define XINPUT_GAMEPAD_Y                    0x8000
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30
#endif
    
#ifndef XUSER_MAX_COUNT
#define XUSER_MAX_COUNT 4
#endif
    
    void zpl_platform_update(zplPlatform *p) {
        isize i;
        
        { // NOTE: Set window state
            // TODO: Should this be moved to zpl__win32_window_callback ?
            RECT window_rect;
            i32 x, y, w, h;
            
            GetClientRect(cast(HWND)p->window_handle, &window_rect);
            x = window_rect.left;
            y = window_rect.top;
            w = window_rect.right - window_rect.left;
            h = window_rect.bottom - window_rect.top;
            
            if ((p->window_width != w) || (p->window_height != h)) {
                if (p->renderer_type == zplRenderer_Software)
                    zpl__platform_resize_dib_section(p, w, h);
            }
            
            
            p->window_x = x;
            p->window_y = y;
            p->window_width = w;
            p->window_height = h;
            ZPL_MASK_SET(p->window_flags, IsIconic(cast(HWND)p->window_handle) != 0, zplWindow_Minimized);
            
            p->window_has_focus = GetFocus() == cast(HWND)p->window_handle;
        }
        
        { // NOTE: Set mouse position
            POINT mouse_pos;
            DWORD win_button_id[zplMouseButton_Count] = {
                VK_LBUTTON,
                VK_MBUTTON,
                VK_RBUTTON,
                VK_XBUTTON1,
                VK_XBUTTON2,
            };
            
            // NOTE: This needs to be GetAsyncKeyState as RAWMOUSE doesn't aways work for some odd reason
            // TODO: Try and get RAWMOUSE to work for key presses
            for (i = 0; i < zplMouseButton_Count; i++)
                zpl_key_state_update(p->mouse_buttons+i, GetAsyncKeyState(win_button_id[i]) < 0);
            
            GetCursorPos(&mouse_pos);
            ScreenToClient(cast(HWND)p->window_handle, &mouse_pos);
            {
                i32 x = mouse_pos.x;
                i32 y = p->window_height-1 - mouse_pos.y;
                p->mouse_dx = x - p->mouse_x;
                p->mouse_dy = y - p->mouse_y;
                p->mouse_x = x;
                p->mouse_y = y;
            }
            
            if (p->mouse_clip) {
                b32 update = false;
                i32 x = p->mouse_x;
                i32 y = p->mouse_y;
                if (p->mouse_x < 0) {
                    x = 0;
                    update = true;
                } else if (p->mouse_y > p->window_height-1) {
                    y = p->window_height-1;
                    update = true;
                }
                
                if (p->mouse_y < 0) {
                    y = 0;
                    update = true;
                } else if (p->mouse_x > p->window_width-1) {
                    x = p->window_width-1;
                    update = true;
                }
                
                if (update)
                    zpl_platform_set_mouse_position(p, x, y);
            }
            
            
        }
        
        
        // NOTE: Set Key/Button states
        if (p->window_has_focus) {
            p->char_buffer_count = 0; // TODO: Reset buffer count here or else where?
            
            // NOTE: Need to update as the keys only get updates on events
            for (i = 0; i < zplKey_Count; i++) {
                b32 is_down = (p->keys[i] & zplKeyState_Down) != 0;
                zpl_key_state_update(&p->keys[i], is_down);
            }
            
            p->key_modifiers.control = p->keys[zplKey_Lcontrol] | p->keys[zplKey_Rcontrol];
            p->key_modifiers.alt     = p->keys[zplKey_Lalt]     | p->keys[zplKey_Ralt];
            p->key_modifiers.shift   = p->keys[zplKey_Lshift]   | p->keys[zplKey_Rshift];
            
        }
        
        { // NOTE: Set Controller states
            isize max_controller_count = XUSER_MAX_COUNT;
            if (max_controller_count > zpl_count_of(p->game_controllers))
                max_controller_count = zpl_count_of(p->game_controllers);
            
            for (i = 0; i < max_controller_count; i++) {
                zplGameController *controller = &p->game_controllers[i];
                XINPUT_STATE controller_state = {0};
                if (p->xinput.get_state(cast(DWORD)i, &controller_state) != 0) {
                    // NOTE: The controller is not available
                    controller->is_connected = false;
                } else {
                    // NOTE: This controller is plugged in
                    // TODO: See if ControllerState.dwPacketNumber increments too rapidly
                    XINPUT_GAMEPAD *pad = &controller_state.Gamepad;
                    
                    controller->is_connected = true;
                    
                    // TODO: This is a square deadzone, check XInput to verify that the deadzone is "round" and do round deadzone processing.
                    controller->axes[zplControllerAxis_LeftX]  = zpl__process_xinput_stick_value(pad->sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
                    controller->axes[zplControllerAxis_LeftY]  = zpl__process_xinput_stick_value(pad->sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
                    controller->axes[zplControllerAxis_RightX] = zpl__process_xinput_stick_value(pad->sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
                    controller->axes[zplControllerAxis_RightY] = zpl__process_xinput_stick_value(pad->sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
                    
                    controller->axes[zplControllerAxis_LeftTrigger]  = cast(f32)pad->bLeftTrigger / 255.0f;
                    controller->axes[zplControllerAxis_RightTrigger] = cast(f32)pad->bRightTrigger / 255.0f;
                    
                    
                    if ((controller->axes[zplControllerAxis_LeftX] != 0.0f) ||
                        (controller->axes[zplControllerAxis_LeftY] != 0.0f)) {
                        controller->is_analog = true;
                    }
                    
#define ZPL__PROCESS_DIGITAL_BUTTON(button_type, xinput_button) \
                    zpl_key_state_update(&controller->buttons[button_type], (pad->wButtons & xinput_button) == xinput_button)
                    
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_A,              XINPUT_GAMEPAD_A);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_B,              XINPUT_GAMEPAD_B);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_X,              XINPUT_GAMEPAD_X);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_Y,              XINPUT_GAMEPAD_Y);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_LeftShoulder,  XINPUT_GAMEPAD_LEFT_SHOULDER);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_RightShoulder, XINPUT_GAMEPAD_RIGHT_SHOULDER);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_Start,          XINPUT_GAMEPAD_START);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_Back,           XINPUT_GAMEPAD_BACK);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_Left,           XINPUT_GAMEPAD_DPAD_LEFT);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_Right,          XINPUT_GAMEPAD_DPAD_RIGHT);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_Down,           XINPUT_GAMEPAD_DPAD_DOWN);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_Up,             XINPUT_GAMEPAD_DPAD_UP);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_LeftThumb,     XINPUT_GAMEPAD_LEFT_THUMB);
                    ZPL__PROCESS_DIGITAL_BUTTON(zplControllerButton_RightThumb,    XINPUT_GAMEPAD_RIGHT_THUMB);
#undef ZPL__PROCESS_DIGITAL_BUTTON
                }
            }
        }
        
        { // NOTE: Process pending messages
            MSG message;
            for (;;) {
                BOOL is_okay = PeekMessageW(&message, 0, 0, 0, PM_REMOVE);
                if (!is_okay) break;
                
                switch (message.message) {
                    case WM_QUIT:
                    p->quit_requested = true;
                    break;
                    
                    default:
                    TranslateMessage(&message);
                    DispatchMessageW(&message);
                    break;
                }
            }
        }
    }
    
    void zpl_platform_display(zplPlatform *p) {
        if (p->renderer_type == zplRenderer_Opengl) {
            SwapBuffers(cast(HDC)p->win32_dc);
        } else if (p->renderer_type == zplRenderer_Software) {
            StretchDIBits(cast(HDC)p->win32_dc,
                          0, 0, p->window_width, p->window_height,
                          0, 0, p->window_width, p->window_height,
                          p->sw_framebuffer.memory,
                          &p->sw_framebuffer.win32_bmi,
                          DIB_RGB_COLORS, SRCCOPY);
        } else {
            ZPL_PANIC("Invalid window rendering type");
        }
        
        {
            f64 prev_time = p->curr_time;
            f64 curr_time = zpl_time_now();
            p->dt_for_frame = curr_time - prev_time;
            p->curr_time = curr_time;
        }
    }
    
    
    void zpl_platform_destroy(zplPlatform *p) {
        if (p->renderer_type == zplRenderer_Opengl)
            wglDeleteContext(cast(HGLRC)p->opengl.context);
        else if (p->renderer_type == zplRenderer_Software)
            zpl_vm_free(zpl_virtual_memory(p->sw_framebuffer.memory, p->sw_framebuffer.memory_size));
        
        DestroyWindow(cast(HWND)p->window_handle);
    }
    
    void zpl_platform_show_cursor(zplPlatform *p, b32 show) {
        zpl_unused(p);
        ShowCursor(show);
    }
    
    void zpl_platform_set_mouse_position(zplPlatform *p, i32 x, i32 y) {
        POINT point;
        point.x = cast(LONG)x;
        point.y = cast(LONG)(p->window_height-1 - y);
        ClientToScreen(cast(HWND)p->window_handle, &point);
        SetCursorPos(point.x, point.y);
        
        p->mouse_x = point.x;
        p->mouse_y = p->window_height-1 - point.y;
    }
    
    
    
    void zpl_platform_set_controller_vibration(zplPlatform *p, isize index, f32 left_motor, f32 right_motor) {
        if (zpl_is_between(index, 0, ZPL_MAX_GAME_CONTROLLER_COUNT-1)) {
            XINPUT_VIBRATION vibration = {0};
            left_motor  = zpl_clamp01(left_motor);
            right_motor = zpl_clamp01(right_motor);
            vibration.wLeftMotorSpeed  = cast(WORD)(65535 * left_motor);
            vibration.wRightMotorSpeed = cast(WORD)(65535 * right_motor);
            
            p->xinput.set_state(cast(DWORD)index, &vibration);
        }
    }
    
    
    void zpl_platform_set_window_position(zplPlatform *p, i32 x, i32 y) {
        RECT rect;
        i32 width, height;
        
        GetClientRect(cast(HWND)p->window_handle, &rect);
        width  = rect.right - rect.left;
        height = rect.bottom - rect.top;
        MoveWindow(cast(HWND)p->window_handle, x, y, width, height, false);
    }
    
    void zpl_platform_set_window_title(zplPlatform *p, char const *title, ...) {
        u16 buffer[256] = {0};
        char str[512] = {0};
        va_list va;
        va_start(va, title);
        zpl_snprintf_va(str, zpl_size_of(str), title, va);
        va_end(va);
        
        if (str[0] != '\0')
            SetWindowTextW(cast(HWND)p->window_handle, cast(wchar_t const *)zpl_utf8_to_ucs2(buffer, zpl_size_of(buffer), str));
    }
    
    void zpl_platform_toggle_fullscreen(zplPlatform *p, b32 fullscreen_desktop) {
        // NOTE: From the man himself, Raymond Chen! (Modified for my need.)
        HWND handle = cast(HWND)p->window_handle;
        DWORD style = cast(DWORD)GetWindowLongW(handle, GWL_STYLE);
        WINDOWPLACEMENT placement;
        
        if (style & WS_OVERLAPPEDWINDOW) {
            MONITORINFO monitor_info = {zpl_size_of(monitor_info)};
            if (GetWindowPlacement(handle, &placement) &&
                GetMonitorInfoW(MonitorFromWindow(handle, 1), &monitor_info)) {
                style &= ~WS_OVERLAPPEDWINDOW;
                if (fullscreen_desktop) {
                    style &= ~WS_CAPTION;
                    style |= WS_POPUP;
                }
                SetWindowLongW(handle, GWL_STYLE, style);
                SetWindowPos(handle, HWND_TOP,
                             monitor_info.rcMonitor.left, monitor_info.rcMonitor.top,
                             monitor_info.rcMonitor.right - monitor_info.rcMonitor.left,
                             monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top,
                             SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
                
                if (fullscreen_desktop)
                    p->window_flags |= zplWindow_FullscreenDesktop;
                else
                    p->window_flags |= zplWindow_Fullscreen;
            }
        } else {
            style &= ~WS_POPUP;
            style |= WS_OVERLAPPEDWINDOW | WS_CAPTION;
            SetWindowLongW(handle, GWL_STYLE, style);
            SetWindowPlacement(handle, &placement);
            SetWindowPos(handle, 0, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                         SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
            
            p->window_flags &= ~zplWindow_Fullscreen;
        }
    }
    
    void zpl_platform_toggle_borderless(zplPlatform *p) {
        HWND handle = cast(HWND)p->window_handle;
        DWORD style = GetWindowLongW(handle, GWL_STYLE);
        b32 is_borderless = (style & WS_POPUP) != 0;
        
        ZPL_MASK_SET(style, is_borderless,  WS_OVERLAPPEDWINDOW | WS_CAPTION);
        ZPL_MASK_SET(style, !is_borderless, WS_POPUP);
        
        SetWindowLongW(handle, GWL_STYLE, style);
        
        ZPL_MASK_SET(p->window_flags, !is_borderless, zplWindow_Borderless);
    }
    
    
    
    zpl_inline void zpl_platform_make_opengl_context_current(zplPlatform *p) {
        if (p->renderer_type == zplRenderer_Opengl) {
            wglMakeCurrent(cast(HDC)p->win32_dc, cast(HGLRC)p->opengl.context);
        }
    }
    
    zpl_inline void zpl_platform_show_window(zplPlatform *p) {
        ShowWindow(cast(HWND)p->window_handle, SW_SHOW);
        p->window_flags &= ~zplWindow_Hidden;
    }
    
    zpl_inline void zpl_platform_hide_window(zplPlatform *p) {
        ShowWindow(cast(HWND)p->window_handle, SW_HIDE);
        p->window_flags |= zplWindow_Hidden;
    }
    
    zpl_inline zplVideoMode zpl_video_mode_get_desktop(void) {
        DEVMODEW win32_mode = {zpl_size_of(win32_mode)};
        EnumDisplaySettingsW(NULL, ENUM_CURRENT_SETTINGS, &win32_mode);
        return zpl_video_mode(win32_mode.dmPelsWidth, win32_mode.dmPelsHeight, win32_mode.dmBitsPerPel);
    }
    
    isize zpl_video_mode_get_fullscreen_modes(zplVideoMode *modes, isize max_mode_count) {
        DEVMODEW win32_mode = {zpl_size_of(win32_mode)};
        i32 count;
        for (count = 0;
             count < max_mode_count && EnumDisplaySettingsW(NULL, count, &win32_mode);
             count++) {
            modes[count] = zpl_video_mode(win32_mode.dmPelsWidth, win32_mode.dmPelsHeight, win32_mode.dmBitsPerPel);
        }
        
        zpl_sort_array(modes, count, zpl_video_mode_dsc_cmp);
        return count;
    }
    
    
    
    b32 zpl_platform_has_clipboard_text(zplPlatform *p) {
        b32 result = false;
        
        if (IsClipboardFormatAvailable(1/*CF_TEXT*/) &&
            OpenClipboard(cast(HWND)p->window_handle)) {
            HANDLE mem = GetClipboardData(1/*CF_TEXT*/);
            if (mem) {
                char *str = cast(char *)GlobalLock(mem);
                if (str && str[0] != '\0')
                    result = true;
                GlobalUnlock(mem);
            } else {
                return false;
            }
            
            CloseClipboard();
        }
        
        return result;
    }
    
    // TODO: Handle UTF-8
    void zpl_platform_set_clipboard_text(zplPlatform *p, char const *str) {
        if (OpenClipboard(cast(HWND)p->window_handle)) {
            isize i, len = zpl_strlen(str)+1;
            
            HANDLE mem = cast(HANDLE)GlobalAlloc(0x0002/*GMEM_MOVEABLE*/, len);
            if (mem) {
                char *dst = cast(char *)GlobalLock(mem);
                if (dst) {
                    for (i = 0; str[i]; i++) {
                        // TODO: Does this cause a buffer overflow?
                        // NOTE: Change \n to \r\n 'cause windows
                        if (str[i] == '\n' && (i == 0 || str[i-1] != '\r')) {
                            *dst++ = '\r';
                        }
                        *dst++ = str[i];
                    }
                    *dst = 0;
                }
                GlobalUnlock(mem);
            }
            
            EmptyClipboard();
            if (!SetClipboardData(1/*CF_TEXT*/, mem))
                return;
            CloseClipboard();
        }
    }
    
    // TODO: Handle UTF-8
    char *zpl_platform_get_clipboard_text(zplPlatform *p, zplAllocator a) {
        char *text = NULL;
        
        if (IsClipboardFormatAvailable(1/*CF_TEXT*/) &&
            OpenClipboard(cast(HWND)p->window_handle)) {
            HANDLE mem = GetClipboardData(1/*CF_TEXT*/);
            if (mem) {
                char *str = cast(char *)GlobalLock(mem);
                text = zpl_alloc_str(a, str);
                GlobalUnlock(mem);
            } else {
                return NULL;
            }
            
            CloseClipboard();
        }
        
        return text;
    }
    
#elif defined(ZPL_SYSTEM_OSX)
    
#include <CoreGraphics/CoreGraphics.h>
#include <objc/objc.h>
#include <objc/message.h>
#include <objc/NSObjCRuntime.h>
    
#if __LP64__ || (TARGET_OS_EMBEDDED && !TARGET_OS_IPHONE) || TARGET_OS_WIN32 || NS_BUILD_32_LIKE_64
#define NSIntegerEncoding  "q"
#define NSUIntegerEncoding "L"
#else
#define NSIntegerEncoding  "i"
#define NSUIntegerEncoding "I"
#endif
    
#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#else
    typedef CGPoint NSPoint;
    typedef CGSize  NSSize;
    typedef CGRect  NSRect;
    
    extern id NSApp;
    extern id const NSDefaultRunLoopMode;
#endif
    
#if defined(__OBJC__) && __has_feature(objc_arc)
#error TODO: Cannot compile as objective-c code just yet!
#endif
    
    // ABI is a bit different between platforms
#ifdef __arm64__
#define abi_objc_msgSend_stret objc_msgSend
#else
#define abi_objc_msgSend_stret objc_msgSend_stret
#endif
#ifdef __i386__
#define abi_objc_msgSend_fpret objc_msgSend_fpret
#else
#define abi_objc_msgSend_fpret objc_msgSend
#endif
    
#define objc_msgSend_id				((id (*)(id, SEL))objc_msgSend)
#define objc_msgSend_void			((void (*)(id, SEL))objc_msgSend)
#define objc_msgSend_void_id		((void (*)(id, SEL, id))objc_msgSend)
#define objc_msgSend_void_bool		((void (*)(id, SEL, BOOL))objc_msgSend)
#define objc_msgSend_id_char_const	((id (*)(id, SEL, char const *))objc_msgSend)
    
    zpl_internal NSUInteger zpl__osx_application_should_terminate(id self, SEL _sel, id sender) {
        // NOTE: Do nothing
        return 0;
    }
    
    zpl_internal void zpl__osx_window_will_close(id self, SEL _sel, id notification) {
        NSUInteger value = true;
        object_setInstanceVariable(self, "closed", cast(void *)value);
    }
    
    zpl_internal void zpl__osx_window_did_become_key(id self, SEL _sel, id notification) {
        zplPlatform *p = NULL;
        object_getInstanceVariable(self, "zplPlatform", cast(void **)&p);
        if (p) {
            // TODO:
        }
    }
    
    b32 zpl__platform_init(zplPlatform *p, char const *window_title, zplVideoMode mode, zplRendererType type, u32 window_flags) {
        if (p->is_initialized)
            return true;
        // Init Platform
        { // Initial OSX State
            Class appDelegateClass;
            b32 resultAddProtoc, resultAddMethod;
            id dgAlloc, dg, menubarAlloc, menubar;
            id appMenuItemAlloc, appMenuItem;
            id appMenuAlloc, appMenu;
            
#if defined(ARC_AVAILABLE)
#error TODO: This code should be compiled as C for now
#else
            id poolAlloc = objc_msgSend_id(cast(id)objc_getClass("NSAutoreleasePool"), sel_registerName("alloc"));
            p->osx_autorelease_pool = objc_msgSend_id(poolAlloc, sel_registerName("init"));
#endif
            
            objc_msgSend_id(cast(id)objc_getClass("NSApplication"), sel_registerName("sharedApplication"));
            ((void (*)(id, SEL, NSInteger))objc_msgSend)(NSApp, sel_registerName("setActivationPolicy:"), 0);
            
            appDelegateClass = objc_allocateClassPair((Class)objc_getClass("NSObject"), "AppDelegate", 0);
            resultAddProtoc = class_addProtocol(appDelegateClass, objc_getProtocol("NSApplicationDelegate"));
            assert(resultAddProtoc);
            resultAddMethod = class_addMethod(appDelegateClass, sel_registerName("applicationShouldTerminate:"), cast(IMP)zpl__osx_application_should_terminate, NSUIntegerEncoding "@:@");
            assert(resultAddMethod);
            dgAlloc = objc_msgSend_id(cast(id)appDelegateClass, sel_registerName("alloc"));
            dg = objc_msgSend_id(dgAlloc, sel_registerName("init"));
#ifndef ARC_AVAILABLE
            objc_msgSend_void(dg, sel_registerName("autorelease"));
#endif
            
            objc_msgSend_void_id(NSApp, sel_registerName("setDelegate:"), dg);
            objc_msgSend_void(NSApp, sel_registerName("finishLaunching"));
            
            menubarAlloc = objc_msgSend_id(cast(id)objc_getClass("NSMenu"), sel_registerName("alloc"));
            menubar = objc_msgSend_id(menubarAlloc, sel_registerName("init"));
#ifndef ARC_AVAILABLE
            objc_msgSend_void(menubar, sel_registerName("autorelease"));
#endif
            
            appMenuItemAlloc = objc_msgSend_id(cast(id)objc_getClass("NSMenuItem"), sel_registerName("alloc"));
            appMenuItem = objc_msgSend_id(appMenuItemAlloc, sel_registerName("init"));
#ifndef ARC_AVAILABLE
            objc_msgSend_void(appMenuItem, sel_registerName("autorelease"));
#endif
            
            objc_msgSend_void_id(menubar, sel_registerName("addItem:"), appMenuItem);
            ((id (*)(id, SEL, id))objc_msgSend)(NSApp, sel_registerName("setMainMenu:"), menubar);
            
            appMenuAlloc = objc_msgSend_id(cast(id)objc_getClass("NSMenu"), sel_registerName("alloc"));
            appMenu = objc_msgSend_id(appMenuAlloc, sel_registerName("init"));
#ifndef ARC_AVAILABLE
            objc_msgSend_void(appMenu, sel_registerName("autorelease"));
#endif
            
            {
                id processInfo = objc_msgSend_id(cast(id)objc_getClass("NSProcessInfo"), sel_registerName("processInfo"));
                id appName = objc_msgSend_id(processInfo, sel_registerName("processName"));
                
                id quitTitlePrefixString = objc_msgSend_id_char_const(cast(id)objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), "Quit ");
                id quitTitle = ((id (*)(id, SEL, id))objc_msgSend)(quitTitlePrefixString, sel_registerName("stringByAppendingString:"), appName);
                
                id quitMenuItemKey = objc_msgSend_id_char_const(cast(id)objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), "q");
                id quitMenuItemAlloc = objc_msgSend_id(cast(id)objc_getClass("NSMenuItem"), sel_registerName("alloc"));
                id quitMenuItem = ((id (*)(id, SEL, id, SEL, id))objc_msgSend)(quitMenuItemAlloc, sel_registerName("initWithTitle:action:keyEquivalent:"), quitTitle, sel_registerName("terminate:"), quitMenuItemKey);
#ifndef ARC_AVAILABLE
                objc_msgSend_void(quitMenuItem, sel_registerName("autorelease"));
#endif
                
                objc_msgSend_void_id(appMenu, sel_registerName("addItem:"), quitMenuItem);
                objc_msgSend_void_id(appMenuItem, sel_registerName("setSubmenu:"), appMenu);
            }
        }
        
        { // Init Window
            NSRect rect = {{0, 0}, {cast(CGFloat)mode.width, cast(CGFloat)mode.height}};
            id windowAlloc, window, wdgAlloc, wdg, contentView, titleString;
            Class WindowDelegateClass;
            b32 resultAddProtoc, resultAddIvar, resultAddMethod;
            
            windowAlloc = objc_msgSend_id(cast(id)objc_getClass("NSWindow"), sel_registerName("alloc"));
            window = ((id (*)(id, SEL, NSRect, NSUInteger, NSUInteger, BOOL))objc_msgSend)(windowAlloc, sel_registerName("initWithContentRect:styleMask:backing:defer:"), rect, 15, 2, NO);
#ifndef ARC_AVAILABLE
            objc_msgSend_void(window, sel_registerName("autorelease"));
#endif
            
            // when we are not using ARC, than window will be added to autorelease pool
            // so if we close it by hand (pressing red button), we don't want it to be released for us
            // so it will be released by autorelease pool later
            objc_msgSend_void_bool(window, sel_registerName("setReleasedWhenClosed:"), NO);
            
            WindowDelegateClass = objc_allocateClassPair((Class)objc_getClass("NSObject"), "WindowDelegate", 0);
            resultAddProtoc = class_addProtocol(WindowDelegateClass, objc_getProtocol("NSWindowDelegate"));
            ZPL_ASSERT(resultAddProtoc);
            resultAddIvar = class_addIvar(WindowDelegateClass, "closed", zpl_size_of(NSUInteger), rint(log2(zpl_size_of(NSUInteger))), NSUIntegerEncoding);
            ZPL_ASSERT(resultAddIvar);
            resultAddIvar = class_addIvar(WindowDelegateClass, "zplPlatform", zpl_size_of(void *), rint(log2(zpl_size_of(void *))), "ˆv");
            ZPL_ASSERT(resultAddIvar);
            resultAddMethod = class_addMethod(WindowDelegateClass, sel_registerName("windowWillClose:"), cast(IMP)zpl__osx_window_will_close,  "v@:@");
            ZPL_ASSERT(resultAddMethod);
            resultAddMethod = class_addMethod(WindowDelegateClass, sel_registerName("windowDidBecomeKey:"), cast(IMP)zpl__osx_window_did_become_key,  "v@:@");
            ZPL_ASSERT(resultAddMethod);
            wdgAlloc = objc_msgSend_id(cast(id)WindowDelegateClass, sel_registerName("alloc"));
            wdg = objc_msgSend_id(wdgAlloc, sel_registerName("init"));
#ifndef ARC_AVAILABLE
            objc_msgSend_void(wdg, sel_registerName("autorelease"));
#endif
            
            objc_msgSend_void_id(window, sel_registerName("setDelegate:"), wdg);
            
            contentView = objc_msgSend_id(window, sel_registerName("contentView"));
            
            {
                NSPoint point = {20, 20};
                ((void (*)(id, SEL, NSPoint))objc_msgSend)(window, sel_registerName("cascadeTopLeftFromPoint:"), point);
            }
            
            titleString = objc_msgSend_id_char_const(cast(id)objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), window_title);
            objc_msgSend_void_id(window, sel_registerName("setTitle:"), titleString);
            
            if (type == zplRenderer_Opengl) {
                // TODO: Make sure this works correctly
                u32 opengl_hex_version = (p->opengl.major << 12) | (p->opengl.minor << 8);
                u32 gl_attribs[] = {
                    8, 24,                  // NSOpenGLPFAColorSize, 24,
                    11, 8,                  // NSOpenGLPFAAlphaSize, 8,
                    5,                      // NSOpenGLPFADoubleBuffer,
                    73,                     // NSOpenGLPFAAccelerated,
                    //72,                   // NSOpenGLPFANoRecovery,
                    //55, 1,                // NSOpenGLPFASampleBuffers, 1,
                    //56, 4,                // NSOpenGLPFASamples, 4,
                    99, opengl_hex_version, // NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
                    0
                };
                
                id pixel_format_alloc, pixel_format;
                id opengl_context_alloc, opengl_context;
                
                pixel_format_alloc = objc_msgSend_id(cast(id)objc_getClass("NSOpenGLPixelFormat"), sel_registerName("alloc"));
                pixel_format = ((id (*)(id, SEL, const uint32_t*))objc_msgSend)(pixel_format_alloc, sel_registerName("initWithAttributes:"), gl_attribs);
#ifndef ARC_AVAILABLE
                objc_msgSend_void(pixel_format, sel_registerName("autorelease"));
#endif
                
                opengl_context_alloc = objc_msgSend_id(cast(id)objc_getClass("NSOpenGLContext"), sel_registerName("alloc"));
                opengl_context = ((id (*)(id, SEL, id, id))objc_msgSend)(opengl_context_alloc, sel_registerName("initWithFormat:shareContext:"), pixel_format, nil);
#ifndef ARC_AVAILABLE
                objc_msgSend_void(opengl_context, sel_registerName("autorelease"));
#endif
                
                objc_msgSend_void_id(opengl_context, sel_registerName("setView:"), contentView);
                objc_msgSend_void_id(window, sel_registerName("makeKeyAndOrderFront:"), window);
                objc_msgSend_void_bool(window, sel_registerName("setAcceptsMouseMovedEvents:"), YES);
                
                
                p->window_handle = cast(void *)window;
                p->opengl.context = cast(void *)opengl_context;
            } else {
                ZPL_PANIC("TODO: Software rendering");
            }
            
            {
                id blackColor = objc_msgSend_id(cast(id)objc_getClass("NSColor"), sel_registerName("blackColor"));
                objc_msgSend_void_id(window, sel_registerName("setBackgroundColor:"), blackColor);
                objc_msgSend_void_bool(NSApp, sel_registerName("activateIgnoringOtherApps:"), YES);
            }
            object_setInstanceVariable(wdg, "zplPlatform", cast(void *)p);
            
            p->is_initialized = true;
        }
        
        return true;
    }
    
    // NOTE: Software rendering
    b32 zpl_platform_init_with_software(zplPlatform *p, char const *window_title, i32 width, i32 height, u32 window_flags) {
        ZPL_PANIC("TODO: Software rendering in not yet implemented on OS X\n");
        return zpl__platform_init(p, window_title, zpl_video_mode(width, height, 32), zplRenderer_Software, window_flags);
    }
    // NOTE: OpenGL Rendering
    b32 zpl_platform_init_with_opengl(zplPlatform *p, char const *window_title, i32 width, i32 height, u32 window_flags,
                                      i32 major, i32 minor, b32 core, b32 compatible) {
        
        p->opengl.major = major;
        p->opengl.minor = minor;
        p->opengl.core  = core;
        p->opengl.compatible = compatible;
        return zpl__platform_init(p, window_title, zpl_video_mode(width, height, 32), zplRenderer_Opengl, window_flags);
    }
    
    // NOTE: Reverse engineering can be fun!!!
    zpl_internal zplKeyType zpl__osx_from_key_code(u16 key_code) {
        switch (key_code) {
            default: return zplKey_Unknown;
            case 0x1d: return zplKey_0;
            case 0x12: return zplKey_1;
            case 0x13: return zplKey_2;
            case 0x14: return zplKey_3;
            case 0x15: return zplKey_4;
            case 0x17: return zplKey_5;
            case 0x16: return zplKey_6;
            case 0x1a: return zplKey_7;
            case 0x1c: return zplKey_8;
            case 0x19: return zplKey_9;
            
            case 0x00: return zplKey_A;
            case 0x0b: return zplKey_B;
            case 0x08: return zplKey_C;
            case 0x02: return zplKey_D;
            case 0x0e: return zplKey_E;
            case 0x03: return zplKey_F;
            case 0x05: return zplKey_G;
            case 0x04: return zplKey_H;
            case 0x22: return zplKey_I;
            case 0x26: return zplKey_J;
            case 0x28: return zplKey_K;
            case 0x25: return zplKey_L;
            case 0x2e: return zplKey_M;
            case 0x2d: return zplKey_N;
            case 0x1f: return zplKey_O;
            case 0x23: return zplKey_P;
            case 0x0c: return zplKey_Q;
            case 0x0f: return zplKey_R;
            case 0x01: return zplKey_S;
            case 0x11: return zplKey_T;
            case 0x20: return zplKey_U;
            case 0x09: return zplKey_V;
            case 0x0d: return zplKey_W;
            case 0x07: return zplKey_X;
            case 0x10: return zplKey_Y;
            case 0x06: return zplKey_Z;
            
            case 0x21: return zplKey_Lbracket;
            case 0x1e: return zplKey_Rbracket;
            case 0x29: return zplKey_Semicolon;
            case 0x2b: return zplKey_Comma;
            case 0x2f: return zplKey_Period;
            case 0x27: return zplKey_Quote;
            case 0x2c: return zplKey_Slash;
            case 0x2a: return zplKey_Backslash;
            case 0x32: return zplKey_Grave;
            case 0x18: return zplKey_Equals;
            case 0x1b: return zplKey_Minus;
            case 0x31: return zplKey_Space;
            
            case 0x35: return zplKey_Escape;       // Escape
            case 0x3b: return zplKey_Lcontrol;     // Left Control
            case 0x38: return zplKey_Lshift;       // Left Shift
            case 0x3a: return zplKey_Lalt;         // Left Alt
            case 0x37: return zplKey_Lsystem;      // Left OS specific: window (Windows and Linux), apple/cmd (MacOS X), ...
            case 0x3e: return zplKey_Rcontrol;     // Right Control
            case 0x3c: return zplKey_Rshift;       // Right Shift
            case 0x3d: return zplKey_Ralt;         // Right Alt
            // case 0x37: return zplKey_Rsystem;      // Right OS specific: window (Windows and Linux), apple/cmd (MacOS X), ...
            case 0x6e: return zplKey_Menu;         // Menu
            case 0x24: return zplKey_Return;       // Return
            case 0x33: return zplKey_Backspace;    // Backspace
            case 0x30: return zplKey_Tab;          // Tabulation
            case 0x74: return zplKey_Pageup;       // Page up
            case 0x79: return zplKey_Pagedown;     // Page down
            case 0x77: return zplKey_End;          // End
            case 0x73: return zplKey_Home;         // Home
            case 0x72: return zplKey_Insert;       // Insert
            case 0x75: return zplKey_Delete;       // Delete
            case 0x45: return zplKey_Plus;         // +
            case 0x4e: return zplKey_Subtract;     // -
            case 0x43: return zplKey_Multiply;     // *
            case 0x4b: return zplKey_Divide;       // /
            case 0x7b: return zplKey_Left;         // Left arrow
            case 0x7c: return zplKey_Right;        // Right arrow
            case 0x7e: return zplKey_Up;           // Up arrow
            case 0x7d: return zplKey_Down;         // Down arrow
            case 0x52: return zplKey_Numpad0;      // Numpad 0
            case 0x53: return zplKey_Numpad1;      // Numpad 1
            case 0x54: return zplKey_Numpad2;      // Numpad 2
            case 0x55: return zplKey_Numpad3;      // Numpad 3
            case 0x56: return zplKey_Numpad4;      // Numpad 4
            case 0x57: return zplKey_Numpad5;      // Numpad 5
            case 0x58: return zplKey_Numpad6;      // Numpad 6
            case 0x59: return zplKey_Numpad7;      // Numpad 7
            case 0x5b: return zplKey_Numpad8;      // Numpad 8
            case 0x5c: return zplKey_Numpad9;      // Numpad 9
            case 0x41: return zplKey_NumpadDot;    // Numpad .
            case 0x4c: return zplKey_NumpadEnter;  // Numpad Enter
            case 0x7a: return zplKey_F1;           // F1
            case 0x78: return zplKey_F2;           // F2
            case 0x63: return zplKey_F3;           // F3
            case 0x76: return zplKey_F4;           // F4
            case 0x60: return zplKey_F5;           // F5
            case 0x61: return zplKey_F6;           // F6
            case 0x62: return zplKey_F7;           // F7
            case 0x64: return zplKey_F8;           // F8
            case 0x65: return zplKey_F9;           // F8
            case 0x6d: return zplKey_F10;          // F10
            case 0x67: return zplKey_F11;          // F11
            case 0x6f: return zplKey_F12;          // F12
            case 0x69: return zplKey_F13;          // F13
            case 0x6b: return zplKey_F14;          // F14
            case 0x71: return zplKey_F15;          // F15
            // case : return zplKey_Pause;        // Pause // NOTE: Not possible on OS X
        }
    }
    
    zpl_internal void zpl__osx_on_cocoa_event(zplPlatform *p, id event, id window) {
        if (!event) {
            return;
        } else if (objc_msgSend_id(window, sel_registerName("delegate"))) {
            NSUInteger event_type = ((NSUInteger (*)(id, SEL))objc_msgSend)(event, sel_registerName("type"));
            switch (event_type) {
                case 1: zpl_key_state_update(&p->mouse_buttons[zplMouseButton_Left],  true);  break; // NSLeftMouseDown
                case 2: zpl_key_state_update(&p->mouse_buttons[zplMouseButton_Left],  false); break; // NSLeftMouseUp
                case 3: zpl_key_state_update(&p->mouse_buttons[zplMouseButton_Right], true);  break; // NSRightMouseDown
                case 4: zpl_key_state_update(&p->mouse_buttons[zplMouseButton_Right], false); break; // NSRightMouseUp
                case 25: { // NSOtherMouseDown
                    // TODO: Test thoroughly
                    NSInteger number = ((NSInteger (*)(id, SEL))objc_msgSend)(event, sel_registerName("buttonNumber"));
                    if (number == 2) zpl_key_state_update(&p->mouse_buttons[zplMouseButton_Middle], true);
                    if (number == 3) zpl_key_state_update(&p->mouse_buttons[zplMouseButton_X1],     true);
                    if (number == 4) zpl_key_state_update(&p->mouse_buttons[zplMouseButton_X2],     true);
                } break;
                case 26: { // NSOtherMouseUp
                    NSInteger number = ((NSInteger (*)(id, SEL))objc_msgSend)(event, sel_registerName("buttonNumber"));
                    if (number == 2) zpl_key_state_update(&p->mouse_buttons[zplMouseButton_Middle], false);
                    if (number == 3) zpl_key_state_update(&p->mouse_buttons[zplMouseButton_X1],     false);
                    if (number == 4) zpl_key_state_update(&p->mouse_buttons[zplMouseButton_X2],     false);
                    
                } break;
                
                // TODO: Scroll wheel
                case 22: { // NSScrollWheel
                    CGFloat dx = ((CGFloat (*)(id, SEL))abi_objc_msgSend_fpret)(event, sel_registerName("scrollingDeltaX"));
                    CGFloat dy = ((CGFloat (*)(id, SEL))abi_objc_msgSend_fpret)(event, sel_registerName("scrollingDeltaY"));
                    BOOL precision_scrolling = ((BOOL (*)(id, SEL))objc_msgSend)(event, sel_registerName("hasPreciseScrollingDeltas"));
                    if (precision_scrolling) {
                        dx *= 0.1f;
                        dy *= 0.1f;
                    }
                    // TODO: Handle sideways
                    p->mouse_wheel_delta = dy;
                    // p->mouse_wheel_dy = dy;
                    // zpl_printf("%f %f\n", dx, dy);
                } break;
                
                case 12: { // NSFlagsChanged
#if 0
                    // TODO: Reverse engineer this properly
                    NSUInteger modifiers = ((NSUInteger (*)(id, SEL))objc_msgSend)(event, sel_registerName("modifierFlags"));
                    u32 upper_mask = (modifiers & 0xffff0000ul) >> 16;
                    b32 shift   = (upper_mask & 0x02) != 0;
                    b32 control = (upper_mask & 0x04) != 0;
                    b32 alt     = (upper_mask & 0x08) != 0;
                    b32 command = (upper_mask & 0x10) != 0;
#endif
                    
                    // zpl_printf("%u\n", keys.mask);
                    // zpl_printf("%x\n", cast(u32)modifiers);
                } break;
                
                case 10: { // NSKeyDown
                    u16 key_code;
                    
                    id input_text = objc_msgSend_id(event, sel_registerName("characters"));
                    char const *input_text_utf8 = ((char const *(*)(id, SEL))objc_msgSend)(input_text, sel_registerName("UTF8String"));
                    p->char_buffer_count = zpl_strnlen(input_text_utf8, zpl_size_of(p->char_buffer));
                    zpl_memcopy(p->char_buffer, input_text_utf8, p->char_buffer_count);
                    
                    key_code = ((unsigned short (*)(id, SEL))objc_msgSend)(event, sel_registerName("keyCode"));
                    zpl_key_state_update(&p->keys[zpl__osx_from_key_code(key_code)], true);
                } break;
                
                case 11: { // NSKeyUp
                    u16 key_code = ((unsigned short (*)(id, SEL))objc_msgSend)(event, sel_registerName("keyCode"));
                    zpl_key_state_update(&p->keys[zpl__osx_from_key_code(key_code)], false);
                } break;
                
                default: break;
            }
            
            objc_msgSend_void_id(NSApp, sel_registerName("sendEvent:"), event);
        }
    }
    
    
    void zpl_platform_update(zplPlatform *p) {
        id window, key_window, content_view;
        NSRect original_frame;
        
        window = cast(id)p->window_handle;
        key_window = objc_msgSend_id(NSApp, sel_registerName("keyWindow"));
        p->window_has_focus = key_window == window; // TODO: Is this right
        
        
        if (p->window_has_focus) {
            isize i;
            p->char_buffer_count = 0; // TODO: Reset buffer count here or else where?
            
            // NOTE: Need to update as the keys only get updates on events
            for (i = 0; i < zplKey_Count; i++) {
                b32 is_down = (p->keys[i] & zplKeyState_Down) != 0;
                zpl_key_state_update(&p->keys[i], is_down);
            }
            
            for (i = 0; i < zplMouseButton_Count; i++) {
                b32 is_down = (p->mouse_buttons[i] & zplKeyState_Down) != 0;
                zpl_key_state_update(&p->mouse_buttons[i], is_down);
            }
            
        }
        
        { // Handle Events
            id distant_past = objc_msgSend_id(cast(id)objc_getClass("NSDate"), sel_registerName("distantPast"));
            id event = ((id (*)(id, SEL, NSUInteger, id, id, BOOL))objc_msgSend)(NSApp, sel_registerName("nextEventMatchingMask:untilDate:inMode:dequeue:"), NSUIntegerMax, distant_past, NSDefaultRunLoopMode, YES);
            zpl__osx_on_cocoa_event(p, event, window);
        }
        
        if (p->window_has_focus) {
            p->key_modifiers.control = p->keys[zplKey_Lcontrol] | p->keys[zplKey_Rcontrol];
            p->key_modifiers.alt     = p->keys[zplKey_Lalt]     | p->keys[zplKey_Ralt];
            p->key_modifiers.shift   = p->keys[zplKey_Lshift]   | p->keys[zplKey_Rshift];
        }
        
        { // Check if window is closed
            id wdg = objc_msgSend_id(window, sel_registerName("delegate"));
            if (!wdg) {
                p->window_is_closed = false;
            } else {
                NSUInteger value = 0;
                object_getInstanceVariable(wdg, "closed", cast(void **)&value);
                p->window_is_closed = (value != 0);
            }
        }
        
        
        
        content_view = objc_msgSend_id(window, sel_registerName("contentView"));
        original_frame = ((NSRect (*)(id, SEL))abi_objc_msgSend_stret)(content_view, sel_registerName("frame"));
        
        { // Window
            NSRect frame = original_frame;
            frame = ((NSRect (*)(id, SEL, NSRect))abi_objc_msgSend_stret)(content_view, sel_registerName("convertRectToBacking:"), frame);
            p->window_width  = frame.size.width;
            p->window_height = frame.size.height;
            frame = ((NSRect (*)(id, SEL, NSRect))abi_objc_msgSend_stret)(window, sel_registerName("convertRectToScreen:"), frame);
            p->window_x = frame.origin.x;
            p->window_y = frame.origin.y;
        }
        
        { // Mouse
            NSRect frame = original_frame;
            NSPoint mouse_pos = ((NSPoint (*)(id, SEL))objc_msgSend)(window, sel_registerName("mouseLocationOutsideOfEventStream"));
            mouse_pos.x = zpl_clamp(mouse_pos.x, 0, frame.size.width-1);
            mouse_pos.y = zpl_clamp(mouse_pos.y, 0, frame.size.height-1);
            
            {
                i32 x = mouse_pos.x;
                i32 y = mouse_pos.y;
                p->mouse_dx = x - p->mouse_x;
                p->mouse_dy = y - p->mouse_y;
                p->mouse_x = x;
                p->mouse_y = y;
            }
            
            if (p->mouse_clip) {
                b32 update = false;
                i32 x = p->mouse_x;
                i32 y = p->mouse_y;
                if (p->mouse_x < 0) {
                    x = 0;
                    update = true;
                } else if (p->mouse_y > p->window_height-1) {
                    y = p->window_height-1;
                    update = true;
                }
                
                if (p->mouse_y < 0) {
                    y = 0;
                    update = true;
                } else if (p->mouse_x > p->window_width-1) {
                    x = p->window_width-1;
                    update = true;
                }
                
                if (update)
                    zpl_platform_set_mouse_position(p, x, y);
            }
        }
        
        { // TODO: Controllers
            
        }
        
        // TODO: Is this in the correct place?
        objc_msgSend_void(NSApp, sel_registerName("updateWindows"));
        if (p->renderer_type == zplRenderer_Opengl) {
            objc_msgSend_void(cast(id)p->opengl.context, sel_registerName("update"));
            zpl_platform_make_opengl_context_current(p);
        }
    }
    
    void zpl_platform_display(zplPlatform *p) {
        // TODO: Do more
        if (p->renderer_type == zplRenderer_Opengl) {
            zpl_platform_make_opengl_context_current(p);
            objc_msgSend_void(cast(id)p->opengl.context, sel_registerName("flushBuffer"));
        } else if (p->renderer_type == zplRenderer_Software) {
            // TODO:
        } else {
            ZPL_PANIC("Invalid window rendering type");
        }
        
        {
            f64 prev_time = p->curr_time;
            f64 curr_time = zpl_time_now();
            p->dt_for_frame = curr_time - prev_time;
            p->curr_time = curr_time;
        }
    }
    
    void zpl_platform_destroy(zplPlatform *p) {
        zpl_platform_make_opengl_context_current(p);
        
        objc_msgSend_void(cast(id)p->window_handle, sel_registerName("close"));
        
#if defined(ARC_AVAILABLE)
        // TODO: autorelease pool
#else
        objc_msgSend_void(cast(id)p->osx_autorelease_pool, sel_registerName("drain"));
#endif
    }
    
    void zpl_platform_show_cursor(zplPlatform *p, b32 show) {
        if (show ) {
            // objc_msgSend_void(class_registerName("NSCursor"), sel_registerName("unhide"));
        } else {
            // objc_msgSend_void(class_registerName("NSCursor"), sel_registerName("hide"));
        }
    }
    
    void zpl_platform_set_mouse_position(zplPlatform *p, i32 x, i32 y) {
        // TODO:
        CGPoint pos = {cast(CGFloat)x, cast(CGFloat)y};
        pos.x += p->window_x;
        pos.y += p->window_y;
        CGWarpMouseCursorPosition(pos);
    }
    
    void zpl_platform_set_controller_vibration(zplPlatform *p, isize index, f32 left_motor, f32 right_motor) {
        // TODO:
    }
    
    b32 zpl_platform_has_clipboard_text(zplPlatform *p) {
        // TODO:
        return false;
    }
    
    void zpl_platform_set_clipboard_text(zplPlatform *p, char const *str) {
        // TODO:
    }
    
    char *zpl_platform_get_clipboard_text(zplPlatform *p, zplAllocator a) {
        // TODO:
        return NULL;
    }
    
    void zpl_platform_set_window_position(zplPlatform *p, i32 x, i32 y) {
        // TODO:
    }
    
    void zpl_platform_set_window_title(zplPlatform *p, char const *title, ...) {
        id title_string;
        char buf[256] = {0};
        va_list va;
        va_start(va, title);
        zpl_snprintf_va(buf, zpl_count_of(buf), title, va);
        va_end(va);
        
        title_string = objc_msgSend_id_char_const(cast(id)objc_getClass("NSString"), sel_registerName("stringWithUTF8String:"), buf);
        objc_msgSend_void_id(cast(id)p->window_handle, sel_registerName("setTitle:"), title_string);
    }
    
    void zpl_platform_toggle_fullscreen(zplPlatform *p, b32 fullscreen_desktop) {
        // TODO:
    }
    
    void zpl_platform_toggle_borderless(zplPlatform *p) {
        // TODO:
    }
    
    void zpl_platform_make_opengl_context_current(zplPlatform *p) {
        objc_msgSend_void(cast(id)p->opengl.context, sel_registerName("makeCurrentContext"));
    }
    
    void zpl_platform_show_window(zplPlatform *p) {
        // TODO:
    }
    
    void zpl_platform_hide_window(zplPlatform *p) {
        // TODO:
    }
    
    i32 zpl__osx_mode_bits_per_pixel(CGDisplayModeRef mode) {
        i32 bits_per_pixel = 0;
        CFStringRef pixel_encoding = CGDisplayModeCopyPixelEncoding(mode);
        if(CFStringCompare(pixel_encoding, CFSTR(IO32BitDirectPixels), kCFCompareCaseInsensitive) == kCFCompareEqualTo) {
            bits_per_pixel = 32;
        } else if(CFStringCompare(pixel_encoding, CFSTR(IO16BitDirectPixels), kCFCompareCaseInsensitive) == kCFCompareEqualTo) {
            bits_per_pixel = 16;
        } else if(CFStringCompare(pixel_encoding, CFSTR(IO8BitIndexedPixels), kCFCompareCaseInsensitive) == kCFCompareEqualTo) {
            bits_per_pixel = 8;
        }
        CFRelease(pixel_encoding);
        
        return bits_per_pixel;
    }
    
    i32 zpl__osx_display_bits_per_pixel(CGDirectDisplayID display) {
        CGDisplayModeRef mode = CGDisplayCopyDisplayMode(display);
        i32 bits_per_pixel = zpl__osx_mode_bits_per_pixel(mode);
        CGDisplayModeRelease(mode);
        return bits_per_pixel;
    }
    
    zplVideoMode zpl_video_mode_get_desktop(void) {
        CGDirectDisplayID display = CGMainDisplayID();
        return zpl_video_mode(CGDisplayPixelsWide(display),
                              CGDisplayPixelsHigh(display),
                              zpl__osx_display_bits_per_pixel(display));
    }
    
    
    isize zpl_video_mode_get_fullscreen_modes(zplVideoMode *modes, isize max_mode_count) {
        CFArrayRef cg_modes = CGDisplayCopyAllDisplayModes(CGMainDisplayID(), NULL);
        CFIndex i, count;
        if (cg_modes == NULL) {
            return 0;
        }
        
        count = zpl_min(CFArrayGetCount(cg_modes), max_mode_count);
        for (i = 0; i < count; i++) {
            CGDisplayModeRef cg_mode = cast(CGDisplayModeRef)CFArrayGetValueAtIndex(cg_modes, i);
            modes[i] = zpl_video_mode(CGDisplayModeGetWidth(cg_mode),
                                      CGDisplayModeGetHeight(cg_mode),
                                      zpl__osx_mode_bits_per_pixel(cg_mode));
        }
        
        CFRelease(cg_modes);
        
        zpl_sort_array(modes, count, zpl_video_mode_dsc_cmp);
        return cast(isize)count;
    }
    
#endif
    
    
    // TODO: OSX Platform Layer
    // NOTE: Use this as a guide so there is no need for Obj-C https://github.com/jimon/osx_app_in_plain_c
    
    zpl_inline zplVideoMode zpl_video_mode(i32 width, i32 height, i32 bits_per_pixel) {
        zplVideoMode m;
        m.width = width;
        m.height = height;
        m.bits_per_pixel = bits_per_pixel;
        return m;
    }
    
    zpl_inline b32 zpl_video_mode_is_valid(zplVideoMode mode) {
        zpl_local_persist zplVideoMode modes[256] = {0};
        zpl_local_persist isize mode_count = 0;
        zpl_local_persist b32 is_set = false;
        isize i;
        
        if (!is_set) {
            mode_count = zpl_video_mode_get_fullscreen_modes(modes, zpl_count_of(modes));
            is_set = true;
        }
        
        for (i = 0; i < mode_count; i++) {
            zpl_printf("%d %d\n", modes[i].width, modes[i].height);
        }
        
        return zpl_binary_search_array(modes, mode_count, &mode, zpl_video_mode_cmp) >= 0;
    }
    
    ZPL_COMPARE_PROC(zpl_video_mode_cmp) {
        zplVideoMode const *x = cast(zplVideoMode const *)a;
        zplVideoMode const *y = cast(zplVideoMode const *)b;
        
        if (x->bits_per_pixel == y->bits_per_pixel) {
            if (x->width == y->width)
                return x->height < y->height ? -1 : x->height > y->height;
            return x->width < y->width ? -1 : x->width > y->width;
        }
        return x->bits_per_pixel < y->bits_per_pixel ? -1 : +1;
    }
    
    ZPL_COMPARE_PROC(zpl_video_mode_dsc_cmp) {
        return zpl_video_mode_cmp(b, a);
    }

#endif
    
#if defined(__cplusplus)
}
#endif


#endif // ZPL_INCLUDE_ZPL_PLATFORM_H