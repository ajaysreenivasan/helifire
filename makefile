All:game

game: Runner.o GameEffects.o GameObject.o Helicopter.o MovingObject.o StationaryObject.o Building.o Turret.o Projectile.o Missile.o Bomb.o EnemyMissile.o
	g++ -o Game GameEffects.o Helicopter.o Building.o Turret.o Runner.o MovingObject.o StationaryObject.o GameObject.o Projectile.o Missile.o Bomb.o EnemyMissile.o -L/usr/X11R6/lib -lX11 -lstdc++
	./Game

Runner.o: Runner.cpp Helicopter.cpp GameObject.cpp
	g++ -c Runner.cpp

GameObject.o: GameObject.cpp
	g++ -c GameObject.cpp

MovingObject.o: MovingObject.cpp MovingObject.h GameObject.h GameObject.cpp
	g++ -c MovingObject.cpp

Projectile.o: Projectile.h Projectile.cpp MovingObject.cpp MovingObject.h GameObject.h GameObject.cpp
	g++ -c Projectile.cpp

Missile.o: Missile.h Missile.cpp Projectile.h Projectile.cpp MovingObject.cpp MovingObject.h GameObject.h GameObject.cpp
	g++ -c Missile.cpp

Bomb.o: Bomb.h Bomb.cpp Projectile.h Projectile.cpp MovingObject.cpp MovingObject.h GameObject.h GameObject.cpp
	g++ -c Bomb.cpp

EnemyMissile.o: EnemyMissile.h EnemyMissile.cpp Projectile.h Projectile.cpp MovingObject.cpp MovingObject.h GameObject.h GameObject.cpp
	g++ -c EnemyMissile.cpp

StationaryObject.o: StationaryObject.cpp StationaryObject.h GameObject.h GameObject.cpp
	g++ -c StationaryObject.cpp

Helicopter.o: Helicopter.h Helicopter.cpp MovingObject.h MovingObject.cpp GameObject.cpp GameObject.h
	g++ -c Helicopter.cpp

Building.o: Building.h Building.cpp StationaryObject.h StationaryObject.cpp GameObject.cpp GameObject.h
	g++ -c Building.cpp

Turret.o: Turret.h Turret.cpp Building.h Building.cpp StationaryObject.h StationaryObject.cpp GameObject.cpp GameObject.h
	g++ -c Turret.cpp

GameEffects.o: GameEffects.h GameEffects.cpp Building.h Building.cpp StationaryObject.h StationaryObject.cpp GameObject.cpp GameObject.h
	g++ -c GameEffects.cpp

clean:
	rm -rf *.o Game Game.exe