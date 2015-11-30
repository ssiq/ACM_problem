struct Point {double x, y;};    // 點的資料結構
struct Vector {double x, y;};   // 向量的資料結構，和點一樣
struct Line {Point p1, p2;};    // 線的資料結構，注意p1和p2不能相等！
struct Segment {Point p1, p2;}; // 線段的資料結構，注意p1和p2不能相等！

Point INF(1e9, 1e9);

// 內積運算
int dot(Vector& v1, Vector& v2)
{
    return v1.x * v2.x + v1.y * v2.y;   // 都是整數運算，沒有除法
}

// 外積運算，只回傳外積結果的純量（只有大小、沒有方向）
int cross(Vector& v1, Vector& v2)
{
    return v1.x * v2.y - v1.y * v2.x;   // 都是整數運算，沒有除法
}

double length(Vector& v)
{
    return sqrt(v1.x * v1.x + v2.y * v2.y);
}

double distance_point_to_point(Point& p1, Point& p2)
{
    return sqrt( (p2.x - p1.x) * (p2.x - p1.x)
                + (p2.y - p1.y) * (p2.y - p1.y) );
}

double distance_point_to_line(Point& p, Line& l)
{
    Vector v1 = p - p1, v2 = p2 - p1;
    return fabs(cross(v1, v2)) / length(v2);    // 面積除以底得高
}

double distance_point_to_segment(Point& p, Segment& s)
{
    Line l = s;
    Vector p1p = p - s.p1, p1p2 = s.p2 - s.p1;  // 建立向量求內積
    Vector p2p = p - s.p2, p2p1 = s.p1 - s.p2;  // 判斷點在哪一區
    
    if (dot(p1p, p1p2) > 0 && dot(p2p, p2p1) > 0) // 垂直距離區
    {                                           // 用大於等於零也可以 
        // 點到線距離
        return distance(p, l);
    }
    else    // 端點距離區
    {
        // 點到點距離
        return min( distance(p, s.p1) , distance(p, s.p2) );
    }
}

double distance_segment_to_line(Segment& s, Line& l)
{
    Vector v = l.p2 - l.p1;
    Vector v1 = s.p1 - l.p1, v2 = s.p2 - l.p1;
    
    // 計算外積，根據正負號來判斷同邊
    double c1 = cross(v1, v), c2 = cross(v2, v);
 
    // 判斷正負號
    // 由於cross的值通常很大，故不用 c1 * c2 > 0 來判斷同邊，避免溢位
    
    if (c1 > 0 && c2 > 0 || c1 < 0 && c2 < 0) // 同邊，且不在線上
    {
        // 點到線距離
//      return min( distance(s.p1, l) , distance(s.p2, l) );
        
        // 不必再呼叫函式重算 v1 v2
//      return min( fabs(cross(v1, v)) / length(v),
//                  fabs(cross(v2, v)) / length(v) );
 
        return min( fabs(cross(v1,v)),
                    fabs(cross(v2,v)) ) / length(v);
    }
    else    // 不同邊，或有一點在線上
    {
        return 0.0;
    }
}

// 判斷線段相交
bool intersect(Segment& s1, Segment& s2)
{
    Vector v1 = s1.p2-s1.p1, v1a = s2.p1-s1.p1, v1b = s1.p2-s1.p1;
    Vector v2 = s2.p2-s2.p1, v2a = s1.p1-s2.p1, v2b = s1.p2-s2.p1;
 
    // 兩線段平行或共線，恰好可以用端點到線段的距離求出答案
    // 不用理會兩線段是否相交
    double c12 = cross(v1, v2);
    if (c12 == 0) return false;
 
    double c1a = cross(v1, v1a), c1b = cross(v1, v1b);
    double c2a = cross(v2, v2a), c2b = cross(v2, v2b);
    
    // 看看線段的兩端點是否位於另一線段的兩側，如此才會相交
    return ((c1a <= 0 && c1b >= 0) || (c1a >= 0 && c1b <= 0))
        && ((c2a <=0 && c2b >= 0) || (c2a >= 0 && c2b <= 0));
}


// // 判斷線段相交，但不能處理端點共線的情況
// bool intersect(Segment& s1, Segment& s2)
// {
//     Vector v1 = s2.p1 - s1.p1, v2 = s1.p2 - s2.p1;
//     Vector v3 = s2.p2 - s1.p2, v4 = s1.p1 - s2.p2;
    
//     double c1 = cross(v1, v2), c2 = cross(v2, v3);
//     double c3 = cross(v3, v4), c4 = cross(v4, v1);
    
//     // 朝同一方向轉彎。都是順時針，或者都是逆時針。
//     return (c1 > 0 && c2 > 0 && c3 > 0 && c4 > 0)
//         || (c1 < 0 && c2 < 0 && c3 < 0 && c4 < 0);
// }

double distance_segment_to_segment(Segment& s1, Segment& s2)
{
    if (intersect(s1, s2))  // 線段不平行又相交時
    {
        return 0.0;
    }
    else    // 線段不平行又不相交時
    {       // 或者兩線段平行或共線時
        // 點到線段距離
        return min( distance(s1.p1, s2), distance(s1.p2, s2),
                    distance(s2.p1, s1), distance(s2.p2, s1) );
    }
}

double distance_line_to_line(Line& l1, Line& l2)
{
    Vector v1 = l1.p2 - l1.p1, v2 = l2.p2 - l2.p1;
    
    if (cross(v1, v2) == 0) // 平行、不相交
    {
        // 點到線距離
        return distance(l1.p1, l2);
    }
    else    // 相交
    {
        return 0.0;
    }
}

//line p1,p2 intersect with line p3,p4
Point intersection_in_two_lines(Point& p1, Point& p2, Point& p3, Point& p4)
{
    Point p12 = p2 - p1, p13 = p3 - p1, p34 = p4 - p3;
    double c1 = cross(p13, p34), c2 = cross(p12, p34);
 
    if (c2 == 0)
        if (c1 == 0)
            cout << "兩線重疊";
        else
            cout << "兩線平行但不重疊";
    else
        return p1 + (p12 * (c1 / c2));
}

//segment p1,p2 intersect with segment p3,p4
Point intersection_in_two_segment(Point& p1, Point& p2, Point& p3, Point& p4)
{
   Point p12 = p2 - p1, p13 = p3 - p1, p34 = p4 - p3;
    double c1 = cross(p13, p34), c2 = cross(p12, p34);
    double c3 = cross(p13, p12);
    
    if (c2 < 0) c1 = -c1, c2 = -c2, c3 = -c3;
 
    if (c2 != 0 && c1 >= 0 && c1 <= c2 && c3 >= 0 && c3 <= c2)
        return p1 + (p12 * (c1 / c2));
    else
        return INF;
}

