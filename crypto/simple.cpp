#pragma warning( disable : 4996 )


#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>



int __cdecl main(int argc, TCHAR* argv[])
{

	HCRYPTPROV hCryptProv;
	HCRYPTHASH hHash;
	HCRYPTKEY hKey;
	DWORD dwBufferlen = 100;
	DWORD dwBufsize = 100;
	char passw[100] = "password12";
	char buff[100] = "hello world";

	// Get the handle to the default provider. 
	if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, 0)) {
		printf("Error during CryptAcquireContext!\n");
		return false;
	}

	if (!CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash)) {
		printf("Error during CryptCreateHash!\n");
		return false;
	}

	if (!CryptHashData(hHash, (BYTE*)passw, strlen(passw), 0)) {
		printf("Error during CryptHashData.\n");
		return false;
	}

	// Derive a session key from the hash object
	if (!CryptDeriveKey(hCryptProv, CALG_RC4, hHash, 0, &hKey)) {
		printf("Error during CryptDeriveKey!\n");
		return false;
	}

	if (hHash) {
		if (!(CryptDestroyHash(hHash))) {
			printf("Error during CryptDestroyHash\n");
			return false;
		}
		hHash = 0;
	}
	
	printf("message : %s\n", buff);
	CryptEncrypt(hKey, 0, TRUE, 0, NULL, &dwBufferlen, dwBufferlen);
	if (!CryptEncrypt(hKey, 0, TRUE, 0, (BYTE*)buff, &dwBufferlen, dwBufferlen)) {
		printf("Error during Encrypt.\n");
		return false;
	}

	printf("cipher : %s\n", buff);
	if (!CryptDecrypt(hKey, 0, FALSE, 0, (BYTE*)buff, &dwBufferlen)) {
		printf("Error during Decrypt.\n");
		return false;
	}

	printf("plain : %s\n", buff);


	if (hKey)
		if (!(CryptDestroyKey(hKey))) {
			printf("Error during CryptDestroyKey\n");
			return false;
		}

	if (hCryptProv)
		if (!(CryptReleaseContext(hCryptProv, 0))) {
			printf("Error during CryptReleaseContext\n");
			return false;
		}

	return true;
}
