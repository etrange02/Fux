#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "14";
	static const char MONTH[] = "06";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] = "13.06";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 2;
	static const long MINOR = 4;
	static const long BUILD = 1521;
	static const long REVISION = 8433;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 3009;
	#define RC_FILEVERSION 2,4,1521,8433
	#define RC_FILEVERSION_STRING "2, 4, 1521, 8433\0"
	static const char FULLVERSION_STRING[] = "2.4.1521.8433";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 21;
	

}
#endif //VERSION_H
