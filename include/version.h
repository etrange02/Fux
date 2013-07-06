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
	static const long MINOR  = 6;
	static const long BUILD  = 1703;
	static const long REVISION  = 9429;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3369;
	#define RC_FILEVERSION 2,6,1703,9429
	#define RC_FILEVERSION_STRING "2, 6, 1703, 9429\0"
	static const char FULLVERSION_STRING [] = "2.6.1703.9429";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 3;
	

}
#endif //VERSION_H
