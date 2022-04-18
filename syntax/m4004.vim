if exists("b:current_syntax")
  finish
endif

syn keyword m4004Reg ra rb
syn keyword m4004Todo contained TODO
syn match m4004Comment ";.*$" contains=m4004Todo
syn match m4004Directive "^\s*[.][a-zA-Z]\+"
syn match m4004Number "[0-9a-fA-F]h\+"
syn match m4004Number "\<[0-9]\+D\=\>"
syn match m4004Op "^\s*[a-zA-Z0-9_]\+\s"
syn match m4004Op "^\s*[a-zA-Z0-9_]\+$"

" syn region m4004Op start='^' end='$'
syn region m4004Label start="^\s*[a-zA-Z0-9_.]" end=":" oneline contains=m4004LabelName,m4004MacroArg,m4004Addr

syn match m4004LabelName "^[a-zA-Z0-9_\.]\+:\=" contained

let b:current_syntax = "m4004"
hi def link m4004Todo Todo
hi def link m4004Comment Comment
hi def link m4004LabelName Label
hi def link m4004Directive Macro
hi def link m4004Op Function
hi def link m4004Reg Identifier
hi def link m4004Number Number
