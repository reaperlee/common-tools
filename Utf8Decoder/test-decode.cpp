#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>

using namespace std;

static bool decodeString( char* token, int size,string &decoded );
static bool decodeUnicodeCodePoint( char* token,char*& current,char* end,unsigned int &unicode );
static std::string codePointToUTF8(unsigned int cp);
static bool decodeUnicodeEscapeSequence( char* token,char*& current,char* end,unsigned int &unicode );

static bool decodeString( char* token, int size,string &decoded )
{
	//decoded.reserve(size-2);
	char* current = token; // skip '"'
	char* end = token+size-1;      // do not include '"'
	while ( current != end )
	{
		char c = *current++;
		if ( c == '"' )
			break;  
		else if ( c == '\\' )
		{
			if ( current == end )
				return cerr<<"Empty escape sequence in string"<<endl;
			char escape = *current++;
			switch ( escape )
			{       
				case '"': decoded += '"'; break;
				case '/': decoded += '/'; break;
				case '\\': decoded += '\\'; break;
				case 'b': decoded += '\b'; break;
				case 'f': decoded += '\f'; break;
				case 'n': decoded += '\n'; break;
				case 'r': decoded += '\r'; break;
				case 't': decoded += '\t'; break;
				case 'u':
						  {       
							  unsigned int unicode;
							  if ( !decodeUnicodeCodePoint( token, current, end, unicode ) )
								  return false;
							  decoded += codePointToUTF8(unicode);
							  fprintf(stderr,"unicode=%x\n",unicode);
						  }       
						  break;  
				default:
						  return cerr<<"Bad escape sequence in string"<<endl;
			}       
		}
		else    
		{
			decoded += c;
		}
	}
	return true;
}

static bool decodeUnicodeCodePoint( char* token,char*& current,char* end,unsigned int &unicode )
{
	if ( !decodeUnicodeEscapeSequence( token, current, end, unicode ) )
		return false;
	if (unicode >= 0xD800 && unicode <= 0xDBFF)
	{
		// surrogate pairs
		if (end - current < 6)
			return cerr<<"additional six characters expected to parse unicode surrogate pair."<<endl;
		unsigned int surrogatePair;
		if (*(current++) == '\\' && *(current++)== 'u')
		{
			if (decodeUnicodeEscapeSequence( token, current, end, surrogatePair ))
			{
				unicode = 0x10000 + ((unicode & 0x3FF) << 10) + (surrogatePair & 0x3FF);
			}
			else
				return false;
		}
		else
			return cerr<<"expecting another \\u token to begin the second half of a unicode surrogate pair"<<endl;
	}
	return true;
}

static bool decodeUnicodeEscapeSequence( char* token,char*& current,char* end,unsigned int &unicode )
{
	if ( end - current < 4 )
		return cerr<<"Bad unicode escape sequence in string: four digits expected."<<endl;
	unicode = 0;
	for ( int index =0; index < 4; ++index )
	{
		char c = *current++;
		unicode *= 16;
		if ( c >= '0'  &&  c <= '9' )
			unicode += c - '0';
		else if ( c >= 'a'  &&  c <= 'f' )
			unicode += c - 'a' + 10;
		else if ( c >= 'A'  &&  c <= 'F' )
			unicode += c - 'A' + 10;
		else
			return cerr<<"Bad unicode escape sequence in string: hexadecimal digit expected."<<endl;
	}
	return true;
}

static std::string codePointToUTF8(unsigned int cp)
{     
	std::string result;

	// based on description from http://en.wikipedia.org/wiki/UTF-8

	if (cp <= 0x7f)  
	{  
		result.resize(1);
		result[0] = static_cast<char>(cp);
	} 
	else if (cp <= 0x7FF)
	{
		result.resize(2);
		result[1] = static_cast<char>(0x80 | (0x3f & cp));
		result[0] = static_cast<char>(0xC0 | (0x1f & (cp >> 6)));
	}              
	else if (cp <= 0xFFFF)  
	{
		result.resize(3);
		result[2] = static_cast<char>(0x80 | (0x3f & cp));
		result[1] = 0x80 | static_cast<char>((0x3f & (cp >> 6)));
		result[0] = 0xE0 | static_cast<char>((0xf & (cp >> 12)));
	}
	else if (cp <= 0x10FFFF)
	{
		result.resize(4);
		result[3] = static_cast<char>(0x80 | (0x3f & cp));
		result[2] = static_cast<char>(0x80 | (0x3f & (cp >> 6)));
		result[1] = static_cast<char>(0x80 | (0x3f & (cp >> 12)));
		result[0] = static_cast<char>(0xF0 | (0x7 & (cp >> 18)));
	}

	return result;
}

int main(int argc,char* argv[]){
	if(argc!=2){
		cerr<<"Usage:"<<argv[0]<<" [encoded-string]"<<endl;
		return 1;
	}
	char buffer[1024]={0};	
	
	memcpy(buffer,argv[1],strlen(argv[1]));
	string decodeStr;

	//decodeString(buffer,strlen(buffer)+1,decodeStr);
	decodeString(buffer,strlen(buffer)+1,decodeStr);

	cout<<"decodeStr="<<decodeStr<<endl;
	return 0;

}
