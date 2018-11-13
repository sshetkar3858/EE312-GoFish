final: go_fish.o player.o deck.o card.o
	g++ -o gofish  go_fish.o player.o deck.o card.o
go_fish.o: go_fish.cpp
	g++ -c go_fish.cpp
player.o: player.cpp player.h
	g++ -c player.cpp
deck.o: deck.cpp deck.h
	g++ -c deck.cpp
card.o: card.cpp card.h
	g++ -c card.cpp
