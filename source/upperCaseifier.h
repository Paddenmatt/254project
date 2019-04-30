//Makes the letter inserted into uppercase so functions can read it
#ifndef UPPERCASEIFIER_H
#define UPPERCASEIFIER_H
string upperCaseifier(string s){
	for(int x = 0; x < s.length(); x++){
		s[x] = toupper(s[x]);
	}

	return s;
}
#endif
