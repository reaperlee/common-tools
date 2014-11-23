#include"UrlDecoder.h"
#include<iostream>
#include<string>

using namespace std;

int main(int argc,char* argv[]){
	if(argc!=2){
		cerr<<"Usage:main [encoded str]"<<endl;
		return 1;
	}
	CUrlDecoder decoder;

	string debugMsg;
	string encodedStr=argv[1];
	string strAfterDecode;
	if(!decoder.init(debugMsg)){
		cerr<<"init failed:"<<debugMsg<<endl;
		return 1;
	}
	
	cout<<"Before:"<<encodedStr<<endl;
	decoder.decode(encodedStr,strAfterDecode);
	cout<<"After :"<<strAfterDecode<<endl;
	return 0;
}
