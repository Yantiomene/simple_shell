#include "shell.h"

/**
 * _memcpy - copies value of a pointer to a new pointer
 * @new_ptr: new pointer
 * @ptr: old pointer
 * @len: len of pointer to be copied
 *
 */
void _memcpy(void *new_ptr, const void *ptr, size_t len)
{
	char *c_ptr = (char *)ptr;
	char *c_new_ptr = (char *)new_ptr;
	size_t i;

	for (i = 0; i < len; i++)
		c_new_ptr[i] = c_ptr[i];
}

/**
 * _realloc - reallocate memory
 * @ptr: pointer to the variable needed more space in memory
 * @len: initial len of the array
 * @new_len: new len of the array
 *
 * Return: a pointer to the new space reallocated
 */
void *_realloc(void *ptr, size_t len, size_t new_len)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(new_len));
	if (new_len == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_len == len)
		return (ptr);
	new_ptr = malloc(new_len);
	if (new_ptr == NULL)
		return (NULL);
	if (new_len < len)
		_memcpy(new_ptr, ptr, new_len);
	else
		_memcpy(new_ptr, ptr, len);
	free(ptr);
	return (new_ptr);
}
