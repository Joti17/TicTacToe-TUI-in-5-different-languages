org 0x7C00
bits 16

%define ENDL 0x0D, 0x0A

start:
    jmp main



; inputs: ES:DI = pointer, CX = length
clear:
    pusha

    mov ax, 0x0700  ; function 07, AL=0 means scroll whole window
    mov bh, 0x07    ; character attribute = white on black
    mov cx, 0x0000  ; row = 0, col = 0
    mov dx, 0x184f  ; row = 24 (0x18), col = 79 (0x4f)
    int 0x10        ; call BIOS video interrupt
    nop
    nop

    popa
    ret


; inputs:
;   SI = pointer to string
;   CX = index
; output:
;   AL = character at string[CX]
getcharatindex:
    mov bx, cx       ; save index in BX
    add si, bx       ; SI now points to string[CX]
    mov al, [si]     ; load character into AL
    ret

; Write a value to an index
; inputs:
;   SI = pointer to string
;   CX = index
;   AL = value to write
setcharatindex:
    push bx
    mov bx, cx       ; save index
    add si, bx       ; SI points to string[index]
    mov [si], al     ; write AL to that position
    pop bx
    ret


; si msg
puts:
    push ax
    push ds
    push es

.loop:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    mov bh, 0    
    int 0x10
    jmp .loop


.done:
    pop es
    pop ds
    pop ax
    ret    




; in ah: scan code
; in al: ASCII code 
getkey:
    mov ah, 0
    int 0x16
    jmp .done

.done:
    ret    


main:
    mov ax, 0
    mov ds, ax
    mov es, ax

    mov ss, ax
    mov sp, 0x7C00          ;setup stack 

    mov di, array
    mov cx, 9
    call clear
    nop
    call MiniGame

    cli
    hlt
    jmp .halt

.halt:
    cli
    hlt
    jmp .halt

MiniGame:
    mov di, 0
    mov si, array
    call print_grid
    jmp .getkey

.getkey:
    mov si, array
.wait_key:
    call getkey       ; AL = ASCII
    cmp al, 'C'       ; check if clear
    je .clear_board
    cmp al, 'c'       ; also accept lowercase
    je .clear_board

    cmp al, '1'       ; only accept 1-9
    jb .wait_key
    cmp al, '9'
    ja .wait_key

    sub al, '0'       ; convert '1'-'9' -> 0-8
    dec al            ; optional: 1->0
    movzx cx, al
    jmp .press

.clear_board:
    mov si, array
    mov cx, 9
.clear_loop:
    mov byte [si], 0
    inc si
    loop .clear_loop
    jmp .prt

.press:
    test di, 1
    jnz .y_turn
.x_turn:
    mov al, "X"
    jmp .write
.y_turn:
    mov al, "O"

.write:
    mov si, array
    call setcharatindex
    inc di
    jmp .prt

.prt:
    ; reset cursor to top-left
    ; clear screen
    mov ah, 0x00
    mov al, 0x03       ; 03 = 80x25 text mode
    int 0x10
    mov ah, 0x02
    mov bh, 0
    mov dh, 0
    mov dl, 0
    int 0x10
    mov si, array
    call print_grid
    jmp .getkey




; ChatGPT:
; ------------------------
; Print 3x3 Tic-Tac-Toe grid
; SI = pointer to array
print_grid:
    mov si, array
    xor cx, cx

.row_loop:
    xor dx, dx
.column_loop:
    mov al, [si]
    cmp al, 0
    jne .print_char
    mov al, ' '
.print_char:
    mov ah, 0x0E
    mov bh, 0
    int 0x10

    inc dx
    cmp dx, 3
    je .end_row

    mov al, ' '
    mov ah, 0x0E
    int 0x10
    mov al, '|'
    mov ah, 0x0E
    int 0x10
    mov al, ' '
    mov ah, 0x0E
    int 0x10

    inc si
    jmp .column_loop

.end_row:
    mov al, 0x0D
    mov ah, 0x0E
    int 0x10
    mov al, 0x0A
    mov ah, 0x0E
    int 0x10

    inc cx
    cmp cx, 3
    je .done

    mov si, hline
.hline_loop:
    lodsb
    or al, al
    jz .after_hline
    mov ah, 0x0E
    mov bh, 0
    int 0x10
    jmp .hline_loop

.after_hline:
    mov si, array
    mov bx, cx
    imul bx, 3
    add si, bx
    jmp .row_loop

.done:
    ret

; End chatGPT, ist zu viel zu schrieben


hline: db '-', '-', '-', '-', '-', '-', '-', '-', '-', ENDL, 0



array: db 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
inputx: db "X's turn, put a number between 1-9", ENDL, 0
inputy: db "O's turn, put a number between 1-9", ENDL, 0









times 510-($-$$) db 0   ; Pad the rest of the boot sector with zeros
dw 0xAA55               ; Boot sector signature    
