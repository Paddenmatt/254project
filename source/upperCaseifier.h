//Makes the letter inserted into uppercase so functions can read it
string upperCaseifier(string s){
	for(int x = 0; x < s.length(); x++){
		s[x] = toupper(s[x]);
	}

	return s;
}
