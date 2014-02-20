// editline.h             -*-c++-*-
//
//   Copyright (C) 2000, 2007 Daniel Burrows
//
//   This program is free software; you can redistribute it and/or
//   modify it under the terms of the GNU General Public License as
//   published by the Free Software Foundation; either version 2 of
//   the License, or (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; see the file COPYING.  If not, write to
//   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
//   Boston, MA 02111-1307, USA.

//  A simple line-editor widget.

#ifndef EDITLINE_H
#define EDITLINE_H

#include "widget.h"

#include <vector>

namespace cwidget
{
  namespace config
  {
    class keybindings;
  }

  namespace widgets
  {
    class editline : public widget
    {
    public:
      typedef std::vector<std::wstring> history_list;
    private:

      std::wstring prompt;
      std::wstring text;

      std::wstring pre_history_text;
      // Used as a "virtual" history entry.

      // curloc is the offset of the cursor within the input string;
      // startloc is the offset of the first visible character within the
      // combined input string and prompt.
      //
      // If allow_wrap is true, startloc is the first character of the
      // first visible line (i.e., it represents vertical scrolling).
      // Otherwise, it is the first character within the sole line that is
      // visible (i.e., it represents horizontal scrolling).
      std::wstring::size_type curloc, startloc;

      int desired_size;

      // The history of the edit-line.  (if NULL, there is no history)
      history_list *history;
      // The current location in the history
      history_list::size_type history_loc;
      // True if we're flipping through the history.  (to avoid signedness
      // problems)
      bool using_history;

      bool allow_wrap;

      /** \brief If \b true and the first user input is a character
       *  insertion, the edit buffer will be cleared.
       *
       *  This is initially \b false.  It may be set to \b true by
       *  set_clear_on_first_edit, and is set back to \b false after the
       *  first keypress or mouse click.
       */
      bool clear_on_first_edit;

      void normalize_cursor();

      /** \return the zero-based index of the line containing the nth character
       *  of the visual representation.
       */
      int get_line_of_character(size_t n, int width);

      /** \return the zero-based index of the first character of the nth
       *  line of the visual representation.
       */
      int get_character_of_line(size_t n, int width);

      /** \return the nth char of the current textual representation of
       *  this edit widget.
       *
       *  The textual representation consists of the prompt concatenated
       *  with the text being edited.
       */
      wchar_t get_char(size_t n);

      /** \return the number of characters in the visual representation. */
      size_t get_num_chars() const { return prompt.size() + text.size(); }
    protected:
      bool handle_key(const config::key &k);

      editline(const std::wstring &_prompt,
	       const std::wstring &_text=L"",
	       history_list *history=NULL);

      /** Transcodes its input strings from the system charset. */
      editline(const std::string &_prompt,
	       const std::string &_text="",
	       history_list *history=NULL);

      editline(int maxlength, const std::wstring &_prompt,
	       const std::wstring &_text, history_list *history);

      /** Transcodes its input strings from the system charset. */
      editline(int maxlength, const std::string &_prompt,
	       const std::string &_text, history_list *history);

    public:
      static util::ref_ptr<editline>
      create(const std::wstring &prompt, const std::wstring &text = L"",
	     history_list *history = NULL)
      {
	util::ref_ptr<editline> rval(new editline(prompt, text, history));
	rval->decref();
	return rval;
      }

      static util::ref_ptr<editline>
      create(const std::string &prompt, const std::string &text = "",
	     history_list *history = NULL)
      {
	util::ref_ptr<editline> rval(new editline(prompt, text, history));
	rval->decref();
	return rval;
      }

      static util::ref_ptr<editline>
      create(int maxlength, const std::wstring &prompt,
	     const std::wstring &text = L"", history_list *history = NULL)
      {
	util::ref_ptr<editline> rval(new editline(maxlength, prompt, text, history));
	rval->decref();
	return rval;
      }

      static util::ref_ptr<editline>
      create(int maxlength, const std::string &prompt,
	     const std::string &text = "", history_list *history = NULL)
      {
	util::ref_ptr<editline> rval(new editline(maxlength, prompt, text, history));
	rval->decref();
	return rval;
      }

      /** \return \b true if the contents of this edit-line will be erased
       *  if the first character pressed is an edit (i.e., not an arrow
       *  key).
       */
      bool get_clear_on_first_edit() const { return clear_on_first_edit; }
      /** Change whether the contents of this edit-line widget will be
       *  erased if the first character pressed is an edit.
       *
       *  This is initially \b false.
       */
      void set_clear_on_first_edit(bool value)
      {
	clear_on_first_edit = value;
      }

      void set_allow_wrap(bool allow) { allow_wrap = allow; }
      bool get_allow_wrap() const { return allow_wrap; }

      bool focus_me();
      void paint(const style &st);
      void dispatch_mouse(short id, int x, int y, int z, mmask_t bstate);

      sigc::signal1<void, std::wstring> entered;
      // Called when the user presses Enter to confirm the text
      sigc::signal1<void, std::wstring> text_changed;
      // Called when the text is altered.

      std::wstring get_text() {return text;}
      void set_text(std::wstring _text);

      /** Decodes the given multibyte string, and sets the current text
       *  of this edit-line to it.
       */
      void set_text(std::string _text);

      bool get_cursorvisible();
      point get_cursorloc();

      int width_request();
      int height_request(int height);

      static void add_to_history(std::wstring s,
				 history_list *history);
      // Appends the string to the end of the history list (convenience routine)

      void add_to_history(std::wstring s);
      void reset_history();

      static config::keybindings *bindings;
      static void init_bindings();
    };

    typedef util::ref_ptr<editline> editline_ref;
  }
}

#endif
