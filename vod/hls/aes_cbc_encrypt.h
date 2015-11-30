#ifndef __AES_CBC_ENCRYPT_H__
#define __AES_CBC_ENCRYPT_H__

// TODO make it optional, like #if (NGX_OPENSSL)

// includes
#include <openssl/evp.h>
#include "../common.h"

// macros
#ifndef AES_BLOCK_SIZE
#define AES_BLOCK_SIZE (16)
#endif // AES_BLOCK_SIZE
#define aes_round_to_block(n) (((n) + 0x10) & ~0xf)

// typedefs
typedef struct {
	request_context_t* request_context;
	write_callback_t callback;
	void* callback_context;
	EVP_CIPHER_CTX cipher;
	u_char last_block[AES_BLOCK_SIZE];
} aes_cbc_encrypt_context_t;

// functions
vod_status_t aes_cbc_encrypt_init(
	aes_cbc_encrypt_context_t** ctx,
	request_context_t* request_context,
	write_callback_t callback, 
	void* callback_context, 
	const u_char* key, 
	const u_char* iv);

vod_status_t aes_cbc_encrypt_write(
	aes_cbc_encrypt_context_t* ctx, 
	u_char* buffer, 
	uint32_t size);

vod_status_t aes_cbc_encrypt_flush(aes_cbc_encrypt_context_t* ctx);

#endif // __AES_CBC_ENCRYPT_H__
