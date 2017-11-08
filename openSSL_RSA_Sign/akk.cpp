bool RSAVerifySignature(RSA* publicRSAKey, unsigned char* Signature,
                        size_t SignatureLen, const char* Msg, size_t MsgLen,
                        bool* Authentic) {
  *Authentic = false;
  EVP_PKEY* pubKey = EVP_PKEY_new();
  EVP_PKEY_assign_RSA(pubKey, publicRSAKey);
  EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

  if (EVP_VerifyInit(m_RSAVerifyCtx, EVP_sha256()) <= 0) {
    return false;
  }
  if (EVP_VerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) <= 0) {
    return false;
  }
  int AuthStatus =
      EVP_VerifyFinal(m_RSAVerifyCtx, Signature, SignatureLen, pubKey);
  if (AuthStatus == 1) {
    *Authentic = true;
    EVP_MD_CTX_destroy(m_RSAVerifyCtx);
    return true;
  } else if (AuthStatus == 0) {
    *Authentic = false;
    EVP_MD_CTX_destroy(m_RSAVerifyCtx);
    return true;
  } else {
    *Authentic = false;
    EVP_MD_CTX_destroy(m_RSAVerifyCtx);
    return false;
  }
}

bool verifySignature(std::string publicKey, std::string sha256PlainText,
                     char* signatureBase64) {
  RSA* publicRSA = createPublicRSAObject(publicKey);

  unsigned char* decMessage;
  size_t decMessageLength;
  bool authentic;

  Base64Decode(signatureBase64, &decMessage, &decMessageLength);

  bool result = RSAVerifySignature(publicRSA, decMessage, decMessageLength,
                                   sha256PlainText.c_str(),
                                   sha256PlainText.length(), &authentic);
  return result & authentic;
}

bool authentic =
    verifySignature(*loadRSAPEM(puKey), sha256PlainText, signature);
