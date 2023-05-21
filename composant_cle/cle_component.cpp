#include <pybind11/pybind11.h>
#include "uECC.h"
#include <string>
#include <sstream>
#include <stddef.h>
#include <iostream>

char version[]="1.0";

char const* getVersion() {
	return version;
}

class Cle
{
    public:
        Cle(){}
	
	/*uint8_t castStringToUint8(const std::string& str) {
		
   		std::istringstream iss(str);
    		int intValue;
    		iss >> intValue;
		
    		if (intValue < 0 || intValue > 255) {}
    		return static_cast<uint8_t>(intValue);
	}*/
	unsigned char hexchr2bin(const char hex){
		unsigned char result;

		if (hex >= '0' && hex <= '9') {
		result = hex - '0';
		} else if (hex >= 'A' && hex <= 'F') {
		result = hex - 'A' + 10;
		} else if (hex >= 'a' && hex <= 'f') {
		result = hex - 'a' + 10;
		} else {
		return 0;
		}
		return result;
	}



	void hexStringToBin(unsigned char *out,const char * hexPrivate) {
    		for (int i=0; i<32; i++){
			out[i] = hexchr2bin(hexPrivate[2*i])<<4 | hexchr2bin(hexPrivate[2*i+1]);
    		}
	}


	char *binToHexString(char *out,const unsigned char *bin, size_t len){
   		size_t  i;

    		if (bin == NULL || len == 0) return NULL;

    		for (i=0; i<len; i++) {
			out[i*2]   = "0123456789abcdef"[bin[i] >> 4];
			out[i*2+1] = "0123456789abcdef"[bin[i] & 0x0F];
   		 }
   		 out[len*2] = '\0';

   		 return out;
	}
	
	void initialize(std::string &pk){
		privatekey = pk;
		//uint8_t a = castStringToUint8(privatekey);
		//uint8_t b = castStringToUint8(publickey);
		uECC_Curve curve_256k1 = uECC_secp256k1();
		const unsigned char *b
		std::cout << "L'élément est : " << uECC_make_key("4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0",&b,curve_256k1) << std::endl;
	}
        const std::string &getPrivateKey() const {
	       return privatekey;
       	}
        const std::string &getPublicKey() const {
           return publickey;
           }
    private:
        std::string privatekey;
        std::string publickey;
        
};
 
namespace py = pybind11;


PYBIND11_MODULE(cle_component,greetings)
{
  greetings.doc() = "greeting_object 1.0";
  greetings.def("getVersion", &getVersion, "a function returning the version");
  
   // bindings to Cle class
    py::class_<Cle>(greetings, "Cle", py::dynamic_attr())
        .def(py::init<>())
	.def("initialize", &Cle::initialize)
        .def("getPrivateKey", &Cle::getPrivateKey)
        .def("getPublicKey", &Cle::getPublicKey);
}
