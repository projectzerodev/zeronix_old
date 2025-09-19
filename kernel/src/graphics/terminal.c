#include "terminal.h"
#include <flanterm.h>
#include <flanterm_backends/fb.h>
#include <limine.h>

struct flanterm_context *ft_ctx;

int _term_init(struct limine_framebuffer *fb) {
    ft_ctx = flanterm_fb_init(
        NULL, NULL, fb->address, fb->width, fb->height, fb->pitch,
        fb->red_mask_size, fb->red_mask_shift, fb->green_mask_size,
        fb->green_mask_shift, fb->blue_mask_size, fb->blue_mask_shift, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 0, 0);
    return 0;
}

void _term_write(const char *buf, size_t len) {
    flanterm_write(ft_ctx, buf, len);
}
