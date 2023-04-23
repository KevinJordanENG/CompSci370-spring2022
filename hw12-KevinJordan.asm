# Welcome to HW12 for CSCI 370 Spring 2022 @ UND
# Assembly program takes int input and uses value
# to determine number of values to print of Fibonacci sequence
# (max 45). Also takes 8 input bits (0/1), prints entered
# bits back to screen, and calculates ODD parity bit.
# By Kevin Jordan UND ID: 1301006 kevin.jordan@und.edu


            .data
fibSeq:     .word 0:45 # array var for sequence vals
seqSize:    .word 45 # size of array var
space:      .asciiz " " 
newLine:    .asciiz "\n"
            .text
            # Part 1: Fibonacci Sequence
            la $t0, fibSeq # load address of sequence
            lw $t5, seqSize # load seqSize
            li $t2, 1 # put val 1 into temp2 (1st & 2nd seq val)
            sw $t2, 0($t0) # fibSeq[0] = 1;
            sw $t2, 4($t0) # fibSeq[1] = 1;
            addi $t1, $t5, -2 # set loop_counter (seqSize - 2, because fibSeq[0]&fibSeq[1] already filled)
calcNums:   lw $t3, 0($t0) # load fibSeq[n] 
            lw $t4, 4($t0) # load fibSeq[n+1]
            add $t2, $t3, $t4 # temp2 = fibSeq[n] + fibSeq[n+1]
            sw $t2, 8($t0) # save fibSeq[n+2] = temp2
            addi $t0, $t0, 4 # seq_address++
            addi $t1, $t1, -1 # loop_counter--
            bgtz $t1, calcNums # branch > 0: loop till seqSize reached
            la $a0, fibSeq # arg0 for printFS subroutine
            jal printFS # subroutine Fib seq
            la $a0, newLine # address of "\n"
            li $v0, 4 # 4 == print_string
            syscall # print "\n"
            # Part 2: 8-bit ODD parity
            jal bitStrRtn # subroutine bit parity
            li $v0, 10 # 10 == exit
            syscall # end of prog

		
# Subroutine to print specified number of values of Fibonacci seq (Part 1)
            .data
prompt1:    .asciiz "Enter the Fibonacci sequence size: "
loopMax:    .word 0 # initialize var to receive user input
            .text
printFS:    add $t0, $zero, $a0 # starting address of array var from main routine
            la $a0, prompt1 # load address of prompt
            li $v0, 4 # 4 == print_string
            syscall # print prompt1
            li $v0, 5 # 5 == read_int
            syscall # read int to use as max number of Fib seq vals to print (MAX 45 as largest 32 bit storable int of seq!)
            sw $v0, loopMax # save entered int val into loopMax
            lw $t1, loopMax # load saved max size val
printNums:  lw $a0, 0($t0) # load val to print
            li $v0, 1 # 1 == print_int
            syscall # print fibonacci val
            la $a0, space # address of " "
            li $v0, 4 # 4 == print_string (" ")
            syscall # print " "
            addi $t0, $t0, 4 # address_to_print_++
            addi $t1, $t1, -1 # loop_counter--
            bgtz $t1, printNums # branch > 0: loop till loopMax reached
            jr $ra # return to main prog
            

# Subroutine to get bit string and print it + its ODD parity
            .data
prompt2:    .asciiz "Enter a binary string: "
bitStr:     .asciiz "" # empty string to hold user input bit string
numOddBits: .word 0 # counter for odd bit parity
parityBit:  .word 0 # for parity
            .text
bitStrRtn:  la $a0, prompt2 # address of prompt2
            li $v0, 4 # 4 == print_string
            syscall # print prompt2
            la $a0, bitStr # set arg0 (address of str input buffer)
            li $a1, 9 # set arg1 (str len n accounting for '\0')
            li $v0, 8 # 8 == read_string
            syscall # read in user entered bit string as asciiz type
            la $a0, newLine # address of "\n"
            li $v0, 4 # 4 == print_string
            syscall # print "\n"
            la $a0, bitStr # load address of entered string
            li $v0, 4 # 4 == print_string
            syscall # print entered bit string
            la $a0, newLine # address of "\n"
            li $v0, 4 # 4 == print_string
            syscall # print "\n"
            li $t1, 0 # set temp1 to 0 as loop counter
            li $t3, 0 # set temp3 to 0 as 1s counter
            li $t4, 0 # set temp4 to 0 for parity finding
oddBitCnt:  lb $a0, bitStr($t1) # take nth bit from entered string
            move $t2, $a0 # move it to temp2 for use
            beq $t2, 0x0a, endBitCnt # if == '\n' end of string and end of counting 1s
            beq $t2, 0x00, endBitCnt # if == '\0' end of string and end of counting 1s
            addi $t1, $t1, 1 # loop_counter++
            beq $t2, 0x30, oddBitCnt # if bit from string == 0 no need to increment 1s count
            addi $t3, $t3, 1 # otherwise incremnt 1s count
            j oddBitCnt # jump to top of loop
endBitCnt:  addi $t3, $t3, 0x30 # add '0' value to counted 1s so it will print nicely
            sw $t3, numOddBits # save num of total number of 1s
            beq $t3, 0x30, print1 # if 0 1s, even & need 1 as parity bit
            beq $t3, 0x31, print0 # if 1 1s, already odd print 0
            beq $t3, 0x32, print1 # if 2 1s, even & need 1 as parity bit
            beq $t3, 0x33, print0 # if 3 1s, already odd print 0
            beq $t3, 0x34, print1 # if 4 1s, even & need 1 as parity bit
            beq $t3, 0x35, print0 # if 5 1s, already odd print 0
            beq $t3, 0x36, print1 # if 6 1s, even & need 1 as parity bit
            beq $t3, 0x37, print0 # if 7 1s, already odd print 0
            beq $t3, 0x38, print1 # if 8 1s, even & need 1 as parity bit
print0:     addi $t4, $t4, 0x30 # add hex 30 to make nice for print
            sw $t4, parityBit # put '0' in parityBit
            j parity # jump to print it out
print1:     addi $t4, $t4, 0x31 # add hex 31 to make nice for print
            sw $t4, parityBit # put '1' in parityBit
parity:     la $a0, parityBit # address of stored parity bit
            li $v0, 4 # 4 == print_string
            syscall # print parityBit
            jr $ra # return to main prog
            
            
