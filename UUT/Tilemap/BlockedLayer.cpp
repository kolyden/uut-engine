#include "BlockedLayer.h"
#include <AStar/stlastar.h>
#include "Tilemap.h"

namespace uut
{
	class MapSearchNode
	{
	public:
		int x;	 // the (x,y) positions of the node
		int y;

		static BlockedLayer* _layer;
		static int MAP_WIDTH;
		static int MAP_HEIGHT;

		MapSearchNode() { x = y = 0; }
		MapSearchNode(int px, int py) { x = px; y = py; }

		float GoalDistanceEstimate(const MapSearchNode &nodeGoal) const
		{
			return fabsf(x - nodeGoal.x) + fabsf(y - nodeGoal.y);
		}

		bool IsGoal(const MapSearchNode &nodeGoal) const
		{
			if ((x == nodeGoal.x) &&
				(y == nodeGoal.y))
			{
				return true;
			}

			return false;
		}

		bool GetSuccessors(AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node) const
		{
			int parent_x = -1;
			int parent_y = -1;

			if (parent_node)
			{
				parent_x = parent_node->x;
				parent_y = parent_node->y;
			}


			MapSearchNode NewNode;

			// push each possible move except allowing the search to go backwards

			if ((GetMap(x - 1, y) < 9)
				&& !((parent_x == x - 1) && (parent_y == y))
				)
			{
				NewNode = MapSearchNode(x - 1, y);
				astarsearch->AddSuccessor(NewNode);
			}

			if ((GetMap(x, y - 1) < 9)
				&& !((parent_x == x) && (parent_y == y - 1))
				)
			{
				NewNode = MapSearchNode(x, y - 1);
				astarsearch->AddSuccessor(NewNode);
			}

			if ((GetMap(x + 1, y) < 9)
				&& !((parent_x == x + 1) && (parent_y == y))
				)
			{
				NewNode = MapSearchNode(x + 1, y);
				astarsearch->AddSuccessor(NewNode);
			}


			if ((GetMap(x, y + 1) < 9)
				&& !((parent_x == x) && (parent_y == y + 1))
				)
			{
				NewNode = MapSearchNode(x, y + 1);
				astarsearch->AddSuccessor(NewNode);
			}

			return true;
		}

		float GetCost(const MapSearchNode &successor) const
		{
			return (float)GetMap(x, y);
		}

		bool IsSameState(const MapSearchNode &rhs) const
		{
			// same state in a maze search is simply when (x,y) are the same
			if ((x == rhs.x) &&
				(y == rhs.y))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		static int GetMap(int x, int y)
		{
			if (x < 0 ||
				x >= MAP_WIDTH ||
				y < 0 ||
				y >= MAP_HEIGHT
				)
			{
				return 9;
			}

			return _layer->Get(x, y) > 0 ? 9 : 1;
		}
	};

	BlockedLayer* MapSearchNode::_layer = nullptr;
	int MapSearchNode::MAP_WIDTH = 0;
	int MapSearchNode::MAP_HEIGHT = 0;

	/////////////////////////////////////////////////////
	UUT_OBJECT_IMPLEMENT(BlockedLayer)
	{}

	BlockedLayer::BlockedLayer()
	{}

	bool BlockedLayer::MakePath(const IntVector2& start, const IntVector2& end, List<IntVector2>& path)
	{
		auto& size = _tilemap->GetSize();

		MapSearchNode::_layer = this;
		MapSearchNode::MAP_WIDTH = size.x;
		MapSearchNode::MAP_HEIGHT = size.y;

		AStarSearch<MapSearchNode> astarsearch;

		unsigned int SearchCount = 0;

		const unsigned int NumSearches = 1;
		while (SearchCount < NumSearches)
		{
			// Create a start state
			MapSearchNode nodeStart;
			nodeStart.x = start.x;
			nodeStart.y = start.y;

			// Define the goal state
			MapSearchNode nodeEnd;
			nodeEnd.x = end.x;
			nodeEnd.y = end.y;

			// Set Start and goal states

			astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);

			unsigned int SearchState;
			unsigned int SearchSteps = 0;

			do
			{
				SearchState = astarsearch.SearchStep();
				SearchSteps++;
			} while (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);

			if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED)
			{
				MapSearchNode *node = astarsearch.GetSolutionStart();

				int steps = 0;

				path << IntVector2(node->x, node->y);
				for (;; )
				{
					node = astarsearch.GetSolutionNext();

					if (!node)
					{
						break;
					}

					path << IntVector2(node->x, node->y);
					steps++;
				};

				// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();
				return true;
			}
			else if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED)
			{
			}

			SearchCount++;
			astarsearch.EnsureMemoryFreed();
		}

		return false;
	}
}