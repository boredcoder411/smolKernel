#include "./io.h"
#include "./string.h"

#define WHITE_TXT 0x07

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);
void disable_cursor();
void k_keyboard();
int k_keyboard_handler(int scancode);
void process_command(char *command);

void k_main()
{
	k_clear_screen();
	k_printf("Hello, world! Welcome to my kernel.", 0);
	k_keyboard();
};

void k_clear_screen()
{
	char *vidmem = (char *)0xb8000;
	unsigned int i = 0;
	while (i < (80 * 25 * 2))
	{
		vidmem[i] = ' ';
		i++;
		vidmem[i] = WHITE_TXT;
		i++;
	};
};

unsigned int k_printf(char *message, unsigned int line)
{
	char *vidmem = (char *)0xb8000;
	unsigned int i = 0;

	i = (line * 80 * 2);

	while (*message != 0)
	{
		if (*message == '\n')
		{
			line++;
			i = (line * 80 * 2);
			*message++;
		}
		else
		{
			vidmem[i] = *message;
			*message++;
			i++;
			vidmem[i] = WHITE_TXT;
			i++;
		};
	};

	return (1);
}

void k_keyboard()
{
	char command[80];
	int index = 0;
	int previous_scancode = -1;
	int entered_command = 0;

	while (1)
	{
		int scancode = inb(0x60);

		if (scancode != previous_scancode)
		{
			previous_scancode = scancode;

			if (scancode != -1)
			{
				if (scancode == 0x1C)
				{
					if (entered_command)
					{
						command[index] = '\0';
						k_printf("\n", 2);
						process_command(command);
						index = 0;
						entered_command = 0;
						strcpy(command, "");
					}
				}
				else if (scancode == 0x0E)
				{
					if (index > 0)
					{
						index--;
						command[index] = ' ';
						k_printf(command, 2);
					}
				}
				else
				{
					char character = k_keyboard_handler(scancode);

					if (character != '\0')
					{
						command[index] = character;
						index++;
						entered_command = 1;
						k_printf(command, 2);
					}
				}
			}
		}
	}
}

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

int k_keyboard_handler(int scancode)
{
	switch (scancode)
	{
	case 0x00:
		return ' ';
	case 0x01:
		return '\0';
	case 0x02:
		return '1';
	case 0x03:
		return '2';
	case 0x04:
		return '3';
	case 0x05:
		return '4';
	case 0x06:
		return '5';
	case 0x07:
		return '6';
	case 0x08:
		return '7';
	case 0x09:
		return '8';
	case 0x0A:
		return '9';
	case 0x0B:
		return '0';
	case 0x10:
		return 'q';
	case 0x11:
		return 'w';
	case 0x12:
		return 'e';
	case 0x13:
		return 'r';
	case 0x14:
		return 't';
	case 0x15:
		return 'y';
	case 0x16:
		return 'u';
	case 0x17:
		return 'i';
	case 0x18:
		return 'o';
	case 0x19:
		return 'p';
	case 0x1A:
		return '¨';
	case 0x1B:
		return '\'';
	case 0x1E:
		return 'a';
	case 0x1F:
		return 's';
	case 0x20:
		return 'd';
	case 0x21:
		return 'f';
	case 0x22:
		return 'g';
	case 0x23:
		return 'h';
	case 0x24:
		return 'j';
	case 0x25:
		return 'k';
	case 0x26:
		return 'l';
	case 0x27:
		return 'ç';
	case 0x28:
		return '`';
	case 0x2C:
		return 'z';
	case 0x2D:
		return 'x';
	case 0x2E:
		return 'c';
	case 0x2F:
		return 'v';
	case 0x30:
		return 'b';
	case 0x31:
		return 'n';
	case 0x32:
		return 'm';
	case 0x33:
		return ',';
	case 0x34:
		return '.';
	case 0x35:
		return '-';
	case 0x39:
		return ' ';
	default:
		return '\0';
	}
}

void process_command(char *command)
{
	if (strcmp(command, "clear") == 0)
	{
		k_clear_screen();
	}
	else if (strcmp(command, "hello") == 0)
	{
		k_printf("Hello! How are you?", 2);
	}
	else if (strcmp(command, "help") == 0)
	{
		k_printf("Available commands: clear, hello, help", 2);
	}
	else
	{
		k_printf("Unknown command. Type 'help' for a list of commands.", 2);
	}
}
