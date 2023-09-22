#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - the code will print a character
 * @types: code will list all arguments
 * @buffer: the buffer array handles print
 * @flags:  this will calculate active flags
 * @width: this is the width
 * @precision: this is the code precision specifier
 * @size: the code size specifier
 * Return: printed number of characters
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
  * print_char - the code will print a character
 * @types: code will list all arguments
 * @buffer: the buffer array handles print
 * @flags:  this will calculate active flags
 * @width: this is the width
 * @precision: this is the code precision specifier
 * @size: the code size specifier
 * Return: printed number of characters
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, k;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (k = width - length; k > 0; k--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (k = width - length; k > 0; k--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Print the percentage symbol
 * @types: code will list all arguments
 * @buffer: the buffer array handles print
 * @flags:  this will calculate active flags
 * @width: this is the width
 * @precision: this is the code precision specifier
 * @size: the code size specifier
 * Return: printed number of characters
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print the integer
 * @types: code will list all arguments
 * @buffer: the buffer array handles print
 * @flags:  this will calculate active flags
 * @width: this is the width
 * @precision: this is the code precision specifier
 * @size: the code size specifier
 * Return: printed number of characters
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	int is_negative = 0;
	long int m = va_arg(types, long int);
	unsigned long int num;

	m = convert_size_number(m, size);

	if (m == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (m < 0)
	{
		num = (unsigned long int)((-1) * m);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[k--] = (num % 10) + '0';
		num /= 10;
	}

	k++;

	return (write_number(is_negative, k, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Print unsigned number
 * @types: code will list all arguments
 * @buffer: the buffer array handles print
 * @flags:  this will calculate active flags
 * @width: this is the width
 * @precision: this is the code precision specifier
 * @size: the code size specifier
 * Return: printed number of characters
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int m, w, k, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	m = va_arg(types, unsigned int);
	w = 2147483648; /* (2 ^ 31) */
	a[0] = m / w;
	for (k = 1; k < 32; k++)
	{
		w /= 2;
		a[k] = (m / w) % 2;
	}
	for (k = 0, sum = 0, count = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char z = '0' + a[k];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

