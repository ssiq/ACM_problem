struct Point {int x, y;};

//Graham's Scan
//this algorithm can't find the point in the segment in the convex hull
class find_convex_hull
{
	// 向量OA cross 向量OB。大於零表示從OA到OB為順時針旋轉。
	double cross(Point& o, Point& a, Point& b)
	{
	    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
	}

	// 小於。用以找出最低最左邊的點。
	bool compare_position(Point& a, Point& b)
	{
	    return (a.y < b.y) || (a.y == b.y && a.x < b.x);
	}

	// 小於。以P[0]當中心點做角度排序，以逆時針方向排序。
	// 若角度一樣，則順序隨便。
	bool compare_angle(Point& a, Point& b)
	{
	    return cross(P[0], a, b) > 0;
	}
public:

	// P為平面上的那些點。這裡設定為剛好100點。
	// CH為凸包上的點。這裡設定為照逆時針順序排列。
	void findConvexHull(Point * P,Point* CH,int size)
	{
	    /* 用最低最左邊的點當作是起點。起點必須是凸包的端點。 */
	    
	    // 將端點換到第一點。O(N)
	    swap(P[0], *min_element(P, P+size, compare_position));
	 
	    // 其餘各點照角度排序，並以第一點當中心點。O(NlogN)
	    sort(P+1, P+size, compare_angle);
	    
	    /* 包，逆時針方向。O(N) */
	    
	    P[N] = P[0];
	    
	    int m = 0;      // m 為凸包頂點數目
	    for (int i=0; i<=size; ++i) {
	        while (m >= 2 && cross(CH[m-2], CH[m-1], P[i]) < 0) m--;
	        CH[m++] = P[i];
	    }
	    
	    m--;    // 最後一個點是重複出現兩次的起點，故要減一。
	}

};