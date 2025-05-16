// Take all points that lie on convex hull (ke ca 3 diem thang hang)
vector<Point> getHull(vector<Point> points) {
    for (auto &p : points) if (make_pair(p.y, p.x) < make_pair(points[0].y, points[0].x)) {
        swap(p, points[0]);
    }
 
    sort (points.begin() + 1, points.end(), [&](const Point &A, const Point &B) {
        int tmp = ccw(points[0], A, B);
        if (tmp != 0) return tmp > 0;
        return (A - points[0]).norm() < (B - points[0]).norm();
    });
 
    int p = points.size() - 1;
    while (p >= 0 && ccw(points[0], points[p], points.back()) == 0) --p;
    reverse(points.begin() + p + 1, points.end());
 
    vector<Point> hull;
    for (auto p : points) {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p) < 0) hull.pop_back();
        hull.emplace_back(p);
    }
    return hull;
}

double getArea(vector<Point> points) {
    if (points.empty()) return 0;
    double area = 0; points.emplace_back(points[0]);
    for (int i = 0; i + 1 < points.size(); ++i)
        area += points[i] * points[i + 1];
    return abs(area) * 0.5;
}