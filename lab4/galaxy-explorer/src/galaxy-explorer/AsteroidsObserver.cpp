/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */


#include <galaxy-explorer/AsteroidsObserver.hpp>

void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
   asteroid_list.pushFront(asteroid);
//   printf("asteroid x: %d \n" , asteroid.getVelocity().x);
//   printf("asteroid y: %d \n" , asteroid.getVelocity().y);
//    printf("asteroid start x: %d \n" , asteroid.getCurrentHitbox().left);
//     printf("asteroid start y: %d \n" , asteroid.getCurrentHitbox().top);
    /**
	 * Called whenever a new asteroid appears on the field
	 */
}

void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    asteroid_list.pushFront(asteroid);
    AsteroidListItem * ptr = asteroid_list.begin();
    AsteroidListItem * pptr = asteroid_list.begin();
      while (ptr != nullptr && ptr->getData().getID() != asteroid.getID())
    {
        pptr = ptr;
        ptr = ptr->getNext();
    }
    asteroid_list.eraseAfter(pptr);
    
    /**
	 * Called when an asteroid has moved.
	 * Use the ID of the asteroid to determine what asteroid to replace
	 */
}

void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    AsteroidListItem * ptr = asteroid_list.begin();
    AsteroidListItem * pptr = asteroid_list.begin();
      while (ptr != nullptr && ptr->getData().getID() != asteroid.getID())
    {
        pptr = ptr;
        ptr = ptr->getNext();
    }
    asteroid_list.eraseAfter(pptr);
    /**
	 * Called when an asteroid leaves the field without being destroyed
	 */
}

void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    AsteroidListItem * ptr = asteroid_list.begin();
    AsteroidListItem * pptr = asteroid_list.begin();
    while (ptr != nullptr && ptr->getData().getID() != asteroid.getID())
    {
        pptr = ptr;
        ptr = ptr->getNext();
    }
    asteroid_list.eraseAfter(pptr);
    /**
	 * Called when an asteroid is destroyed by a phaser shot
	 */
}
