#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "15";
	static const char MONTH[] = "08";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] =  "13.08";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 9;
	static const long BUILD  = 2043;
	static const long REVISION  = 11321;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3984;
	#define RC_FILEVERSION 2,9,2043,11321
	#define RC_FILEVERSION_STRING "2, 9, 2043, 11321\0"
	static const char FULLVERSION_STRING [] = "2.9.2043.11321";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 43;
	

}
#endif //VERSION_H
