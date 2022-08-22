#include "printf.h"
#include "uart.h"

#define MAX_PRINT_SIZE 256

void printf(char *string, ...)
{

	va_list ap;
	va_start(ap, string);
	char buffer[MAX_PRINT_SIZE];
	int buffer_index = 0;

	char temp_buffer[MAX_PRINT_SIZE];

	while (1)
	{
		if (*string == 0)
			break;
		if (*string == '%')
		{
			string++;

			if (*string == 'd')
			{
				string++;
				int x = va_arg(ap, int);
				int temp_index = MAX_PRINT_SIZE - 1;
				//Looping through every single characters. 
				do
				{
					//Get remainder value of x value and convert to characters and then saves it into temp_buffer array from the very lastindex of array.
					temp_buffer[temp_index] = (x % 10) + '0';
					temp_index--;
					x /= 10;
				} while (x != 0);
				//Lopping through temp_buffer array. 
				for (int i = temp_index + 1; i < MAX_PRINT_SIZE; i++)
				{
					buffer[buffer_index] = temp_buffer[i];
					buffer_index++;
				}
			}
			else if (*string == 'c')
			{
				string++;
				char x = va_arg(ap, int);
				//Store character into buffer array. 
				buffer[buffer_index] = x;
				buffer_index++;
			}else if (*string == 's')
			{
				string++;
				char *str = va_arg(ap, char*);
				//Looping through String to the end.
				while (*str != '\0')
				{
					//store each character of string into buffer array. 
					buffer[buffer_index] = *str;
					buffer_index++;
					*str++;
				}
			}else if(*string == 'x')
			{
				string++;
				int x = va_arg(ap, int);
				int temp_index = MAX_PRINT_SIZE - 1;
				//Looping through hexadecimal 
				do
				{
					//Since 0-9 in decimal and hexadecimal are the same. However, 10-15 in decimal convert to hexadecimal as A,B,C,D,E,F corresponding order. 
					//Check if remainder of character number after devided for 16 greater or equal to 10
					if ((x % 16) >= 10)
					{
						//Store converted remainder character into temp_buffer.
						temp_buffer[temp_index] = (x % 16) + '7';
					}else{
						//Store converted remainder character into temp_buffer when remainder is smaller than 10.
						temp_buffer[temp_index] = (x % 16) + '0';
					}
					//Continue loopping. 
					temp_index--;
					x /= 16;
				} while (x != 0);
				//Store all character in temp_buffer array into buffer array.
				for (int i = temp_index + 1; i < MAX_PRINT_SIZE; i++)
				{
					buffer[buffer_index] = temp_buffer[i];
					buffer_index++;
				}
			}else if(*string == 'o'){
				string++;
				int x = va_arg(ap, int);
				int temp_index = MAX_PRINT_SIZE - 1;
				//Looping through value of x.
				do
				{
					//storing converted remainder of x devide to 8 to character.
					temp_buffer[temp_index] = (x % 8) + '0';
					x /= 8;
					temp_index--;
				} while (x != 0);
				//Store all character in temp_buffer array into buffer array.
				for (int i = temp_index + 1; i < MAX_PRINT_SIZE; i++)
				{
					buffer[buffer_index] = temp_buffer[i];
					buffer_index++;
				}
			}else if (*string == '%')
			{
				buffer[buffer_index] = '%';
				buffer_index++;
			}
			
		}
		else
		{
			buffer[buffer_index] = *string;
			buffer_index++;
			string++;
		}

		if (buffer_index == MAX_PRINT_SIZE - 1)
			break;
	}

	va_end(ap);

	// Print out formated string
	uart_puts(buffer);
}
