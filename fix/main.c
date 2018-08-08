#include <pspkernel.h>

PSP_MODULE_INFO("AKBTPFIX", PSP_MODULE_USER, 1, 1);

//jis编码转换算法
unsigned int hook_6828(unsigned int code1, unsigned int code2)
{
	//自定义编码转换
	//这就不实现了
	return code1;
}

int module_start(int argc, char *argv[])
{
	//直接修改地址，跳转到插件内置函数
	unsigned int hook_address = 0x0880A828;
	*(unsigned int *)(hook_address) = 0x08000000 | (((unsigned int)hook_6828) & 0x0FFFFFFC) >> 2;	//j
	*(unsigned int *)(hook_address + 4) = 0;								//nop

	//刷新内存
	sceKernelDcacheWritebackInvalidateRange((const void *)hook_address, 8);
	sceKernelIcacheInvalidateRange((const void *)hook_address, 8);
	return 0;
}

