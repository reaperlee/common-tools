#ifndef _URL_DECODE_H
#define _URL_DECODE_H

#include<map>
#include<string>

using namespace std;
class CUrlDecoder{
private:
	enum{
		STATE_FIND_NONE,
		STATE_FIND_PERCENT,
		STATE_FIND_FIRST
	} m_decodeStates;
	bool m_inited;
	map<string,char> m_decodeMap;//decode map:%21->! %23->#...and so on
public:
	CUrlDecoder(){
		m_inited=false;
		m_decodeStates=STATE_FIND_NONE;
	}
	bool decode(const string& before,string& afterDecode);
	bool init(string& debugMsg);
	void printMap();
};
#endif
