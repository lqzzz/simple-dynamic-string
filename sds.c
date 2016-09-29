#include "sds.h"
#include<stdlib.h>
#include<assert.h>
#include<string.h>
//��һ��
//if (psds->free <= size)
//{
//	size_t newsize = (psds->len + size) * 2 - 1;
//	char* newstrp = malloc(newsize);
//	char* restrp = newstrp;
//	*newstrp = '\0';
//	while (*newstrp++ == *oldstrp++);//ȥ������
//	char* constrp = newstrp;
//	while (*constrp++ = *str++);
//	psds->buf = restrp;
//	free(psds->buf);
//	psds->free = psds->len = (newsize - 1) / 2;
//}
//�ڶ���
//if (psds->free <= size)
//{
//	size_t newsize = (psds->len + size) * 2 - 1;
//	char* newstrp = malloc(newsize);
//	char* restrp = newstrp;
//	*newstrp = '\0';//!!
//	while (*restrp++ = *oldstrp++);//
//	puts(newstrp); //
//	char* constrp = restrp;
//	--constrp		//������Ҫ����һ��ָ��
//	while (*constrp++ = *str++);
//	puts(newstrp);
//	free(psds->buf);
//	psds->buf = newstrp;
//	psds->free = psds->len = (newsize - 1) / 2;
//}

//��һ��
//else
//{
//	char *endstrp = psds->buf + psds->len;
//	while (*endstrp++ == *str++);//��������
//	psds->free -= size - 1;
//	psds->len += size - 1;
//}
void sds_clear(sds * const sdsp)
{
	char* p = sdsp->buf;
	while (*p++) sdsp->free++;
	sdsp->len = 0;
	*sdsp->buf = '\0';
}
void sds_cat(sds * psds, const char * str)
{
	int size = (int)strlen(str) + 1;//�����������Ŀռ�
	char *oldstrp = psds->buf;
	if (psds->free <= size)
	{	
		size_t newsize = (psds->len + size)*2-1; //�¿����ַ�����������
		char* newstrp = malloc(newsize);
		assert(newstrp);
		char* restrp = newstrp;
		*newstrp = '\0';
		while (*restrp++ = *oldstrp++);
		--restrp;//������'\0'
		while (*restrp++ = *str++);
		free(psds->buf);//�ͷ�ԭ�ַ����ڴ�
		psds->buf = newstrp;//ָ�����ڴ�
		psds->free = psds->len = (newsize - 1) / 2;
	}
	else
	{
		char *endstrp = psds->buf + psds->len;//ֱ��ƫ����'\0'
		while (*endstrp++ = *str++);
		psds->free -= size - 1;
		psds->len += size - 1;
	}
}
void sds_cpy(const char * str, sds * psds)
{
	
}
sds* sds_dup(const sds* const source)
{	
	sds* sdsp = sds_empty();

	sdsp->buf = (char*)malloc(strlen(source->buf) + 1);//ע������ڴ棡

	sdsp->free = source->free;

	sdsp->len = source->len;

	char *sp = source->buf;

	char *dp = sdsp->buf;

	while (*dp++ = *sp++);

	return sdsp;
}

int sds_avail(const sds *const sdsp)
{
	return sdsp->free;
}

int sds_len(const sds*const sdsp)
{
	return sdsp->len;
}

sds * sds_new(const char * src)
{
	sds* sdsp = sds_empty();

	//char* p = sdsp->buf = (char*)malloc(sizeof(strlen(src)+1));//sizeofʲô��
	char* p = sdsp->buf = (char*)malloc(strlen(src) + 1);//'\0'�ַ�

	*p = '\0';
 
	while (*p++=*src++) sdsp->len++; //��ֵͬʱƫ������һλ

	return sdsp;
}

sds * sds_empty()
{
	sds * p = (sds*)malloc(sizeof(sds));

	assert(p);

	p->buf = NULL;

	p->free = 0;

	p->len = 0;

	return p;
}

void sds_free(sds* block)
{
	assert(block);
	if(block->buf)  free(block->buf);
	free(block);
}