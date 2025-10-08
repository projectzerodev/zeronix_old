#include "tty.h"
#include "flanterm.h"
#include "flanterm_backends/fb.h"
#include "hal/cpu.h"
#include "limine.h"

struct flanterm_context *ft_ctx;

void _tty_init(volatile struct limine_framebuffer_request *framebuffer_request)
{
    if (framebuffer_request->response == NULL ||
        framebuffer_request->response->framebuffer_count < 1)
    {
        halt_loop();
    }

    struct limine_framebuffer *fb = framebuffer_request->response->framebuffers[0];

    ft_ctx = flanterm_fb_init(NULL, NULL, fb->address, fb->width, fb->height, fb->pitch,
                              fb->red_mask_size, fb->red_mask_shift, fb->green_mask_size,
                              fb->green_mask_shift, fb->blue_mask_size, fb->blue_mask_shift, NULL,
                              NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 1, 0, 0, 0);
}

void _tty_write(const char *buf, size_t len)
{
    flanterm_write(ft_ctx, buf, len);
}
