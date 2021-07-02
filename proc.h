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
//


#define MAX_RAM 1024  // $$$ ugly hack, needs to go!
#define MAX_PF   256  // $$$ ugly hack, needs to go!


// common events:
typedef enum
{
	event_reset,
	event_clear_memory,
	event_power_down,
	event_power_up,
	event_sleep,
	event_wake,
	event_cycle,       // occurs during every simulation cycle
	event_save_starting,
	event_save_completed,
	event_restore_starting,
	event_restore_completed,
	
	first_arch_event = 0x100,  // CPU architecture specific events
	
	first_chip_event = 0x200   // chip specific events
} event_t;


typedef uint32_t addr_t;

typedef uint16_t rom_word_t;


