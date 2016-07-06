.text
.global machine_switch

machine_switch:
	# address of the new sp is arg1
	# address of the current tcb is arg2
	# need to store all required registered for old tcb
	# restore all required registers from the new tcb
	# then when you return, you should get to the new thread 

	ret 

