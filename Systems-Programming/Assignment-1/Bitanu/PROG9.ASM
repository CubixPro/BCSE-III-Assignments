.model small
.stack 100h
.data
mes1 db 0dh, 0ah, "Enter 1 to exit: ", "$"
mes2 db 0dh, 0ah, "Iterating...", "$"
.code
main proc
mov ax,@data
mov ds,ax
loop1:
lea dx,mes2
mov ah,09h
int 21h
lea dx,mes1
mov ah,09h
int 21h
mov ah,01h
int 21h
cmp al,'1'
jne loop1
mov ah,4ch
int 21h
main endp
end
