/** @file platform.c
@brief Platform layer
@defgroup platform Platform layer


@n NOTE(bill):
@n Coordinate system - +ve x - left to right
@n                  - +ve y - bottom to top
@n                  - Relative to window

@n TODO(bill): Proper documentation for this with code examples
@n
@n Window Support - Complete
@n OS X Support (Not ported yet) - Missing:
@n     * Software framebuffer
@n     * (show|hide) window
@n     * show_cursor
@n     * toggle (fullscreen|borderless)
@n     * set window position
@n     * Clipboard
@n     * GameControllers
@n Linux Support - None
@n Other OS Support - None
@n
@n Ported from https://github.com/gingerBill/gb/

@{
*/


#ifndef ZPL_MAX_GAME_CONTROLLER_COUNT
#define ZPL_MAX_GAME_CONTROLLER_COUNT 4
#endif

typedef enum zpl_key_type {
    ZPL_KEY_UNKNOWN = 0, // Unhandled key

    // NOTE(bill): Allow the basic printable keys to be aliased with their chars
    ZPL_KEY_0 = '0',
    ZPL_KEY_1,
    ZPL_KEY_2,
    ZPL_KEY_3,
    ZPL_KEY_4,
    ZPL_KEY_5,
    ZPL_KEY_6,
    ZPL_KEY_7,
    ZPL_KEY_8,
    ZPL_KEY_9,

    ZPL_KEY_A = 'A',
    ZPL_KEY_B,
    ZPL_KEY_C,
    ZPL_KEY_D,
    ZPL_KEY_E,
    ZPL_KEY_F,
    ZPL_KEY_G,
    ZPL_KEY_H,
    ZPL_KEY_I,
    ZPL_KEY_J,
    ZPL_KEY_K,
    ZPL_KEY_L,
    ZPL_KEY_M,
    ZPL_KEY_N,
    ZPL_KEY_O,
    ZPL_KEY_P,
    ZPL_KEY_Q,
    ZPL_KEY_R,
    ZPL_KEY_S,
    ZPL_KEY_T,
    ZPL_KEY_U,
    ZPL_KEY_V,
    ZPL_KEY_W,
    ZPL_KEY_X,
    ZPL_KEY_Y,
    ZPL_KEY_Z,

    ZPL_KEY_LBRACKET = '[',
    ZPL_KEY_RBRACKET = ']',
    ZPL_KEY_SEMICOLON = ';',
    ZPL_KEY_COMMA = ',',
    ZPL_KEY_PERIOD = '.',
    ZPL_KEY_QUOTE = '\'',
    ZPL_KEY_SLASH = '/',
    ZPL_KEY_BACKSLASH = '\\',
    ZPL_KEY_GRAVE = '`',
    ZPL_KEY_EQUALS = '=',
    ZPL_KEY_MINUS = '-',
    ZPL_KEY_SPACE = ' ',

    ZPL_KEY__PAD = 128, // NOTE(BILL): MAKE SURE ASCII IS RESERVED

    ZPL_KEY_ESCAPE,      // ESCAPE
    ZPL_KEY_LCONTROL,    // LEFT CONTROL
    ZPL_KEY_LSHIFT,      // LEFT SHIFT
    ZPL_KEY_LALT,        // LEFT ALT
    ZPL_KEY_LSYSTEM,     // LEFT OS SPECIFIC: WINDOW (WINDOWS AND LINUX), APPLE/CMD (MACOS X), ...
    ZPL_KEY_RCONTROL,    // RIGHT CONTROL
    ZPL_KEY_RSHIFT,      // RIGHT SHIFT
    ZPL_KEY_RALT,        // RIGHT ALT
    ZPL_KEY_RSYSTEM,     // RIGHT OS SPECIFIC: WINDOW (WINDOWS AND LINUX), APPLE/CMD (MACOS X), ...
    ZPL_KEY_MENU,        // MENU
    ZPL_KEY_RETURN,      // RETURN
    ZPL_KEY_BACKSPACE,   // BACKSPACE
    ZPL_KEY_TAB,         // TABULATION
    ZPL_KEY_PAGEUP,      // PAGE UP
    ZPL_KEY_PAGEDOWN,    // PAGE DOWN
    ZPL_KEY_END,         // END
    ZPL_KEY_HOME,        // HOME
    ZPL_KEY_INSERT,      // INSERT
    ZPL_KEY_DELETE,      // DELETE
    ZPL_KEY_PLUS,        // +
    ZPL_KEY_SUBTRACT,    // -
    ZPL_KEY_MULTIPLY,    // *
    ZPL_KEY_DIVIDE,      // /
    ZPL_KEY_LEFT,        // LEFT ARROW
    ZPL_KEY_RIGHT,       // RIGHT ARROW
    ZPL_KEY_UP,          // UP ARROW
    ZPL_KEY_DOWN,        // DOWN ARROW
    ZPL_KEY_NUMPAD0,     // NUMPAD 0
    ZPL_KEY_NUMPAD1,     // NUMPAD 1
    ZPL_KEY_NUMPAD2,     // NUMPAD 2
    ZPL_KEY_NUMPAD3,     // NUMPAD 3
    ZPL_KEY_NUMPAD4,     // NUMPAD 4
    ZPL_KEY_NUMPAD5,     // NUMPAD 5
    ZPL_KEY_NUMPAD6,     // NUMPAD 6
    ZPL_KEY_NUMPAD7,     // NUMPAD 7
    ZPL_KEY_NUMPAD8,     // NUMPAD 8
    ZPL_KEY_NUMPAD9,     // NUMPAD 9
    ZPL_KEY_NUMPADDOT,   // NUMPAD .
    ZPL_KEY_NUMPADENTER, // NUMPAD ENTER
    ZPL_KEY_F1,          // F1
    ZPL_KEY_F2,          // F2
    ZPL_KEY_F3,          // F3
    ZPL_KEY_F4,          // F4
    ZPL_KEY_F5,          // F5
    ZPL_KEY_F6,          // F6
    ZPL_KEY_F7,          // F7
    ZPL_KEY_F8,          // F8
    ZPL_KEY_F9,          // F8
    ZPL_KEY_F10,         // F10
    ZPL_KEY_F11,         // F11
    ZPL_KEY_F12,         // F12
    ZPL_KEY_F13,         // F13
    ZPL_KEY_F14,         // F14
    ZPL_KEY_F15,         // F15
    ZPL_KEY_PAUSE,       // PAUSE

    ZPL_KEY_COUNT,
} zpl_key_type;

typedef zpl_u8 zpl_key_state;
typedef enum zpl_key_state_flag {
    ZPL_KEY_STATE_DOWN     = ZPL_BIT(0),
    ZPL_KEY_STATE_PRESSED  = ZPL_BIT(1),
    ZPL_KEY_STATE_RELEASED = ZPL_BIT(2)
} zpl_key_state_flag;

ZPL_DEF void zpl_key_state_update(zpl_key_state *s, zpl_b32 is_down);

typedef enum zpl_mouse_button_type {
    ZPL_MOUSEBUTTON_LEFT,
    ZPL_MOUSEBUTTON_MIDDLE,
    ZPL_MOUSEBUTTON_RIGHT,
    ZPL_MOUSEBUTTON_X1,
    ZPL_MOUSEBUTTON_X2,

    ZPL_MOUSEBUTTON_COUNT
} zpl_mouse_button_type;

typedef enum zpl_controller_axis_type {
    ZPL_CONTROLLER_AXIS_LEFTX,
    ZPL_CONTROLLER_AXIS_LEFTY,
    ZPL_CONTROLLER_AXIS_RIGHTX,
    ZPL_CONTROLLER_AXIS_RIGHTY,
    ZPL_CONTROLLER_AXIS_LEFTTRIGGER,
    ZPL_CONTROLLER_AXIS_RIGHTTRIGGER,

    ZPL_CONTROLLER_AXIS_COUNT
} zpl_controller_axis_type;

typedef enum zpl_controller_button_type {
    ZPL_CONTROLLER_BUTTON_UP,
    ZPL_CONTROLLER_BUTTON_DOWN,
    ZPL_CONTROLLER_BUTTON_LEFT,
    ZPL_CONTROLLER_BUTTON_RIGHT,
    ZPL_CONTROLLER_BUTTON_A,
    ZPL_CONTROLLER_BUTTON_B,
    ZPL_CONTROLLER_BUTTON_X,
    ZPL_CONTROLLER_BUTTON_Y,
    ZPL_CONTROLLER_BUTTON_LEFTSHOULDER,
    ZPL_CONTROLLER_BUTTON_RIGHTSHOULDER,
    ZPL_CONTROLLER_BUTTON_BACK,
    ZPL_CONTROLLER_BUTTON_START,
    ZPL_CONTROLLER_BUTTON_LEFTTHUMB,
    ZPL_CONTROLLER_BUTTON_RIGHTTHUMB,

    zplControllerButton_Count
} zpl_controller_button_type;

typedef struct zpl_game_controller {
    zpl_b16 is_connected, is_analog;

    zpl_f32 axes[ZPL_CONTROLLER_AXIS_COUNT];
    zpl_key_state buttons[zplControllerButton_Count];
} zpl_game_controller;

#if defined(ZPL_SYSTEM_WINDOWS)
typedef struct _XINPUT_GAMEPAD XINPUT_GAMEPAD;
typedef struct _XINPUT_STATE XINPUT_STATE;
typedef struct _XINPUT_VIBRATION XINPUT_VIBRATION;

#define ZPL_XINPUT_GET_STATE(name) unsigned long __stdcall name(unsigned long dwUserIndex, XINPUT_STATE *pState)
typedef ZPL_XINPUT_GET_STATE(zpl_xinput_get_state_proc);

#define ZPL_XINPUT_SET_STATE(name) unsigned long __stdcall name(unsigned long dwUserIndex, XINPUT_VIBRATION *pVibration)
typedef ZPL_XINPUT_SET_STATE(zpl_xinput_set_state_proc);
#endif

typedef enum zpl_window_flag {
    ZPL_WINDOW_FULLSCREEN        = ZPL_BIT(0),
    ZPL_WINDOW_HIDDEN            = ZPL_BIT(1),
    ZPL_WINDOW_BORDERLESS        = ZPL_BIT(2),
    ZPL_WINDOW_RESIZABLE         = ZPL_BIT(3),
    ZPL_WINDOW_MINIMIZED         = ZPL_BIT(4),
    ZPL_WINDOW_MAXIMIZED         = ZPL_BIT(5),
    ZPL_WINDOW_FULLSCREENDESKTOP = ZPL_WINDOW_FULLSCREEN | ZPL_WINDOW_BORDERLESS,
} zpl_window_flag;

typedef enum zpl_renderer_type {
    ZPL_RENDERER_OPENGL,
    ZPL_RENDERER_SOFTWARE,

    ZPL_RENDERER_COUNT,
} zpl_renderer_type;

#if defined(ZPL_SYSTEM_WINDOWS) && !defined(_WINDOWS_)
typedef struct tagBITMAPINFOHEADER {
    unsigned long bzpl_isize;
    long biWidth;
    long biHeight;
    zpl_u16 biPlanes;
    zpl_u16 biBitCount;
    unsigned long biCompression;
    unsigned long bzpl_isizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    unsigned long biClrUsed;
    unsigned long biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
typedef struct tagRGBQUAD {
    zpl_u8 rgbBlue;
    zpl_u8 rgbGreen;
    zpl_u8 rgbRed;
    zpl_u8 rgbReserved;
} RGBQUAD;
typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[1];
} BITMAPINFO, *PBITMAPINFO;
#endif

typedef struct zpl_platform {
    zpl_b32 is_initialized;

    void *window_handle;
    zpl_i32 window_x, window_y;
    zpl_i32 window_width, window_height;
    zpl_i32 outline_x, outline_y;
    zpl_i32 outline_width, outline_height;
    zpl_u32 window_flags;
    zpl_b16 window_is_closed, window_has_focus;

#if defined(ZPL_SYSTEM_WINDOWS)
    void *win32_dc;
#elif defined(ZPL_SYSTEM_OSX)
    // TODO(bill): Is this really needed?
    void *osx_autorelease_pool;
#endif

    zpl_renderer_type renderer_type;
    union {
        struct {
            void *context;
            zpl_i32 major;
            zpl_i32 minor;
            zpl_b16 core, compatible;
            zpl_dll_handle dll_handle;
        } opengl;

        // NOTE(bill): Software rendering
        struct {
#if defined(ZPL_SYSTEM_WINDOWS)
            BITMAPINFO win32_bmi;
#endif
            void *memory;
            zpl_isize memory_size;
            zpl_i32 pitch;
            zpl_i32 bits_per_pixel;
        } sw_framebuffer;
    };

    zpl_key_state keys[ZPL_KEY_COUNT];
    struct {
        zpl_key_state control;
        zpl_key_state alt;
        zpl_key_state shift;
    } key_modifiers;

    zpl_rune char_buffer[256];
    zpl_isize char_buffer_count;

    void *window_cursor;
    zpl_b32 mouse_clip;
    zpl_b32 mouse_outside;
    zpl_i32 mouse_x, mouse_y;

    // NOTE(bill): Not raw mouse movement
    zpl_i32 mouse_dx, mouse_dy;

    // NOTE(bill): Raw mouse movement
    zpl_i32 mouse_raw_dx, mouse_raw_dy;

    zpl_f32 mouse_wheel_delta;
    zpl_key_state mouse_buttons[ZPL_MOUSEBUTTON_COUNT];

    zpl_game_controller game_controllers[ZPL_MAX_GAME_CONTROLLER_COUNT];

    zpl_f64 curr_time;
    zpl_f64 dt_for_frame;
    zpl_b32 quit_requested;

#if defined(ZPL_SYSTEM_WINDOWS)
    struct {
        zpl_xinput_get_state_proc *get_state;
        zpl_xinput_set_state_proc *set_state;
    } xinput;
#endif
} zpl_platform;

typedef struct zpl_video_mode {
    zpl_i32 width, height;
    zpl_i32 bits_per_pixel;
} zpl_video_mode;

ZPL_DEF zpl_video_mode zpl_set_video_mode(zpl_i32 width, zpl_i32 height, zpl_i32 bits_per_pixel);
ZPL_DEF zpl_b32        zpl_video_mode_is_valid(zpl_video_mode mode);
ZPL_DEF zpl_video_mode zpl_video_mode_get_desktop(void);

// NOTE(bill): returns mode count
ZPL_DEF zpl_isize      zpl_video_mode_get_fullscreen_modes(zpl_video_mode *modes, zpl_isize max_mode_count);

ZPL_DEF ZPL_COMPARE_PROC(zpl_video_mode_cmp);     // NOTE(bill): Sort smallest to largest (Ascending)
ZPL_DEF ZPL_COMPARE_PROC(zpl_video_mode_dsc_cmp); // NOTE(bill): Sort largest to smallest (Descending)

// NOTE(bill): Software rendering
ZPL_DEF zpl_b32 zpl_platform_init_with_software(zpl_platform *p, char const *window_title, zpl_i32 width, zpl_i32 height, zpl_u32 window_flags);

// NOTE(bill): OpenGL Rendering
ZPL_DEF zpl_b32 zpl_platform_init_with_opengl(zpl_platform *p, char const *window_title, zpl_i32 width, zpl_i32 height, zpl_u32 window_flags, zpl_i32 major, zpl_i32 minor, zpl_b32 core, zpl_b32 compatible);

ZPL_DEF void    zpl_platform_update(zpl_platform *p);
ZPL_DEF void    zpl_platform_display(zpl_platform *p);
ZPL_DEF void    zpl_platform_destroy(zpl_platform *p);
ZPL_DEF void    zpl_platform_show_cursor(zpl_platform *p, zpl_b32 show);
ZPL_DEF void    zpl_platform_set_cursor(zpl_platform *p, void *handle);
ZPL_DEF void    zpl_platform_set_mouse_position(zpl_platform *p, zpl_i32 x, zpl_i32 y);
ZPL_DEF void    zpl_platform_set_controller_vibration(zpl_platform *p, zpl_isize index, zpl_f32 left_motor, zpl_f32 right_motor);
ZPL_DEF zpl_b32 zpl_platform_has_clipboard_text(zpl_platform *p);
ZPL_DEF void    zpl_platform_set_clipboard_text(zpl_platform *p, char const *str);
ZPL_DEF char   *zpl_platform_get_clipboard_text(zpl_platform *p, zpl_allocator a);
ZPL_DEF zpl_u32 zpl_platform_get_scancode(zpl_platform *p, zpl_key_type key);
ZPL_DEF void    zpl_platform_set_window_position(zpl_platform *p, zpl_i32 x, zpl_i32 y);
ZPL_DEF void    zpl_platform_set_window_title(zpl_platform *p, char const *title, ...) ZPL_PRINTF_FORMAT(2, 3);
ZPL_DEF void    zpl_platform_toggle_fullscreen(zpl_platform *p, zpl_b32 fullscreen_desktop);
ZPL_DEF void    zpl_platform_toggle_borderless(zpl_platform *p);
ZPL_DEF void    zpl_platform_make_opengl_context_current(zpl_platform *p);
ZPL_DEF void    zpl_platform_show_window(zpl_platform *p);
ZPL_DEF void    zpl_platform_hide_window(zpl_platform *p);

//! @}
