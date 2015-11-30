The condition that the train and bus can't meet at one vertex except the final one is just trolling. If there's a railway , then the train can take it and wait in town N. If there's no such railway, then there's a road , the bus can take it and wait in N instead. There's nothing forbidding this :D.

The route of one vehicle is clear. How about the other one? Well, it can move as it wants, so the answer is the length of its shortest path from 1 to N... or  - 1 if no such path exists. It can be found by BFS in time O(N + M) = O(N2).

In order to avoid casework, we can just compute the answer as the maximum of the train's and the bus's shortest distance from 1 to N. That way, we compute ; since the answer is  ≥ 1, it works well.

In summary, time and memory complexity: O(N2).

Bonus: Assume that there are M1 roads and M2 railways given on the input, all of them pairwise distinct.

Bonus 2: Additionally, assume that the edges are weighted. The speed of both vehicles is still the same — traversing an edge of length l takes l hours.
