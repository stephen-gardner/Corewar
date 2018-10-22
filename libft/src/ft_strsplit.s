; ---------------------------------------------------------------------------- ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strsplit.s                                      :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2018/10/19 04:20:04 by sgardner          #+#    #+#              ;
;    Updated: 2018/10/20 18:34:10 by sgardner         ###   ########.fr        ;
;                                                                              ;
; ---------------------------------------------------------------------------- ;

	global	_ft_strsplit
	extern	_malloc

	section	.text
_ft_strsplit:
	push	rbp
	mov		rbp, rsp
	sub		rsp, 32				; alignment
	mov		al, sil				; delimiter
	mov		rsi, rdi			; input string
	xor		rdx, rdx			; # words
	xor		r8, r8				; # chars
.calc_size:
	mov		rcx, -1
	rep		scasb
	dec		rdi
	cmp		byte [rdi], 0
	je		.alloc_array
	inc		rdx
.count_chars:
	inc		r8
	cmp		byte [rdi], 0
	je		.alloc_array
	scasb
	jne		.count_chars
	jmp		.calc_size
.alloc_array:
	inc		rdx					; for NULL
	shl		rdx, 3				; x8 words for pointers
	add		r8, rdx
	mov		rdi, r8
	mov		[rbp - 8], rdx
	mov		[rbp - 16], rsi
	mov		[rbp - 24], al
	call	_malloc
	test	rax, rax
	je		.done
	mov		r8, rax				; array start position
	mov		rdx, rax			; array pointer position
	mov		rdi, [rbp - 8]		; array data position
	add		rdi, rax
	mov		rsi, [rbp - 16]		; input string
	mov		al, [rbp - 24]
.build_array:
	xchg	rdi, rsi
	mov		rcx, -1
	rep		scasb
	dec		rdi
	xchg	rdi, rsi
	cmp		byte [rsi], 0
	je		.terminate
	mov		[rdx], rdi
	add		rdx, 8
.copy_chars:
	movsb
	cmp		byte [rsi], 0
	je		.terminate
	cmp		[rsi], al
	jne		.copy_chars
	mov		byte [rdi], 0
	inc		rdi
	jmp		.build_array
.terminate:
	mov		qword [rdx], 0
	mov		byte [rdi], 0
	mov		rax, r8
.done:
	add		rsp, 32
	pop		rbp
	ret
