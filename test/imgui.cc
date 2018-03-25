#define STB_IMAGE_IMPLEMENTATION
#define ZPLGL_NO_FONTS
#define ZPL_PLATFORM
#define ZPL_IMPLEMENTATION
#define ZPL_GLGEN_IMPLEMENTATION
#define ZPLGL_IMPLEMENTATION
#include "zpl.h"
#include "stb_image.h"
#include "zpl_glgen.h"
#include "zpl_opengl.h"

// This example REQUIRES you to download the latest version of Dear ImGUI.
#include "imgui.h"
#include "imgui/imgui_impl_zpl_gl3.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    zpl_platform p_ = { 0 };
    zpl_platform *p = &p_;

    const int window_width = 640;
    const int window_height = 480;

    zpl_platform_init_with_opengl(p, "OpenGL Test", window_width, window_height, 0, 3, 3, false, true);

    zpl_glgen_init();

    zplgl_basic_state state_ = { 0 };
    zplgl_basic_state *state = &state_;

    zplgl_bs_init(state, window_width, window_height);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplZPLGL3_Init(p);

    ImGui::StyleColorsDark();

    b32 is_running = true;

    for (;is_running;) {
        zpl_platform_update(p);
        ImGui_ImplZPLGL3_ProcessEvent(p);

        glClear(GL_COLOR_BUFFER_BIT);

        if (p->window_is_closed ||
            p->keys[ZPL_KEY_ESCAPE]) {
            is_running = false;
        }

        ImGui_ImplZPLGL3_NewFrame(p);

        zplgl_bs_begin(state, window_width, window_height);
        {
            zplgl_bs_draw_circle(state, 320, 240, 32, zplgl_color_orange);
        }
        zplgl_bs_end(state);

        // dear imgui
        {
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::Text("Mouse X: %d, Mouse Y: %d", p->mouse_x, p->mouse_y);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        ImGui::Render();
        ImGui_ImplZPLGL3_RenderDrawData(ImGui::GetDrawData());
        zpl_platform_display(p);
        zpl_yield();
    }

    ImGui_ImplZPLGL3_Shutdown();
    ImGui::DestroyContext();

    zpl_platform_destroy(p);

    return ERROR_SUCCESS;
}