#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <math.h>
#include <iomanip>

using namespace std;

#define eps (1e-8)

int dcmp(double x)
{  
    if(fabs(x) < eps)
      return 0;  
    return x > 0 ? 1 : -1;  
} 

struct Point
{
  double x, y;
  Point(double _x=0, double _y=0) {x=_x;y=_y;}
};

Point operator + (const Point &a, const Point &b)
{  
  return Point(a.x+b.x,a.y+b.y);  
}

Point operator - (const Point &a, const Point &b)
{  
  return Point(a.x-b.x,a.y-b.y);  
}

Point operator * (const Point &a, const double &p)
{  
  return Point(a.x*p,a.y*p);  
}  

Point operator / (const Point &a, const double &p)
{  
  return Point(a.x/p,a.y/p);  
} 

bool operator < (const Point &a, const Point &b)
{  
  return a.x<b.x||(a.x==b.x&&a.y<b.y);  
} 

bool operator == (const Point &a, const Point &b)
{  
  return (dcmp(a.x-b.x) == 0)&&(dcmp(a.y-b.y) == 0);  
}  

double Dot(Point a, Point b)
{  
  return a.x*b.x+a.y*b.y;  
}  

double Length(Point a)
{  
  return sqrt(Dot(a,a));  
}  

double Angle(Point a, Point b)
{  
  return acos(Dot(a,b)/Length(a)/Length(b));  
}  

double angle(Point a)
{  
  return atan2(a.y, a.x);  
}  

double Cross(Point a, Point b)
{  
  return a.x*b.y-a.y*b.x;  
} 

Point vecunit(Point a)
{  
  return a/Length(a);  
}  

Point Normal(Point a)
{  
  return Point(-a.y,a.x)/Length(a);  
}  

Point Rotate(Point& a, double rad)
{  
  return Point(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));  
}  

double Area2(Point a, Point b, Point c)
{  
  return Length(Cross(b-a,c-a));  
} 

struct Line
{  
    Point p, v;  
    double ang;  
    Line(){};  
    Line(Point p, Point v):p(p),v(v) {ang = atan2(v.y,v.x);}  
    bool operator < (const Line &L) const {return ang < L.ang;}  
};  

bool OnLeft(const Line &L,const Point &p)
{  
  return dcmp(Cross(L.v,p-L.p)) >= 0;  
} 

Point GetLineIntersection(Point& p, Point& v, Point& q, Point& w)
{  
  Point u = p-q;  
  double t = Cross(w,u)/Cross(v,w);  
  return p+v*t;  
} 

Point GetLineIntersection(Line& a, Line& b)
{  
  return GetLineIntersection(a.p,a.v,b.p,b.v);  
} 

vector<Point> HPI(vector<Line>& L)
{  
  int n = L.size();  
  sort(L.begin(),L.end());//将所有半平面按照极角排序。  
  int first,last;  
  vector<Point> p(n);  
  vector<Line> q(n);  
  vector<Point> ans;  
  q[first=last=0]=L[0];  
  for(int i=1;i<n;i++)
  {  
    while(first<last&&!OnLeft(L[i],p[last-1]))
      last--;//删除顶部的半平面  
    while(first<last&&!OnLeft(L[i],p[first]))
      first++;//删除底部的半平面  
    q[++last]=L[i];//将当前的半平面假如双端队列顶部。  
    if(fabs(Cross(q[last].v,q[last-1].v))<eps)
    {//对于极角相同的，选择性保留一个。  
      last--;  
      if(OnLeft(q[last],L[i].p))q[last]=L[i];  
    }  
    if(first<last)
      p[last-1]=GetLineIntersection(q[last-1],q[last]);//计算队列顶部半平面交点。  
  }  
  while(first<last&&!OnLeft(q[first],p[last-1]))
    last--;//删除队列顶部的无用半平面。  
  //cout<<first<<" "<<last<<endl;
  if(last-first<=1)
    return ans;//半平面退化  
  p[last]=GetLineIntersection(q[last],q[first]);//计算队列顶部与首部的交点。  
  for(int i = first; i <= last; i++)
    ans.push_back(p[i]);//将队列中的点复制。  
  return ans;  
}  

double PolyArea(vector<Point>& p)
{  
    int n = p.size();  
    double ans = 0.0;  
    for(int i = 1; i < n-1; i++)  
        ans+=Cross(p[i]-p[0],p[i+1]-p[0]);  
    return ans/2;  
} 

double IntersectAreaOfPoly(vector<Point>& poly1, vector<Point>& poly2)
{
  int n,m;
  n = poly1.size();
  m = poly2.size();
  if(n < 3 || m < 3)
    return 0;
  double ret1, ret2, ret = 0;
  ret1 = PolyArea(poly1);
  if(dcmp(ret1) < 0)
    reverse(poly1.begin(),poly1.end());
  //ret += fabs(ret1);

  ret2 = PolyArea(poly2);
  if(dcmp(ret2)<0)
    reverse(poly2.begin(),poly2.end());
  //ret += fabs(ret2);
  for(int i = 1; i < n-1; i++)
  {
    for(int j = 1; j < m-1; j++)
    {
      vector<Point> s1,s2;
      s1.push_back(poly1[0]);
      s1.push_back(poly1[i]);
      s1.push_back(poly1[i+1]);
      s2.push_back(poly2[0]);
      s2.push_back(poly2[j]);
      s2.push_back(poly2[j+1]);
      double r1,r2;
      int flag1,flag2;
      r1=PolyArea(s1);
      if(dcmp(r1)>=0)
        flag1=1;
      else 
        flag1=0;
      if(dcmp(r1)<0)
        reverse(s1.begin(),s1.end());
      r2 = PolyArea(s2);
      if(dcmp(r2)>=0)
        flag2=1;
      else
        flag2=0;
      if(dcmp(r2)<0)
        reverse(s2.begin(),s2.end());
      vector<Line> L;
      for(int k=0;k<3;k++)
        L.push_back(Line(s1[k],s1[(k+1)%3]-s1[k]));
      for(int k=0;k<3;k++)
        L.push_back(Line(s2[k],s2[(k+1)%3]-s2[k]));
      vector<Point> tt = HPI(L);
      if(flag1==flag2)
        ret -= PolyArea(tt);
      else ret += PolyArea(tt);
    }
  }
  return fabs(ret);
}






int main()
{
  Point p1,p2,p3,p4,p5;
  p1.x = 0;
  p1.y = 0;
  p2.x = 1;
  p2.y = 0;
  p3.x = 1;
  p3.y = 1;
  p4.x = 0;
  p4.y = 1;
  p5.x = 1.0/2;
  p5.y = 3.0/2;

  vector<Point> polygon1, polygon2;
  polygon1.push_back(p1);
  polygon1.push_back(p2);
  polygon1.push_back(p3);
  polygon1.push_back(p4);

  polygon2.push_back(p2);
  polygon2.push_back(p5);
  polygon2.push_back(p4);

  cout<<IntersectAreaOfPoly(polygon1, polygon2)<<endl;


  return 0;
}
