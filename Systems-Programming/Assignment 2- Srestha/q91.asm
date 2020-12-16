.MODEL SMALL
.STACK 300H
.DATA
ARRAY1 DB 11,22,33,44,55
MSG4 DB 0AH,0DH,'Enter size of the array: $'
MSG1 DB 0AH,0DH,'Enter number to be searched: $'
MSG2 DB 0AH,0DH,'FOUND AT POSITION $ '
MSG3 DB 0AH,0DH,'NOT FOUND$'
ENDL DB 0AH,0DH,'$'

SE DB 33H
COUNT DB 00H

.CODE

PRINT MACRO MSG
	push ax
	push dx
	mov AH, 09H
	lea DX, MSG
	int 21H
	;int 3
	pop dx
	pop ax
ENDM

MAIN PROC
	MOV AX,@DATA
	MOV DS,AX

START:

	PRINT MSG4
	call readnum
	mov COUNT, al
	mov cl, COUNT
	mov bx, 00h
	rdnxt:
		PRINT ENDL
		call readnum
		mov ARRAY1[BX],AL
		inc BX
	loop rdnxt
	
	mov cl, COUNT
	PRINT MSG1
	call readnum
	mov se,al
	mov al,se
	mov ah,00h
	;call writenum
	;PRINT ENDL
	;mov al,se
	;mov ah,00h
	;call writenum
	LEA SI, ARRAY1
	;mov bx, 05h
	;call PRINT_ARRAY
	;MOV CX, 04H
	mov bh, 00h
UP:
	MOV BL,[SI]
	CMP AL, BL
	JZ FO
	INC SI
	inc bh
	loop UP
	PRINT MSG3
	JMP END1
 
FO:
	
	PRINT MSG2
	mov al, bh
	call writenum
 
END1:
	mov ah, 4ch
	int 21h

MAIN ENDP


readnum proc near
	
	push bx
	push cx
	mov cx,0ah
	mov bx,00h
loopnum: 
	mov ah,01h
	int 21h
	cmp al,'0'
	jb skip
	cmp al,'9'
	ja skip
	sub al,'0'
	push ax
	mov ax,bx
	mul cx
	mov bx,ax
	pop ax
	mov ah,00h
	add bx,ax
	jmp loopnum
skip:
	mov ax,bx
	pop cx
	pop bx
	ret
readnum endp

writenum PROC near
   ; this procedure will display a decimal number
   ; input : AX
   ; output : none

   push bx                        ; push BX onto the STACK
   push cx                        ; push CX onto the STACK
   push dx                        ; push DX onto the STACK

   XOR CX, CX                     ; clear CX
   MOV BX, 10                     ; set BX=10

   @OUTPUT:                       ; loop label
     XOR DX, DX                   ; clear DX
     DIV BX                       ; divide AX by BX
     PUSH DX                      ; push DX onto the STACK
     INC CX                       ; increment CX
     OR AX, AX                    ; take OR of Ax with AX
   JNE @OUTPUT                    ; jump to label @OUTPUT if ZF=0

   MOV AH, 2                      ; set output function

   @DISPLAY:                      ; loop label
     POP DX                       ; pop a value from STACK to DX
     OR DL, 30H                   ; convert decimal to ascii code
     INT 21H                      ; print a character
   LOOP @DISPLAY                  ; jump to label @DISPLAY if CX!=0

   POP DX                         ; pop a value from STACK into DX
   POP CX                         ; pop a value from STACK into CX
   POP BX                         ; pop a value from STACK into BX

   RET                            ; return control to the calling procedure
writenum ENDP
	
END MAIN