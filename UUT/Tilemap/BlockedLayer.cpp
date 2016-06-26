#include "BlockedLayer.h"
#include <AStar/stlastar.h>
#include "Tilemap.h"
#include <Core/Math/Math.h>

namespace uut
{
	class MapSearchNode
	{
	public:
		IntVector2 pos = IntVector2::Zero;

		static BlockedLayer* _layer;
		static int MAP_WIDTH;
		static int MAP_HEIGHT;

		MapSearchNode() {}
		MapSearchNode(int x, int y) : pos(x, y) {}
		explicit MapSearchNode(const IntVector2& position) : pos(position) {}

		float GoalDistanceEstimate(const MapSearchNode &nodeGoal) const
		{
			return Math::Abs(pos.x - nodeGoal.pos.x) + Math::Abs(pos.y - nodeGoal.pos.y);
		}

		bool IsGoal(const MapSearchNode &nodeGoal) const
		{
			return (pos == nodeGoal.pos);
		}

		bool GetSuccessors(AStarSearch<MapSearchNode>* astarsearch, const MapSearchNode* parent_node) const
		{
			IntVector2 parent_pos(-1, -1);

			if (parent_node)
				parent_pos = parent_node->pos;

			MapSearchNode NewNode;
			// push each possible move except allowing the search to go backwards
			if ((GetMap(pos.x - 1, pos.y) < 9)
				&& !((parent_pos.x == pos.x - 1) && (parent_pos.y == pos.y))
				)
			{
				NewNode = MapSearchNode(pos.x - 1, pos.y);
				astarsearch->AddSuccessor(NewNode);
			}

			if ((GetMap(pos.x, pos.y - 1) < 9)
				&& !((parent_pos.x == pos.x) && (parent_pos.y == pos.y - 1))
				)
			{
				NewNode = MapSearchNode(pos.x, pos.y - 1);
				astarsearch->AddSuccessor(NewNode);
			}

			if ((GetMap(pos.x + 1, pos.y) < 9)
				&& !((parent_pos.x == pos.x + 1) && (parent_pos.y == pos.y))
				)
			{
				NewNode = MapSearchNode(pos.x + 1, pos.y);
				astarsearch->AddSuccessor(NewNode);
			}

			if ((GetMap(pos.x, pos.y + 1) < 9)
				&& !((parent_pos.x == pos.x) && (parent_pos.y == pos.y + 1))
				)
			{
				NewNode = MapSearchNode(pos.x, pos.y + 1);
				astarsearch->AddSuccessor(NewNode);
			}

			return true;
		}

		float GetCost(const MapSearchNode& successor) const
		{
			return static_cast<float>(GetMap(pos.x, pos.y));
		}

		bool IsSameState(const MapSearchNode &rhs) const
		{
			return pos == rhs.pos;
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
			MapSearchNode nodeStart(start);
			MapSearchNode nodeEnd(end);

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

				path << IntVector2(node->pos);
				for (;; )
				{
					node = astarsearch.GetSolutionNext();

					if (!node)
					{
						break;
					}

					path << IntVector2(node->pos);
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
