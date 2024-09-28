for transmission 
ORG 0000H 
MOV TMOD, #20H         ; Timer 1 in mode 2 as a counter
MOV TH1, #-6DH         ; baud rate in  4800
MOV SCON,#50H          ; SCON REGISTER 50 H enable  01010000b
SETB TR1               ; start the timer 
AGAIN:MOV SBUF,#"G"    ;moving the data in sbuff
L1: JNB TI,L1          ;after transmission the transmission will give 1
CLR TI                 ;clear the transmission
CLR TR1                ;start the Timer
SJMP AGAIN             
END
