#ifndef _MYHTTPPARSER_H
#define _MYHTTPPARSER_H

#include<string>
#include<map>
using namespace std;
namespace MyHttp{

class CHttpParser{
private:
	//http header parse states
	enum{
		STATE_FINISH,
		STATE_READ_START_LINE,
		STATE_READ_HEADER_LINE,
		STATE_READ_CRLF,
		STATE_READ_POSTDATA
	};
	//start line parse states
	enum{
		STATE_FIND_METHOD=1,
		STATE_FIND_URL,
		STATE_FIND_HTTP_PROTOCOL,
		STATE_FIND_CR_STARTLINE,
		STATE_FIND_LF_STARTLINE
	};
	//head line parse states
	enum{
		STATE_FIND_KEY,
		STATE_FIND_SEP,
		STATE_FIND_VALUE,
		STATE_FIND_CR_HEADLINE,
		STATE_FIND_LF_HEADLINE
	};
	//http errors
	enum{
		//check complete errors

		//header parse errors
		ERROR_UNCOMPLETE_HTTPPACKAGE= -1,
		ERROR_NO_CONTENTLEN_POST=-3,
		ERROR_ILLEGAL_CONTENTLEN_POST=-4,
		//start line errors start at -20
		ERROR_UNCOMPLETE_STARTLINE=-20,
		ERROR_UNSUPPORT_HTTP_METHOD=-21,
		//head line errors
		ERROR_UNCOMPLETE_HEADLINE=-30,
	};
	unsigned int m_state;
	unsigned int m_currentPos;
	unsigned int m_parseStartPos;
	map<string, string>	m_headerMap;
	unsigned int m_contentLen;
	bool m_isStrictMode;
	string m_postData;

	unsigned int m_startLineSubState;
	string m_url;
	string m_strHttpMethod;
	string m_strHttpProtocol;
	unsigned int m_httpMethod;

	unsigned int m_headLineSubState;
	string m_currentKey;
	string m_currentValue;

	int parseUnStrict(const char* data,size_t dataLen);
	int parseStrict(const char* data,size_t dataLen);
	int parseStartLine(char currentChar);
	int parseHeaderLine(char currentChar);
	void getContentLength();

	static int checkCompleteStrict(const char* data,size_t dataLen);
	static int checkCompleteUnStrict(const char* data,size_t dataLen);
	void clearStartLineState();
	void clearHeadLineState();
		
public:
	//supported http methods
	enum{
		HTTP_METHOD_UNKNOW = 0,
		HTTP_METHOD_GET,
		HTTP_METHOD_POST
	};
	CHttpParser(){
		m_state = STATE_READ_START_LINE;
		m_startLineSubState = STATE_FIND_METHOD;
		m_headLineSubState = STATE_FIND_KEY;
		m_httpMethod = HTTP_METHOD_UNKNOW;
		m_url = "";
		m_strHttpMethod = "";
		m_strHttpProtocol = "";
		m_currentPos = 0;
		m_parseStartPos = 0;
		m_headerMap.clear();
		m_contentLen = 0;
		this->m_isStrictMode = true;
	}
	~CHttpParser(){

	}
	/*解析Http请求串
	@param data 原始字节流	
	@param dataLen 原始字节流的长度
	@returns 0:成功 1:还需要额外的数据 <0:解析失败
	注：若将该类声明为一个全局的变量，则应在每次解析成功和失败之后调用clearStates清除内部的状态机
	*/
	int parse(const char* data,size_t dataLen);
	/*设置为非严格解析模式（匹配单一换行符的结尾）
	@param none
	@returns none
	*/
	void setUnstrictMode();
	/*检查HTTP包的完整性
	@param data 原始字节流
	@param dataLen 原始字节流的长度
	@returns 0:还需要额外的数据 >0数据包的长度 <0
	*/
	static int checkComplete(const char* data,size_t dataLen,bool strictMode=true);
	/*清除上次http解析的状态机等中间数据
	*/
	void clearStates();
	/*格式化输出头部的内容
	
	*/
	void printFormatedHeader()const;
	/*返回http方法
	@return HTTP_METHOD_GET:GET 方法 HTTP_METHOD_POST:Post方法
	*/
	int httpMethod()const{
		return this->m_httpMethod;
	}
	/*返回HTTP的头部字段
	@param key 头部字段的名字
	@param str 返回的字段value
	@returns true:成功 false:失败，无key所指示的字段
	*/
	bool getValueOfHeader(const string& key,string& str)const;
	/*返回HTTP的头部字段
	@param key 头部字段的名字
	@param val 返回的字段value
	@returns true:成功 false:失败，无key所指示的字段
	*/
	bool getValueOfHeader(const string& key,long int *str)const;
	/*返回HTTP的头部字段
	@param key 头部字段的名字
	@param val 返回的字段value
	@returns true:成功 false:失败，无key所指示的字段
	*/
	bool getValueOfHeader(const string& key,int *str)const;
	/*返回HTTP的头部字段
	@param key 头部字段的名字
	@param val 返回的字段value
	@returns true:成功 false:失败，无key所指示的字段
	*/
	bool getValueOfHeader(const string& key, unsigned int *str)const;
	/*返回HTTP的url
	@returns http的url
	*/
	string getUrl()const{
		return m_url;
	}
};
}
#endif