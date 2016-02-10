XX = g++
CXXFLAGS = -Wall -MMD
OBJECTS = main.o game.o board.o textdisplay.o cell.o content.o character.o player.o enemy.o treasure.o normal.o smallhorde.o dragonhorde.o merchanthorde.o potion.o positivehp.o positiveatk.o positivedef.o negativehp.o negativeatk.o negativedef.o human.o orc.o elves.o dwarf.o dragon.o phoenix.o werewolf.o troll.o vampire.o merchant.o goblin.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}



