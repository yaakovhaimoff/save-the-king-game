SAVE THE KING 
Yaakov Haimoff 318528510

This project is a game called save the king.
The purpose of the game is to get the king to the '@'.
In the game there are four player which the user can
move, as mentioned a King, Mage, Warroir and lastley a Thief.
The game tools who will as well show in the game are:
GateKey, Fire, Teleport, Throne, Orc, Gate, and Space.
In the way the user will face obstacles, each player has a set
of moves he is abe to do, and as well set of move his enabled from doing.

The King is allowed to step on the GateKey but not take it,
he can't pass fire, a gate, and an orc. But he can use the teleport.

The Mage is able to step on GateKey but not take it, his special power is 
the walking on fire, he cant use the teleport, pass on the throne, 
orc, and the gate.

The Warrior is able to step on GateKey but not take it, his special power is
to fight the orc and get a keyGate from him.
The Warrior is enabled of passing on the throne, fire and the gate.
The Warrior is able to use the teleport.

Lastley the Thief, his special power is to steal the GateKey and use it to 
open the gate, he can use the teleport, but can't pass on the throne,
fire and the orc.

The program has four classes for the four player objects, 
and has two classes of board, controller and location
which is a struct to keep the object locations in the program.
The controller runs the user interface. He first sets the board
and then intializes the user objects on the board.
From then the level will start, and the controller will get the
user keyboard move and will decide which player will be active
as wll be explained later. The move will be send to class which is her object
is playing at the moment, the class will check if the move is valid and it 
should do with it, eeither to move player or not do a thing.

files in the project:
include - where all the headers are stalled.
src - where all the cpp are stalled, the class implementation are and the main.
rcs - where the board.txt is.
README.txt - where the explaing of the project is.

As mentioned the main objects in this class are the player objectwhich are King, Mage,
Warrior and Thief.

A algorithm worse mentioning is the way I'm swich the player objects in
a circle, I distributed each object into a Equilibrium classes by the remaining
of the division by the amount of players there are.

No bugs I'm aware of.

