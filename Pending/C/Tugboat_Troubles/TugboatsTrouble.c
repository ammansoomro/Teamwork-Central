#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <windows.h>

typedef struct TugBoat {
  char name[20];
  int x, y;
  int distanceToRoute;
  int distanceToShip;
  int xOnRoute, yOnRoute;

} TugBoat;

typedef struct Route {
  int shipX, shipY;   // Ship's coordinates
  int harborX, harborY;     // Harbor's coordinates
  int distance;     // Distance between ship and harbor

} Route;

int distance(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
  Route route;
  int numberOfTugBoats;

  scanf("%d %d %d %d", &route.shipX, &route.shipY, &route.harborX, &route.harborY);

  route.distance = sqrt(pow(route.shipX - route.harborX, 2) + pow(route.shipY - route.harborY, 2));

  scanf("%d", &numberOfTugBoats);

  TugBoat *tugBoats = malloc(numberOfTugBoats * sizeof(TugBoat));

  for (int i = 0; i < numberOfTugBoats; i++) {
    scanf("%d %d ", &tugBoats[i].x, &tugBoats[i].y);
    scanf("%[^\n]s", tugBoats[i].name);
    float slope1 = (float)(route.shipY - route.harborY) / (float)(route.shipX - route.harborX);
    float slope2, b1, b2;
    if( slope1 != 0) {
      slope2 = (-1 / slope1);
      b1 = route.shipY - slope1 * route.shipX;
      b2 = tugBoats[i].y - slope2 * tugBoats[i].x;
      tugBoats[i].xOnRoute = round((b2 - b1) / (slope1 - slope2));
      tugBoats[i].yOnRoute = round(slope1 * (float)tugBoats[i].xOnRoute + b1);
    } else {
      if(tugBoats[i].y == route.harborY) {
        tugBoats[i].xOnRoute = distance(tugBoats[i].x, tugBoats[i].y, route.shipX, route.shipY) > distance(tugBoats[i].x, tugBoats[i].y, route.harborX, route.harborY) ? route.harborX : route.shipX;
        tugBoats[i].yOnRoute = route.shipY;
      } else {
        tugBoats[i].xOnRoute = tugBoats[i].x;
        tugBoats[i].yOnRoute = route.shipY;
      }
    }
    tugBoats[i].distanceToRoute = distance(tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, tugBoats[i].x, tugBoats[i].y);
    tugBoats[i].distanceToShip = distance(tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, route.shipX, route.shipY);
  }

  // Selecting boats who tow ship max distance on route closer to harbor
  char **boatNames = malloc(numberOfTugBoats);
  for (int i = 0; i < numberOfTugBoats; i++) {
    boatNames[i] = malloc(20);
  }
  int boatIndex = 0;
  while (route.distance > 0) {
    int minDistance = INT_MAX;
    int minDistanceIndex = -1;
    // Updating distance to ship
    for (int i = 0; i < numberOfTugBoats; i++) {
      tugBoats[i].distanceToShip = distance(tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, route.shipX, route.shipY);
      int dist = tugBoats[i].distanceToShip;
      int distToHarbor = distance(tugBoats[i].xOnRoute, tugBoats[i].yOnRoute, route.harborX, route.harborY);
      if (dist < minDistance && dist > 0 ) {
        minDistance = dist;
        minDistanceIndex = i;
      } else if (dist == minDistance && dist > 0) {
        if(distToHarbor < distance(tugBoats[minDistanceIndex].xOnRoute, tugBoats[minDistanceIndex].yOnRoute, route.harborX, route.harborY)) {
          tugBoats[minDistanceIndex].xOnRoute = 99999999;
          tugBoats[minDistanceIndex].yOnRoute = 99999999;
          minDistance = dist;
          minDistanceIndex = i;

        }
        else if (tugBoats[i].distanceToRoute < tugBoats[minDistanceIndex].distanceToRoute) {
          tugBoats[minDistanceIndex].xOnRoute = 99999999;
          tugBoats[minDistanceIndex].yOnRoute = 99999999;
          minDistance = dist;
          minDistanceIndex = i;
        } else if (tugBoats[i].distanceToRoute == tugBoats[minDistanceIndex].distanceToRoute) {
          if (strcmp(tugBoats[i].name, tugBoats[minDistanceIndex].name) < 0) {
            tugBoats[minDistanceIndex].xOnRoute = 99999999;
            tugBoats[minDistanceIndex].yOnRoute = 99999999;
            minDistance = dist;
            minDistanceIndex = i;
          } else {
            tugBoats[i].xOnRoute = 99999999;
            tugBoats[i].yOnRoute = 99999999;
          }
        } else {
          tugBoats[i].xOnRoute = 99999999;
          tugBoats[i].yOnRoute = 99999999;
        }
      }
    }
    boatNames[boatIndex] = tugBoats[minDistanceIndex].name;
    boatIndex++;
    route.shipX = tugBoats[minDistanceIndex].xOnRoute;
    route.shipY = tugBoats[minDistanceIndex].yOnRoute;
    route.distance = distance(route.shipX, route.shipY, route.harborX, route.harborY);
    tugBoats[minDistanceIndex].xOnRoute = 99999999;
    tugBoats[minDistanceIndex].yOnRoute = 99999999;
  }
  printf("%d\n", boatIndex);
  for (int i = 0; i < boatIndex; i++) {
    printf("%s\n", boatNames[i]);
  }
  free(tugBoats);
  return 0;
}