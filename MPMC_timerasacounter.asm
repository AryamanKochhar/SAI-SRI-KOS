PORT PROGRAMMING 
ORG 0000H 
MOV P1, #00H
MOV P2, #00H
MOV TMOD, #50H         ; Timer 1 in mode 2 as a counter
AGAIN: MOV TH1, #00H
MOV TL1, #00H
SETB TR1               ; Start Timer 1 (used as a counter)
L1: MOV A, TL1
MOV P1, A
MOV A, TH1
MOV P2, A
JNB TF1, L1            ; Wait until overflow
CLR TF1
CLR TR1
SJMP AGAIN
END

