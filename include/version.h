#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "05";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] =  "13.07";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 5;
	static const long BUILD  = 1680;
	static const long REVISION  = 9303;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3344;
	#define RC_FILEVERSION 2,5,1680,9303
	#define RC_FILEVERSION_STRING "2, 5, 1680, 9303\0"
	static const char FULLVERSION_STRING [] = "2.5.1680.9303";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 80;
	

}
#endif //VERSION_H
