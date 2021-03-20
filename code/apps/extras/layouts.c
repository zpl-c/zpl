#define ZPL_IMPL
#define ZPL_NANO
#define ZPL_ENABLE_MATH
#include <zpl.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_STDIO
#include "stb_image.h"

#define BMP_W 1024
#define BMP_H 768
#define BMP_C 4
#define BMP_S (BMP_W*BMP_H*BMP_C)
#define BMP_L(x,y) ((y*BMP_W)+x)
#define BMP_X(i) ((i) % BMP_W)
#define BMP_Y(i) ((i) / BMP_W)

#define LINES_C 20
#define LINE_H 15
#define LINE_S 5
#define TOTAL_LINES_H (LINES_C * (LINE_H+LINE_S))

zpl_u8 buf[BMP_S];

void draw_rect(zpl_aabb2 a, zpl_u32 color);
void draw_rect_tex(zpl_aabb2 a, stbi_uc *imgdata, zpl_isize img_w, zpl_isize img_h);
void draw_circle(zpl_vec2 a, zpl_u32 color, zpl_f32 radius);
void draw_rect_round(zpl_aabb2 a, zpl_u32 color);

int main(void) {
    zpl_aabb2 fr = zpl_aabb2f(0, 0, BMP_W, BMP_H);

    zpl_file_contents fc = zpl_file_read_contents(zpl_heap(), 0, "bg.png");
    zpl_i32 imgw, imgh, imgc;
    stbi_uc *imgdata = stbi_load_from_memory(fc.data, fc.size, &imgw, &imgh, &imgc, 4);
    draw_rect_tex(fr, imgdata, imgw, imgh);

    zpl_rect2 window = zpl_rect2f(zpl_vec2f(120, 20), zpl_vec2f(350, 600));
    zpl_aabb2 fill = zpl_aabb2_rect2(window);
    draw_rect(fill, 0xFF333333);
    {
        // header
        {
            zpl_aabb2 header = zpl_aabb2_cut_top(&fill, 30);
            draw_rect(header, 0xFF007788);
        }
        // footer
        {
            zpl_aabb2 footer = zpl_aabb2_cut_bottom(&fill, 120);
            zpl_aabb2_cut_left(&footer, 30);
            zpl_aabb2_cut_right(&footer, 30);
            zpl_aabb2_cut_bottom(&footer, 30);
            draw_rect(footer, 0xFF007788);
            footer = zpl_aabb2_contract(&footer, 10);
            draw_rect(footer, 0xFF333333);
        }
        // body
        {
            zpl_aabb2 content = zpl_aabb2_contract(&fill, 15);
            zpl_rect2 crect = zpl_rect2_aabb2(content);
            for (zpl_isize i=0; i<LINES_C; i++) {
                zpl_rect2 line = zpl_rect2f(content.min, zpl_vec2f(zpl_step(zpl_max(crect.dim.x/4, rand() % cast(zpl_isize)crect.dim.x), 10), LINE_H));
                line.pos.y += (i*(LINE_H+LINE_S));
                draw_rect_round(zpl_aabb2_rect2(line), 0xFF666666);
            }
        }
    }
    stbi_write_png("test.png", BMP_W, BMP_H, BMP_C, buf, BMP_C*BMP_W);
    zpl_file_free_contents(&fc);
    return 0;
}

void draw_rect(zpl_aabb2 a, zpl_u32 color) {
    for (zpl_isize i=0; i<BMP_W*BMP_H; i++) {
        zpl_isize x = BMP_X(i);
        zpl_isize y = BMP_Y(i);
        if (zpl_aabb2_contains(a, x, y)) {
            *(cast(zpl_u32*)&buf[i*BMP_C]) = color;
        }
    }
}

void draw_rect_tex(zpl_aabb2 a, stbi_uc *imgdata, zpl_isize img_w, zpl_isize img_h) {
    zpl_isize ai = 0;
    for (zpl_isize i=0; i<BMP_W*BMP_H; i++) {
        zpl_isize x = BMP_X(i);
        zpl_isize y = BMP_Y(i);
        if (zpl_aabb2_contains(a, x, y)) {
            *(cast(zpl_u32*)&buf[i*BMP_C]) = *(cast(zpl_u32*)&imgdata[i*BMP_C]);
        }
    }
}

void draw_circle(zpl_vec2 a, zpl_u32 color, zpl_f32 radius) {
    for (zpl_isize i=0; i<BMP_W*BMP_H; i++) {
        zpl_isize x = BMP_X(i);
        zpl_isize y = BMP_Y(i);
        zpl_vec2 pos = zpl_vec2f(x,y);
        zpl_vec2 v;
        zpl_vec2_sub(&v, pos, a);
        if (zpl_vec2_mag2(v) <= zpl_square(radius/2)) {
            *(cast(zpl_u32*)&buf[i*BMP_C]) = color;
        }
    }
}

void draw_rect_round(zpl_aabb2 a, zpl_u32 color) {
    zpl_rect2 r = zpl_rect2_aabb2(a);
    zpl_vec2 pos = r.pos, endpos;
    pos.y += r.dim.y/2-0.5f;
    endpos = pos;
    endpos.x += r.dim.x;
    draw_circle(pos, color, r.dim.y);
    draw_circle(endpos, color, r.dim.y);
    draw_rect(a, color);
}
