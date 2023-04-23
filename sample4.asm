        .data
val:    .byte 1
        .half 2
        .word 3
        .text
        lb $a0, val+1
        li $v0, 1
        syscall