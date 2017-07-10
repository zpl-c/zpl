/*
New File
*/

#define ZPL_IMPLEMENTATION
#define ZPL_PLATFORM
#include "zpl.h"

#define ZPL_GL3W_IMPLEMENTATION
#include "zpl_gl3w.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

int
main(void) {
    zplPlatform p_ = {0};
    zplPlatform*p  = &p_;
    
    zpl_platform_init_with_opengl(p, "OpenGL test", WIN_WIDTH, WIN_HEIGHT, 0, 3, 3, false, true);
    
    b32 is_running = true;
    
    zpl_gl3w_init();
    
    while(is_running) {
        zpl_platform_update(p);
        
        if (p->keys[zplKey_Escape] == true ||
            p->keys[zplKey_Space]  == true) {
            is_running = false;
        }
        else if (p->window_is_closed) {
            is_running = false;
        }
        
        zpl_platform_display(p);
        zpl_sleep_ms(10);
    }
    
    return 0;
}