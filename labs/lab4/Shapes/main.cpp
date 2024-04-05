#include "Canvas.h"
#include "ShapeApp.h"
#include "ShapeCreator.h"

int main()
{
	CShapeCreator creator;
	CCanvas canvas;
	CShapeApp app(creator, canvas, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!app.HandleCommand())
		{
			std::cout << "Unknown command!\n";
		}
	}

	return 0;
}