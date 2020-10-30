CC = gcc
CFLAGS = $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf
OBJ = main.o \
			game.o \
			render.o \
			sprite.o \
			text.o \
			vec2.o \
			player.o \
			enemy.o \
			explosion.o \
			projectile.o \

run: game
	./game

game: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o && rm -f game
