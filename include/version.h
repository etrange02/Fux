#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "21";
	static const char MONTH[] = "12";
	static const char YEAR[] = "2014";
	static const char UBUNTU_VERSION_STYLE[] =  "14.12";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 6;
	static const long BUILD  = 3168;
	static const long REVISION  = 17488;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 5823;
	#define RC_FILEVERSION 2,6,3168,17488
	#define RC_FILEVERSION_STRING "2, 6, 3168, 17488\0"
	static const char FULLVERSION_STRING [] = "2.6.3168.17488";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 168;
	

}
#endif //VERSION_H
