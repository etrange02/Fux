#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "06";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] =  "13.07";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 5;
	static const long BUILD  = 1691;
	static const long REVISION  = 9359;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3357;
	#define RC_FILEVERSION 2,5,1691,9359
	#define RC_FILEVERSION_STRING "2, 5, 1691, 9359\0"
	static const char FULLVERSION_STRING [] = "2.5.1691.9359";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 91;
	

}
#endif //VERSION_H
