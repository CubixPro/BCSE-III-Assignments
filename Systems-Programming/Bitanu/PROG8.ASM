.model small
.stack 100h

.data
prompt_0  db  'enter the number of array elements :',0dh,0ah,'$'
prompt_1  db  'enter the array elements :',0dh,0ah,'$'
prompt_2  db  'the maximum is : $'
prompt_3  db  'the minimum is : $'

array   dw  50 dup(0)    

s dw ?

.code
main proc

		mov ax, @data                ; initialize ds
		mov ds, ax

		lea dx, prompt_0             ; load and display the string prompt_0
		mov ah, 9     
		int 21h

		mov ah,1                                    ;for taking input
		int 21h

		input1:
		cmp al,0dh                                  ;compare whether the pressed key is 'enter' or not
		je line1                                    ;if it is equal to 'enter' then stop taking first value

		and al,0fh                                  ;convert it's ascii value to real value by masking

		shl bx, 1
		shl bx, 1
		shl bx, 1
		shl bx, 1
		or  bl,al                                   ;making 'or' will add the current value with previous value

		int 21h
		jmp input1

		line1:     
		lea dx, prompt_1             ; load and display the string prompt_1
		mov ah, 9     
		int 21h

		lea si, array                ; set si=offset address of array

		mov cx, bx                     ; set cx=bx


		@read_array:                   ; loop label

		mov ah,1                                    ;for taking input
		int 21h

		xor dx,dx

		input2:
		cmp al,0dh                                  ;compare whether the pressed key is 'enter' or not
		je line2                                   ;if it is equal to 'enter' then stop taking first value

		and al,0fh                                 ;convert it's ascii value to real value by masking

		shl dx,1
		shl dx,1
		shl dx,1
		shl dx,1
		or  dl,al                                   ;making 'or' will add the current value with previous value

		int 21h
		jmp input2

		line2:
		mov [si], dx                 ; set [si]=ax
		add si, 2                    ; set si=si+2

		mov dl, 0ah                  ; line feed
		mov ah, 2                    ; set output function
		int 21h                      ; print a character

		loop @read_array               ; jump to label @read_array while cx!=0 
		; array input done

		lea si,array
		mov ax,bx
		dec ax
		xor bx,bx
		xor cx,cx
		mov bx,word ptr[si]	;store the maximum
		mov cx,word ptr[si]	;store the minimum
		add si, 2

		; loop to find max and min
		arrayloop2:

		cmp word ptr[si],bx
		jg maximum

		cmp word ptr[si],cx
		jl minimum

		jmp incre
		maximum:
		mov bx,word ptr[si]
		jmp incre

		minimum:
		mov cx,word ptr[si]

		incre:
		add si, 2
		dec ax

		jnz arrayloop2

		; displaying the prompt
		lea dx,prompt_2
		mov ah,09h
		int 21h

		; display contents of bx
		output:                                   ;level for printing their sum

		mov dh,bh
		shr dh, 1
		shr dh, 1
		shr dh, 1
		shr dh, 1
		and dh,0fh

		add dh,'0'                               
		mov dl,dh
		mov ah,2
		int 21h

		mov dh,bh
		and dh,0fh
		add dh,'0'
		mov dl,dh
		mov ah,2
		int 21h

		mov dh,bl
		shr dh, 1
		shr dh, 1
		shr dh, 1
		shr dh, 1
		and dh,0fh
		add dh,'0'
		mov dl,dh
		mov ah,2
		int 21h

		mov dh,bl
		and dh,0fh
		cmp dh,10
		add dh,'0'
		mov dl,dh
		mov ah,2
		int 21h

		mov dl, 0ah                  ; line feed
		mov ah, 2                    ; set output function
		int 21h                      ; print a character

		; displaying the prompt
		lea dx,prompt_3	
		mov ah,09h
		int 21h

		; display contents of cx
		mov bx,cx

		mov dh,bh
		shr dh, 1
		shr dh, 1
		shr dh, 1
		shr dh, 1
		and dh,0fh

		add dh,'0'                               
		mov dl,dh
		mov ah,2
		int 21h

		mov dh,bh
		and dh,0fh
		add dh,'0'
		mov dl,dh
		mov ah,2
		int 21h

		mov dh,bl
		shr dh, 1
		shr dh, 1
		shr dh, 1
		shr dh, 1
		and dh,0fh
		add dh,'0'
		mov dl,dh
		mov ah,2
		int 21h

		mov dh,bl
		and dh,0fh
		cmp dh,10
		add dh,'0'
		mov dl,dh
		mov ah,2
		int 21h


		exit:
		mov ah, 4ch                               ;return control to dos
		int 21h

main endp
end main
