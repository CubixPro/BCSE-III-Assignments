.model small
.stack 100h

.data
x db 0ah, 0dh, '$'

.code
main proc
mov ax, @data
mov ds, ax
mov cl, 2
mov ch, 00h
l1: mov bl, 1
mov bh, 0
l2: mov ax, cx
div bl
cmp ah, 0
jne l3
inc bh
l3: inc bl
cmp bl, cl
jne l2

cmp bh, 1
jg l4

mov ax, cx
call displayNumber

l4: inc cl
cmp cl, 100
jne l1

mov ah, 4ch
int 21h

main endp
displayNumber proc
mov bl, 10
mov bh, 00h
l5: mov ah, 00h
div bl
push ax
inc bh
cmp al, 0
jne l5
l6: pop dx
mov dl, dh
mov dh, 0
add dl, 48
mov ah, 02h
int 21h
dec bh
cmp bh, 0
jne l6

lea dx, x
mov ah, 09h
int 21h
ret

displayNumber endp
end
