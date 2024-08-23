#ifndef GLOBALID_H
#define GLOBALID_H
class GlobalID
{
public:
	static int createGlobalID(int c, int i) {
		return (i % 1000000 + 1000000 * c);
	}
	static int getClassID(int g) {
		return (g / 1000000);
	}
	static int getInstanceID(int g) {
		return (g % 1000000);
	}
};
#endif