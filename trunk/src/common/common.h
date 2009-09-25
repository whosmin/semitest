#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

enum State
{
	FORCE_LOW       = 'D',
	FORCE_HIGH      = 'U',
	FORCE_Z         = 'Z', // Z
	FORCE_UNKNOWN   = 'N',
	FORCE_OFF       = '_',
	COMPARE_LOW     = 'L',
	COMPARE_HIGH    = 'H',
	COMPARE_Z       = 'T',
	COMPARE_UNKNOWN = 'X', // Mask

	UNKNOWN_LOW     = '0',
	UNKNOWN_HIGH    = '1',

	//PREVIOUS,
	UNKNOWN         = '?'
};

struct SignalInfo
{
	std::string  name;
	std::string  scope;
	unsigned int size;
	std::string  alias;
	std::string  type;
	unsigned int index;

    void print(std::ostream& os, std::string delim="\t");
    static void print(std::vector<SignalInfo>& header, std::ostream& os, std::string delim="\t");

//        bool operator<(SignalInfo& rhs) {
//            return (index < rhs.index);
//        }
    friend std::ostream& operator<<(std::ostream& os, SignalInfo& info);
};
//    bool operator<(SignalInfo& lhs, SignalInfo& rhs) {
//        return (lhs.index < rhs.index);
//    }

typedef std::vector<SignalInfo> SignalHeader;

std::vector<std::string> getNames(const SignalHeader& header);

void reorderSignalHeader( SignalHeader& signalHeader, const std::vector<std::string>& pinOrder);

//void getSignalHeaderNames( const SignalHeader& signalHeader, std::vector<std::string>& names, bool vertical=true);

//struct print_element {
//template <typename T>
//void operator()(const T& o) { std::cout << ""; }
//}

void horizToVert( const std::vector<std::string>& input, std::vector<std::string>& output, unsigned int align = 0);

template <typename IterT>
void print_elements ( IterT begin, IterT end, std::string delim = "") {
    IterT iter;

    for(iter = begin; iter != end; iter++) {
        std::cout << *iter << delim;
    }
    std::cout << std::endl;
}

class CommonData {
    public:
        CommonData();
        virtual ~CommonData();
    public:
        virtual void         clear           () = 0;
        virtual void         setName         (std::string str);
        virtual std::string  getName         (void);
        virtual bool         setSignalHeader (const SignalHeader& header);
        virtual SignalHeader getSignalHeader ();

        virtual bool         removeSignal     ( std::string              signalName) = 0;
        virtual bool         removeSignal     ( std::vector<std::string> signalVec)  = 0;
        virtual bool         keepSignal       ( std::vector<std::string> signalVec)  = 0;
    public:
    protected:
        SignalHeader signalHeader;
        std::string name;
    private:

};

double my_round(double value);

#endif

