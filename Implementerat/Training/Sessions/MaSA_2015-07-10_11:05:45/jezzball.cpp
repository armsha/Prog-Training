
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class atom
{
public:

	int x;
	int y;
	int vx;
	int vy;

	atom( int x, int y, int vx, int vy ): x(x), y(y), vx(vx), vy(vy) {};

	double intersects( double t, int Px, int Py, int h, int w, int rw ) {

		double ftime = max(Py,h-Py)/rw;

		double startTravelX = t*vx; 
		double startTravelY = t*vy;

		double actualTravelX = fmod(startTravelX,2.0*w);
		double actualTravelY = fmod(startTravelY,2.0*h);

		double currX = x + actualTravelX;
		if (currX < 0)
			currX = -currX;
		if (currX > w)
			currX = w - (currX-w);

		double currY = y + actualTravelY;
		if (currY < 0)
			currY = -currY;
		if (currY > h)
			currY = h - (currY-h);

		double currVX = vx;
		if ( fmod(startTravelX/(double)w,2.0) >= 1 )
			currVX = -currVX;

		double currVY = vy;
		if ( fmod(startTravelY/(double)h,2.0) >= 1 )
			currVY = -currVY;


		double intersectX = -1;
		double endX = x + currVX*ftime;
		if (endX < 0) {
			endX = -endX;
			intersectX = 0;
		}
		if (endX > w){
			endX = w - (endX-w);
			intersectX = w;
		}

		double intersectY = -1;
		double endY = y + currVY*ftime;
		if (endY < 0){
			endY = -endY;
			intersectY = 0;
		}
		if (endY > h){
			endY = h - (endY-h);
			intersectY = h;
		}

		double intersectTime1 = -1;
		double midtime = 0;
		double intersectTime2 = -1;
		double intersectY1 = -1;
		double intersectY2 = -1;
		if ( intersectX==-1 )
		{
			if ( ( currX < Px and endX > Px ) or
				 ( currX > Px and endX < Px ) )
			{
				intersectTime1 = (Px-currX)/currVX;
				intersectY1 = currY + currVy*intersectTime1;
				if intersectY1 < 0
					intersectY1 = -intersectY1;
				if intersectY1 > h 
					intersectY1 = h- (intersectY1-h);
				if (intersectY1 >= Py)
				{
					if ( Py+ rw*intersectTime1 > intersectY1)
					{
						return intersectTime1;
					}
				} else {
					if ( Py- rw*intersectTime1 < intersectY1)
					{
						return intersectTime1;
					}
				}
			}
		} else {
			
			if ( ( currX < Px and endX > Px ) or
				 ( currX > Px and endX < Px ) )
			{
				intersectTime1 = (Px-currX)/currVX;
				intersectY1 = currY + currVy*intersectTime1;
				if intersectY1 < 0
					intersectY1 = -intersectY1;
				if intersectY1 > h 
					intersectY1 = h- (intersectY1-h);
				if (intersectY1 >= Py)
				{
					if ( Py+ rw*intersectTime1 > intersectY1)
					{
						return intersectTime1;
					}
				} else {
					if ( Py- rw*intersectTime1 < intersectY1)
					{
						return intersectTime1;
					}
				}
			} else if ( intersectX == 0 and (currX > Px) ) {

				intersectTime1 = (Px-currX)/currVX;
				midtime = (0-currX)/currVX;
				intersectY1 = currY + currVy*intersectTime1;
				if intersectY1 < 0
					intersectY1 = -intersectY1;
				if intersectY1 > h 
					intersectY1 = h- (intersectY1-h);
				if (intersectY1 >= Py)
				{
					if ( Py+ rw*intersectTime1 > intersectY1)
					{
						return intersectTime1;
					}
				} else {
					if ( Py- rw*intersectTime1 < intersectY1)
					{
						return intersectTime1;
					}
				}

				if ( endX > Px ){

					intersectTime2 = midtime + (Px)/(-currVX);
					intersectY2 = currY + currVy*intersectTime1;
					if intersectY2 < 0
						intersectY2 = -intersectY2;
					if intersectY2 > h 
						intersectY2 = h- (intersectY2-h);
					if (intersectY2 >= Py)
					{
						if ( Py+ rw*intersectTime2 > intersectY2)
						{
							return intersectTime2;
						}
					} else {
						if ( Py- rw*intersectTime2 < intersectY2)
						{
							return intersectTime2;
						}
					}
				}

			} else if ( intersectX == w and (currX < Px) ) {
				
				intersectTime1 = (Px-currX)/currVX;
				midtime = (w-currX)/currVX;
				intersectY1 = currY + currVy*intersectTime1;
				if intersectY1 < 0
					intersectY1 = -intersectY1;
				if intersectY1 > h 
					intersectY1 = h- (intersectY1-h);
				if (intersectY1 >= Py)
				{
					if ( Py+ rw*intersectTime1 > intersectY1)
					{
						return intersectTime1;
					}
				} else {
					if ( Py- rw*intersectTime1 < intersectY1)
					{
						return intersectTime1;
					}
				}

				if ( endX > Px ){

					intersectTime2 = midtime + (w-Px)/(currVX);
					intersectY2 = currY + currVy*intersectTime1;
					if intersectY2 < 0
						intersectY2 = -intersectY2;
					if intersectY2 > h 
						intersectY2 = h- (intersectY2-h);
					if (intersectY2 >= Py)
					{
						if ( Py+ rw*intersectTime2 > intersectY2)
						{
							return intersectTime2;
						}
					} else {
						if ( Py- rw*intersectTime2 < intersectY2)
						{
							return intersectTime2;
						}
					}
				}

			}
		}

		return -1.0;

	}


};

double solve( vector<atom> atoms, int x, int y, int h, int w, int rv ){

	double t = 0;
	bool success = false;

	bool intersected;
	double itime;
	while (t <= 10000) {

		intersected = false;
		for( atom a: atoms ){

			itime = a.intersects( t,x,y,h,w,rv );
			if ( itime > 0 )
			{	
				intersected = true;
				t += itime;
				break;
			}
		}
		if ( not intersected )
		{
			success = true;
			break;
		}
	}

	if success
		return t;
	else
		return -1;

}


int main(int argc, char const *argv[])
{
	
	int n;
	int x;
	int y;

	int h = 1024;
	int w = 768;
	int rv = 200;

	int xa;
	int ya;
	int vax;
	int vay;

	vector<atom> atoms;
	vector<atom> atoms2;

	while (true) {

		cin >> n;

		if (n==0)
			break;

		cin >> x >> y;

		atoms = vector<atom>();
		for (int i = 0; i < n; ++i)
		{
			cin >> xa >> ya >> vax >> vay;
			atoms.pushback( atom( xa, ya, vax, vay ) );
			atoms.pushback( atom( ya, xa, vay, vax ) );
		}

		cout << solve( atoms, x, y, h, w, rv ) << endl;
		cout << solve( atoms2, y, x, w, h, rv ) << endl;

	}

	return 0;
}