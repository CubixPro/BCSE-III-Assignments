.model small
.stack 100h
.data
mes1 db 0ah,0dh,"Enter 1st number:$"
mes2 db 0ah,0dh,"Enter 2nd number:$"
mes3 db 0ah,0dh,"First number is greater than second number$"
mes4 db 0ah,0dh,"Second number is greater than first number$"
mes5 db 0ah,0dh,"The two numbers are equal$"
.code
main proc
mov ax,@data
mov ds,ax
lea dx,mes1
mov ah,09h
int 21h
mov ah,01h
int 21h
mov bl,al
lea dx,mes2
mov ah,09h
int 21h
mov ah,01h
int 21h
cmp bl,al
jg cond1
jl cond2
lea dx,mes5
mov ah,09h
int 21h
mov ah,4ch
int 21h
cond1:
lea dx,mes3
mov ah,09h
int 21h
mov ah,4ch
int 21h
cond2:
lea dx,mes4
mov ah,09h
int 21h
mov ah,4ch
int 21h
main endp
end
