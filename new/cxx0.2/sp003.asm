; Listing generated by Microsoft (R) Optimizing Compiler Version 19.37.32825.0 

	TITLE	C:\tmp\cxx\sp003.obj
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_gcLocalSmartPointer
PUBLIC	_main
EXTRN	_gcLocalMalloc:PROC
EXTRN	_gc:DWORD
; Function compile flags: /Ogtpy
;	COMDAT _main
_TEXT	SEGMENT
_main	PROC						; COMDAT
; File C:\tmp\cxx\tst\sp003.c
; Line 54
	push	ebx
	push	esi
	push	edi
; Line 55
	mov	edi, DWORD PTR _gc
; Line 22
	push	8
	push	edi
	call	_gcLocalMalloc
	mov	esi, eax
	add	esp, 8
; Line 24
	test	esi, esi
	je	SHORT $LN4@main
; Line 30
	push	400					; 00000190H
	push	edi
	mov	WORD PTR [esi+4], 257			; 00000101H
	mov	BYTE PTR [esi+6], 0
	call	_gcLocalMalloc
	add	esp, 8
; Line 31
	test	eax, eax
	je	SHORT $LN4@main
; Line 33
	mov	DWORD PTR [esi], eax
; Line 34
	mov	BYTE PTR [esi+6], 1
; Line 46
	jmp	SHORT $LN3@main
$LN4@main:
; Line 57
	xor	esi, esi
$LN3@main:
	mov	eax, DWORD PTR [esi]
; Line 22
	push	8
; Line 57
	mov	DWORD PTR [eax], 10			; 0000000aH
; Line 59
	mov	ebx, DWORD PTR _gc
; Line 22
	push	ebx
	call	_gcLocalMalloc
	mov	edi, eax
	add	esp, 8
; Line 24
	test	edi, edi
	je	SHORT $LN10@main
; Line 30
	push	400					; 00000190H
	push	ebx
	mov	WORD PTR [edi+4], 257			; 00000101H
	mov	BYTE PTR [edi+6], 0
	call	_gcLocalMalloc
	add	esp, 8
; Line 31
	test	eax, eax
	je	SHORT $LN10@main
; Line 33
	mov	DWORD PTR [edi], eax
; Line 34
	mov	BYTE PTR [edi+6], 1
; Line 61
	mov	eax, DWORD PTR [esi]
	mov	ecx, DWORD PTR [edi]
; Line 64
	pop	edi
	pop	esi
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR [ecx], eax
	xor	eax, eax
	pop	ebx
; Line 65
	ret	0
$LN10@main:
; Line 61
	mov	eax, DWORD PTR [esi]
	xor	edi, edi
	mov	ecx, DWORD PTR [edi]
	mov	eax, DWORD PTR [eax]
; Line 64
	pop	edi
	pop	esi
	mov	DWORD PTR [ecx], eax
	xor	eax, eax
	pop	ebx
; Line 65
	ret	0
_main	ENDP
_TEXT	ENDS
; Function compile flags: /Ogtpy
;	COMDAT _gcLocalSmartPointer
_TEXT	SEGMENT
_gc$ = 8						; size = 4
_ptrSize$ = 12						; size = 4
_gcLocalSmartPointer PROC				; COMDAT
; File C:\tmp\cxx\tst\sp003.c
; Line 21
	push	esi
; Line 22
	push	8
	push	DWORD PTR _gc$[esp+4]
	call	_gcLocalMalloc
	mov	esi, eax
	add	esp, 8
; Line 24
	test	esi, esi
	je	SHORT $LN2@gcLocalSma
; Line 30
	push	DWORD PTR _ptrSize$[esp]
	mov	WORD PTR [esi+4], 257			; 00000101H
	push	DWORD PTR _gc$[esp+4]
	mov	BYTE PTR [esi+6], 0
	call	_gcLocalMalloc
	add	esp, 8
; Line 31
	test	eax, eax
	je	SHORT $LN2@gcLocalSma
; Line 33
	mov	DWORD PTR [esi], eax
; Line 46
	mov	eax, esi
	mov	BYTE PTR [esi+6], 1
	pop	esi
; Line 47
	ret	0
$LN2@gcLocalSma:
; Line 43
	xor	eax, eax
	pop	esi
; Line 47
	ret	0
_gcLocalSmartPointer ENDP
_TEXT	ENDS
END
