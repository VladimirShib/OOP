#include "stdafx.h"

constexpr int LABYRINTH_SIZE = 100;
constexpr char EMPTY = ' ';
constexpr char WALL = '#';
constexpr char START = 'A';
constexpr char DESTINATION = 'B';
constexpr char PATH = '.';
const std::unordered_set<char> VALID_CHARS = { EMPTY, WALL, START, DESTINATION };

struct Vector2i
{
	int x;
	int y;
};

struct Point
{
	int x;
	int y;

	Point operator+(const Vector2i v) const
	{
		return { x + v.x, y + v.y };
	}
};

struct Cell
{
	char type;
	int waveDistance;
};

using Labyrinth = std::array<std::array<Cell, LABYRINTH_SIZE>, LABYRINTH_SIZE>;

Labyrinth GetLabyrinthFromFile(const std::string& fileName);
Labyrinth ReadLabyrinth(std::istream& input);
void InitLabyrinth(Labyrinth& labyrinth);
Point ValidateLabyrinthAndFindStartingPoint(const Labyrinth& labyrinth);
void FindPath(Labyrinth& labyrinth, const Point& start);
std::optional<Point> FindDestinationPoint(Labyrinth& labyrinth, std::queue<Point>& queue);
bool CanMove(const Labyrinth& labyrinth, const Point point);
void Backtrace(Labyrinth& labyrinth, const Point& destination);
void PrintLabyrinthToFile(const Labyrinth& labyrinth, const std::string& fileName);
void WriteToFile(std::ostream& output, const Labyrinth& labyrinth);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: labyrinth.exe <input file> <output file>\n";

		return 1;
	}

	try
	{
		Labyrinth labyrinth = GetLabyrinthFromFile(argv[1]);
		Point start = ValidateLabyrinthAndFindStartingPoint(labyrinth);
		FindPath(labyrinth, start);
		PrintLabyrinthToFile(labyrinth, argv[2]);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";

		return 1;
	}

	return 0;
}

Labyrinth GetLabyrinthFromFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Couldn't open file \"" + fileName + "\"");
	}

	return ReadLabyrinth(file);
}

Labyrinth ReadLabyrinth(std::istream& input)
{
	Labyrinth labyrinth;
	InitLabyrinth(labyrinth);

	std::string line;
	size_t row = 0;

	while (std::getline(input, line))
	{
		for (size_t i = 0; i < line.size(); ++i)
		{
			if (VALID_CHARS.contains(line[i]))
			{
				labyrinth[row][i].type = line[i];
			}
			else
			{
				throw std::invalid_argument("Only 'A', 'B', ' ' and '#' symbols are accepted");
			}
		}

		++row;
	}

	return labyrinth;
}

void InitLabyrinth(Labyrinth& labyrinth)
{
	for (size_t i = 0; i < LABYRINTH_SIZE; ++i)
	{
		for (size_t j = 0; j < LABYRINTH_SIZE; ++j)
		{
			labyrinth[i][j].type = EMPTY;
			labyrinth[i][j].waveDistance = 0;
		}
	}
}

Point ValidateLabyrinthAndFindStartingPoint(const Labyrinth& labyrinth)
{
	Point start;
	bool startFound = false;
	bool destinationFound = false;

	for (size_t i = 0; i < LABYRINTH_SIZE; ++i)
	{
		for (size_t j = 0; j < LABYRINTH_SIZE; ++j)
		{
			if (labyrinth[i][j].type == START)
			{
				if (startFound)
				{
					throw std::invalid_argument("More than one starting point found");
				}

				start.x = static_cast<int>(i);
				start.y = static_cast<int>(j);
				startFound = true;
			}
			else if (labyrinth[i][j].type == DESTINATION)
			{
				if (destinationFound)
				{
					throw std::invalid_argument("More than one destination point found");
				}
				
				destinationFound = true;
			}
		}
	}
	if (!startFound || !destinationFound)
	{
		throw std::invalid_argument("No starting or destination point found");
	}

	return start;
}

void FindPath(Labyrinth& labyrinth, const Point& start)
{
	std::queue<Point> queue;
	queue.push(start);

	std::optional<Point> destination = FindDestinationPoint(labyrinth, queue);
	if (destination.has_value())
	{
		Backtrace(labyrinth, *destination);
	}
}

std::optional<Point> FindDestinationPoint(Labyrinth& labyrinth, std::queue<Point>& queue)
{
	const std::array<Vector2i, 4> moves = {{ { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } }};
	while (!queue.empty())
	{
		Point current = queue.front();
		queue.pop();
		int wave = labyrinth[current.x][current.y].waveDistance;

		for (const auto& move : moves)
		{
			Point newPoint = current + move;
			if (CanMove(labyrinth, newPoint))
			{
				if (labyrinth[newPoint.x][newPoint.y].type == DESTINATION)
				{
					labyrinth[newPoint.x][newPoint.y].waveDistance = wave + 1;
					return std::optional<Point>({ newPoint.x, newPoint.y });
				}
				else if (labyrinth[newPoint.x][newPoint.y].waveDistance == 0)
				{
					labyrinth[newPoint.x][newPoint.y].waveDistance = wave + 1;
					queue.push({ newPoint.x, newPoint.y });
				}
			}
		}
	}

	return std::nullopt;
}

bool CanMove(const Labyrinth& labyrinth, const Point point)
{
	return {
		labyrinth[point.x][point.y].type != WALL &&
		(point.x >= 0 && point.x < LABYRINTH_SIZE) &&
		(point.y >= 0 && point.y < LABYRINTH_SIZE)
	};
}

void Backtrace(Labyrinth& labyrinth, const Point& destination)
{
	const std::array<Vector2i, 4> moves = {{ { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } }};
	Point current = destination;
	int wave = labyrinth[current.x][current.y].waveDistance;

	while (wave > 1)
	{
		for (const auto& move : moves)
		{
			Point newPoint = current + move;

			if (labyrinth[newPoint.x][newPoint.y].waveDistance == wave - 1)
			{
				labyrinth[newPoint.x][newPoint.y].type = PATH;
				current = { newPoint.x, newPoint.y };
				break;
			}
		}
		--wave;
	}
}

void PrintLabyrinthToFile(const Labyrinth& labyrinth, const std::string& fileName)
{
	std::ofstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Couldn't open file \"" + fileName + "\"");
	}

	WriteToFile(file, labyrinth);
}

void WriteToFile(std::ostream& output, const Labyrinth& labyrinth)
{
	for (const auto& row : labyrinth)
	{
		for (const auto& cell : row)
		{
			output << cell.type;
		}
		output << "\n";
	}
}