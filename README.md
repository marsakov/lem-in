# Lemin
    
### The goal of this project is to find the quickest way to get n ants across the farm.

* Obviously, there are some basic constraints. To be the first to arrive, ants will need to take the shortest path (and that isn’t necessarily the simplest). They will also need to avoid traffic jams as well as walking all over their fellow ants.

* At the beginning of the game, all the ants are in the room ##start. The goal is to bring them to the room ##end with as few turns as possible. Each room can only contain one ant at a time. (except at ##start and ##end which can contain as many ants as necessary.)

* At each turn you can move each ant only once and through a tube (the room at the receiving end must be empty).

* You must to display your results on the standard output in the following format:
```
number_of_ants
the_rooms
the_links

Lx-y Lz-w Lr-o ...
```
x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y, w, o represents the rooms’ names.

#### Map example

	12
	##start
	1 23 3
	2 16 7
	#comment
	3 16 3
	4 16 5
	5 9 3
	6 1 5
	7 4 8
	8 9 5
	##end
	1-2
	2-4
	1-3
	3-4
	1-4
	1-5
	5-6
	6-7
	7-8
	8-4
	6-4
	1-8

You can choose one in `lem-in_maps/` after cloning this repo.

### Usage
```
git clone https://github.com/marsakov/lem-in.git
cd lem-in
make
./lem-in < lem-in_maps/map1.txt
```
Also as a bonus to this project I decided to find all unique ways on the map and let the ants walk on all of them.

