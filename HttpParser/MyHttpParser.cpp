#include "MyHttpParser.h"
#include<iostream>
#include<string>
#include<map>

using namespace std;
using namespace MyHttp;

int CHttpParser::parseUnStrict(const char* data,size_t dataLen){
	return 0;
}

int CHttpParser::parseStrict(const char* data,size_t dataLen){
	int ret = 0;
	if (m_parseStartPos>=dataLen){//
		clearStates();
		return ERROR_UNCOMPLETE_HTTPPACKAGE;
	}

	for (m_currentPos=m_parseStartPos; m_currentPos < dataLen;m_currentPos++){
		switch (this->m_state)
		{
		case STATE_READ_START_LINE:
			ret = parseStartLine(data[m_currentPos]);
			if (ret>0){
				m_state = STATE_READ_HEADER_LINE;
			}
			else if (ret==0){
				
			}
			else{
				clearStates();
				return ret;
			}
			break;
		case STATE_READ_HEADER_LINE:
			ret = parseHeaderLine(data[m_currentPos]);
			if (ret==1){
				clearHeadLineState();
			}
			else if(ret==2){//an empty line parsed
				clearHeadLineState();
				if (m_httpMethod==HTTP_METHOD_GET){//for HTTP GET method,this is an end of the package
					//clearStates();
					return 0;
				}
				else if (m_httpMethod==HTTP_METHOD_POST){
					getContentLength();
					if (m_contentLen==0){
						clearStates();
						return ERROR_NO_CONTENTLEN_POST;
					}
					m_state = STATE_READ_POSTDATA;
				}
				else {
					clearStates();
					return ERROR_UNSUPPORT_HTTP_METHOD;
				}
			}
			else if (ret==0){

			}
			else{
				clearStates();
				return ret;
			}
			break;
		case STATE_READ_POSTDATA:
			m_postData += data[m_currentPos];
			if (m_postData.size()==m_contentLen){
				return 0;
			}
			//here!!!!!
			break;
		default:
			break;
		}

	}
	m_parseStartPos = m_currentPos;
	return 1;
}

int CHttpParser::parse(const char* data, size_t dataLen){
	if (this->m_isStrictMode){
		return this->parseStrict(data,dataLen);
	}
	return this->parseUnStrict(data,dataLen);
}

void CHttpParser::setUnstrictMode(){
	this->m_isStrictMode = false;
}

int CHttpParser::parseHeaderLine(char currentChar){
	if (currentChar=='\r'){
		m_headLineSubState = STATE_FIND_CR_HEADLINE;
	}
	else if (currentChar == '\n'){
		if (m_headLineSubState==STATE_FIND_LF_HEADLINE){
			
		}
		else{
			return ERROR_UNCOMPLETE_HEADLINE;
		}
	}
	else{

	}

	switch (m_headLineSubState)
	{
	case STATE_FIND_KEY:
		if (currentChar!=':'){
			m_currentKey += currentChar;
		}
		else{
			if (m_currentKey.empty()){
				return ERROR_UNCOMPLETE_HEADLINE;
			}
			m_headLineSubState = STATE_FIND_SEP;
		}
		break;
	case STATE_FIND_SEP:
		if (currentChar==' '){
			break;
		}
		else{
			m_headLineSubState = STATE_FIND_VALUE;
		}
	case STATE_FIND_VALUE:
		m_currentValue += currentChar;
		break;
	case STATE_FIND_CR_HEADLINE:
		m_headLineSubState = STATE_FIND_LF_HEADLINE;
		break;
	case STATE_FIND_LF_HEADLINE:
		if (currentChar == '\n'){
			if (!m_currentKey.empty()&&!m_currentValue.empty()){
				m_headerMap[m_currentKey] = m_currentValue;
				return 1;
			}
			else if (m_currentKey.empty()&&m_currentValue.empty()){//this is an empty header,so it's actually a end separater
				return 2;
			}
			else{
				return ERROR_UNCOMPLETE_HEADLINE;
			}
		}
		else{
			return ERROR_UNCOMPLETE_HEADLINE;
		}
		break;
	default:
		break;
	}
	return 0;
}

int CHttpParser::parseStartLine(char currentChar){
	if (currentChar=='\r'){
		if (m_startLineSubState==STATE_FIND_HTTP_PROTOCOL){
			m_startLineSubState = STATE_FIND_CR_STARTLINE;
		}
		else{
			return ERROR_UNCOMPLETE_STARTLINE;
		}
	}
	else if (currentChar=='\n'){
		if (m_startLineSubState!=STATE_FIND_LF_STARTLINE){
			return ERROR_UNCOMPLETE_STARTLINE;
		}
	}
	else{

	}

	switch (m_startLineSubState){
	case STATE_FIND_METHOD:
		if (currentChar!= ' '){
			this->m_strHttpMethod += currentChar;
		}
		else{//found space between method and url
			if (this->m_strHttpMethod.compare("POST") == 0){
				this->m_httpMethod = HTTP_METHOD_POST;
				this->m_startLineSubState = STATE_FIND_URL;
			}
			else if (this->m_strHttpMethod.compare("GET") == 0){
				this->m_httpMethod = HTTP_METHOD_GET;
				this->m_startLineSubState = STATE_FIND_URL;
			}
			else{
				this->m_httpMethod = HTTP_METHOD_UNKNOW;
				return ERROR_UNSUPPORT_HTTP_METHOD;
			}
		}
		break;
	case STATE_FIND_URL:
		if (currentChar != ' '){
			this->m_url += currentChar;
		}
		else{//found the space between url and HTTP protocol
			this->m_startLineSubState = STATE_FIND_HTTP_PROTOCOL;
		}
		break;
	case STATE_FIND_HTTP_PROTOCOL:
		this->m_strHttpProtocol += currentChar;
		break;
	case STATE_FIND_CR_STARTLINE:
		//
		m_startLineSubState = STATE_FIND_LF_STARTLINE;
		break;
	case STATE_FIND_LF_STARTLINE:
		if (currentChar=='\n'){
			if (!m_url.empty()&&
				!m_strHttpProtocol.empty()){
				return 1;
			}
			else{
				return ERROR_UNCOMPLETE_STARTLINE;
			}

		}
		else{
			return ERROR_UNCOMPLETE_STARTLINE;
		}
		break;
	default:
		break;
	}
	return 0;
}


void CHttpParser::getContentLength(){
	map<string, string>::const_iterator it;
	it = m_headerMap.find("Content-Length");
	if (it!=m_headerMap.end()){//found it
		m_contentLen=atol(it->second.c_str());
	}
	else{
		m_contentLen = 0;
	}
}

int CHttpParser::checkCompleteStrict(const char* data,size_t dataLen){
	if (data==NULL){
		return -1;
	}
	if (dataLen==0){
		return 0;
	}
	string httpHeader = data;
	size_t CRLFPos = -1;
	CRLFPos = httpHeader.find("\r\n\r\n");
	if (CRLFPos==string::npos){
		return 0;
	}
	size_t headerLen = CRLFPos + 4;
	size_t contentLengthPos = -1;
	bool colonFound = false;
	bool readingNum = false;
	bool trueContentLength = false;
	string numStr = "";
	size_t i = 0;
	do{
		colonFound = false;
		readingNum = false;
		numStr = "";

		contentLengthPos = httpHeader.find("Content-Length", i);
		if (contentLengthPos == string::npos){//this should be a GET request
			if (httpHeader.compare(0,4,"POST")==0){//A post request but No Content-length,error
				return ERROR_NO_CONTENTLEN_POST;
			}
			return headerLen;
		}

		for (i = contentLengthPos + 14; i < dataLen; i++){
			if (!colonFound){//need to find colon first
				if (data[i]==':'){
					colonFound = true;
					continue;
				}
				else if (data[i]==' '){
					break;
				}
				else{//this head key is actually not Content-length,it's Content-lengthxxx
					break;
				}
			}
			else{
				if (readingNum){
					if (data[i]>='0'&&data[i]<='9'){
						numStr += data[i];
					}
					else if(data[i]=='\r'){
						goto PARSE_END;
					}
					else{
						return ERROR_ILLEGAL_CONTENTLEN_POST;
					}
				}
				else{
					if (data[i]>='0'&&data[i]<='9'){
						readingNum = true;
						numStr += data[i];
					}
					else if(data[i]==' '){
						continue;
					}
					else{
						return ERROR_ILLEGAL_CONTENTLEN_POST;
					}
				}
			}
		}

		if (colonFound){
			break;
		}
	}while (i<dataLen);
PARSE_END:	
	if (numStr.size()==0){
		return ERROR_ILLEGAL_CONTENTLEN_POST;
	}
	int contentLength = atol(numStr.c_str());
	if (contentLength+headerLen==dataLen){
		return (contentLength+headerLen);
	}
	return 0;
}

int CHttpParser::checkCompleteUnStrict(const char* data,size_t dataLen){
	return 0;

}
int CHttpParser::checkComplete(const char* data,size_t dataLen,bool strictMode){
	if (strictMode){
		return CHttpParser::checkCompleteStrict(data,dataLen);
	}
	return CHttpParser::checkCompleteUnStrict(data,dataLen);
}

void CHttpParser::printFormatedHeader()const{
	map<string, string>::const_iterator headMapIt;
	if (m_httpMethod==HTTP_METHOD_GET){
		cout << "This is a GET request" << endl;
		cout << "uri:" << m_url << endl;
		cout << "Http Protocol Verison:" << m_strHttpProtocol << endl;
		cout << "head lines:\n";
		for (headMapIt = m_headerMap.begin(); headMapIt != m_headerMap.end();++headMapIt){
			cout << "key=" << headMapIt->first << "|value=" << headMapIt->second << endl;
		}
	}
	else if (m_httpMethod==HTTP_METHOD_POST){
		cout << "This is a POST request" << endl;
		cout << "uri:" << m_url << endl;
		cout << "Http Protocol Verison:" << m_strHttpProtocol << endl;
		cout << "head lines:\n";
		for (headMapIt = m_headerMap.begin(); headMapIt != m_headerMap.end();++headMapIt){
			cout << "key=" << headMapIt->first << "|value=" << headMapIt->second << endl;
		}
		cout << "Content-Length=" << m_contentLen << endl;
		cout << "postdata:" << m_postData << endl;

	}
	else{
		cout << "Unsupported Http Method!" << endl;
	}
}

bool CHttpParser::getValueOfHeader(const string& key, string& val)const{
	map<string, string>::const_iterator headMapIt;
	headMapIt = m_headerMap.find(key);
	if (headMapIt!=m_headerMap.end()){
		val = headMapIt->second;
		return true;
	}
	return false;
}

bool CHttpParser::getValueOfHeader(const string& key,long int * val)const{
	map<string, string>::const_iterator headMapIt;
	headMapIt = m_headerMap.find(key);
	if (headMapIt!=m_headerMap.end()){
		*val = atol(headMapIt->second.c_str());
		return true;
	}
	return false;
}

bool CHttpParser::getValueOfHeader(const string& key,int * val)const{
	map<string, string>::const_iterator headMapIt;
	headMapIt = m_headerMap.find(key);
	if (headMapIt!=m_headerMap.end()){
		*val = atoi(headMapIt->second.c_str());
		return true;
	}
	return false;
}

bool CHttpParser::getValueOfHeader(const string& key,unsigned int * val)const{
	map<string, string>::const_iterator headMapIt;
	headMapIt = m_headerMap.find(key);
	if (headMapIt != m_headerMap.end()){
		*val = atol(headMapIt->second.c_str());
		return true;
	}
	return false;
}
//clear state functions

void CHttpParser::clearStates(){
	//clear head line state
	clearHeadLineState();
	//clearStartLineState
	m_startLineSubState = STATE_FIND_METHOD;
	m_httpMethod = HTTP_METHOD_UNKNOW;
	m_url = "";
	m_strHttpProtocol = "";
	m_strHttpMethod = "";
	
	//clear common state
	m_state = STATE_READ_START_LINE;
	m_startLineSubState = STATE_FIND_METHOD;
	m_headLineSubState = STATE_FIND_KEY;
	m_currentPos = 0;
	m_parseStartPos = 0;
	m_headerMap.clear();
	m_contentLen = 0;
	m_postData = "";
}

void CHttpParser::clearStartLineState(){
	
}

void CHttpParser::clearHeadLineState(){
	m_currentKey = "";
	m_currentValue = "";
	m_headLineSubState = STATE_FIND_KEY;
}
