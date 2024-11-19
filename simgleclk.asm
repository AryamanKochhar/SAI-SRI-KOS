org 0000h
	mov p1,#000h;
	AGAIN: mov tmod,#10h
	mov th1,#0ffh
	mov tl1,#0E7H
	CPL P1.2
	SETB TR1
  	HERE: JNB TF1,HERE
	CLR TF1
	CLR  TR1
	SJMP AGAIN
	end
