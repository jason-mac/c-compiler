struct Point
{
  int x;
  int y;
};

struct Point make_point(int x, int y)
{
  struct Point p;
  p.x = x;
  p.y = y;
  return p;
}

int distance_squared(struct Point a, struct Point b)
{
  int dx = a.x - b.x;
  int dy = a.y - b.y;
  return dx * dx + dy * dy;
}
