struct Point {int x, y;};

//Jarvis' March （ Gift Wrapping Algorithm ） O(N*M) N is the number of point, M is the number of point in convex hull
class find_convex_hull
{
	// 小於。用以找出最低最左邊的點。
	bool compare(Point& a, Point& b)
	{
	    return (a.y < b.y) || (a.y == b.y && a.x < b.x);
	}

	// 向量OA cross 向量OB。大於零表示從OA到OB為順時針旋轉。
	double cross(Point& o, Point& a, Point& b)
	{
	    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
	}
public:

	//P is the array of the total point.CH is the point on the Convex Hull
	void findConvexHull(Point * P,Point* CH,int size)
	{
		/* 用最低最左邊的點當作是起點。起點可以用凸包上面任意一個點。 */
		int s = 0;
		for (int i=0; i<size; ++i)
			if (compare(P[i], P[s]))
				s = i;

		 /* 包禮物，逆時針方向。 */

		CH[0] = P[s];               // 紀錄起點

		for (int m=1; true; ++m)    // m 為凸包頂點數目
		{
        			/* 開始窮舉所有點，找出位於最外圍的一點 */

			int next = s;
			if (m == 1) next = !s;  // 找第一點時，next預設為起點以外的點，
		              // 否則cross會一直等於零。

		        	for (int i=0; i<size; ++i)
		        		if (cross(CH[m], P[i], P[next]) < 0)
		        			next = i;

		        	if (next == s) break;   // 繞一圈後回到起點了
		       	 CH[m] = P[next];        // 紀錄方才所找到的點
   		}
	}
};