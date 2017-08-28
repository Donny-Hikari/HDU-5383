# Yu-Gi-Oh!

## Problem Description
"Yu-Gi-Oh!", also known as "Dueling Monsters", is a popular trading card game which has nearly 20 years history. Next year, YGO will reach its 20th birthday.

Stilwell has n monsters on the desk, each monster has its leveli and ATKi. There are two kinds of monsters, Tuner monsters and Non-Tuner monsters.

Now, Stilwell plans to finish some "Synchro Summon", and "Synchro Summon" is a kind of special summon following these rules (a little different from the standard YGO rules):

(1) A "Synchro Summon" needs two monsters as the material of this summon, and they must be one Tuner monster and one Non-Tuner monster.
In other words, we can cost one Tuner monster and one Non-Tuner monster to get a Synchro monster ("cost" means remove form the desk, "get" means put on to the desk).

(2) To simplify this problem, Synchro monsters are neither Tuner monsters nor Non-Tuner monsters.

(3) The level sum of two material must be equal to the level of Synchro monster we summon.
For example:
A Level 3 Tuner monster + A Level 2 Non-Tuner monster = A Level 5 Synchro Monster
A Level 2 Tuner monster + A Level 4 Non-Tuner monster = A Level 6 Synchro Monster
A Level 4 Tuner monster + A Level 4 Non-Tuner monster = A Level 8 Synchro Monster

(4) The material of some Synchro monster has some limits, the material must contain some specific monster.
For example:
A Level 5 Synchro Monster α requires A Level 3 Tuner monster α to be its material
A Level 6 Synchro Monster β requires A Level 4 Non-Tuner monster β to be its material
A Level 8 Synchro Monster γ requires A Level 4 Tuner monster γ + A Level 4 Non-Tuner monster γ to be its material
A Level 5 Synchro Monster φ doesn't require any monsters to be its material
Then
A Level 3 Tuner monster α + A Level 2 Non-Tuner monster = A Level 5 Synchro Monster α
A Level 3 Tuner monster δ + A Level 2 Non-Tuner monster ≠ A Level 5 Synchro Monster α
A Level 2 Tuner monster + A Level 4 Non-Tuner monster β = A Level 6 Synchro Monster β
A Level 3 Tuner monster + A Level 3 Non-Tuner monster ζ ≠ A Level 6 Synchro Monster β
A Level 4 Tuner monster γ + A Level 4 Non-Tuner monster γ = A Level 8 Synchro Monster γ
A Level 4 Tuner monster σ + A Level 4 Non-Tuner monster γ ≠ A Level 8 Synchro Monster γ
A Level 4 Tuner monster γ + A Level 4 Non-Tuner monster ϕ ≠ A Level 8 Synchro Monster γ
A Level 3 Tuner monster + A Level 2 Non-Tuner monster = A Level 5 Synchro Monster φ
A Level 3 Tuner monster α + A Level 2 Non-Tuner monster = A Level 5 Synchro Monster φ

Stilwell has m kinds of Synchro Monster cards, the quantity of each Synchro Monster cards is infinity.

Now, given leveli and ATKi of every card on desk and every kind of Synchro Monster cards. Please finish some Synchro Summons (maybe zero) to maximum ∑ATKi of the cards on desk.
 

## Input
The first line of the input contains a single number T, the number of test cases.

For each test case, the first line contains two integers n, m.

Next n lines, each line contains three integers tuneri, leveli, and ATKi, describe a monster on the desk. If this monster is a Tuner monster, then tuneri=1, else tuneri=0 for Non-Tuner monster.

Next m lines, each line contains integers levelj, ATKj, rj, and following rj integers are the required material of this Synchro Monster (the integers given are the identifier of the required material).
The input data guarantees that the required material list is available, two Tuner monsters or two Non-Tuner monsters won't be required. If ri=2 the level sum of two required material will be equal to the level of Synchro Monster.

T≤10, n,m≤300, 1≤leveli≤12, 0≤ATKi≤5000, 0≤ri≤2
 

## Output
T lines, find the maximum ∑ATKi after some Synchro Summons.
 

## Sample Input
5
2 2
1 3 1300
0 2 900
5 2300 1 1
8 2500 0
2 1
1 3 1300
1 2 900
5 2300 1 1
3 1
1 3 1300
0 2 900
0 2 800
5 2300 1 1
3 1
1 1 233
0 1 233
0 1 200
2 466 2 1 2
6 3
1 3 1300
0 2 900
0 5 1350
1 4 1800
0 10 4000
0 10 1237
5 2300 1 1
8 3000 0
6 2800 0
 

## Sample Output
2300
2200
3200
666
11037