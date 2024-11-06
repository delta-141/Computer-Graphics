#include<iostream>
//#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
//#include<dos.h>



#include<iostream>
#include<graphics.h>
#include<stdlib.h>
using namespace std;

class walkingman {
  int rhx, rhy;

public:
  void draw(int, int);    // Function to draw random characters
  void draw(int);         // Function to animate walking man
};

void walkingman::draw(int i) {
  line(20, 380, 580, 380);   // Draw ground line

  if (i % 2) {
    // Right leg forward
    line(25 + i, 380, 35 + i, 340);
    line(45 + i, 380, 35 + i, 340);
    line(35 + i, 310, 25 + i, 330); // Left leg back
    delay(20);   // Short delay for animation effect
  } else {
    // Left leg forward
    line(35 + i, 340, 35 + i, 310);
    line(35 + i, 310, 40 + i, 330);  // Right leg back
    delay(20);  // Short delay for animation effect
  }

  // Draw body and head
  line(35 + i, 340, 35 + i, 310); // Body
  circle(35 + i, 300, 10);  // Head (circle)
  line(35 + i, 310, 50 + i, 330);  // Right arm
  line(50 + i, 330, 50 + i, 280);  // Arm
  line(15 + i, 280, 85 + i, 280);  // Ground line
  arc(50 + i, 280, 180, 0, 35);    // Legs arc (foot placement)
  arc(55 + i, 330, 360, 180, 5);   // Arm arc (swinging)
}

void walkingman::draw(int x, int y) {
  int j;
  rhx = x;
  rhy = y;

  // Randomly place slashes on the screen
  for (j = 0; j < 100; j++) {
    outtextxy(rand() % rhx, rand() % (rhy - 50), "/");
    setcolor(WHITE);
  }
}

int main() {
  int gd = DETECT, gm;
  int rhx, rhy, j, i;
  walkingman obj;

  // Initialize graphics mode
  initgraph(&gd, &gm, "");

  // Main loop for animation
  for (i = 0; i < 500; i++) {
    obj.draw(i); // Draw the walking man
    rhx = getmaxx();
    rhy = getmaxy();
    obj.draw(rhx, rhy); // Draw random slashes on the screen
    delay(750);   // Delay for animation effect
    cleardevice();  // Clear screen for next frame
  }

  getch();  // Wait for user input before closing
  closegraph();  // Close graphics mode
  return 0;
}
