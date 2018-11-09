.name		"Fragmenter"
.comment	"Panochita dulce"

# r9 = payload

setup:
	fork	%:p1
	st		r1,				6
	live	%1111638594
	fork	%:p2
	st		r1,				6
	live	%1111638594
	fork	%:p3
	st		r1,				6
	live	%1111638594
	fork	%:p4
	ld		%0,				r2
	zjmp	%:unleash



# first 4 bytes (zjmp out of code, live instruction)

p1:
	ld		%150999041,		r9							# zjmp. live (09 00 10 01)
	ld		%0,				r2
	zjmp	%:formation



# second 4 bytes (champion id)

p2:
	ld		%4,				r8							# offset +4
	or		r1,				r1,					r9		# champion id (XX XX XX XX)
	ld		%0,				r2
	zjmp	%:formation



# third 4 bytes (sti)

p3:
	ld		%8,				r8							# offset +8
	ld		%190056712,		r9							# sti (0B 54 09 08)
	ld		%0,				r2
	zjmp	%:formation



# last 4 bytes (sti, zjmp)

p4:
	ld		%12,			r8							# offset + 12
	ld		%118030444,		r9							# sti, zjmp (07 09 00 6C)
	ld		%0,				r2
	zjmp	%:formation



# unleash the beast

unleash:
	xor		r14,			r14,				r14
	xor		r15,			r15,				r15
	xor		r10,			r10,				r10
	xor		r11,			r11,				r11
	ld		%5963776,		r2							# (00 5B 00 00)
	st		r2,				45
	ld		%0,				r2
	zjmp	%:live



# holding area

formation:
	ld		%110,			r7							# primary offset
	sti		r9,				r8,				r7
	st		r1,				13
	ld		%0,				r2
wait:
	live	%1111638594
	zjmp	%:wait



# suicide the initial process

live:
	st		r1,				6
loop:
	live	%1111638594
	zjmp	%:loop
