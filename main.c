#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_BUFF 50

int get_size_token(const char* token)
{
	int i;

	for (i = 0; token[i] && (token[i] != '\n'); ++i);

	return ++i;
}

void cpy(char* str1, const char* str2, int size)
{
	strcpy(str1, str2);

	str1[size - 1] = '\0';
}

void free_arglist(char** arglist, int n)
{
	int i;
	for (i = 0; i < n; ++i) {
		if (arglist[i] != NULL) {
			free(arglist[i]);
			arglist[i] = NULL;
		}
	}
}

int main()
{
	char input_symbol[SIZE_BUFF + 1];
	const char* delim = " ";
	char* savedptr;
	char* token;
	char** arg_list;

	int count_arg = 7; // 0 - command, 6 - NULL
	int size_arg;

	int i = 0;

	pid_t pid;
	int status;

	arg_list = malloc(sizeof(char*) * count_arg);

	while (1) {
		printf(">>>");
	
		fgets(input_symbol, SIZE_BUFF, stdin);

		token = strtok_r(input_symbol, delim, &savedptr);
		if (token == NULL) {
			break;
		}

		size_arg = get_size_token(token);
		arg_list[0] = malloc(sizeof(char) * size_arg);
		cpy(arg_list[0], token, size_arg);

		if (!strcmp(arg_list[0], "q"))
			break;

		for (i = 1; (token = strtok_r(NULL, delim, &savedptr))
						&& (i < count_arg - 1); ++i) {
			size_arg = get_size_token(token);
			arg_list[i] = malloc(sizeof(char) * size_arg);
			cpy(arg_list[i], token, size_arg);
		}

		arg_list[i] = NULL;

		#if 1
		pid = fork();
		if (pid == 0) {
			exit(0);
		} else {
			wait(&status);
		}
		#endif

		arg_list[i] = NULL;

		memset(input_symbol, 0, SIZE_BUFF + 1);
		free_arglist(arg_list, count_arg);
	}

	free_arglist(arg_list, count_arg);
	free(arg_list);

	return 0;
}
