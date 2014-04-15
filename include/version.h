#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "16";
	static const char MONTH[] = "04";
	static const char YEAR[] = "2014";
	static const char UBUNTU_VERSION_STYLE[] =  "14.04";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 3;
	static const long MINOR  = 0;
	static const long BUILD  = 2253;
	static const long REVISION  = 12424;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 4312;
	#define RC_FILEVERSION 3,0,2253,12424
	#define RC_FILEVERSION_STRING "3, 0, 2253, 12424\0"
	static const char FULLVERSION_STRING [] = "3.0.2253.12424";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 53;
	

}
#endif //VERSION_H
