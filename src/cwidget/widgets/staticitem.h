// staticitem.h    -*-c++-*-
//
//  Copyright 2000, 2001, 2005 Daniel Burrows
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; see the file COPYING.  If not, write to
//  the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
//  Boston, MA 02111-1307, USA.
//
//

#ifndef STATICITEM_H
#define STATICITEM_H

#include "treeitem.h"

namespace cwidget
{
  namespace widgets
  {
    class staticitem : public treeitem
    {
      std::wstring name,value;
    public:
      staticitem(std::wstring _name, std::wstring _value)
	: treeitem(false),name(_name),value(_value) {}
      void paint(tree *win, int y, bool hierarchical, const style &st);
      const wchar_t *tag() {return value.c_str();}
      const wchar_t *label() {return value.c_str();}
    };
  }
}

#endif
