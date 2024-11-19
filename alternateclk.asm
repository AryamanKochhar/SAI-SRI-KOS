org 0000h
	back:mov TMOD,#10h ;using timer 1 mode 1
	mov TH1,#0efH;
	mov TL1,#92H;
	mov P0,#00h
	setb TR1
	acall flagp
	mov TH1,#0aH;
	mov TL1,#0bH;
	mov P0,#0ffh
	setb TR1
	acall flagp
	SJMP back
	flagp: jnb TF1,flagp
	clr TR1
	clr TF1 
	ret 
	end
		