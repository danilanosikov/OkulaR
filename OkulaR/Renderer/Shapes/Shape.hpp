#pragma once

namespace Shape {
	
	struct Point{
		
		float position[3];
		
		Point(float x = 0, float y = 0, float z = 0){
			position[0] = x; position[1] = y; position[2] = z;
		}
	}; static Point default_point = Point(0,0,0);
	
	struct Triangle{
		Point points[3];
		Triangle(Point a = default_point, Point b = default_point, Point c = default_point){
			points[0] = a; points[1] = b; points[2] = c;
		}
	};
	
	struct Square{
		Triangle triangle1;
		Triangle triangle2;
		
		Square(Point centre  = default_point, float side_length = 1){
			float shift = side_length/2;
			
			float ox = centre.position[0];
			float oy = centre.position[1];
			float oz = centre.position[2];
			
			Point p1(ox - shift, oy - shift, oz);
			Point p2(ox + shift, oy + shift, oz);
			Point p3(ox + shift, oy - shift, oz);
			Point p4(ox - shift, oy + shift, oz);
			
			this->triangle1 = Triangle(p1, p2, p3);
			this->triangle2 = Triangle(p1, p4, p2);
			
		}
	};
	
	struct Cube{
		float side;
		Point front_face;
		Point back_face;
		
		Cube(Point centre, float side_length) {
			side = side_length;
			float shift = side_length/2;
			
			float ox = centre.position[0];
			float oy = centre.position[1];
			float oz = centre.position[2];
			
			front_face = Point(ox, oy, oz + shift);
			back_face = Point(ox, oy, oz - shift);
			
		}
	};
}
