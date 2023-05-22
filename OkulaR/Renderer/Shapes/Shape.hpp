#pragma once

namespace Shape {
	
	struct Ponit{
		float x, y, z;
		float  colour[4]; // rgba - 1.0f is max
	};
	
	struct Triangle{
		Point* x, y, z;
	};
	
	struct Racktangle{
		Triangle triangle;
		
		Racktangle(triangle);
		Racktangle(float a, float b, float c);
		Racktangle(float x, float y, float height, float width);
	};
}
