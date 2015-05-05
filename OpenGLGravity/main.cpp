#include <iostream>
#include <GL\glew.h>
#include"display.h"
#include"shader.h"
#include "mesh.h"
#include <SDL2\SDL.h>
//#include "Texture.h"
#include "transform.h"
#include "camera.h"
#include "Obj_loader.h"
#include <GL\glut.h>
#include <fstream>
#include <iterator>
#include <string>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <numeric>
#include<cmath>
#undef main

#define WIDTH 1400
#define HEIGHT 900



double Abstand(double x1, double y1, double z1, double x2, double y2, double z2)
{
 double distsquare = x1*x1 + y1*y1 + z1*z1 - 2 * (x1*x2 + y1*y2 + z1*z2) + x2*x2 + y2*y2 + z2*z2;
	return sqrt(distsquare);
}


int main(int argc, char *argv[]){

	Display display(WIDTH, HEIGHT, "Gravity Simulation");
	

	//Texture texture("bricks.bmp");
	/*Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

	Vertex vertices2[] = { Vertex(glm::vec3(1, -1, -1), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(-0.5, 1.0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0.5, 1.0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1.0, 0.0)),
	    Vertex(glm::vec3(-1, 1, -1), glm::vec2(1.0, 0.0))};*/





	unsigned int indices[] = { 0, 1, 2 };
	unsigned int indices2[] = { 0,1,2,3,4,7,6,5,0,4,5,1,1,5,6,2,2,6,7,3,4,0,3,7};


	//Mesh mesh2(vertices2, sizeof(vertices2) / sizeof(vertices2[0]), indices2, sizeof(indices2) / sizeof(indices2[0]));
	Mesh meshmonkey("./res/eagle.obj");
	Mesh meshTriforce("./res/Triforce.obj");
	Mesh sphere("./res/sphere.obj");
	Mesh monkey("./res/monkey3.obj");
	
	//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	
	Shader shader("./res/basicShader.vss", "./res/basicShader.fss");
	Shader shader2("./res/basicShader.vss", "./res/fragmentshader2.fss");
	Shader starshader("./res/basicShader.vss", "./res/fragmentshader3.fss");
	Camera camera(glm::vec3(0, 0, -450), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;
	double counter = 0.0f;
	float sinCounter = sinf(counter);
	float cosCounter = cosf(counter);
	double v1x = -0.5;
	double v1y = 0;
	double v1z = 0;
	double v2x = 0.005;
	double v2y = 0;
	double v2z = 0;
	double v3x = 0.5;
	double v3y = 0;
	double v3z = 0;
	double Gm1m2 = 7.93e+44;
	double r120 = 149e+9;
	double m1 = 5.973e+24;
	double xx10 = 30, yy10 = 10, zz10 = 40;
	double xx1 =120 , yy1 = 100, zz1 = 40;
	double xx20 = -30, yy20 = -10, zz20 = 0;
	double xx2 = -30, yy2 = -10, zz2 = 0;
	double xx30 = -150, yy30 = -100, zz30 = -20;
	double xx3 = -150, yy3 = -100, zz3 = -20;
	double M = 50;





	srand(time(NULL));
	std::vector<int> random_numbersx(1400);
	std::iota(random_numbersx.begin(), random_numbersx.end(), -700);
	std::vector<int> random_numbersy(1400);
	std::iota(random_numbersy.begin(), random_numbersy.end(), -700);

	std::random_shuffle(random_numbersx.begin(), random_numbersx.end());
	for (unsigned i = 0; i < random_numbersx.size(); i++)
	{
		std::cout << random_numbersx[i] << std::endl;
	}
	std::random_shuffle(random_numbersy.begin(), random_numbersy.end());
	for (unsigned i = 0; i < random_numbersy.size(); i++)
	{
		std::cout << random_numbersy[i] << std::endl;
	}

	

	std::ofstream fileSonne("Sonne.txt"/*, std::ios::app*/);
	std::ofstream fileErde("Erde.txt"/*, std::ios::app*/);// create output file stream 
	if (!fileSonne) // check stream for error (check if it opened the file correctly)
		std::cout << "error opening file for writing." << std::endl;
	if (!fileErde) // check stream for error (check if it opened the file correctly)
		std::cout << "error opening file for writing." << std::endl;

		while (!display.IsClosed())
		{
			display.Clear(0.53f, 0.808f, 0.922, 1.0f);
		    //display.Clear(0.8f, 1.0f, 1.0f, 1.0f);
			


//==============================LEAPFROG==================================================================

			transform.SetScale(glm::vec3(2, 2, 2));
			//transform.GetPos()->x = -10*counter;
			//transform.GetRot()->z = counter*5;
			transform.GetPos()->z = zz2;
			transform.GetPos()->y = yy2;
			transform.GetPos()->x = xx2;
			transform.GetRot()->z = 20 * cosf(10 * counter);
		   

			xx20 = xx2;
			yy20 = yy2;
			zz20 = zz2;



		


			shader.Bind();
			//texture.Bind(0);
			shader.Update(transform, camera);

			
			//mesh.Draw();
			meshTriforce.Draw();
			
			fileSonne << transform.GetPos()->x << ":"
				<< transform.GetPos()->y << ":" << transform.GetPos()->z << ":" << counter << std::endl;



//==========================================Third Object Setting=====================================================================

			transform.SetScale(glm::vec3(10, 10, 10));
			transform.GetPos()->z = zz3;
			transform.GetPos()->y = yy3;
			transform.GetPos()->x = xx3;
			transform.GetRot()->z = 20 * cosf(10 * counter);


			xx30 = xx3;
			yy30 = yy3;
			zz30 = zz3;



			shader2.Bind();
			shader2.Update(transform, camera);
			monkey.Draw();


//========================================== Second Object Setting ==================================================================


			//mesh2.Draw2();


			//newTexture.Bind(); shader.Update(newOBJsTransform, ...); newOBJMesh.Draw();
			
			
			//std::cout << "vecpos1 x :: y :: z: " << transform.GetPos()->x << " :: " << transform.GetPos()->y << " :: " << transform.GetPos()->z << std::endl;


			transform.SetScale(glm::vec3(20, 20, 20));
			//transform.GetPos()->x = -10*counter;
			transform.GetRot()->z = 10 * cosf(counter);
			transform.GetRot()->y = 10 * sinf(counter);
			transform.GetRot()->x = 2;
			transform.GetPos()->z = zz1;
			transform.GetPos()->y = yy1;
			transform.GetPos()->x = xx1;


			xx10 = xx1;
			yy10 = yy1;
			zz10 = zz1;

			xx1 = xx10 + v1x*counter - M*(xx10 - xx20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				)*counter*counter/2; 

			yy1 = yy10 + v1y*counter - M*(yy10 - yy20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				)*counter*counter / 2;

			zz1 = zz10 + v1z*counter - M*(zz10 - zz20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				)*counter*counter / 2;



			xx2 = xx20 + v2x*counter + (xx10 - xx20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				)*counter*counter / 2;

			yy2 = yy20 + v2y*counter + (yy10 - yy20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				)*counter*counter / 2;

			zz2 = zz20 + v2z*counter + (zz10 - zz20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				)*counter*counter / 2;



			xx3 = xx30 + v3x*counter + M*(xx30 - xx20) / (
				Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)
				)*counter*counter / 2;

			yy3 = yy30 + v3y*counter + M*(yy30 - yy20) / (
				Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)
				)*counter*counter / 2;

			zz3 = zz30 + v3z*counter + M*(zz30 - zz20) / (
				Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)
				)*counter*counter / 2;

	

			v1x = v1x + counter / 2 * 
				(
				   -M*(xx10 - xx20) / (
				    Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
					) - M*(xx1 - xx2) / (
					Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)
					)
				);


			v1y = v1y + counter / 2 *
				(
				-M*(yy10 - yy20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				) - M*(yy1 - yy2) / (
				Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)
				)
				);


			v1z = v1z + counter / 2 *
				(
				-M*(zz10 - zz20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				) - M*(zz1 - zz2) / (
				Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)
				)
				);



			v2x = v2x + counter / 2 *
				(
				+(xx10 - xx20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				) + (xx1 - xx2) / (
				Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)
				)
				);


			v2y = v2y + counter / 2 *
				(
				+(yy10 - yy20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				) + (yy1 - yy2) / (
				Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)
				)
				);


			v2z = v2z + counter / 2 *
				(
				+(zz10 - zz20) / (
				Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)*Abstand(xx10, yy10, zz10, xx20, yy20, zz20)
				) + (zz1 - zz2) / (
				Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)*Abstand(xx1, yy1, zz1, xx2, yy2, zz2)
				)
				);


			v3x = v3x + counter / 2 *
				(
				-M*(xx30 - xx20) / (
				Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)
				) - M*(xx3 - xx2) / (
				Abstand(xx3, yy3, zz3, xx2, yy2, zz2)*Abstand(xx3, yy3, zz3, xx2, yy2, zz2)*Abstand(xx3, yy3, zz3, xx2, yy2, zz2)
				)
				);


			v3y = v3y + counter / 2 *
				(
				-M*(yy30 - yy20) / (
				Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)
				) - M*(yy3 - yy2) / (
				Abstand(xx3, yy3, zz3, xx2, yy2, zz2)*Abstand(xx3, yy3, zz3, xx2, yy2, zz2)*Abstand(xx3, yy3, zz3, xx2, yy2, zz2)
				)
				);

			v3z = v3z + counter / 2 *
				(
				-M*(zz30 - zz20) / (
				Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)*Abstand(xx30, yy30, zz30, xx20, yy20, zz20)
				) - M*(zz3 - zz2) / (
				Abstand(xx3, yy3, zz3, xx2, yy2, zz2)*Abstand(xx3, yy3, zz3, xx2, yy2, zz2)*Abstand(xx3, yy3, zz3, xx2, yy2, zz2)
				)
				);

				




//=====================================================END LEAPFROG======================================================================






			shader2.Bind();
			//texture.Bind(0);
			shader2.Update(transform, camera);

			

			//mesh.Draw();
			meshmonkey.Draw();

			//mesh2.Draw2();




		
		
            fileErde << transform.GetPos()->x << ":"
					<< transform.GetPos()->y << ":" << transform.GetPos()->z <<  ":" << counter << std::endl;
			//file << "currentDateTime()=" << display.currentDateTime() << std::endl;
			//getchar();

//=====================================  Starfield Seting  ===========================================================================


			

			//	transform.SetScale(glm::vec3(1, 1, 1));

			//for (int j = 0; j < 300; j++)
			//{
			//	transform.GetRot()->x=0;
			//	transform.GetRot()->y=0;
			//	transform.GetRot()->z=0;
			//		transform.GetPos()->z = 500;
			//		/*std::vector<int> zwischenvec2;
			//		zwischenvec2 = arrayOfStarCoords.at(j);
			//		std::cout << zwischenvec2.at(0) << zwischenvec2.at(1);*/
			//		transform.GetPos()->x = (float)random_numbersx[j];
			//		transform.GetPos()->y = (float)random_numbersy[j];
			//		






			//		starshader.Bind();
			//		//texture.Bind(0);
			//		starshader.Update(transform, camera);



			//		//mesh.Draw();
			//		sphere.Draw();

			//	}


			//transform.SetScale(glm::vec3(3, 3, 3));

			//
			//    transform.GetRot()->x = 10*cosf(counter);
			//	transform.GetRot()->y = 10*sinf(counter);
			//	transform.GetRot()->z = 0;
			//	transform.GetPos()->x = -100;
			//	transform.GetPos()->z = -100;
			//	transform.GetPos()->y = 100;
			//	


			//	starshader.Bind();
			//	//texture.Bind(0);
			//	starshader.Update(transform, camera);

			//	//mesh.Draw();
			//	sphere.Draw();

		
					display.Update();

					counter += 0.0008f;


				

		}
		fileSonne.close();
		fileErde.close();
		return 0;
}



