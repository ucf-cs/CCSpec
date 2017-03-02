#include <string>
#include <stdio.h>
#include <string.h>

//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>

#include <unistd.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include "stl-model.h"

#define CHAR_BUFFER 10000
#define FILENAME "LCDC/historyObj.txt"

class History {
public:

    History();
    History(ModelChecker *model_arg);
    ~History();
    
    ModelVector<ModelAction *> s;
    
    int p;
    unsigned int length;
    
    int method_id(unsigned int index, int tid);
    bool is_active(unsigned int index, int tid);
    bool check_correctness();
	void archive_history();
	void retrieve_history();
	
	//static std::stringstream ss;
	//ModelOFstream ofs;

private:
	
	typedef enum method_status {
		INACTIVE = 0,
		ACTIVE
	} method_status_t;

	typedef struct method_record {
		method_status_t status;
		int method_number;
		std::string *method_name;
		uint64_t input;
		uint64_t input2;
		uint64_t output;
	} method_record_t;

	method_record_t **records;
	
	std::string *condition;
	
	//friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & p;
        ar & length;
    }
    
    
	
};
/*
namespace boost {
namespace serialization {

template<class Archive>
void serialize(Archive & ar, History & h, const unsigned int version)
{
    ar & h.p;
    ar & h.length;
}

} // namespace serialization
} // namespace boost
*/
