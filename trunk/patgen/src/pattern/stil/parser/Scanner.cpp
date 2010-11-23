

#include <memory.h>
#include <string.h>
#include "Scanner.h"

// string handling, wide character

char* coco_string_create_wchar(const char* value) {
	char* data;
	int len = 0;
	if (value) { len = strlen(value); }
	data = new char[len + 1];
	strncpy(data, value, len);
	data[len] = 0;
	return data;
}

char* coco_string_create(const char *value , int startIndex, int length) {
	int len = 0;
	char* data;

	if (value) { len = length; }
	data = new char[len + 1];
	strncpy(data, &(value[startIndex]), len);
	data[len] = 0;

	return data;
}

char* coco_string_create_upper(const char* data) {
	if (!data) { return NULL; }

	int dataLen = 0;
	if (data) { dataLen = strlen(data); }

	char *newData = new char[dataLen + 1];

	for (int i = 0; i <= dataLen; i++) {
		if (('a' <= data[i]) && (data[i] <= 'z')) {
			newData[i] = data[i] + ('A' - 'a');
		}
		else { newData[i] = data[i]; }
	}

	newData[dataLen] = '\0';
	return newData;
}

char* coco_string_create_lower(const char* data) {
	if (!data) { return NULL; }
	int dataLen = strlen(data);
	return coco_string_create_lower(data, 0, dataLen);
}

char* coco_string_create_lower(const char* data, int startIndex, int dataLen) {
	if (!data) { return NULL; }

	char* newData = new char[dataLen + 1];

	for (int i = 0; i <= dataLen; i++) {
		char ch = data[startIndex + i];
		if (('A' <= ch) && (ch <= 'Z')) {
			newData[i] = ch - ('A' - 'a');
		}
		else { newData[i] = ch; }
	}
	newData[dataLen] = '\0';
	return newData;
}

char* coco_string_create_append(const char* data1, const char* data2) {
	char* data;
	int data1Len = 0;
	int data2Len = 0;

	if (data1) { data1Len = strlen(data1); }
	if (data2) {data2Len = strlen(data2); }

	data = new char[data1Len + data2Len + 1];

	if (data1) { strcpy(data, data1); }
	if (data2) { strcpy(data + data1Len, data2); }

	data[data1Len + data2Len] = 0;

	return data;
}

char* coco_string_create_append(const char *target, const char appendix) {
	int targetLen = coco_string_length(target);
	char* data = new char[targetLen + 2];
	strncpy(data, target, targetLen);
	data[targetLen] = appendix;
	data[targetLen + 1] = 0;
	return data;
}

void coco_string_delete_wchar(char* &data) {
	delete [] data;
	data = NULL;
}

int coco_string_length(const char* data) {
	if (data) { return strlen(data); }
	return 0;
}

bool coco_string_endswith(const char* data, const char *end) {
	int dataLen = strlen(data);
	int endLen = strlen(end);
	return (endLen <= dataLen) && (strcmp(data + dataLen - endLen, end) == 0);
}

int coco_string_indexof(const char* data, const char value) {
	const char* chr = strchr(data, value);

	if (chr) { return (chr-data); }
	return -1;
}

int coco_string_lastindexof(const char* data, const char value) {
	const char* chr = strrchr(data, value);

	if (chr) { return (chr-data); }
	return -1;
}

void coco_string_merge(char* &target, const char* appendix) {
	if (!appendix) { return; }
	char* data = coco_string_create_append(target, appendix);
	delete [] target;
	target = data;
}

bool coco_string_equal(const char* data1, const char* data2) {
	return strcmp( data1, data2 ) == 0;
}

int coco_string_compareto(const char* data1, const char* data2) {
	return strcmp(data1, data2);
}

int coco_string_hash(const char *data) {
	int h = 0;
	if (!data) { return 0; }
	while (*data != 0) {
		h = (h * 7) ^ *data;
		++data;
	}
	if (h < 0) { h = -h; }
	return h;
}

// string handling, ascii character

char* coco_string_create(const char* value) {
	int len = 0;
	if (value) { len = strlen(value); }
	char* data = new char[len + 1];
	for (int i = 0; i < len; ++i) { data[i] = (char) value[i]; }
	data[len] = 0;
	return data;
}

char* coco_string_create_char(const char *value) {
	int len = coco_string_length(value);
	char *res = new char[len + 1];
	for (int i = 0; i < len; ++i) { res[i] = (char) value[i]; }
	res[len] = 0;
	return res;
}

void coco_string_delete(char* &data) {
	delete [] data;
	data = NULL;
}




Token::Token() {
	kind = 0;
	pos  = 0;
	col  = 0;
	line = 0;
	val  = NULL;
	next = NULL;
}

Token::~Token() {
	coco_string_delete(val);
}

Buffer::Buffer(FILE* s, bool isUserStream) {
// ensure binary read on windows
#if _MSC_VER >= 1300
	_setmode(_fileno(s), _O_BINARY);
#endif
	stream = s; this->isUserStream = isUserStream;
	if (CanSeek()) {
		fseek(s, 0, SEEK_END);
		fileLen = ftell(s);
		fseek(s, 0, SEEK_SET);
		bufLen = (fileLen < MAX_BUFFER_LENGTH) ? fileLen : MAX_BUFFER_LENGTH;
		bufStart = INT_MAX; // nothing in the buffer so far
	} else {
		fileLen = bufLen = bufStart = 0;
	}
	bufCapacity = (bufLen>0) ? bufLen : MIN_BUFFER_LENGTH;
	buf = new unsigned char[bufCapacity];	
	if (fileLen > 0) SetPos(0);          // setup  buffer to position 0 (start)
	else bufPos = 0; // index 0 is already after the file, thus Pos = 0 is invalid
	if (bufLen == fileLen && CanSeek()) Close();
}

Buffer::Buffer(Buffer *b) {
	buf = b->buf;
	bufCapacity = b->bufCapacity;
	b->buf = NULL;
	bufStart = b->bufStart;
	bufLen = b->bufLen;
	fileLen = b->fileLen;
	bufPos = b->bufPos;
	stream = b->stream;
	b->stream = NULL;
	isUserStream = b->isUserStream;
}

Buffer::Buffer(const unsigned char* buf, int len) {
	this->buf = new unsigned char[len];
	memcpy(this->buf, buf, len*sizeof(unsigned char));
	bufStart = 0;
	bufCapacity = bufLen = len;
	fileLen = len;
	bufPos = 0;
	stream = NULL;
}

Buffer::~Buffer() {
	Close(); 
	if (buf != NULL) {
		delete [] buf;
		buf = NULL;
	}
}

void Buffer::Close() {
	if (!isUserStream && stream != NULL) {
		fclose(stream);
		stream = NULL;
	}
}

int Buffer::Read() {
	if (bufPos < bufLen) {
		return buf[bufPos++];
	} else if (GetPos() < fileLen) {
		SetPos(GetPos()); // shift buffer start to Pos
		return buf[bufPos++];
	} else if ((stream != NULL) && !CanSeek() && (ReadNextStreamChunk() > 0)) {
		return buf[bufPos++];
	} else {
		return EoF;
	}
}

int Buffer::Peek() {
	int curPos = GetPos();
	int ch = Read();
	SetPos(curPos);
	return ch;
}

char* Buffer::GetString(int beg, int end) {
	int len = 0;
	char *buf = new char[end - beg];
	int oldPos = GetPos();
	SetPos(beg);
	while (GetPos() < end) buf[len++] = (char) Read();
	SetPos(oldPos);
	char *res = coco_string_create(buf, 0, len);
	coco_string_delete(buf);
	return res;
}

int Buffer::GetPos() {
	return bufPos + bufStart;
}

void Buffer::SetPos(int value) {
	if ((value >= fileLen) && (stream != NULL) && !CanSeek()) {
		// Wanted position is after buffer and the stream
		// is not seek-able e.g. network or console,
		// thus we have to read the stream manually till
		// the wanted position is in sight.
		while ((value >= fileLen) && (ReadNextStreamChunk() > 0));
	}

	if ((value < 0) || (value > fileLen)) {
		printf("--- buffer out of bounds access, position: %d\n", value);
		exit(1);
	}

	if ((value >= bufStart) && (value < (bufStart + bufLen))) { // already in buffer
		bufPos = value - bufStart;
	} else if (stream != NULL) { // must be swapped in
		fseek(stream, value, SEEK_SET);
		bufLen = fread(buf, sizeof(unsigned char), bufCapacity, stream);
		bufStart = value; bufPos = 0;
	} else {
		bufPos = fileLen - bufStart; // make Pos return fileLen
	}
}

// Read the next chunk of bytes from the stream, increases the buffer
// if needed and updates the fields fileLen and bufLen.
// Returns the number of bytes read.
int Buffer::ReadNextStreamChunk() {
	int free = bufCapacity - bufLen;
	if (free == 0) {
		// in the case of a growing input stream
		// we can neither seek in the stream, nor can we
		// foresee the maximum length, thus we must adapt
		// the buffer size on demand.
		bufCapacity = bufLen * 2;
		unsigned char *newBuf = new unsigned char[bufCapacity];
		memcpy(newBuf, buf, bufLen*sizeof(unsigned char));
		delete [] buf;
		buf = newBuf;
		free = bufLen;
	}
	int read = fread(buf + bufLen, sizeof(unsigned char), free, stream);
	if (read > 0) {
		fileLen = bufLen = (bufLen + read);
		return read;
	}
	// end of stream reached
	return 0;
}

bool Buffer::CanSeek() {
	return (stream != NULL) && (ftell(stream) != -1);
}

int UTF8Buffer::Read() {
	int ch;
	do {
		ch = Buffer::Read();
		// until we find a utf8 start (0xxxxxxx or 11xxxxxx)
	} while ((ch >= 128) && ((ch & 0xC0) != 0xC0) && (ch != EoF));
	if (ch < 128 || ch == EoF) {
		// nothing to do, first 127 chars are the same in ascii and utf8
		// 0xxxxxxx or end of file character
	} else if ((ch & 0xF0) == 0xF0) {
		// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		int c1 = ch & 0x07; ch = Buffer::Read();
		int c2 = ch & 0x3F; ch = Buffer::Read();
		int c3 = ch & 0x3F; ch = Buffer::Read();
		int c4 = ch & 0x3F;
		ch = (((((c1 << 6) | c2) << 6) | c3) << 6) | c4;
	} else if ((ch & 0xE0) == 0xE0) {
		// 1110xxxx 10xxxxxx 10xxxxxx
		int c1 = ch & 0x0F; ch = Buffer::Read();
		int c2 = ch & 0x3F; ch = Buffer::Read();
		int c3 = ch & 0x3F;
		ch = (((c1 << 6) | c2) << 6) | c3;
	} else if ((ch & 0xC0) == 0xC0) {
		// 110xxxxx 10xxxxxx
		int c1 = ch & 0x1F; ch = Buffer::Read();
		int c2 = ch & 0x3F;
		ch = (c1 << 6) | c2;
	}
	return ch;
}

Scanner::Scanner(const unsigned char* buf, int len) {
	buffer = new Buffer(buf, len);
	Init();
}

Scanner::Scanner(const char* fileName) {
	FILE* stream;
	char *chFileName = coco_string_create_char(fileName);
	if ((stream = fopen(chFileName, "rb")) == NULL) {
		printf("--- Cannot open file %ls\n", fileName);
		exit(1);
	}
	coco_string_delete(chFileName);
	buffer = new Buffer(stream, false);
	Init();
}

Scanner::Scanner(FILE* s) {
	buffer = new Buffer(s, true);
	Init();
}

Scanner::Scanner(std::istream& is) {
    char* charBuffer;
    is.seekg( 0, std::ios::end);
    int length = is.tellg();
    is.seekg( 0, std::ios::beg);
    charBuffer = new char[length];
    is.read( charBuffer, length);
    buffer = new Buffer( (unsigned char*) charBuffer, length);
    delete[] charBuffer;
    Init();
}

Scanner::~Scanner() {
	char* cur = (char*) firstHeap;

	while(cur != NULL) {
		cur = *(char**) (cur + HEAP_BLOCK_SIZE);
		free(firstHeap);
		firstHeap = cur;
	}
	delete [] tval;
	delete buffer;
}

void Scanner::Init() {
	EOL    = '\n';
	eofSym = 0;
	maxT = 42;
	noSym = 42;
	int i;
	for (i = 48; i <= 57; ++i) start.set(i, 22);
	for (i = 59; i <= 59; ++i) start.set(i, 2);
	for (i = 46; i <= 46; ++i) start.set(i, 3);
	for (i = 65; i <= 90; ++i) start.set(i, 5);
	for (i = 95; i <= 95; ++i) start.set(i, 5);
	for (i = 97; i <= 122; ++i) start.set(i, 5);
	start.set(60, 6);
	start.set(34, 16);
	start.set(39, 18);
	start.set(91, 20);
	start.set(93, 21);
	start.set(123, 23);
	start.set(125, 24);
	start.set(61, 25);
	start.set(47, 26);
	start.set(63, 27);
	start.set(35, 28);
	start.set(37, 29);
		start.set(Buffer::EoF, -1);
	keywords.set("ForceDown", 9);
	keywords.set("ForceUp", 10);
	keywords.set("Unknown", 11);
	keywords.set("STIL", 14);
	keywords.set("Signals", 15);
	keywords.set("ScanIn", 18);
	keywords.set("ScanOut", 19);
	keywords.set("InOut", 20);
	keywords.set("Out", 21);
	keywords.set("In", 22);
	keywords.set("Supply", 23);
	keywords.set("Pseudo", 24);
	keywords.set("SignalGroups", 25);
	keywords.set("Timing", 27);
	keywords.set("WaveformTable", 28);
	keywords.set("Period", 29);
	keywords.set("InheritWaveformTable", 30);
	keywords.set("Waveforms", 31);
	keywords.set("Spec", 36);
	keywords.set("Category", 37);
	keywords.set("Min", 38);
	keywords.set("Typ", 39);
	keywords.set("Max", 40);
	keywords.set("Selector", 41);


	tvalLength = 128;
	tval = new char[tvalLength]; // text of current token

	// HEAP_BLOCK_SIZE byte heap + pointer to next heap block
	heap = malloc(HEAP_BLOCK_SIZE + sizeof(void*));
	firstHeap = heap;
	heapEnd = (void**) (((char*) heap) + HEAP_BLOCK_SIZE);
	*heapEnd = 0;
	heapTop = heap;
	if (sizeof(Token) > HEAP_BLOCK_SIZE) {
		printf("--- Too small HEAP_BLOCK_SIZE\n");
		exit(1);
	}

	pos = -1; line = 1; col = 0;
	oldEols = 0;
	NextCh();
	if (ch == 0xEF) { // check optional byte order mark for UTF-8
		NextCh(); int ch1 = ch;
		NextCh(); int ch2 = ch;
		if (ch1 != 0xBB || ch2 != 0xBF) {
			printf("Illegal byte order mark at start of file");
			exit(1);
		}
		Buffer *oldBuf = buffer;
		buffer = new UTF8Buffer(buffer); col = 0;
		delete oldBuf; oldBuf = NULL;
		NextCh();
	}


	pt = tokens = CreateToken(); // first token is a dummy
}

void Scanner::NextCh() {
	if (oldEols > 0) { ch = EOL; oldEols--; }
	else {
		pos = buffer->GetPos();
		ch = buffer->Read(); col++;
		// replace isolated '\r' by '\n' in order to make
		// eol handling uniform across Windows, Unix and Mac
		if (ch == '\r' && buffer->Peek() != '\n') ch = EOL;
		if (ch == EOL) { line++; col = 0; }
	}

}

void Scanner::AddCh() {
	if (tlen >= tvalLength) {
		tvalLength *= 2;
		char *newBuf = new char[tvalLength];
		memcpy(newBuf, tval, tlen*sizeof(char));
		delete [] tval;
		tval = newBuf;
	}
	if (ch != Buffer::EoF) {
		tval[tlen++] = ch;
		NextCh();
	}
}


bool Scanner::Comment0() {
	int level = 1, pos0 = pos, line0 = line, col0 = col;
	NextCh();
	if (ch == '/') {
		NextCh();
		for(;;) {
			if (ch == 10) {
				level--;
				if (level == 0) { oldEols = line - line0; NextCh(); return true; }
				NextCh();
			} else if (ch == buffer->EoF) return false;
			else NextCh();
		}
	} else {
		buffer->SetPos(pos0); NextCh(); line = line0; col = col0;
	}
	return false;
}

bool Scanner::Comment1() {
	int level = 1, pos0 = pos, line0 = line, col0 = col;
	NextCh();
	if (ch == '/') {
		NextCh();
		for(;;) {
			if (ch == 13) {
				NextCh();
				if (ch == 10) {
					level--;
					if (level == 0) { oldEols = line - line0; NextCh(); return true; }
					NextCh();
				}
			} else if (ch == buffer->EoF) return false;
			else NextCh();
		}
	} else {
		buffer->SetPos(pos0); NextCh(); line = line0; col = col0;
	}
	return false;
}

bool Scanner::Comment2() {
	int level = 1, pos0 = pos, line0 = line, col0 = col;
	NextCh();
	if (ch == '*') {
		NextCh();
		for(;;) {
			if (ch == '*') {
				NextCh();
				if (ch == '/') {
					level--;
					if (level == 0) { oldEols = line - line0; NextCh(); return true; }
					NextCh();
				}
			} else if (ch == '/') {
				NextCh();
				if (ch == '*') {
					level++; NextCh();
				}
			} else if (ch == buffer->EoF) return false;
			else NextCh();
		}
	} else {
		buffer->SetPos(pos0); NextCh(); line = line0; col = col0;
	}
	return false;
}


void Scanner::CreateHeapBlock() {
	void* newHeap;
	char* cur = (char*) firstHeap;

	while(((char*) tokens < cur) || ((char*) tokens > (cur + HEAP_BLOCK_SIZE))) {
		cur = *((char**) (cur + HEAP_BLOCK_SIZE));
		free(firstHeap);
		firstHeap = cur;
	}

	// HEAP_BLOCK_SIZE byte heap + pointer to next heap block
	newHeap = malloc(HEAP_BLOCK_SIZE + sizeof(void*));
	*heapEnd = newHeap;
	heapEnd = (void**) (((char*) newHeap) + HEAP_BLOCK_SIZE);
	*heapEnd = 0;
	heap = newHeap;
	heapTop = heap;
}

Token* Scanner::CreateToken() {
	Token *t;
	if (((char*) heapTop + (int) sizeof(Token)) >= (char*) heapEnd) {
		CreateHeapBlock();
	}
	t = (Token*) heapTop;
	heapTop = (void*) ((char*) heapTop + sizeof(Token));
	t->val = NULL;
	t->next = NULL;
	return t;
}

void Scanner::AppendVal(Token *t) {
	int reqMem = (tlen + 1) * sizeof(char);
	if (((char*) heapTop + reqMem) >= (char*) heapEnd) {
		if (reqMem > HEAP_BLOCK_SIZE) {
			printf("--- Too long token value\n");
			exit(1);
		}
		CreateHeapBlock();
	}
	t->val = (char*) heapTop;
	heapTop = (void*) ((char*) heapTop + reqMem);

	strncpy(t->val, tval, tlen);
	t->val[tlen] = '\0';
}

Token* Scanner::NextToken() {
	while (ch == ' ' ||
			(ch >= 9 && ch <= 10) || ch == 13
	) NextCh();
	if ((ch == '/' && Comment0()) || (ch == '/' && Comment1()) || (ch == '/' && Comment2())) return NextToken();
	int recKind = noSym;
	int recEnd = pos;
	t = CreateToken();
	t->pos = pos; t->col = col; t->line = line;
	int state = start.state(ch);
	tlen = 0; AddCh();

	switch (state) {
		case -1: { t->kind = eofSym; break; } // NextCh already done
		case 0: {
			case_0:
			if (recKind != noSym) {
				tlen = recEnd - t->pos;
				SetScannerBehindT();
			}
			t->kind = recKind; break;
		} // NextCh already done
		case 1:
			case_1:
			recEnd = pos; recKind = 2;
			if ((ch >= '0' && ch <= '9')) {AddCh(); goto case_1;}
			else {t->kind = 2; break;}
		case 2:
			{t->kind = 3; break;}
		case 3:
			if (ch == '.') {AddCh(); goto case_4;}
			else {goto case_0;}
		case 4:
			case_4:
			{t->kind = 4; break;}
		case 5:
			case_5:
			recEnd = pos; recKind = 5;
			if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || ch == '_' || (ch >= 'a' && ch <= 'z')) {AddCh(); goto case_5;}
			else {t->kind = 5; char *literal = coco_string_create(tval, 0, tlen); t->kind = keywords.get(literal, t->kind); coco_string_delete(literal); break;}
		case 6:
			if (ch == '(') {AddCh(); goto case_7;}
			else {goto case_0;}
		case 7:
			case_7:
			if (ch == '*') {AddCh(); goto case_8;}
			else {goto case_0;}
		case 8:
			case_8:
			if (ch == 'T') {AddCh(); goto case_9;}
			else {goto case_0;}
		case 9:
			case_9:
			if (ch == 'O') {AddCh(); goto case_10;}
			else {goto case_0;}
		case 10:
			case_10:
			if (ch == 'D') {AddCh(); goto case_11;}
			else {goto case_0;}
		case 11:
			case_11:
			if (ch == 'O') {AddCh(); goto case_12;}
			else {goto case_0;}
		case 12:
			case_12:
			if (ch == '*') {AddCh(); goto case_13;}
			else {goto case_0;}
		case 13:
			case_13:
			if (ch == ')') {AddCh(); goto case_14;}
			else {goto case_0;}
		case 14:
			case_14:
			if (ch == '>') {AddCh(); goto case_15;}
			else {goto case_0;}
		case 15:
			case_15:
			{t->kind = 6; break;}
		case 16:
			case_16:
			if (ch <= 9 || (ch >= 11 && ch <= 12) || (ch >= 14 && ch <= '!') || (ch >= '#' && ch <= '[') || (ch >= ']' && ch <= 65535)) {AddCh(); goto case_16;}
			else if (ch == '"') {AddCh(); goto case_17;}
			else {goto case_0;}
		case 17:
			case_17:
			{t->kind = 7; break;}
		case 18:
			case_18:
			if (ch <= 12 || (ch >= 14 && ch <= '&') || (ch >= '(' && ch <= '[') || (ch >= ']' && ch <= 65535)) {AddCh(); goto case_18;}
			else if (ch == 39) {AddCh(); goto case_19;}
			else {goto case_0;}
		case 19:
			case_19:
			{t->kind = 8; break;}
		case 20:
			{t->kind = 12; break;}
		case 21:
			{t->kind = 13; break;}
		case 22:
			case_22:
			recEnd = pos; recKind = 1;
			if ((ch >= '0' && ch <= '9')) {AddCh(); goto case_22;}
			else if (ch == '.') {AddCh(); goto case_1;}
			else {t->kind = 1; break;}
		case 23:
			{t->kind = 16; break;}
		case 24:
			{t->kind = 17; break;}
		case 25:
			{t->kind = 26; break;}
		case 26:
			{t->kind = 32; break;}
		case 27:
			{t->kind = 33; break;}
		case 28:
			{t->kind = 34; break;}
		case 29:
			{t->kind = 35; break;}

	}
	AppendVal(t);
	return t;
}

void Scanner::SetScannerBehindT() {
	buffer->SetPos(t->pos);
	NextCh();
	line = t->line; col = t->col;
	for (int i = 0; i < tlen; i++) NextCh();
}

// get the next token (possibly a token already seen during peeking)
Token* Scanner::Scan() {
	if (tokens->next == NULL) {
		pt = tokens = NextToken();
	} else {
		pt = tokens = tokens->next;
	}
    return pt;
}

// peek for the next token, ignore pragmas
Token* Scanner::Peek() {
	do {
		if (pt->next == NULL) {
			pt->next = NextToken();
		}
		pt = pt->next;
	} while (pt->kind > maxT); // skip pragmas

	return pt;
}

// make sure that peeking starts at the current scan position
void Scanner::ResetPeek() {
	pt = tokens;
}



