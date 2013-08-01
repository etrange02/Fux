#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "01";
	static const char MONTH[] = "08";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] =  "13.08";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 7;
	static const long BUILD  = 1859;
	static const long REVISION  = 10315;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3636;
	#define RC_FILEVERSION 2,7,1859,10315
	#define RC_FILEVERSION_STRING "2, 7, 1859, 10315\0"
	static const char FULLVERSION_STRING [] = "2.7.1859.10315";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 59;
	

}
#endif //VERSION_H
