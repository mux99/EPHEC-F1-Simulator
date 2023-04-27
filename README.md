# F1 world cup simulator
## Objective
simulate a full F1 world cup.
each race, practice, qualification, etc.
generate randomly the times for each cars.
display the leaderborad in "real" time. (meaning sped up)
providing ample options for customizing the event.

## Inner workings
basically it's a mess. let me elaborate...

*---tbd---*


## Functionnality
- [x] generate cars time at random between 25 and 45 seconds
- [x] have a practice event of 60 minutes
- [x] have 3 qualifs rounds of 18, 15 and 12 minutes
- [x] have optional sprint of 100km
- [x] have a race of 300-350km
- [x] keep track of the best time in each of 3 sectors
- [x] keep track of pit-stops (third sector)
- [x] the pitstops are 25s addition to the sector time (and lap time obviously)
- [x] keep track of who has the best time in each sector
- [x] order cars (in display) by best complete lap (or total time for race)
- [x] display time difference with previous car
- [x] for races the initial order is the starting grid
- [x] have options to personalize the simulation
- [x] data can be saved to file at the end of each activity
- [x] for the race each car must PIT at least onece
- [x] for the sprint the first 8 cars receive points 8 -> 1
- [x] for the race the best lap receive 1 point (if one of the 10 first)
