global get_pml4
get_pml4:
	mov rax, cr3
	ret
