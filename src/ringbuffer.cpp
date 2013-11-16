/****************************************************************************

    ringbuffer.c - a ringbuffer designed to be used in shared memory

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

#include <cstring>
#include <iostream>

#include "ringbuffer.hpp"


RingBuffer::RingBuffer(int size)
{
    read_pos = 0;
    write_pos = 0;
    atom_size = sizeof(float);
    max_pos = size;

    data = new float[max_pos];
}


int RingBuffer::ringbuf_read(float* dest, int size)
{
    int n = 0;
    static int col = 0;

    if (size == 0)
        return 0;

    //std::cout << "Request to read " << size << " atoms" << std::endl;

    if (read_pos > write_pos)
    {
        n = max_pos - read_pos;
        n = (n > size ? size : n);
        if (dest)
            memcpy(dest, &data[read_pos], n * atom_size);
        read_pos = (read_pos + n) % max_pos;
    }
    if (read_pos < write_pos && n < size)
    {
        int m = write_pos - read_pos;
        m = (m > size - n ? size - n : m);
        if (dest)
            memcpy(&dest[n], &data[read_pos], m * atom_size);
        read_pos = (read_pos + m) % max_pos;
        n += m;
    }

    //if(dest)
      //  for(int i = 0 ; i<size; i++ )
        //    std::cout << dest[i] << std::endl;

    /*  fprintf(stderr, "RB %d atoms read from the ringbuffer\n"
        "\tread_pos = %d write_pos = %d max_pos = %d\n",
        n, read_pos, write_pos, max_pos); */

    /*if (n < size)
      fprintf(stderr, "RB: read collision %d\n", col++);*/

    return n;
}


int RingBuffer::ringbuf_write(float* src, int size)
{
    int n = 0;
    static int col = 0;

    if (size == 0)
        return 0;

    if (write_pos >= read_pos)
    {
        //std::cout << "ringbuf_write write_pos >= read_pos" << std::endl;
        n = max_pos - write_pos;
        if (read_pos == 0)
            --n;
        n = (n > size ? size : n);
        //std::cout << "RB " << n << " atoms written to the ringbuffer\n\tread_pos = " << read_pos << " write_pos = " << write_pos << " max_pos = " << max_pos << std::endl;
        //memcpy(data + write_pos * atom_size, src, n * atom_size);
        memcpy(&data[write_pos], src, n * atom_size);
        write_pos = (write_pos + n) % max_pos;
    }
    if (write_pos + 1 < read_pos && n < size)
    {
        //std::cout << "ringbuf_write write_pos + 1 < read_pos && n < size" << std::endl;
        int m = read_pos - write_pos - 1;
        m = (m > size - n ? size - n : m);
        //memcpy(data + write_pos * atom_size, (float*)src + n * atom_size, m * atom_size);
        memcpy(&data[write_pos], &src[n], m * atom_size);
        write_pos = (write_pos + m) % max_pos;
        n += m;
    }

    return n;
}


int RingBuffer::ringbuf_write_zeros(int size)
{
    std::cout << "ringbuf_write_zeros " << size << std::endl;
    int n = 0;
    static int col = 0;

    if (size == 0)
        return 0;

    if (write_pos >= read_pos)
    {
        n = max_pos - write_pos;
        if (read_pos == 0)
            --n;
        n = (n > size ? size : n);
        //memset(data + write_pos * atom_size, 0, n * atom_size);
        memset(&data[write_pos], 0, n * atom_size);
        write_pos = (write_pos + n) % max_pos;
    }
    if (write_pos + 1 < read_pos && n < size)
    {
        int m = read_pos - write_pos - 1;
        m = (m > size - n ? size - n : m);
        //memset(data + write_pos * atom_size, 0, m * atom_size);
        memset(&data[write_pos], 0, m * atom_size);
        write_pos = (write_pos + m) % max_pos;
        n += m;
    }

    /*fprintf(stderr, "RB %d atoms written to the ringbuffer\n"
      "\tread_pos = %d write_pos = %d max_pos = %d\n",
      n, read_pos, write_pos, max_pos);*/

    /* if (n < size)
       fprintf(stderr, "RB: write collision %d\n", col++); */

    return n;
}


int RingBuffer::ringbuf_available()
{
    if (read_pos <= write_pos)
        return write_pos - read_pos;
    else
        return max_pos - read_pos + write_pos;
}


int RingBuffer::ringbuf_available_contiguous()
{
    //std::cout << "ringbuf_available_contiguous " << read_pos << " " << write_pos << " " << max_pos << std::endl;
    if (read_pos <= write_pos)
        return write_pos - read_pos;
    else
        return max_pos - read_pos;
}


//int RingBuffer::ringbuf_get_size(int atom_size, int size)
//{
//  return sizeof(ringbuf_t) - 1 + size * atom_size;
//}


int RingBuffer::ringbuf_get_read_pos()
{
    return read_pos;
}


int RingBuffer::ringbuf_get_write_pos()
{
    return write_pos;
}


float* RingBuffer::ringbuf_get_read_ptr()
{
    //return data + read_pos * atom_size;
    return &data[read_pos];
}
