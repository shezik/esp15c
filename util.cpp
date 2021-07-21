/*
 $Id$
 Copyright 1995, 2003, 2004, 2005 Eric L. Smith <eric@brouhaha.com>
 
 Nonpareil is free software; you can redistribute it and/or modify it
 under the terms of the GNU General Public License version 2 as
 published by the Free Software Foundation.  Note that I am not
 granting permission to redistribute or modify Nonpareil under the
 terms of any later version of the General Public License.
 
 Nonpareil is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program (in the file "COPYING"); if not, write to the
 Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 MA 02111, USA.
 */

//
// changes for mac os x by Maciej Bartosiak
// changes for esp32 by shezik
//


#include "util.h"

void *alloc (size_t size)
{
	//Serial.printf("Going into %s!\n", __func__); //debug
	void *p;
	
	p = calloc (1, size);
	if (! p)
		fatal(2, "Memory allocation failed\n");
	//Serial.printf("Leaving %s!\n", __func__); //debug
	return (p);
}

void trim_trailing_whitespace (char *s)
{
	int i;
	char c;
	
	i = strlen (s);
	while (--i >= 0)
    {
		c = s [i];
		if ((c == '\n') || (c == '\r') || (c == ' ') || (c == '\t'))
			s [i] = '\0';
		else
			break;
    }
}

void exit (int ret)
{
	Serial.printf("Program returned %d\n\n", ret);
	while(1);  // dead loop
}
