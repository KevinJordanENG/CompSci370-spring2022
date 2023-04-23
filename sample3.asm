        .data
s:      .space 4
        .text
        la $a0, s
        li $a1, 4
        li $v0, 8
        syscall
        #enter 12345
        la $a0, s
        li $v0, 4
        syscall