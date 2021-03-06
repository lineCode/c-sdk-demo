#include "simple_upload.h"
#include "resumable_upload.h"
#include "res_manage.h"
#include "qiniu/http.h"
#include <tchar.h>

void upload_files(Qiniu_Mac *mac)
{
	char *bucket = "if-pbl";
	char *imageKey = "2016/05/08/test.jpg";

	//注意中文文件名的写法
	wchar_t *videoKey = L"2016/05/08/测试.wmv";
	//covert to utf8
	char videoKeyUtf8[256];
	WideCharToMultiByte(CP_UTF8, 0, videoKey, -1, videoKeyUtf8, 256, NULL, NULL);
	char *localImageFile = "C:\\Users\\Public\\Pictures\\Sample Pictures\\Koala.jpg";

	//注意中文路径名的写法
	char *localVideoFile = (char*)L"C:/Users/Public/Videos/Sample Videos/测试.wmv";
	//localVideoFile = (char*)L"E:\\测试.txt";
	//localVideoFile = argv[1];
	//printf("Upload %s\n",localVideoFile);
	//simpleUploadWithoutKey(&mac, bucket, localImageFile);
	//simpleUploadWithKey(&mac,bucket,imageKey,localImageFile);
	//simpleUploadWithPutExtra(&mac,bucket,imageKey,localImageFile);
	//simpleUploadWithPfop(&mac,bucket,imageKey,localImageFile);
	//simpleUploadWithCallback(&mac, bucket, imageKey, localImageFile);

	resumableUploadWithKey(mac, bucket, videoKeyUtf8, localVideoFile);
}

void resource_manage(Qiniu_Mac *mac)
{
	char *bucket = "if-pbl";
	wchar_t *key = L"中文名字.jpg";

	// change to utf8
	char keyUtf8[256];
	WideCharToMultiByte(CP_UTF8, 0, key, -1, keyUtf8, 256, NULL, NULL);

	Qiniu_Client client;

	Qiniu_Global_Init(-1);
	Qiniu_Client_InitMacAuth(&client, 1024, mac);

	rsStat(&client, bucket, keyUtf8);

	Qiniu_Client_Cleanup(&client);
	Qiniu_Global_Cleanup();
}

int _tmain(int argc, _TCHAR*argv[])
{

	//从 https://portal.qiniu.com/user/key 这里获取
	//char *accessKey = "<AccessKey>";
	//char *secretKey = "<SecretKey>";

	char *accessKey = "6_GYcCEEzCDNPgy7nxBt5jnLg3_JqVHJEJXrpfaS";
	char *secretKey = "lRBgL6skPMSbYhUNALVseeghJ3e0_uqcweDRPUc7";

	Qiniu_Mac mac;
	mac.accessKey = accessKey;
	mac.secretKey = secretKey;

	//upload files
	//upload_files(&mac);
	//get resource info
	resource_manage(&mac);
	//wait to exit
	getchar();
	return 0;
}
