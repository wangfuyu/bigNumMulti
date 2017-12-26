#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG_LOG printf
#define DEBUG_PRINT printf 

#define CHAR0 '0'

void freeBigNum(char *result)
{
	if (result)
	{
		free(result);
		result = NULL;
	}

	return ;
}

char *revertStr(char *str, int m, int n)
{
	char tmp = 0;
	
	DEBUG_LOG("start: what input? %s, start: %d, end: %d\n", 
				NULL == str ? "NULL" : str, m, n);
	if (NULL == str || 0 == (n - m))
	{
		return str;
	}

	while (m < n)
	{
		tmp = str[m];
		str[m] = str[n];
		str[n] = tmp;
		m++;
		n--;
	}

	return str;
}

char *bigNumMulti(char *str1, char *str2)
{
	int i = 0;
	int j = 0;
	int lenStr1 = 0;
	int lenStr2 = 0;
	int lenResult = 0;
	int tmpMultiValue1 = 0;
	int tmpMultiValue2 = 0;
	int carryValue1 = 0;
	int carryValue2 = 0;
	char *result = NULL;

	if (NULL == str1 || NULL == str2)
	{
		return NULL;
	}

	lenStr1 = strlen(str1);
	lenStr2 = strlen(str2);
	lenResult = lenStr1 + lenStr2;
	
	result = (char *)malloc((lenResult + 1) * sizeof(char));
	if (NULL == result)
	{
		DEBUG_LOG("Malloc space for result failed.\n");
		return NULL;
	}
	else
	{
		memset(result, '0', lenResult);
		result[lenResult] = '\0';
	}

	str1 = revertStr(str1, 0, lenStr1 - 1);
	str2 = revertStr(str2, 0, lenStr2 - 1);

	DEBUG_LOG("After revert, str1: %s, str2: %s, CHAR0: %d.\n", str1, str2, CHAR0);

	for (i = 0; i < lenStr1; i++)
	{
		carryValue1 = 0;
		carryValue2 = 0;

		for (j = 0; j < lenStr2; j++)
		{
			tmpMultiValue1 = (str1[i] - CHAR0) * (str2[j] - CHAR0) + carryValue1;
			carryValue1 = tmpMultiValue1 / 10;
			DEBUG_LOG("---------tmp1: %d, carry1: %d---------\n", tmpMultiValue1, carryValue1);
			tmpMultiValue1 = tmpMultiValue1 % 10;
			tmpMultiValue2 = (result[i + j] - CHAR0) + tmpMultiValue1 + carryValue2;
			carryValue2 = tmpMultiValue2 / 10;
			result[i + j] = tmpMultiValue2 % 10 + CHAR0;
			DEBUG_LOG("---------tmp2: %d, carry2: %d---------\n", tmpMultiValue2, carryValue2);
		}

		result[i + lenStr2] = result[i + lenStr2] + carryValue1 + carryValue2;
	}

	DEBUG_LOG("Befor revert, result: %s.\n", result);
	j = lenResult - 1;
	while ('0' == result[j] && 0 < j)
	{
		j--;
	}
	result[j + 1] = '\0';
	
	result = revertStr(result, 0, j);
	DEBUG_LOG("After revert, result: %s.\n", result);
	return result;
}

int main(int argc, char *argv[])
{	
	char *result = NULL;
	
	if (3 != argc)
	{
		DEBUG_LOG("paras num[%d] invalid.\n", argc);
		return -1;
	}

	DEBUG_LOG("argc is %d, argv[0]: %s, argv[1]: %s.\n", argc, argv[1], argv[2]);
	result = bigNumMulti(argv[1], argv[2]);
	if (result)
	{
		DEBUG_PRINT("%s * %s = %s\n", argv[1], argv[2], result);
	}

	freeBigNum(result);
	return 0;
}
