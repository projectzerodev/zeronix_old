global amd64_idt_load
amd64_idt_load:
    lidt [rdi]
