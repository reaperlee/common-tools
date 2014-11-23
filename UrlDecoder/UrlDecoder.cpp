#include "UrlDecoder.h"
#include<iostream>
#include<map>
#include<string>
#include<cstring>

//#define MODULE_DEBUG
using namespace std;
char raw[]="!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ ";
char* encoded[]={"%21","%22","%23","%24","%25","%26","%27","%28","%29","%2A","%2B","%2C","%2D","%2E","%2F","%3A","%3B","%3C","%3D","%3E","%3F","%40","%5B","%5C","%5D","%5E","%5F","%60","%7B","%7C","%7D","%7E","%7F","00"};

bool CUrlDecoder::decode(const string& before,string& afterDecode){
	if(!m_inited){
		return false;
	}
	
	m_decodeStates=STATE_FIND_NONE;
	char encodedElement[4]={0};
	for(int i=0;i<before.size();i++){
		switch(m_decodeStates){
			case STATE_FIND_NONE:
				if(before[i]=='%'){
					memset(encodedElement,0,sizeof(encodedElement));
					encodedElement[0]='%';
					m_decodeStates=STATE_FIND_PERCENT;
				}
				else{
					afterDecode+=before[i];
				}
				break;
			case STATE_FIND_PERCENT:
				if(before[i]>='0'&&before[i]<='9'){
					encodedElement[1]=before[i];
					m_decodeStates=STATE_FIND_FIRST;
				}
				else{
					encodedElement[1]=before[i];
					afterDecode+=encodedElement;
					m_decodeStates=STATE_FIND_NONE;
				}
				break;
			case STATE_FIND_FIRST:
				if((before[i]>='0'&&before[i]<='9')||(before[i]>='A'&&before[i]<='F')){
					encodedElement[2]=before[i];
					map<string,char>::const_iterator findIt;
					findIt=m_decodeMap.find(encodedElement);
					if(findIt!=m_decodeMap.end()){
						afterDecode+=findIt->second;
					}
					else{
						afterDecode+=encodedElement;
					}
					m_decodeStates=STATE_FIND_NONE;
				}
				else if(before[i]>='a'&&before[i]<='f'){
					encodedElement[2]=before[i]-('a'-'A');
					map<string,char>::const_iterator findIt;
					findIt=m_decodeMap.find(encodedElement);
					if(findIt!=m_decodeMap.end()){
						afterDecode+=findIt->second;
					}
					else{
						afterDecode+=encodedElement;
					}
					m_decodeStates=STATE_FIND_NONE;
				}
				else{
					encodedElement[2]=before[i];
					afterDecode+=encodedElement;
					m_decodeStates=STATE_FIND_NONE;
				}
				break;
			default:break;
		}
	}

	if(m_decodeStates==STATE_FIND_PERCENT){
		afterDecode+=encodedElement;
	}

	return true;
}

bool CUrlDecoder::init(string& debugMsg){
	//cerr<<"raw="<<raw<<" raw size="<<strlen(raw)<<endl;
	char* tmp;
	tmp=encoded[0];
	int count=0;
	while(strcmp(tmp,"00")!=0){
		count++;	
		tmp=encoded[count];
	}

	if(count!=strlen(raw)){
		#ifdef MODULE_DEBUG
		cerr<<"count!=strlen(raw)!!!!"<<endl;
		#endif
		debugMsg="[CUrlDecoder]Fatal:number not matched!";
		return false;
	}

	for(int i=0;i<strlen(raw);i++){
		m_decodeMap.insert(pair<string,char>(string(encoded[i]),raw[i]));
	}

	m_inited=true;
	//cerr<<"decode size="<<sizeof(decoded)<<endl;
	return true;
}

void CUrlDecoder::printMap(){
	map<string,char>::const_iterator it;
	for(it=m_decodeMap.begin();it!=m_decodeMap.end();++it){
		cout<<it->first<<" -> "<<it->second<<endl;
	}
}
