/*
    This is bd, a binary display tool.

    Copyright (C) 2012 Christopher Redmon.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void usage(void)
{
   printf("usage: bd [flags] [number]\n");
   printf("\n");
   printf(" flags:\n");
   printf("  -d Converts number from decimal format to visualized binary.\n");
   printf("  -x Converts number from hexadecimal format to visualized binary.\n");
}

unsigned int htoi(const char* string)
{
   unsigned int len = strlen(string);
   unsigned int i;
   unsigned int sum = 0;
   unsigned int pow16 = 1;

   for (i = 1; i < len; i++)
   {
      pow16 *= 16;
   }

   for (i = 0; i < len; i++)
   {
      switch(string[i])
      {
         case '0':
            sum += (0 * pow16);
            break;
         case '1':
            sum += (1 * pow16);
            break;
         case '2':
            sum += (2 * pow16);
            break;
         case '3':
            sum += (3 * pow16);
            break;
         case '4':
            sum += (4 * pow16);
            break;
         case '5':
            sum += (5 * pow16);
            break;
         case '6':
            sum += (6 * pow16);
            break;
         case '7':
            sum += (7 * pow16);
            break;
         case '8':
            sum += (8 * pow16);
            break;
         case '9':
            sum += (9 * pow16);
            break;
         case 'a':
         case 'A':
            sum += (10 * pow16);
            break;
         case 'b':
         case 'B':
            sum += (11 * pow16);
            break;
         case 'c':
         case 'C':
            sum += (12 * pow16);
            break;
         case 'd':
         case 'D':
            sum += (13 * pow16);
            break;
         case 'e':
         case 'E':
            sum += (14 * pow16);
            break;
         case 'f':
         case 'F':
            sum += (15 * pow16);
            break;
      }

      pow16 /= 16;
   }

   return sum;
}

unsigned int nibble_swap(unsigned int number)
{
   unsigned int new_number = 0;

   new_number |= ((number & 0xF0000000) >> (28 -  0));
   new_number |= ((number & 0x0F000000) >> (24 -  4));
   new_number |= ((number & 0x00F00000) >> (20 -  8));
   new_number |= ((number & 0x000F0000) >> (16 - 12));
   new_number |= ((number & 0x0000F000) << (16 - 12));
   new_number |= ((number & 0x00000F00) << (20 -  8));
   new_number |= ((number & 0x000000F0) << (24 -  4));
   new_number |= ((number & 0x0000000F) << (28 -  0));

   return new_number;
}

void print_number_as_visualized_binary(int number)
{
   unsigned int i;
   unsigned int nibble;
   unsigned int mask = 0xF0000000;
   unsigned int remainder;
   
   remainder = nibble_swap(number);

   for (i = 0; i < (sizeof(unsigned int)*2); i++)
   {
      nibble    = (remainder & mask) >> (28-i*4);
      remainder = (remainder & (~mask));
      mask      = mask >> 4;

      switch (nibble)
      {
         case 0:
            printf(" 0000 ");
            break;
         case 1:
            printf(" 0001 ");
            break;
         case 2:
            printf(" 0010 ");
            break;
         case 3:
            printf(" 0011 ");
            break;
         case 4:
            printf(" 0100 ");
            break;
         case 5:
            printf(" 0101 ");
            break;
         case 6:
            printf(" 0110 ");
            break;
         case 7:
            printf(" 0111 ");
            break;
         case 8:
            printf(" 1000 ");
            break;
         case 9:
            printf(" 1001 ");
            break;
         case 0xA:
            printf(" 1010 ");
            break;
         case 0xB:
            printf(" 1011 ");
            break;
         case 0xC:
            printf(" 1100 ");
            break;
         case 0xD:
            printf(" 1101 ");
            break;
         case 0xE:
            printf(" 1110 ");
            break;
         case 0xF:
            printf(" 1111 ");
            break;
         default:
            printf("oops.\n");
            break;
      }

      printf("(bits %2d -> %2d)\n",((i*4)+4)-1,i*4);


      if (!remainder)
      {
         break;
      }
   }

}

void print_number_as_binary(int number)
{
   unsigned int i;
   unsigned int nibble;
   unsigned int mask = 0x0000000F;
   unsigned int remainder;
   
   remainder = nibble_swap(number);

   for (i = 0; i < (sizeof(unsigned int)*2); i++)
   {
      nibble    = (remainder & mask) >> (i*4);
      remainder = (remainder & (~mask));
      mask      = mask << 4;

      switch (nibble)
      {
         case 0:
            printf("0000");
            break;
         case 1:
            printf("0001");
            break;
         case 2:
            printf("0010");
            break;
         case 3:
            printf("0011");
            break;
         case 4:
            printf("0100");
            break;
         case 5:
            printf("0101");
            break;
         case 6:
            printf("0110");
            break;
         case 7:
            printf("0111");
            break;
         case 8:
            printf("1000");
            break;
         case 9:
            printf("1001");
            break;
         case 0xA:
            printf("1010");
            break;
         case 0xB:
            printf("1011");
            break;
         case 0xC:
            printf("1100");
            break;
         case 0xD:
            printf("1101");
            break;
         case 0xE:
            printf("1110");
            break;
         case 0xF:
            printf("1111");
            break;
         default:
            printf("oops.\n");
            break;
      }
   }
}

int main(int argc, char** argv)
{
   int num;
   int opt;

   while((opt = getopt(argc,argv,"-d:-x:")) != -1)
   {
      switch (opt)
      {
         case 'd':
            num = atoi(optarg);
            break;
         case 'x':
            num = htoi(optarg);
            break;
         default:
            usage();
            return 1;
      }
      printf("dec: 0d%d\n",num);
      printf("hex: 0x%0X\n",num);
      printf("bin: 0b");
      print_number_as_binary(num);
      printf("\n");

      print_number_as_visualized_binary(num);
      return 0;
   }
   usage();
   return 1;
}
