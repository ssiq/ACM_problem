struct Point {int x, y;};

//Andrew's Monotone Chain
class find_convex_hull
{
	// 向量OA cross 向量OB。大於零表示從OA到OB為順時針旋轉。
	double cross(Point& o, Point& a, Point& b)
	{
	    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
	}

	// 小於。依座標大小排序，先排 x 再排 y。
	bool compare(Point& a, Point& b)
	{
	    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
	}
public:
	// P為平面上的那些點。這裡設定為剛好100點。
	// CH為凸包上的點。這裡設定為照逆時針順序排列。
	void findConvexHull(Point* P,Point* CH,int size)
	{
	    // 將所有點依照座標大小排序
	    sort(P, P+size, compare);
	 
	    int m = 0;  // m 為凸包頂點數目
	 
	    // 包下半部
	    for (int i=0; i<size; ++i) {
	        while (m >= 2 && cross(CH[m-2], CH[m-1], P[i]) <= 0) m--;
	        CH[m++] = P[i];
	    }
	 
	    // 包上半部，不用再包入方才包過的終點，但會再包一次起點
	    for (int i=size-2, t=m+1; i>=0; --i) {
	        while (m >= t && cross(CH[m-2], CH[m-1], P[i]) <= 0) m--;
	        CH[m++] = P[i];
	    }
	}
};