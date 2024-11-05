#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int pi[10]; // Array to store transformed coordinates
double b[3][3]; // Transformation matrix
float a[1][2]; // Temporary array for coordinates

void matmul(float p[]);

int main() {
    int op, i, tx, ty, sx, sy, angle;
    int gd = DETECT, gm;

    // Initial coordinates of the polygon (square)
    float p1[10] = {
        50, 50,
        100, 50,
        100, 100,
        50, 100,
        50, 50 // Closing the shape
    };

    cout << "\nSelect transformation:";
    cout << "\n1. Translation";
    cout << "\n2. Rotation";
    cout << "\n3. Scaling";
    cout << "\n4. Rotation about arbitrary point";
    cout << "\nEnter the option: ";
    cin >> op;

    switch(op) {
        case 1: // Translation
            cout << "\nEnter the x translation: ";
            cin >> tx;
            cout << "\nEnter the y translation: ";
            cin >> ty;

            // Set up translation matrix
            b[0][0] = 1;
            b[0][1] = 0;
            b[0][2] = 0;
            b[1][0] = 0;
            b[1][1] = 1;
            b[1][2] = 0;
            b[2][0] = tx;
            b[2][1] = ty;
            b[2][2] = 1;
            break;

        case 2: // Rotation
            cout << "\nEnter the rotation angle: ";
            cin >> angle;
            angle = angle * 3.142 / 180; // Convert to radians

            // Set up rotation matrix
            b[0][0] = cos(angle);
            b[0][1] = sin(angle);
            b[0][2] = 0;
            b[1][0] = -sin(angle);
            b[1][1] = cos(angle);
            b[1][2] = 0;
            b[2][0] = 0;
            b[2][1] = 0;
            b[2][2] = 1;
            break;

        case 3: // Scaling
            cout << "\nEnter the x scaling factor: ";
            cin >> sx;
            cout << "\nEnter the y scaling factor: ";
            cin >> sy;

            // Set up scaling matrix
            b[0][0] = sx;
            b[0][1] = 0;
            b[0][2] = 0;
            b[1][0] = 0;
            b[1][1] = sy;
            b[1][2] = 0;
            b[2][0] = 0;
            b[2][1] = 0;
            b[2][2] = 1;
            break;

        /* Uncomment to enable rotation about an arbitrary point
        case 4:
            int x, y;
            cout << "\nEnter x coordinate of arbitrary point: ";
            cin >> x;
            cout << "\nEnter y coordinate of arbitrary point: ";
            cin >> y;
            cout << "\nEnter the rotation angle: ";
            cin >> angle;

            // Set up the transformation matrix for rotation about an arbitrary point
            // (Not implemented)
            break;
        */
        
        default:
            cout << "Invalid option!";
            return 1;
    }

    initgraph(&gd, &gm, NULL); // Initialize graphics
    int xmax = getmaxx(); // Get the maximum x coordinate
    int ymax = getmaxy(); // Get the maximum y coordinate
    int xmid = xmax / 2; // Get the center x coordinate
    int ymid = ymax / 2; // Get the center y coordinate

    // Draw original shape
    setcolor(1); // Color for the original shape
    for (i = 0; i < 8; i += 2) {
        line(xmid + p1[i], ymid - p1[i + 1], xmid + p1[i + 2], ymid - p1[i + 3]);
    }

    // Perform matrix multiplication to get transformed coordinates
    matmul(p1);

    // Draw transformed shape
    setcolor(15); // Color for the transformed shape
    for (i = 0; i < 8; i += 2) {
        line(xmid + pi[i], ymid - pi[i + 1], xmid + pi[i + 2], ymid - pi[i + 3]);
    }

    getch();
    closegraph();
    return 0;
}

void matmul(float p[]) {
    for (int i = 0; i < 8; i += 2) { // For each vertex
        a[0][0] = p[i];
        a[0][1] = p[i + 1];

        // Matrix multiplication
        pi[i] = (int)(a[0][0] * b[0][0] + a[0][1] * b[1][0] + b[2][0]);
        pi[i + 1] = (int)(a[0][0] * b[0][1] + a[0][1] * b[1][1] + b[2][1]);
    }
}

