.model small
.stack 100h
.data 
x db 0ah, 0dh, "$"
.code
main proc
mov ax, @data
mov ds, ax
mov al, 0
mov bl, 1

call displayNumber
mov al, bl
call displayNumber
mov al, 0
mov ch, 02h
l1:
mov cl, bl
add bl, al
mov al, bl
call displayNumber
mov al, cl
inc ch
cmp ch, 10
jne l1

mov ah, 4ch
int 21h
main endp

displayNumber proc
push bx
mov bl, 10
mov bh, 00h
l2: mov ah, 00h
div bl
push ax
inc bh
cmp al, 0
jne l2
l3: pop dx
mov dl, dh
mov dh, 0
add dl, 48
mov ah, 02h
int 21h
dec bh
cmp bh, 0
jne l3
lea dx, x
mov ah, 09h
int 21h
pop bx
ret

displayNumber endp
end
