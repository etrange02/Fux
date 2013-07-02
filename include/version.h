#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "24";
	static const char MONTH[] = "06";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] =  "13.06";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 5;
	static const long BUILD  = 1627;
	static const long REVISION  = 9005;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3260;
	#define RC_FILEVERSION 2,5,1627,9005
	#define RC_FILEVERSION_STRING "2, 5, 1627, 9005\0"
	static const char FULLVERSION_STRING [] = "2.5.1627.9005";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 27;
	

}
#endif //VERSION_H
