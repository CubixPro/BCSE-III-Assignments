.model small
.stack 100h
.data 
x db 0ah, 0dh, "Quotient : $"
y db 0ah, 0dh, "Remainder : $"
.code
main proc

mov ax, @data
mov ds, ax
lea dx, x
mov ah, 09h
int 21h

mov ax, 10AAh
mov bl, 26h

div bl

mov cl , ah
call displayNumber 

lea dx, y
mov ah, 09h
int 21h

mov al, cl
call displayNumber

mov ah, 4ch
int 21h

main endp

displayNumber proc
mov ch, 0
mov bl, 10
l1:mov ah,0
div bl
push ax
inc ch
cmp al, 0
jne l1

l2: pop dx
mov dl, dh
add dl, 48
mov dh, 0
mov ah, 02h
int 21h

dec ch
cmp ch, 0
jne l2

ret
displayNumber endp

end
