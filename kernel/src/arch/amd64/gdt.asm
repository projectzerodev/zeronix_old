; void amd64_gdt_load(gdt_ptr_t *pointer, uint16_t code_segment, uint16_t data_segment)
global amd64_gdt_load
amd64_gdt_load:
    lgdt [rdi]

    movzx   rax, si
    push    rax
    lea     rax, [rel .reload_cs]
    push    rax
    retfq

.reload_cs:
    mov     ds, dx
    mov     es, dx
    mov     fs, dx
    mov     gs, dx
    mov     ss, dx
    ret
