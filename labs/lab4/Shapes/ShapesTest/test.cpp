#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../Canvas.h"
#include "../Circle.h"
#include "../Line.h"
#include "../Point.h"
#include "../Rectangle.h"
#include "../ShapeApp.h"
#include "../ShapeCreator.h"
#include "../Triangle.h"

namespace
{

std::string GetFileContents(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return "";
	}

	std::string contents;
	std::string line;

	while (std::getline(file, line))
	{
		contents += line;
	}

	return contents;
}

} // namespace

SCENARIO("Testing lines")
{
	GIVEN("Two points")
	{
		CPoint p1(10, 10);
		CPoint p2(20, 20);

		WHEN("Creating a line without color")
		{
			CLine line(p1, p2);

			THEN("Default color line is created")
			{
				CHECK(line.GetStartPoint().x == 10);
				CHECK(line.GetStartPoint().y == 10);
				CHECK(line.GetEndPoint().x == 20);
				CHECK(line.GetEndPoint().y == 20);
				CHECK(line.GetOutlineColor() == 0);
				CHECK(line.GetPerimeter() == Approx(14.14).margin(0.01));
			}
		}

		WHEN("Creating a line with color")
		{
			CLine line(p1, p2, 0xff);

			THEN("Line with provided color is created")
			{
				CHECK(line.GetStartPoint().x == 10);
				CHECK(line.GetStartPoint().y == 10);
				CHECK(line.GetEndPoint().x == 20);
				CHECK(line.GetEndPoint().y == 20);
				CHECK(line.GetOutlineColor() == 0xff);
				CHECK(line.GetPerimeter() == Approx(14.14).margin(0.01));
			}
		}
	}
}

SCENARIO("Testing circles")
{
	GIVEN("Point and radius")
	{
		CPoint p1(10, 10);
		double radius = 10;

		WHEN("Creating a circle without color")
		{
			CCircle circle(p1, radius);

			THEN("Default color circle is created")
			{
				CHECK(circle.GetCenter().x == 10);
				CHECK(circle.GetCenter().y == 10);
				CHECK(circle.GetRadius() == 10);
				CHECK(circle.GetOutlineColor() == 0);
				CHECK(circle.GetFillColor() == 0xffffff);
				CHECK(circle.GetPerimeter() == Approx(62.83).margin(0.01));
				CHECK(circle.GetArea() == Approx(314.16).margin(0.01));
			}
		}

		WHEN("Creating a circle with color")
		{
			CCircle circle(p1, radius, 0xff0000, 0xbb);

			THEN("Circle with provided colors is created")
			{
				CHECK(circle.GetCenter().x == 10);
				CHECK(circle.GetCenter().y == 10);
				CHECK(circle.GetRadius() == 10);
				CHECK(circle.GetOutlineColor() == 0xff0000);
				CHECK(circle.GetFillColor() == 0xbb);
				CHECK(circle.GetPerimeter() == Approx(62.83).margin(0.01));
				CHECK(circle.GetArea() == Approx(314.16).margin(0.01));
			}
		}
	}
}

SCENARIO("Testing rectangles")
{
	GIVEN("Point and two doubles")
	{
		CPoint topLeft(10, 10);
		double width = 20;
		double height = 15;

		WHEN("Creating a rectangle without color")
		{
			CRectangle rectangle(topLeft, width, height);

			THEN("Default color rectangle is created")
			{
				CHECK(rectangle.GetTopLeft().x == 10);
				CHECK(rectangle.GetTopLeft().y == 10);
				CHECK(rectangle.GetWidth() == 20);
				CHECK(rectangle.GetHeight() == 15);
				CHECK(rectangle.GetOutlineColor() == 0);
				CHECK(rectangle.GetFillColor() == 0xffffff);
				CHECK(rectangle.GetPerimeter() == 70);
				CHECK(rectangle.GetArea() == 300);
			}
		}

		WHEN("Creating a rectangle with color")
		{
			CRectangle rectangle(topLeft, width, height, 0x00ff00, 0x0000ff);

			THEN("Rectangle with provided colors is created")
			{
				CHECK(rectangle.GetTopLeft().x == 10);
				CHECK(rectangle.GetTopLeft().y == 10);
				CHECK(rectangle.GetWidth() == 20);
				CHECK(rectangle.GetHeight() == 15);
				CHECK(rectangle.GetOutlineColor() == 0x00ff00);
				CHECK(rectangle.GetFillColor() == 0x0000ff);
				CHECK(rectangle.GetPerimeter() == 70);
				CHECK(rectangle.GetArea() == 300);
			}
		}
	}
}

SCENARIO("Testing triangles")
{
	GIVEN("Three points")
	{
		CPoint p1(10, 10);
		CPoint p2(20, 10);
		CPoint p3(10, 20);

		WHEN("Creating a triangle without color")
		{
			CTriangle triangle(p1, p2, p3);

			THEN("Default color triangle is created")
			{
				CHECK(triangle.GetVertex1().x == 10);
				CHECK(triangle.GetVertex1().y == 10);
				CHECK(triangle.GetVertex2().x == 20);
				CHECK(triangle.GetVertex2().y == 10);
				CHECK(triangle.GetVertex3().x == 10);
				CHECK(triangle.GetVertex3().y == 20);
				CHECK(triangle.GetOutlineColor() == 0);
				CHECK(triangle.GetFillColor() == 0xffffff);
				CHECK(triangle.GetPerimeter() == Approx(34.14).margin(0.01));
				CHECK(triangle.GetArea() == 50);
			}
		}

		WHEN("Creating a triangle with color")
		{
			CTriangle triangle(p1, p2, p3, 0x00ff00, 0x0000ff);

			THEN("Triangle with provided colors is created")
			{
				CHECK(triangle.GetVertex1().x == 10);
				CHECK(triangle.GetVertex1().y == 10);
				CHECK(triangle.GetVertex2().x == 20);
				CHECK(triangle.GetVertex2().y == 10);
				CHECK(triangle.GetVertex3().x == 10);
				CHECK(triangle.GetVertex3().y == 20);
				CHECK(triangle.GetOutlineColor() == 0x00ff00);
				CHECK(triangle.GetFillColor() == 0x0000ff);
				CHECK(triangle.GetPerimeter() == Approx(34.14).margin(0.01));
				CHECK(triangle.GetArea() == 50);
			}
		}
	}
}

SCENARIO("Testing shape creator")
{
	GIVEN("Shape creator and some points")
	{
		CShapeCreator creator;
		CPoint p1(10, 10);
		CPoint p2(20, 20);
		CPoint p3(30, 15);

		CHECK(creator.GetShapes().empty());

		WHEN("Creating shapes")
		{
			creator.CreateLine(p1, p2);
			creator.CreateCircle(p1, 30 /*radius*/);
			creator.CreateRectangle(p1, 30 /*width*/, 15 /*height*/);
			creator.CreateTriangle(p1, p2, p3);

			THEN("All shapes are created")
			{
				CHECK(creator.GetShapes().size() == 4u);
			}

			AND_WHEN("Deleting shapes")
			{
				creator.DeleteShapes();

				THEN("All shapes are deleted")
				{
					CHECK(creator.GetShapes().empty());
				}
			}
		}
	}
}

SCENARIO("Testing shape app")
{
	GIVEN("Shape creator and shape app")
	{
		std::istringstream iss;
		std::ostringstream oss;

		CShapeCreator creator;
		CSVGCanvas canvas; // required to construct shape app
		CShapeApp app(creator, canvas, iss, oss);

		WHEN("Unknown command")
		{
			std::string command = "retangle";
			iss.str(command);

			THEN("Command won't be handled")
			{
				CHECK(!app.HandleCommand());
			}
		}

		WHEN("Creating a line")
		{
			AND_WHEN("Not enough arguments")
			{
				std::string command = "line 10 10 15";
				iss.str(command);

				THEN("Line won't be created")
				{
					CHECK(app.HandleCommand());
					CHECK(creator.GetShapes().empty());
				}
			}

			WHEN("Arguments are valid")
			{
				std::string command = "line 10 10 15 20";
				iss.str(command);

				THEN("Line will be created")
				{
					CHECK(app.HandleCommand());
					CHECK(creator.GetShapes().size() == 1u);
				}
			}
		}

		WHEN("Creating a triangle")
		{
			AND_WHEN("Not enough arguments")
			{
				std::string command = "triangle 10 10 15 15 20";
				iss.str(command);

				THEN("Triangle won't be created")
				{
					CHECK(app.HandleCommand());
					CHECK(creator.GetShapes().empty());
				}
			}

			WHEN("Arguments are valid")
			{
				std::string command = "triangle 10 10 15 15 20 21";
				iss.str(command);

				THEN("Triangle will be created")
				{
					CHECK(app.HandleCommand());
					CHECK(creator.GetShapes().size() == 1u);
				}
			}
		}

		WHEN("Creating a rectangle")
		{
			AND_WHEN("Not enough arguments")
			{
				std::string command = "rectangle 10 10 100";
				iss.str(command);

				THEN("Rectangle won't be created")
				{
					CHECK(app.HandleCommand());
					CHECK(creator.GetShapes().empty());
				}
			}

			AND_WHEN("Width and height are negative")
			{
				std::string command = "rectangle 10 10 -100 -50";
				iss.str(command);

				THEN("Rectangle won't be created")
				{
					CHECK(app.HandleCommand());
					CHECK(creator.GetShapes().empty());
				}
			}

			WHEN("Arguments are valid")
			{
				std::string command = "rectangle 10 10 100 50";
				iss.str(command);

				THEN("Rectangle will be created")
				{
					CHECK(app.HandleCommand());
					CHECK(creator.GetShapes().size() == 1u);
				}
			}
		}

		WHEN("Creating a circle")
		{
			AND_WHEN("Not enough arguments")
			{
				std::string command = "circle 10 10";
				iss.str(command);

				THEN("Circle won't be created")
				{
					CHECK(app.HandleCommand());
					CHECK(creator.GetShapes().empty());
				}
			}

			AND_WHEN("Radius is negative")
			{
				std::string command = "circle 10 10 -25";
				iss.str(command);

				THEN("Circle won't be created")
				{
					CHECK(app.HandleCommand());
					CHECK(creator.GetShapes().empty());
				}
			}

			WHEN("Arguments are valid")
			{
				std::string command = "circle 10 10 25";
				iss.str(command);

				THEN("Circle will be created")
				{
					CHECK(app.HandleCommand());
					CHECK(creator.GetShapes().size() == 1u);
				}
			}
		}

		WHEN("Printing info")
		{
			creator.CreateLine({ 0, 0 }, { 10, 0 });
			creator.CreateRectangle({ 0, 0 }, 100, 50);
			creator.CreateTriangle({ 0, 0 }, { 100, 0 }, { 0, 50 });
			CHECK(creator.GetShapes().size() == 3u);

			std::string command = "info";
			iss.str(command);

			THEN("Line will be min perimeter shape and rectangle will be max area shape")
			{
				std::string output = "Max area shape:\n"
									 "Rectangle\nPerimeter: "
									 "300.00"
									 "\nArea: "
									 "5000.00"
									 "\nOutline color: "
									 "000000"
									 "\nFill color: "
									 "ffffff\n\n"
									 "Min perimeter shape:\n"
									 "Line\nLength: "
									 "10.00"
									 "\nArea: 0\n"
									 "Color: "
									 "000000\n\n";

				CHECK(app.HandleCommand());
				CHECK(output == oss.str());

				AND_WHEN("Deleting shapes")
				{
					command = "delete";
					iss.clear();
					iss.str(command);

					THEN("All shapes will be deleted")
					{
						CHECK(app.HandleCommand());
						CHECK(creator.GetShapes().empty());
					}
				}
			}
		}
	}
}

SCENARIO("Testing canvas")
{
	GIVEN("Shape creator, shape app and canvas")
	{
		std::istringstream iss;
		std::ostringstream oss;

		CShapeCreator creator;
		CSVGCanvas canvas;
		CShapeApp app(creator, canvas, iss, oss);

		std::string canvasFile = "D://Study//OOP//labs//lab4//Shapes//canvas.svg";
		std::string emptyCanvas = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
								  "<svg width=\"1000px\" height=\"800px\" xmlns=\"http://www.w3.org/2000/svg\">"
								  "</svg>";
		canvas.Clear(canvasFile);

		std::string contents = ::GetFileContents(canvasFile);
		CHECK(contents == emptyCanvas);

		WHEN("Drawing a line")
		{
			canvas.DrawLine({ 0, 0 }, { 10, 10 }, 0xffffff);
			canvas.RenderToFile(canvasFile);

			THEN("Line will be drawn")
			{
				std::string canvasWithLine = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
											 "<svg width=\"1000px\" height=\"800px\" xmlns=\"http://www.w3.org/2000/svg\">"
											 "\t<line x1=\"0.00\" y1=\"0.00\" x2=\"10.00\" y2=\"10.00\" style=\"stroke:#ffffff;stroke-width:3\" />"
											 "</svg>";
				contents = ::GetFileContents(canvasFile);
				CHECK(contents == canvasWithLine);
			}
		}

		WHEN("Drawing a triangle")
		{
			std::vector<CPoint> points = { { 0, 0 }, { 10, 0 }, { 0, 10 } };
			canvas.DrawPolygon(points, 0xff1024, 0x0000cc);
			canvas.RenderToFile(canvasFile);

			THEN("Triangle will be drawn")
			{
				std::string canvasWithTriangle = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
												 "<svg width=\"1000px\" height=\"800px\" xmlns=\"http://www.w3.org/2000/svg\">"
												 "\t<polygon points=\"0.00,0.00 10.00,0.00 0.00,10.00 \" style=\"fill:#0000cc;stroke:#ff1024;stroke-width:3\" />"
												 "</svg>";
				contents = ::GetFileContents(canvasFile);
				CHECK(contents == canvasWithTriangle);
			}
		}

		WHEN("Drawing a rectangle")
		{
			std::vector<CPoint> points = { { 0, 0 }, { 10, 0 }, { 10, 10 }, { 0, 10 } };
			canvas.DrawPolygon(points);
			canvas.RenderToFile(canvasFile);

			THEN("Rectangle will be drawn")
			{
				std::string canvasWithRectangle = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
												  "<svg width=\"1000px\" height=\"800px\" xmlns=\"http://www.w3.org/2000/svg\">"
												  "\t<polygon points=\"0.00,0.00 10.00,0.00 10.00,10.00 0.00,10.00 \" style=\"fill:#ffffff;stroke:#000000;stroke-width:3\" />"
												  "</svg>";
				contents = ::GetFileContents(canvasFile);
				CHECK(contents == canvasWithRectangle);
			}
		}

		WHEN("Drawing a circle")
		{
			canvas.DrawCircle({ 50, 50 }, 25, 0xabcdef50, 0xff00ff);
			canvas.RenderToFile(canvasFile);

			THEN("Circle will be drawn")
			{
				std::string canvasWithCircle = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
											   "<svg width=\"1000px\" height=\"800px\" xmlns=\"http://www.w3.org/2000/svg\">"
											   "\t<circle r=\"25.00\" cx=\"50.00\" cy=\"50.00\" style=\"fill:#ff00ff;stroke:#abcdef50;stroke-width:3\" />"
											   "</svg>";
				contents = ::GetFileContents(canvasFile);
				CHECK(contents == canvasWithCircle);
			}

			AND_WHEN("Clearing canvas")
			{
				canvas.Clear(canvasFile);

				THEN("Canvas will be cleared")
				{
					contents = ::GetFileContents(canvasFile);
					CHECK(contents == emptyCanvas);
				}
			}
		}
	}
}