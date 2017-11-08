#include <iostream>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <assert.h>
#include <cstring>
#include <fstream>
#include <sstream>

std::string privateKey ="-----BEGIN RSA PRIVATE KEY-----\n"\
"Proc-Type: 4,ENCRYPTED\n"\
"DEK-Info: DES-EDE3-CBC,FF3B4B2EE8DD0812\n"\
"\n"\
"77p2yKPT17V7De60ZNyg4DBhFkY6n0MbrRwXX6r3IIk63CqrVO67s2qxtDHpVPBs\n"\
"bOTy/L1Z1blPW6WGk4ySiFVJje5765FhjU7FQ8Ic4m0K2YUa60JjOv+JYFXQob81\n"\
"EHNfEyRQOL95BtELQvxJ/fYRkYcjlHLcXGVdLI8yzTPeC7Ui9ZWEWTYct9bEEfNg\n"\
"wEJRVw/+DPwiAedpeUMFnyI/i//ez0CnhmZxnKyXL3oxWNmWJJdRrPyzPmw2gLCI\n"\
"+2otukH0whnC2zPcbsxUlaUcNCPQXU/5+JRWaDoaJllyg1aWqp366xtQRzhYGdXC\n"\
"cYZQvXEbTfZ9AOfclPwCE4AjX4eClm3CTKeEKH5kwgoKpOaExmN86s09Pc7uouu7\n"\
"uU3FzYM4NObRo0ZpVg1vz2PbBHRn2lsP9S8/UYSPkolWvOh41xXdGGPlYq6GJtJ9\n"\
"R+1Q1fE9G2oi2NyVtJvZDb2mky4iBLeyYn/o4Q4sS1S23TnJa9gzomdqlh/sSFBN\n"\
"Uoqn1fRimTIDaj4m60SLc0oflOTe2f309gb8VbelMQgq1rXtiJHk8fi0HfvariPJ\n"\
"RWvNj+xwDIFDnUNOPtrfX9z/rIbbFZ6JqEkGYJDQ+WNYNf1xv2LQuF9JiQmyQobV\n"\
"06vjG2nin0RzgHlXCahngWt0upLDUyCoJz9YHHvjL/sj1UW4RgdA+hc2ntHBPFFR\n"\
"S24OrfMpeQy0zj38EQW+zU3Yiq+bXvTpVG2KA9zdlac1uS3q1vOrT93rdLkp7pY6\n"\
"d8vcufQJV3FA5xEKNTocZa2kxRz2X+2d2PnMYFs0qqb+g9918ZLA/gCLEtcOLY/B\n"\
"DaB/iQxpVnYuu0eHyTgPSEfd1At1k/Bnl+sZuk83yZbM26ESPxeUPXNKcjJUnnmh\n"\
"zGdMAUR0XQNmLa9qcF0MY6izdp/9e8wGVi8TKS++W83EsUTA93+++qkJf1pXd1oU\n"\
"fQ3BRdGjSzeR+hMMQcHW4JLFlKF1gEH10sLbgTBMSmZqNijIe2YiT7+vER2E3QWq\n"\
"QaHMHUJ7OrTZtUibxs+ln2Wu+EbfJ1pEUqCK2RAqaVqyPT7UQawrqUmc2owmmW3K\n"\
"ytNeR9pfPocJB4OWoauOsPE5GaT7pgi+IpVx9SqzJtJ8Cn7FsH2hZa4nXGPI/VJW\n"\
"czE107GsWkeDbEhN5GUZa1US3KMAEMi7JzMXIzwf8u3oHSAQsKMX1dDoBiCyf5uD\n"\
"8l9U8j1WKDS1wi6F5YaV2ZpU2GZrjyEPH6F0F5kl7n2eMTnpkr6d9dZGpi/lxKNf\n"\
"AasBBtKahdwTGIyp6wnQD/YkCWOZDE6zOVdbGHaFv8xSOn8dddFfcUYbhZduLlW1\n"\
"DQsg11TXzM7aSc3U2HySYbfRKMi8Nu3PqTB+AAMOaaLWjQtwm+c8qXMaz9Uox7Zm\n"\
"VWYprpOZ2ywkK7WYbnpEsth/CDsQIB05VS1ClEocWQhufI8/ks/FpH1lrNPI+Maw\n"\
"OY17V5/tPGoZP6bHeJye7F9AmTvYvJnwsV0qtjjGA6OKjvFljR6nmYd46cY6xSVl\n"\
"RLUmze5RxeOC9+hS5nR5LpVAvaaqo24z+rk/fUcE4IApl824y38crQ==\n"\
"-----END RSA PRIVATE KEY-----\n\0";

std::string publicKey ="-----BEGIN PUBLIC KEY-----\n"\
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAstiA5SPTDtykbr8WMHGq\n"\
"0u5kQR9bzfVfq9311tYYizPnFNOdD+9qIMn2jHbCl2YVSGAK//A8sd6BtHfBEc6R\n"\
"Sm7AigjOwoR4STNFqzHSM8f/ZZ2GrMIuiRMTN1hpbhyyl79y68RPLPD3+1iiW/dy\n"\
"WMygZyLkLdjOcsVaBCKTfuufqcT79m23b+di37L1ZTjpErj6+A79iUHym5tQZN3n\n"\
"XrwHsasqGqL+gcjXsLea6MSZ9npM4jHCJYO3sa8k/WM0tRfulm9mVOIkIUbeFRgE\n"\
"MkB5c+b1CfiT5mGtSFeaOwTXj+4Uct/+MDlYGsBLmX7vSd4QuHXEvTNz179RSj4X\n"\
"PQIDAQAB\n"
"-----END PUBLIC KEY-----\n\0";

std::string* loadRSAPEM(std::string& keyFileName) {
    std::ifstream ifs(keyFileName, std::fstream::in);
    std::stringstream ss;
    ss << ifs.rdbuf();
    return new std::string(ss.str());
}

/*
 * creates a RSA Object from an RSA PrivateKey in text format (string)
 */
RSA* createPrivateRSAObject(std::string key) {
    RSA *rsa = NULL;
    const char* c_string = key.c_str();
    BIO * keybio = BIO_new_mem_buf((void*)c_string, -1);
    if (keybio==NULL) {
        return 0;
    }
    rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa,NULL, NULL);
    return rsa;
}

RSA* createPublicRSAObject(std::string key) {
    RSA *rsa = NULL;
    BIO *keybio;
    const char* c_string = key.c_str();
    keybio = BIO_new_mem_buf((void*)c_string, -1);
    if (keybio==NULL) {
        return 0;
    }
    rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);
    return rsa;
}

bool RSASign( RSA* privateRSAKey,
              const unsigned char* Msg,
              size_t MsgLen,
              unsigned char** EncMsg,
              size_t* MsgLenEnc) {
    EVP_MD_CTX* m_RSASignCtx = EVP_MD_CTX_create();
    EVP_PKEY* priKey  = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(priKey, privateRSAKey);
    if (EVP_SignInit(m_RSASignCtx, EVP_sha256()) <=0) {
        return false;
    }
    if (EVP_SignUpdate(m_RSASignCtx, Msg, MsgLen) <= 0) {
        return false;
    }
    *EncMsg = (unsigned char*)malloc(*MsgLenEnc);
    if (EVP_SignFinal(m_RSASignCtx, *EncMsg, (unsigned int*) MsgLenEnc, priKey) <= 0) {
        return false;
    }
    EVP_MD_CTX_destroy(m_RSASignCtx);
    return true;
}

bool RSAVerifySignature( RSA* publicRSAKey,
                         unsigned char* Signature,
                         size_t SignatureLen,
                         const char* Msg,
                         size_t MsgLen,
                         bool* Authentic) {
    *Authentic = false;
    EVP_PKEY* pubKey  = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pubKey, publicRSAKey);
    EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

    if (EVP_VerifyInit(m_RSAVerifyCtx, EVP_sha256()) <=0) {
        return false;
    }
    if (EVP_VerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) <= 0) {
        return false;
    }
    int AuthStatus = EVP_VerifyFinal(m_RSAVerifyCtx, Signature, SignatureLen, pubKey);
    if (AuthStatus==1) {
        *Authentic = true;
        EVP_MD_CTX_destroy(m_RSAVerifyCtx);
        return true;
    } else if(AuthStatus==0){
        *Authentic = false;
        EVP_MD_CTX_destroy(m_RSAVerifyCtx);
        return true;
    } else{
        *Authentic = false;
        EVP_MD_CTX_destroy(m_RSAVerifyCtx);
        return false;
    }
}

void Base64Encode( const unsigned char* buffer,
                   size_t length,
                   char** base64Text) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, buffer, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    *base64Text=(*bufferPtr).data;
}

size_t calcDecodeLength(const char* b64input) {
    size_t len = strlen(b64input), padding = 0;

    if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
        padding = 2;
    else if (b64input[len-1] == '=') //last char is =
        padding = 1;
    return (len*3)/4 - padding;
}

void Base64Decode(const char* b64message, unsigned char** buffer, size_t* length) {
    BIO *bio, *b64;

    int decodeLen = calcDecodeLength(b64message);
    *buffer = (unsigned char*)malloc(decodeLen + 1);
    (*buffer)[decodeLen] = '\0';

    bio = BIO_new_mem_buf(b64message, -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    *length = BIO_read(bio, *buffer, strlen(b64message));
    BIO_free_all(bio);
}

char* signMessage(std::string privateKey, std::string plainText) {
    RSA* privateRSA = createPrivateRSAObject(privateKey);
    unsigned char* encMessage = nullptr;
    char* base64Text = nullptr;
    size_t encMessageLength = 0;
    RSASign(privateRSA, (unsigned char*) plainText.c_str(), plainText.length(), &encMessage, &encMessageLength);
    Base64Encode(encMessage, encMessageLength, &base64Text);
    free(encMessage);
    return base64Text;
}

bool verifySignature(std::string publicKey, std::string plainText, char* signatureBase64) {
    RSA* publicRSA = createPublicRSAObject(publicKey);
    unsigned char* decMessage;
    size_t decMessageLength;
    bool authentic;
    Base64Decode(signatureBase64, &decMessage, &decMessageLength);
    bool result = RSAVerifySignature(publicRSA, decMessage, decMessageLength, plainText.c_str(), plainText.length(), &authentic);
    return result & authentic;
}

int main(int argc, const char** argv) {
    
	if(argc != 3) {
		std::cerr << "wrong call syntax!" << std::endl;
		std::cout << argv[0] << " path/to/privK path/to/pubK";	
		return -1;
	}

    std::string plainText = "My secret message.\n";
    std::string sha256PlainText = "d64ffa2654fcc5139fa6cd4489a9e4f44c27efc4fe4d0cacb2614d47bf7506ef";
    std::cout << "plainText:" << std::endl << plainText << std::endl;

    std::string prKey(argv[1]);
    std::string puKey(argv[2]);

    char* signature = signMessage(*loadRSAPEM(prKey), sha256PlainText);
    std::cout << "signed with signature:" << std::endl;
    for(size_t i = 0;i<strlen(signature);i++) {
        std::cout << signature[i];
    }
    std::cout << std::endl;

    bool authentic = verifySignature(*loadRSAPEM(puKey), sha256PlainText, signature);
    if ( authentic ) {
        std::cout << "Authentic" << std::endl;
    } else {
        std::cout << "Not Authentic" << std::endl;
    }
}
