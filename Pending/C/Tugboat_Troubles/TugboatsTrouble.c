#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <windows.h>

typedef struct TugBoat {
  char name[20];
  long long x, y;
  long long distanceToRoute;
  long long distanceToShip;
  long long xOnRoute, yOnRoute;

} TugBoat;

typedef struct Route {
  long long shipX, shipY;   // Ship's coordinates
  long long harborX, harborY;     // Harbor's coordinates
  long long distance;     // Distance between ship and harbor

} Route;

long long distance(long long x1, long long y1, long long x2, long long y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

long long main() {
  Route route;
  int numberOfTugBoats;

  scanf("%lld %lld %lld %lld", &route.shipX, &route.shipY, &route.harborX, &route.harborY);

  route.distance = sqrt(pow(route.shipX - route.harborX, 2) + pow(route.shipY - route.harborY, 2));

  scanf("%d", &numberOfTugBoats);

  TugBoat *tugBoats = malloc(numberOfTugBoats * sizeof(TugBoat));

  for (int i = 0; i < numberOfTugBoats; i++) {
    scanf("%lld %lld ", &tugBoats[i].x, &tugBoats[i].y);
    scanf("%[^\n]s", tugBoats[i].name);
    double slope1 = (double)(route.shipY - route.harborY) / (double)(route.shipX - route.harborX);
    double slope2, b1, b2;
    if( slope1 != 0) {
      if(tugBoats[i].y == route.harborY) {
        tugBoats[i].xOnRoute = distance(tugBoats[i].x, tugBoats[i].y, route.shipX, route.shipY) > distance(tugBoats[i].x, tugBoats[i].y, route.harborX, route.harborY) ? route.harborX : route.shipX;
        tugBoats[i].yOnRoute = distance(tugBoats[i].x, tugBoats[i].y, route.shipX, route.shipY) > distance(tugBoats[i].x, tugBoats[i].y, route.harborX, route.harborY) ? route.harborY : route.shipY;
      }
      else{
        slope2 = (-1 / slope1);
        b1 = route.shipY - slope1 * route.shipX;
        b2 = tugBoats[i].y - slope2 * tugBoats[i].x;
        tugBoats[i].xOnRoute = round((b2 - b1) / (slope1 - slope2));
        tugBoats[i].yOnRoute = round(slope1 * (double)tugBoats[i].xOnRoute + b1);
        // if the onRoute is not in between ship and harbor and beyond harbor then assign it to harbor
        long long distance1 = distance(tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, route.shipX, route.shipY);
        if (distance1 > route.distance) {
          tugBoats[i].xOnRoute = route.harborX;
          tugBoats[i].yOnRoute = route.harborY;
        }
      }
    } else {
      if(tugBoats[i].y == route.harborY) {
        tugBoats[i].xOnRoute = distance(tugBoats[i].x, tugBoats[i].y, route.shipX, route.shipY) > distance(tugBoats[i].x, tugBoats[i].y, route.harborX, route.harborY) ? route.harborX : route.shipX;
        tugBoats[i].yOnRoute = route.shipY;
      } else {
        tugBoats[i].xOnRoute = tugBoats[i].x;
        tugBoats[i].yOnRoute = route.shipY;
        // if the onRoute is not in between ship and harbor and beyond the harbor then assign it to harbor
        long long distance1 = distance(tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, route.shipX, route.shipY);
        if (distance1 > route.distance) {
          tugBoats[i].xOnRoute = route.harborX;
          tugBoats[i].yOnRoute = route.harborY;
        }
      }
    }
    tugBoats[i].distanceToRoute = distance(tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, tugBoats[i].x, tugBoats[i].y);
    tugBoats[i].distanceToShip = distance(tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, route.shipX, route.shipY);
  }

  // for(int i = 0; i < numberOfTugBoats; i++) {
  //   printf("%s xy(%lld, %lld) onRoute(%lld, %lld) distanceToRoute(%lld) distanceToShip(%lld)\n", tugBoats[i].name, tugBoats[i].x, tugBoats[i].y, tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, tugBoats[i].distanceToRoute, tugBoats[i].distanceToShip);
  // }
  // Selecting boats who tow ship max distance on route closer to harbor
  char **boatNames = malloc(numberOfTugBoats);
  for (int i = 0; i < numberOfTugBoats; i++) {
    boatNames[i] = malloc(20);
  }
  int boatIndex = 0;
  while (route.distance > 0) {
    long long minDistance = INT_MAX;
    int minDistanceIndex = -1;
    // Updating distance to ship
    for (int i = 0; i < numberOfTugBoats; i++) {
      tugBoats[i].distanceToShip = distance(tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, route.shipX, route.shipY);
      long long dist = tugBoats[i].distanceToShip;
      long long distToHarbor = distance(tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, route.harborX, route.harborY);
      if (dist < minDistance && dist > 0 ) {
        minDistance = dist;
        minDistanceIndex = i;
      } else if (dist == minDistance && dist > 0) {
        if(distToHarbor < distance(tugBoats[minDistanceIndex].xOnRoute, tugBoats[minDistanceIndex].yOnRoute, route.harborX, route.harborY)) {
          tugBoats[minDistanceIndex].xOnRoute = INT_MAX;
          tugBoats[minDistanceIndex].yOnRoute = INT_MAX;
          minDistance = dist;
          minDistanceIndex = i;

        }
        else if (tugBoats[i].distanceToRoute < tugBoats[minDistanceIndex].distanceToRoute) {
          tugBoats[minDistanceIndex].xOnRoute = INT_MAX;
          tugBoats[minDistanceIndex].yOnRoute = INT_MAX;
          minDistance = dist;
          minDistanceIndex = i;
        } else if (tugBoats[i].distanceToRoute == tugBoats[minDistanceIndex].distanceToRoute) {
          if (strcmp(tugBoats[i].name, tugBoats[minDistanceIndex].name) < 0) {
            tugBoats[minDistanceIndex].xOnRoute = INT_MAX;
            tugBoats[minDistanceIndex].yOnRoute = INT_MAX;
            minDistance = dist;
            minDistanceIndex = i;
          } else {
            tugBoats[i].xOnRoute = INT_MAX;
            tugBoats[i].yOnRoute = INT_MAX;
          }
        } else {
          tugBoats[i].xOnRoute = INT_MAX;
          tugBoats[i].yOnRoute = INT_MAX;
        }
      }
    }
    boatNames[boatIndex] = tugBoats[minDistanceIndex].name;
    boatIndex++;
    route.shipX = tugBoats[minDistanceIndex].xOnRoute;
    route.shipY = tugBoats[minDistanceIndex].yOnRoute;
    route.distance = distance(route.shipX, route.shipY, route.harborX, route.harborY);
    tugBoats[minDistanceIndex].xOnRoute = INT_MAX;
    tugBoats[minDistanceIndex].yOnRoute = INT_MAX;
    Sleep(1000);
  }
  printf("%d\n", boatIndex);
  for (int i = 0; i < boatIndex; i++) {
    printf("%s\n", boatNames[i]);
  }
  free(tugBoats);
  return 0;
}