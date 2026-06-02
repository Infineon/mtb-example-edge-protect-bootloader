/* user_settings.h
 *
 * WolfSSL configuration for ML-DSA verification via se-rt-services-utils
 * PSA Crypto PQC extension in MCUboot bootloader.
 *
 * se-rt-services-utils uses malloc/free for dilithium_key and key storage,
 * so dynamic allocation must be enabled (no WOLFSSL_NO_MALLOC).
 */

#ifndef WOLFSSL_USER_SETTINGS_H
#define WOLFSSL_USER_SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Enable Dilithium/ML-DSA support */
#define HAVE_DILITHIUM

/* Use WolfSSL's pure C implementation (not liboqs) */
#define WOLFSSL_WC_DILITHIUM

/* Enable only verification (reduce code size) */
#define WOLFSSL_DILITHIUM_VERIFY_ONLY
#define WOLFSSL_DILITHIUM_NO_MAKE_KEY
#define WOLFSSL_DILITHIUM_NO_SIGN

/* Enable small memory verification mode */
#define WOLFSSL_DILITHIUM_VERIFY_SMALL_MEM

/* Use smaller code path: process SHAKE-128 one block at a time instead of 5.
 * Trade-off: possibly slower NTT polynomial rejection sampling. */
#define WOLFSSL_DILITHIUM_SMALL

/* Use built-in hardcoded hash OID tables instead of wc_HashGetOID/OidFromId.
 * Required because ASN.1 OID lookup functions are not compiled in this minimal
 * WolfSSL build. This enables HashML-DSA verify (wc_dilithium_verify_ctx_hash)
 * without pulling in the full ASN.1 infrastructure. */
#define WOLFSSL_DILITHIUM_NO_ASN1

/* Enable all ML-DSA parameter sets (disable unused ones based on USE_MLDSA* from command line) */
#ifndef USE_MLDSA87
#define WOLFSSL_NO_ML_DSA_87
#endif

/* Enable SHA3 and SHAKE (required for Dilithium) */
#define WOLFSSL_SHA3
#define WOLFSSL_SHAKE128
#define WOLFSSL_SHAKE256

/* Disable unused features to minimize code size */
#define NO_FILESYSTEM
#define NO_WRITEV
#define NO_MAIN_DRIVER
#define NO_DEV_RANDOM
#define NO_DSA
#define NO_DH
#define NO_RSA
#define NO_PSK
#define NO_MD4
#define NO_MD5
#define NO_RC4
#define NO_DES3
#define NO_OLD_TLS
#define NO_SESSION_CACHE
#define NO_ERROR_STRINGS

/* Use standard C types */
#define SIZEOF_LONG_LONG 8

/* Platform specific */
#define SINGLE_THREADED
#define WOLFSSL_USER_IO

/* Dynamic memory: se-rt-services-utils uses malloc/free for:
 *   - dilithium_key allocation in ifx_se_pqc_verify_hash()
 *   - key data storage in ifx_se_storage_import_key()
 * Use the standard C malloc/free (via wolfSSL XMALLOC wrappers). */
#define WOLFSSL_MALLOC_CHECK

#ifdef __cplusplus
}
#endif

#endif /* WOLFSSL_USER_SETTINGS_H */
