#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "18";
	static const char MONTH[] = "09";
	static const char YEAR[] = "2014";
	static const char UBUNTU_VERSION_STYLE[] =  "14.09";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 3;
	static const long MINOR  = 6;
	static const long BUILD  = 2838;
	static const long REVISION  = 15677;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 5396;
	#define RC_FILEVERSION 3,6,2838,15677
	#define RC_FILEVERSION_STRING "3, 6, 2838, 15677\0"
	static const char FULLVERSION_STRING [] = "3.6.2838.15677";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 38;
	

}
#endif //VERSION_H
