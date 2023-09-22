
#include "main.h"

/**
 * get_precision - print precision and calculate
 * @format: Format the string and print arguments
 * @k: List arguments to print.
 * @list: list arguments
 *
 * Return: the precision.
 */
int get_precision(const char *format, int *k, va_list list)
{
	int curr_k = *k + 1;
	int precision = -1;

	if (format[curr_k] != '.')
		return (precision);

	precision = 0;

	for (curr_k += 1; format[curr_k] != '\0'; curr_k++)
	{
		if (is_digit(format[curr_k]))
		{
			precision *= 10;
			precision += format[curr_k] - '0';
		}
		else if (format[curr_k] == '*')
		{
			curr_k++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*k = curr_k - 1;

	return (precision);
}
