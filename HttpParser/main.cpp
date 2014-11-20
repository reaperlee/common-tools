#include<iostream>
#include<string>
#include "MyHttpParser.h"

using namespace std;
using namespace MyHttp;

//GET ��������
string generateTestGetHeader1(){
	string header;
	header += "GET /test?cmd=1&key=value HTTP/1.1\r\n";
	header += "Host: test.qq.com\r\n";
	header += "\r\n";
	return header;
}

string generateTestGetHeader2(){
	string header;
	header += "GET /test?cmd=1 HTTP/1.1\r\n\r\n";
	return header;
}
//������������
string generateTestGetHeader3(){
	return "\r\n\r\n"; 
}
//������������
string generateTestGetHeader4(){
	return "\r";
}
//�Ϸ���GET����
string generateTestGetHeader5(){
	string header;
	header += "GET /test?key1=value1&key2=value2 HTTP/1.1\r\n";
	header += "Host:test.qq.video.com\r\n";
	header += "Accept: */*\r\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//�Ƿ���GET���󡪡����в�����������Http����
string generateTestGetHeader6(){
	string header;
	header += "/test?key1=value1&key2=value2 HTTP/1.1\r\n";
	header += "Host:test.qq.video.com\r\n";
	header += "Accept: */*\r\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//�Ƿ���GET���󡪡����в����������޿ո�ָ�
string generateTestGetHeader7(){
	string header;
	header += "GET/test?key1=value1&key2=value2HTTP/1.1\r\n";
	header += "Host:test.qq.video.com\r\n";
	header += "Accept: */*\r\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//�Ƿ���GET���󡪡����в���������һ���ո�ָ�
string generateTestGetHeader8(){
	string header;
	header += "GET /test?key1=value1&key2=value2HTTP/1.1\r\n";
	header += "Host:test.qq.video.com\r\n";
	header += "Accept: */*\r\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//�Ƿ���GET���󡪡����в�����������\r
string generateTestGetHeader9(){
	string header;
	header += "GET /test?key1=value1&key2=value2 HTTP/1.1\n";
	header += "Host:test.qq.video.com\r\n";
	header += "Accept: */*\r\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//�Ƿ���GET���󡪡����в�����������\n
string generateTestGetHeader10(){
	string header;
	header += "GET /test?key1=value1&key2=value2 HTTP/1.1\r";
	header += "Host:test.qq.video.com\r\n";
	header += "Accept: */*\r\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//�Ƿ���GET���󡪡����в�����������\r\n
string generateTestGetHeader11(){
	string header;
	header += "GET /test?key1=value1&key2=value2 HTTP/1.1";
	header += "Host:test.qq.video.com\r\n";
	header += "Accept: */*\r\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//�Ƿ���GET���󡪡�headline������������ð��
string generateTestGetHeader12(){
	string header;
	header += "GET /test?key1=value1&key2=value2 HTTP/1.1\r\n";
	header += "Hosttest.qq.video.com\r\n";
	header += "Accept: */*\r\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//�Ƿ���GET���󡪡�headline������������\r
string generateTestGetHeader13(){
	string header;
	header += "GET /test?key1=value1&key2=value2 HTTP/1.1\r\n";
	header += "Host:test.qq.video.com\r\n";
	header += "Accept: */*\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//�Ƿ���GET���󡪡�headline������������\n
string generateTestGetHeader14(){
	string header;
	header += "GET /test?key1=value1&key2=value2 HTTP/1.1\r\n";
	header += "Host:test.qq.video.com\r";
	header += "Accept: */*\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//�Ƿ���GET���󡪡�ͷ��������������\r\n
string generateTestGetHeader15(){
	string header;
	header += "GET /test?key1=value1&key2=value2 HTTP/1.1\r\n";
	header += "Host:test.qq.video.com\r\n";
	header += "Accept: */*\r\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "";
	return header;
}
//�Ƿ���GET���󡪡�ͷ��������������\r\n
string generateTestGetHeader16(){
	string header;
	header += "GET /test?key1=value1&key2=value2 HTTP/1.1\r\n";
	header += "Host:test.qq.video.com\r\n";
	header += "Accept: */*\r\n";
	header += "Connection:   close\r\n";
	header += "Testkey:testvalue\r\n";
	header += "\r\n";
	return header;
}
//POST ��������
//Content-length��value֮��һ��ð���޸��ո�
string generateTestPostHeader1(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Content-length:12\r\n";
	header += "Accept:*/*\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;
}
//Content-length��value֮��һ��ð�Ŷ���ո�
string generateTestPostHeader2(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Content-length:                            12\r\n";
	header += "Accept:*/*\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;
}
//Content-length��value֮��һ��ð��һ���ո�
string generateTestPostHeader3(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Content-length: 12\r\n";
	header += "Accept:*/*\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//Content-length��value֮����ð��
string generateTestPostHeader4(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Content-length12\r\n";
	header += "Accept:*/*\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//Content-length��value֮����ð��
string generateTestPostHeader5(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Content-length\r\n";
	header += "Accept:*/*\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;
}
//Content-length��valueΪ��
string generateTestPostHeader6(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Content-length:\r\n";
	header += "Accept:*/*\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;
}
//Content-length��value���ǺϷ�������
string generateTestPostHeader7(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Content-length:aaaa\r\n";
	header += "Accept:*/*\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;
}
//Content-length��value���ǺϷ�������
string generateTestPostHeader8(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Content-length:12aaaa\r\n";
	header += "Accept:*/*\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;
}
//formdata ������
string generateTestPostHeader9(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Content-length:12\r\n";
	header += "Accept:*/*\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;
}
//��Content-length�ֶ�
string generateTestPostHeader10(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Accept:*/*\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;
}

//Content-length�ֶ�Ϊ��
string generateTestPostHeader11(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Accept:*/*\r\n";
	header += "Content-length:   \r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}

//Method�ֶ�Ϊ��
string generateTestPostHeader12(){
	string header;
	header += " /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Accept:*/*\r\n";
	header += "Content-length:12\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//�� Method�ֶ�
string generateTestPostHeader13(){
	string header;
	header += "/test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Accept:*/*\r\n";
	header += "Content-length:12\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//startline�޿ո�
string generateTestPostHeader14(){
	string header;
	header += "/test?aaa=bbb&ccc=dddHTTP/1.1";
	header += "Host:aaa.qq.com\r\n";
	header += "Accept:*/*\r\n";
	header += "Content-length:12\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//startline��\n
string generateTestPostHeader15(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r";
	header += "Host:aaa.qq.com\r\n";
	header += "Accept:*/*\r\n";
	header += "Content-length:12\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//startline��\r
string generateTestPostHeader16(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Accept:*/*\r\n";
	header += "Content-length:12\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//headline ��\r\n
string generateTestPostHeader17(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com";
	header += "Accept:*/*\r\n";
	header += "Content-length:12\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//headline ��\r
string generateTestPostHeader18(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\n";
	header += "Accept:*/*\r\n";
	header += "Content-length:12\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//headline ��\n
string generateTestPostHeader19(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r";
	header += "Accept:*/*\r\n";
	header += "Content-length:12\r\n";
	header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//headline ��\r\n
string generateTestPostHeader20(){
	string header;
	header += "POST /test?aaa=bbb&ccc=ddd HTTP/1.1\r\n";
	header += "Host:aaa.qq.com\r\n";
	header += "Accept:*/*\r\n";
	header += "Content-length:12\r\n";
	//header += "\r\n";
	header += "aaaabbbbcccc";
	return header;

}
//�����Բ���
static void testCheckComplete(){
	int ret;
	string header;
	
	//GET requests
	header= generateTestGetHeader1();
	ret = CHttpParser::checkComplete(header.c_str(),header.size());
	cout << "GET Case 1:header size="<<header.size()<<" check complete returned:" << ret << endl;
	
	header = generateTestGetHeader2();
	ret = CHttpParser::checkComplete(header.c_str(),header.size());
	cout << "GET Case 2:header size="<<header.size()<<" check complete returned:" << ret << endl;

	header = generateTestGetHeader3();
	ret = CHttpParser::checkComplete(header.c_str(),header.size());
	cout << "GET Case 3:header size="<<header.size()<<" check complete returned:" << ret << endl;

	//POST requests
	header = generateTestPostHeader1();
	ret = CHttpParser::checkComplete(header.c_str(),header.size());
	cout << "POST Case 1:header size="<<header.size()<<" check complete returned:" << ret << endl;

	header = generateTestPostHeader2();
	ret = CHttpParser::checkComplete(header.c_str(),header.size());
	cout << "POST Case 2:header size="<<header.size()<<" check complete returned:" << ret << endl;

	header = generateTestPostHeader3();
	ret = CHttpParser::checkComplete(header.c_str(),header.size());
	cout << "POST Case 3:header size="<<header.size()<<" check complete returned:" << ret << endl;

	header = generateTestPostHeader4();
	ret = CHttpParser::checkComplete(header.c_str(),header.size());
	cout << "POST Case 4:header size="<<header.size()<<" check complete returned:" << ret << endl;

	header = generateTestPostHeader5();
	ret = CHttpParser::checkComplete(header.c_str(),header.size());
	cout << "POST Case 5:header size="<<header.size()<<" check complete returned:" << ret << endl;

	header = generateTestPostHeader6();
	ret = CHttpParser::checkComplete(header.c_str(),header.size());
	cout << "POST Case 6:header size="<<header.size()<<" check complete returned:" << ret << endl;

	header = generateTestPostHeader7();
	ret = CHttpParser::checkComplete(header.c_str(), header.size());
	cout << "POST Case 7:header size=" << header.size() << " check complete returned:" << ret << endl;

	header = generateTestPostHeader8();
	ret = CHttpParser::checkComplete(header.c_str(), header.size());
	cout << "POST Case 8:header size=" << header.size() << " check complete returned:" << ret << endl;

	header = generateTestPostHeader9();
	ret = CHttpParser::checkComplete(header.c_str(), header.size());
	cout << "POST Case 9:header size=" << header.size() << " check complete returned:" << ret << endl;

	header = generateTestPostHeader10();
	ret = CHttpParser::checkComplete(header.c_str(), header.size());
	cout << "POST Case 10:header size=" << header.size() << " check complete returned:" << ret << endl;

}

//HTTP GETͷ����������
static void testParseGet(){
	int ret;
	CHttpParser httpParser;
	string header;

	//GET case 1
	header = generateTestGetHeader1();
	ret = httpParser.parse(header.c_str(),header.size());
	cout << "GET Parse Case 1:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret==0){
		httpParser.printFormatedHeader();
	}
	else if (ret==1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 2
	header = generateTestGetHeader2();
	ret = httpParser.parse(header.c_str(),header.size());
	cout << "GET Parse Case 2:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret==0){
		httpParser.printFormatedHeader();
	}
	else if (ret==1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();

	//GET case 3
	header = generateTestGetHeader3();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 3:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 4
	header = generateTestGetHeader4();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 4:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 5
	header = generateTestGetHeader5();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 5:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 6
	header = generateTestGetHeader6();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 6:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 7
	header = generateTestGetHeader7();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 7:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 8
	header = generateTestGetHeader8();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 8:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 9
	header = generateTestGetHeader9();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 9:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;
	//GET case 10
	header = generateTestGetHeader10();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 10:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 11
	header = generateTestGetHeader11();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 11:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 12
	header = generateTestGetHeader12();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 12:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 13
	header = generateTestGetHeader13();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 13:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 14
	header = generateTestGetHeader14();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 14:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 15
	header = generateTestGetHeader15();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 15:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//GET case 16
	header = generateTestGetHeader16();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "GET Parse Case 16:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;
}
//HTTP POSTͷ����������
static void testParsePost(){
	int ret;
	CHttpParser httpParser;
	string header;

	//POST case 1
	header = generateTestPostHeader1();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 1:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 2
	header = generateTestPostHeader2();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 2:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 3
	header = generateTestPostHeader3();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 2:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 4
	header = generateTestPostHeader4();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 4:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 5
	header = generateTestPostHeader5();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 5:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 6
	header = generateTestPostHeader6();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 6:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 7
	header = generateTestPostHeader7();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 7:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 8
	header = generateTestPostHeader8();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 8:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 9
	header = generateTestPostHeader9();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 9:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 10
	header = generateTestPostHeader10();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 10:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 11
	header = generateTestPostHeader11();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 11:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 12
	header = generateTestPostHeader12();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 12:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 13
	header = generateTestPostHeader13();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 13:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 14
	header = generateTestPostHeader14();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 14:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 15
	header = generateTestPostHeader15();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 15:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 16
	header = generateTestPostHeader16();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 16:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 17
	header = generateTestPostHeader17();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 17:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 18
	header = generateTestPostHeader18();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 18:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 19
	header = generateTestPostHeader19();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 19:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 20
	header = generateTestPostHeader20();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 20:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;

	//POST case 1
	header = generateTestPostHeader1();
	ret = httpParser.parse(header.c_str(), header.size());
	cout << "POST Parse Case 1:header size=" << header.size() << " parse returned:" << ret << endl;
	if (ret == 0){
		httpParser.printFormatedHeader();
	}
	else if (ret == 1){
		cout << "Not Completed!" << endl;
	}
	else{
		cout << "Parse Error!" << endl;
	}
	httpParser.clearStates();
	cout << endl;
}
int main(int argc,char* argv[]){
	//testCheckComplete();
	//testParseGet();
	testParsePost();
	getchar();
	return 0;
}