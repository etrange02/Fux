#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "30";
	static const char MONTH[] = "12";
	static const char YEAR[] = "2014";
	static const char UBUNTU_VERSION_STYLE[] =  "14.12";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 6;
	static const long BUILD  = 3286;
	static const long REVISION  = 18153;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 5989;
	#define RC_FILEVERSION 2,6,3286,18153
	#define RC_FILEVERSION_STRING "2, 6, 3286, 18153\0"
	static const char FULLVERSION_STRING [] = "2.6.3286.18153";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 286;
	

}
#endif //VERSION_H
