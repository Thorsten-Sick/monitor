Signature::

    * Calling convention: WINAPI
    * Category: crypto


CryptProtectData
================

Signature::

    * Library: crypt32
    * Return value: BOOL

Parameters::

    *  DATA_BLOB *pDataIn
    ** LPCWSTR szDataDescr description
    *  DATA_BLOB *pOptionalEntropy
    *  PVOID pvReserved
    *  CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct
    *  DWORD dwFlags
    *  DATA_BLOB *pDataOut

Ensure::

    * pDataIn

Prelog::

    b buffer pDataIn->cbData, pDataIn->pbData


CryptUnprotectData
==================

Signature::

    * Library: crypt32
    * Return value: BOOL

Parameters::

    *  DATA_BLOB *pDataIn
    *  LPWSTR *ppszDataDescr
    *  DATA_BLOB *pOptionalEntropy
    *  PVOID pvReserved
    *  CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct
    *  DWORD dwFlags
    *  DATA_BLOB *pDataOut

Ensure::

    * pDataOut
    * pOptionalEntropy

Logging::

    u description ppszDataDescr != NULL ? *ppszDataDescr : NULL
    b entropy pOptionalEntropy->cbData, pOptionalEntropy->pbData
    b buffer pDataOut->cbData, pDataOut->pbData


CryptProtectMemory
==================

Signature::

    * Library: crypt32
    * Return value: BOOL

Parameters::

    *  LPVOID pData
    *  DWORD cbData
    ** DWORD dwFlags flags

Prelog::

    b buffer cbData, pData


CryptUnprotectMemory
====================

Signature::

    * Library: crypt32
    * Return value: BOOL

Parameters::

    *  LPVOID pData
    *  DWORD cbData
    ** DWORD dwFlags flags

Logging::

    b buffer cbData, pData


CryptDecrypt
============

Signature::

    * Library: advapi32
    * Return value: BOOL

Parameters::

    ** HCRYPTKEY hKey key_handle
    ** HCRYPTHASH hHash hash_handle
    ** BOOL Final final
    ** DWORD dwFlags flags
    *  BYTE *pbData
    *  DWORD *pdwDataLen

Logging::

    B buffer *pdwDataLen, pbData


CryptEncrypt
============

Signature::

    * Library: advapi32
    * Return value: BOOL

Parameters::

    ** HCRYPTKEY hKey key_handle
    ** HCRYPTHASH hHash hash_handle
    ** BOOL Final final
    ** DWORD dwFlags flags
    *  BYTE *pbData
    *  DWORD *pdwDataLen
    *  DWORD dwBufLen

Logging::

    b buffer dwBufLen, pbData


CryptHashData
=============

Signature::

    * Library: advapi32
    * Return value: BOOL

Parameters::

    ** HCRYPTHASH hHash hash_handle
    *  BYTE *pbData
    *  DWORD dwDataLen
    ** DWORD dwFlags flags

Logging::

    b buffer dwDataLen, pbData


CryptDecodeMessage
==================

Signature::

    * Library: crypt32
    * Return value: BOOL

Parameters::

    *  DWORD dwMsgTypeFlags
    *  PCRYPT_DECRYPT_MESSAGE_PARA pDecryptPara
    *  PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara
    *  DWORD dwSignerIndex
    *  const BYTE *pbEncodedBlob
    *  DWORD cbEncodedBlob
    *  DWORD dwPrevInnerContentType
    *  DWORD *pdwMsgType
    *  DWORD *pdwInnerContentType
    *  BYTE *pbDecoded
    *  DWORD *pcbDecoded
    *  PCCERT_CONTEXT *ppXchgCert
    *  PCCERT_CONTEXT *ppSignerCert

Logging::

    B buffer pcbDecoded, pbDecoded


CryptDecryptMessage
===================

Signature::

    * Library: crypt32
    * Return value: BOOL

Parameters::

    *  PCRYPT_DECRYPT_MESSAGE_PARA pDecryptPara
    *  const BYTE *pbEncryptedBlob
    *  DWORD cbEncryptedBlob
    *  BYTE *pbDecrypted
    *  DWORD *pcbDecrypted
    *  PCCERT_CONTEXT *ppXchgCert

Logging::

    B buffer pcbDecrypted, pbDecrypted


CryptEncryptMessage
===================

Signature::

    * Library: crypt32
    * Return value: BOOL

Parameters::

    * PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara
    * DWORD cRecipientCert
    * PCCERT_CONTEXT rgpRecipientCert[]
    * const BYTE *pbToBeEncrypted
    * DWORD cbToBeEncrypted
    * BYTE *pbEncryptedBlob
    * DWORD *pcbEncryptedBlob

Prelog::

    b buffer cbToBeEncrypted, pbToBeEncrypted


CryptHashMessage
================

Signature::

    * Library: crypt32
    * Return value: BOOL

Parameters::

    *  PCRYPT_HASH_MESSAGE_PARA pHashPara
    *  BOOL fDetachedHash
    *  DWORD cToBeHashed
    *  const BYTE *rgpbToBeHashed[]
    *  DWORD rgcbToBeHashed[]
    *  BYTE *pbHashedBlob
    *  DWORD *pcbHashedBlob
    *  BYTE *pbComputedHash
    *  DWORD *pcbComputedHash

Pre::

    DWORD length = 0;
    for (DWORD i = 0; i < cToBeHashed; i++) {
        length += rgcbToBeHashed[i];
    }

    uint8_t *mem = malloc(length);
    if(mem != NULL) {
        for (DWORD i = 0, off = 0; i < cToBeHashed; i++) {
            memcpy(mem + off, rgpbToBeHashed[i], rgcbToBeHashed[i]);
            off += rgcbToBeHashed[i];
        }
    }

Logging::

    b buffer length, mem

Post::

    if(mem != NULL) {
        free(mem);
    }


CertCreateCertificateContext
============================

Signature::

    * Library: crypt32
    * Return value: PCCERT_CONTEXT

Parameters::

    ** DWORD dwCertEncodingType encoding
    *  const BYTE *pbCertEncoded
    *  DWORD cbCertEncoded

Logging::

    b certificate cbCertEncoded, pbCertEncoded
