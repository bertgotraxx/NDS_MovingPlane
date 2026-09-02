#include <stdio.h>
#include <nds.h>

int main(void) {
	// OpenGL initialization
	glInit();

	// Initialization of debug console
	consoleDemoInit();

	// Set video mode to MODE 0 (3D + 2D)
	videoSetMode(MODE_0_3D);

	// Initial coordinates of the plane
	float x1 = -1;
	float y1 = 1;
	float z1 = -1;

	float x2 = -1;
	float y2 = 1;
	float z2 = 1;

	float x3 = 1;
	float y3 = 1;
	float z3 = 1;
	
	float x4 = 1;
	float y4 = 1;
	float z4 = -1;

	//vramSetBankA(VRAM_A_TEXTURE);
	//vramSetBankB(VRAM_B_TEXTURE);

	// OpenGL rendering settings
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	// Setting up the viewport (background) color for upper screen
	glViewport(0,0,255,191);
	
	glClearColor(0,0,10,1);
	glClearPolyID(0);

	//int textureID;
	//glGenTextures(1,&textureID);
	//glBindTexture(0,textureID);

	// Setting up OpenGL effects
	glMaterialf(GL_AMBIENT, RGB15(8,8,8));
	glMaterialf(GL_DIFFUSE, RGB15(24,24,24));
	glMaterialf(GL_SPECULAR, RGB15(0,0,0));
	glMaterialf(GL_EMISSION, RGB15(0,0,0));

	// Setting up the Matrix mode
	glMatrixMode(GL_PROJECTION);

	// Inject OpenGL settings
	glLoadIdentity();

	// Setting up FOV (Field of View) and Resolution
	gluPerspective(60, 256.0/192.0, 0.1,20);

	printf("\nHELLO WORLD! SAYS NINTENDO DS\n");

	while (true) {
		// Function that refreshes the console's screen
		// to draw a new frame
		swiWaitForVBlank();		

		// Check for any input
		scanKeys();

		// If any input - write into this variable
		uint32_t keys = keysHeld();

		// Controls
		if (keys & KEY_UP) {
			z1 += 0.05;
			z2 += 0.05;
			z3 += 0.05;
			z4 += 0.05;
		}

		if (keys & KEY_DOWN) {
			z1 -= 0.05;
			z2 -= 0.05;
			z3 -= 0.05;
			z4 -= 0.05;
		}

		if (keys & KEY_LEFT) {
			x1 += 0.05;
			x2 += 0.05;
			x3 += 0.05;
			x4 += 0.05;
		}

		
		if (keys & KEY_RIGHT) {
			x1 -= 0.05;
			x2 -= 0.05;
			x3 -= 0.05;
			x4 -= 0.05;
		}

		// Debug information (Plane coordinates)
		printf("\x1b[99D");
		printf("\x1b[99A");
		printf("\x1b[0J");

		printf("X1:%f", x1);
		printf("\x1b[1B");
		printf("\x1b[99D");
		printf("X2:%f", x2);
		printf("\x1b[1B");
		printf("\x1b[99D");
		printf("X3:%f", x3);
		printf("\x1b[1B");
		printf("\x1b[99D");	
		printf("X4:%f", x4);

			
		printf("\x1b[1B");
		printf("\x1b[99D");
		printf("Z1:%f", z1);
		printf("\x1b[1B");
		printf("\x1b[99D");
		printf("Z2:%f", z2);
		printf("\x1b[1B");
		printf("\x1b[99D");
		printf("Z3:%f", z3);
		printf("\x1b[1B");
		printf("\x1b[99D");
		printf("Z4:%f", z4);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		// Setting up the Camera
		gluLookAt(
			0,3.25,-3.25,
			0,1.25,0,
			0,1,0
			);

		// Setting up the light and light color
		glLight(0,RGB15(31,31,31),0,floattov10(-1),0);

		// Setting up the blending modes
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK | POLY_FORMAT_LIGHT0 | POLY_MODULATION);

		// Function for creation and further rendering of a simple 3D plane figure
		glBegin(GL_QUAD);
			// RIGHT UPPER SIDE
			glColor3f(0,0,5); // RGB colors
			glVertex3f(x1,y1,z1); // XYZ coordinates

			// RIGHT DOWN SIDE
			glColor3f(0,0,5);
			glVertex3f(x2,y2,z2);

			// LEFT DOWN SIDE
			glColor3f(0,0,5);
			glVertex3f(x3,y3,z3);

			// LEFT UPPER SIDE
			glColor3f(0,0,5);
			glVertex3f(x4,y4,z4);
		glEnd();

		// Part of screen refresh
		glFlush(GL_TRANS_MANUALSORT);
	}
}
