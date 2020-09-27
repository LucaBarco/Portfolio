				
				
				AREA asm_functions, CODE, READONLY				
                EXPORT  average
average
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
				; extract argument 1 and 2 into R1 and R2
				
				MOV   r5,r1
				MOV   r4,#0
				SUB   r0,r0,#4
				MOV   r6,#1
				CMP   r1, #0
				BNE loop
				MOV r5,#0
				B   end
				
loop			LDR	   r3, [r0, #4]!
				ADDS   r4,r3,r4
				MOVVS  r6,#0
				SUBS   r5,r5,#1
				BNE loop
				
				CMP r6,#0
				UDIVNE r5,r4,r1
				MOVEQ r5,#0
				
				; setup a value for R0 to return
end				MOV	  r0, r5
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END