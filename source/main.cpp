#include <stdio.h>
#include <nds.h>

int main(void) {
	glInit();
	consoleDemoInit();
	videoSetMode(MODE_0_3D);

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

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glViewport(0,0,255,191);
	
	glClearColor(0,0,10,1);
	glClearPolyID(0);

	//int textureID;
	//glGenTextures(1,&textureID);
	//glBindTexture(0,textureID);

	glMaterialf(GL_AMBIENT, RGB15(8,8,8));
	glMaterialf(GL_DIFFUSE, RGB15(24,24,24));
	glMaterialf(GL_SPECULAR, RGB15(0,0,0));
	glMaterialf(GL_EMISSION, RGB15(0,0,0));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 256.0/192.0, 0.1,20);

	printf("\nHELLO WORLD! SAYS NINTENDO DS\n");

	while (true) {
		swiWaitForVBlank();		

		scanKeys();
		uint32_t keys = keysHeld();

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

		gluLookAt(
			0,3.25,-3.25,
			0,1.25,0,
			0,1,0
			);

		glLight(0,RGB15(31,31,31),0,floattov10(-1),0);

		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK | POLY_FORMAT_LIGHT0 | POLY_MODULATION);

		glBegin(GL_QUAD);
			//RIGHT SIDE
			glColor3f(0,0,5);
			glVertex3f(x1,y1,z1);

			glColor3f(0,0,5);
			glVertex3f(x2,y2,z2);

			//LEFT SIDE
			glColor3f(0,0,5);
			glVertex3f(x3,y3,z3);

			glColor3f(0,0,5);
			glVertex3f(x4,y4,z4);
		glEnd();

		glFlush(GL_TRANS_MANUALSORT);
	}
}
