#pragma once

namespace Shape {
	
	struct Point{
		float position[3];
		
		Point(float x = 0, float y = 0, float z = 0){
			position[0] = x; position[1] = y; position[2] = z;
		}
	};
	
	struct Triangle{
		Point points[3];
		Triangle(Point a, Point b, Point c){
			points[0] = a; points[1] = b; points[2] = c;
		}
	};
}
