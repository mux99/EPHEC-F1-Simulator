# EPHEC-OS2
pitch:
simulate a full F1 world cup.
each race, practice, qualification, etc.
generate randomly the times for each cars.
display the leaderborad in "real" time. (meaning sped up)
provide ample options for customizing the event.

___

this project is divided in three parts, display, logic, simulation:
	all 3 work on twoo shared memory slots
	`Car*` -> is a list of cars struct it contains infos on each cars
	`GrandPrix*` -> is a list of all GP to be run it stores all infos
		and results of each GP

- logic:
	main, it initialise the lists to their initial states.
	and will call all other peer programs.

	-1 read CSV files and options
	-2 initialise shared variables
	-3 run each GP
	-- run each GP fases
	-- call one simulation program per car (the right one, there is several)

- display:
	always display the current event (refresh screen regularly)
	the event is given by the GP_state variable.

	---TBD---