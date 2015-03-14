global load_gdt		; make the label visible outside this file

; lgdt - load the global descriptor table
; stack: [esp + 8] the segment descriptor to load into the gdt
;		 [esp	 ] the return address
load_gdt:
	mov eax, [esp + 8]
	lgdt [eax]
	ret 
