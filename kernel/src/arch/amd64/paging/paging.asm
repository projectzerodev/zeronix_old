global get_pml4
get_pml4:
	mov rax, cr3
	ret

global load_pml4
load_pml4:
	mov cr3, rdi
	ret
