        .data
val:    .word 0
        .text
        li $v0, 5
        syscall
        # enter 12345
        sw $v0, val
        lw $a0, val
        li $v0, 1
        syscall