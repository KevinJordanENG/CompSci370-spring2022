; --------------------------------------------------
; Welcome to HW1 for CSCI 370 Spring 2022 @ UND
; Displays the contents of a file on the screen.
; By Kevin Jordan ID: 1301006 kevin.jordan@und.edu
; Compile with: nasm -f elf64 hw1-KevinJordan.asm
; Link with: ld hw1-KevinJordan.o -o hw1-KevinJordan
; run with: ./hw1-KevinJordan
; --------------------------------------------------
section .data
  file db "hw1-KevinJordan.asm",0   ;filename ends with '\0' byte
section .bss
  descriptor resb 4                 ;memory for storing descriptor
  buffer resb 2048
  len equ 2048
section .start
global _start
_start:
  mov eax,5                         ;open
  mov ebx,file                      ;filename
  mov ecx,0                         ;read only
  int 80h                           ;open filename for read only

  mov [descriptor],eax              ;storing the descriptor

  mov eax,3                         ;read from file
  mov ebx,[descriptor]              ;your file descriptor
  mov ecx,buffer                    ;read to buffer
  mov edx,len                       ;read len bytes
  int 80h                           ;read len bytes to buffer from file

  mov edx,eax                       ;storing count of readed bytes to edx
  mov eax,4                         ;write to file
  mov ebx,1                         ;terminal
  mov ecx,buffer                    ;from buffer
  int 80h                           ;write to terminal all readed bytes from buffer

  mov eax,6                         ;close file
  mov ebx,[descriptor]              ;your file descriptor
  int 80h                           ;close your file

  mov eax,1
  mov ebx,0
  int 80h
