#include "stdafx.h"

const std::unordered_set<char> VALID_CHARS = { ' ', '#', 'A', 'B' };

struct Point
{
	int x;
	int y;
};

struct Cell
{
	char type;
	int waveLength;
	bool visited;
};

using Labyrinth = std::vector<std::vector<Cell>>;

Labyrinth GetLabyrinthFromFile(const std::string& fileName);
Labyrinth ReadLabyrinth(std::ifstream& file);
Point ValidateLabyrinthAndFindStartingPoint(const Labyrinth& labyrinth);
void FindPath(Labyrinth& labyrinth, const Point& start);
Point ExpandWave(Labyrinth& labyrinth, std::queue<Point>& queue, bool& destinationReached);
void Backtrace(Labyrinth& labyrinth, const Point& destination);
void PrintLabyrinthToFile(const Labyrinth& labyrinth, const std::string& fileName);
void WriteToFile(std::ofstream& file, const Labyrinth& labyrinth);

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
		throw std::runtime_error("Couldn't open file \"" + fileName + "\"\n");
	}

	return ReadLabyrinth(file);
}

Labyrinth ReadLabyrinth(std::ifstream& file)
{
	Labyrinth labyrinth;
	std::string line;

	while (std::getline(file, line))
	{
		std::vector<Cell> row;

		for (char ch : line)
		{
			if (VALID_CHARS.contains(ch))
			{
				row.push_back({ ch, -1, false });
			}
			else
			{
				throw std::invalid_argument("Only 'A', 'B', ' ' and '#' symbols are accepted\n");
			}
		}
		labyrinth.push_back(row);
	}

	return labyrinth;
}

Point ValidateLabyrinthAndFindStartingPoint(const Labyrinth& labyrinth)
{
	Point start;
	bool startFound = false;
	bool destinationFound = false;

	for (size_t i = 0; i < labyrinth.size(); ++i)
	{
		for (size_t j = 0; j < labyrinth[i].size(); ++j)
		{
			if (labyrinth[i][j].type == 'A')
			{
				if (!startFound)
				{
					start.x = static_cast<int>(i);
					start.y = static_cast<int>(j);
					startFound = true;
				}
				else
				{
					throw std::invalid_argument("More than one starting point found\n");
				}
			}
			else if (labyrinth[i][j].type == 'B')
			{
				if (!destinationFound)
				{
					destinationFound = true;
				}
				else
				{
					throw std::invalid_argument("More than one destination point found\n");
				}
			}
		}
	}
	if (!startFound || !destinationFound)
	{
		throw std::invalid_argument("No starting or destination point found\n");
	}

	return start;
}

void FindPath(Labyrinth& labyrinth, const Point& start)
{
	std::queue<Point> queue;
	queue.push(start);
	labyrinth[start.x][start.y].waveLength = 0;
	labyrinth[start.x][start.y].visited = true;
	bool destinationReached = false;

	Point destination = ExpandWave(labyrinth, queue, destinationReached);
	if (destinationReached)
	{
		Backtrace(labyrinth, destination);
	}
}

Point ExpandWave(Labyrinth& labyrinth, std::queue<Point>& queue, bool& destinationReached)
{
	const std::vector<Point> moves = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

	while (!queue.empty())
	{
		Point current = queue.front();
		queue.pop();
		int wave = labyrinth[current.x][current.y].waveLength;

		for (const auto& move : moves)
		{
			if (labyrinth[current.x + move.x][current.y + move.y].type == 'B')
			{
				destinationReached = true;
				labyrinth[current.x + move.x][current.y + move.y].waveLength = wave + 1;
				return { current.x + move.x, current.y + move.y };
			}
			else if (labyrinth[current.x + move.x][current.y + move.y].type == ' ' &&
					!labyrinth[current.x + move.x][current.y + move.y].visited)
			{
				labyrinth[current.x + move.x][current.y + move.y].visited = true;
				labyrinth[current.x + move.x][current.y + move.y].waveLength = wave + 1;
				queue.push({ current.x + move.x, current.y + move.y });
			}
		}
	}

	return { -1, -1 };
}

void Backtrace(Labyrinth& labyrinth, const Point& destination)
{
	const std::vector<Point> moves = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
	Point current = destination;
	int wave = labyrinth[current.x][current.y].waveLength;

	while (wave > 1)
	{
		for (const auto& move : moves)
		{
			if (labyrinth[current.x + move.x][current.y + move.y].waveLength == wave - 1)
			{
				labyrinth[current.x + move.x][current.y + move.y].type = '.';
				current = { current.x + move.x, current.y + move.y };
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
		throw std::runtime_error("Couldn't open file \"" + fileName + "\"\n");
	}

	WriteToFile(file, labyrinth);
}

void WriteToFile(std::ofstream& file, const Labyrinth& labyrinth)
{
	for (const auto& row : labyrinth)
	{
		for (const auto& cell : row)
		{
			file << cell.type;
		}
		file << "\n";
	}
}