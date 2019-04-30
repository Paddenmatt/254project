//The purpose of this class is to put a time limit
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::_V2::system_clock::time_point globalT;
class timer {
private:
  globalT tBegin;
 	globalT tEnd;
public:
	void start() {
		tBegin = Clock::now();
	}

	unsigned long elapsedTime() {
		tEnd = Clock::now();
		return std::chrono::duration_cast<std::chrono::seconds>(tEnd - tBegin).count();
	}

	bool isTimeout(unsigned long seconds) {
		return elapsedTime() >= seconds;
	}
};
