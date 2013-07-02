#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "02";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] =  "13.07";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 5;
	static const long BUILD  = 1646;
	static const long REVISION  = 9116;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3301;
	#define RC_FILEVERSION 2,5,1646,9116
	#define RC_FILEVERSION_STRING "2, 5, 1646, 9116\0"
	static const char FULLVERSION_STRING [] = "2.5.1646.9116";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 46;
	

}
#endif //VERSION_H
