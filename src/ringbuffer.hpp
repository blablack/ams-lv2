/****************************************************************************

    ringbuffer.h - a ringbuffer designed to be used in shared memory

    Copyright (C) 2005  Lars Luthman <larsl@users.sourceforge.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 01222-1307  USA

****************************************************************************/

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

class RingBuffer
{
private:
    int read_pos, write_pos, max_pos, atom_size;
    float* data;

public:
    RingBuffer(int size);

    int ringbuf_read(float* dest, int size);
    int ringbuf_write(float* src, int size);
    int ringbuf_write_zeros(int size);
    int ringbuf_available();
    int ringbuf_available_contiguous();
    //int ringbuf_get_size(int atom_size, int size);
    int ringbuf_get_read_pos();
    int ringbuf_get_write_pos();
    float* ringbuf_get_read_ptr();
};
#endif


