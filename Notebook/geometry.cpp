struct Point {
    double x, y;
 
    Point() {
        x = y = 0;
    }
 
    Point(double _x, double _y) {
        x = _x, y = _y;
    }
 
    void get() {
        cin >> x >> y;
    }
 
    void show() {
        cout << fixed << setprecision(3) << x << ' ' << y << '\n';
    }
 
    double len() {
        return sqrt(x * x + y * y);
    }
 
    double square_len() {
        return x * x + y * y;
    }

    friend double dist(Point A, Point B) {
        return (B - A).len();
    }

    friend double square_dist(Point A, Point B) {
        return (B - A).square_len();
    }
 
    Point operator+ (const Point other) {
        return Point(x + other.x, y + other.y);
    }
 
    Point operator- (const Point other) {
        return Point(x - other.x, y - other.y);
    }
 
    Point operator- () {
        return Point(-x, -y);
    }
 
    bool operator== (const Point other) {
        return x == other.x && y == other.y;
    }
 
    bool operator!= (const Point other) {
        return x != other.x || y != other.y;
    }
 
    bool operator< (const Point other) {
        return (x == other.x ? y < other.y : x < other.x);
    }
 
    bool operator> (const Point other) {
        return (x == other.x ? y > other.y : x > other.x);
    }
 
    double operator% (const Point other) {
        return x * other.x + y * other.y;
    }
 
    double operator* (const Point other) {
        return x * other.y - y * other.x;
    }
 
    double operator^ (const Point other) {
        return atan2(*this * other, *this % other);
    }
};

int ccw(Point A, Point B) {
    double tmp = A * B;
    if (tmp == 0) return 0;
    return (tmp > 0 ? 1 : -1);
}

int ccw(Point P, Point A, Point B) {
    double tmp = (A - P) * (B - P);
    if (tmp == 0) return 0;
    return (tmp > 0 ? 1 : -1);
}

struct Line {
    double a, b, c;

    Line(double _a = 0, double _b = 0, double _c = 0) {
        a = _a, b = _b, c = _c;
    }

    double eval(Point p) {
        return a * p.x + b * p.y + c;
    }

    void show() {
        cout << fixed << setprecision(5) << a << ' ' << b << ' ' << c << '\n';
    }
};

int ccw(Line l, Point A) {
    Point cp(-l.b, l.a);
    double tmp = cp * A;
    if (tmp == 0) return 0;
    return (tmp > 0 ? 1 : -1);
}

Line getLine(Point A, Point B) {
    Point cp = B - A, pt(-cp.y, cp.x);
    if (pt.x < 0) pt = Point(-pt.x, -pt.y);
    return Line(pt.x, pt.y, -(pt.x * A.x + pt.y * A.y));
}

Line perpenLine(Point A, Line l) {
    Point pt(-l.b, l.a);
    if (pt.x < 0) pt = Point(-pt.x, -pt.y);
    return Line(pt.x, pt.y, -(pt.x * A.x + pt.y * A.y));
}
 
bool onSegment(Point a, Point b, Point c) {
    if (a.x >= min(b.x, c.x) && a.x <= max(b.x, c.x) 
     && a.y >= min(b.y, c.y) && a.y <= max(b.y, c.y))
        return 1;
    return 0;
}
 
bool lineIntersect(Point A, Point B, Point C, Point D) {
    Point p[4]; p[0] = A, p[1] = B, p[2] = C, p[3] = D;
 
    int o1 = ccw(p[1] - p[0], p[2] - p[0]),
        o2 = ccw(p[1] - p[0], p[3] - p[0]),
        o3 = ccw(p[3] - p[2], p[0] - p[2]),
        o4 = ccw(p[3] - p[2], p[1] - p[2]);
 
    if (o1 != o2 && o3 != o4) return 1;
 
    bool res = 0;
 
    res |= (!o1 && onSegment(p[2], p[0], p[1]));
    res |= (!o2 && onSegment(p[3], p[0], p[1]));
    res |= (!o3 && onSegment(p[0], p[2], p[3]));
    res |= (!o4 && onSegment(p[1], p[2], p[3]));
 
    return res;
}

double get_dist(Point X, Line l) {
    return abs(l.eval(X)) / sqrt(l.a * l.a + l.b * l.b);
}

bool obtuse(Point A, Point B, Point C) {
    return (B - A).square_len() + (B - C).square_len() < (C - A).square_len();
}

double get_dist(Point X, Point A, Point B) {
    if (obtuse(X, A, B) || obtuse(X, B, A)) return min(dist(X, A), dist(X, B));
    return get_dist(X, getLine(A, B));
}

double get_dist(Point A, Point B, Point C, Point D) {
    double d1 = min(get_dist(A, C, D), get_dist(B, C, D));
    double d2 = min(get_dist(C, A, B), get_dist(D, A, B));
    return min(d1, d2);
}