.model small
.stack 100h
.data
x db "Hello Nibba!$"
ter db "Terminating...$"
.code
main proc
mov ax,@data
mov ds,ax
lea dx,x
mov ah,09h
int 21h
mov dl,0ah
mov ah,02h
int 21h
mov dl,0dh
mov ah,02h
int 21h
lea dx,ter
mov ah,09h
int 21h
mov ah,4ch
int 21h
main endp
end
